
#pragma once

#include "JuceHeader.h"
#include "SynthParams.h"

class Sound : public SynthesiserSound {
public:
    bool appliesToNote(int /*midiNoteNumber*/) override { return true; }
    bool appliesToChannel(int /*midiChannel*/) override { return true; }
};

struct Waveforms {
    static float sinus(float phs)  { return std::sin(phs); }
    static float square(float phs) { return std::copysign(1.f, float_Pi - phs);  }
    static float saw(float phs)    { return phs / (float_Pi*2.f) - .5f; }
};


template<float(*_waveform)(float)>
struct Oscillator {
    float phase;
    float phaseDelta;

    Oscillator() : phase(0.f), phaseDelta(0.f) {}

    void reset() {
        phase = 0.f;
        phaseDelta = 0.f;
    }

    bool isActive() const {
        return phaseDelta > 0.f;
    }

    float next() {
        const float result = _waveform(phase);
        phase = std::fmod(phase + phaseDelta, float_Pi * 2.0f);
        return result;
    }

    float next(float pitchMod) {
        const float result = _waveform(phase);
        phase = std::fmod(phase + phaseDelta*pitchMod, float_Pi * 2.0f);
        return result;
    }
};

class Voice : public SynthesiserVoice {
public:
    Voice(SynthParams &p, int blockSize)
    : params(p)
    , level (0.f)
    , tailOff (0.f)
    , pitchModBuffer(1,blockSize)
    {}


    bool canPlaySound (SynthesiserSound* sound) override
    {
        ignoreUnused(sound);
        return true;
    }

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int currentPitchWheelPosition) override
    {
        level = velocity * 0.15f;
        tailOff = 0.f;

        currentPitchValue = currentPitchWheelPosition;

        const float sRate = static_cast<float>(getSampleRate());
        float freqHz = static_cast<float>(MidiMessage::getMidiNoteInHertz (midiNoteNumber, params.freq.get()));

        // change the phases of both lfo waveforms, in case the user switches them during a note
        lfo1sine.phase = 0.f;
        lfo1sine.phaseDelta = params.lfo1freq.get() / sRate * 2.f * float_Pi;
        lfo1square.phase = 0.f;
        lfo1square.phaseDelta = params.lfo1freq.get() / sRate * 2.f * float_Pi;

        osc1.phase = 0.f;
        osc1.phaseDelta = freqHz * Param::fromCent(params.osc1fine.get()) / sRate * 2.f * float_Pi;

        // get number of samples for decay and attack
        attackSamples = static_cast<int>(getSampleRate() * params.envAttack.get());
        decaySamples = static_cast<int>(getSampleRate() * params.envDecay.get());
        attackDecayCounter = 0;
    }

    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        if (allowTailOff)
        {
            // start a tail-off by setting this flag. The render callback will pick up on
            // this and do a fade out, calling clearCurrentNote() when it's finished.

            if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
            {                   // stopNote method could be called more than once.
                tailOff = 1.0;

                // get number of samples for release
                releaseSamples = static_cast<int>(getSampleRate() * params.envRelease.get());
                releaseCounter = 0;
            }
        }
        else
        {
            // we're being told to stop playing immediately, so reset everything..
            clearCurrentNote();
            lfo1sine.reset();
            lfo1square.reset();
            osc1.reset();
        }
    }

    void pitchWheelMoved (int newValue) override
    {
        currentPitchValue = newValue;
    }

    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override
    {
        // not interested in controllers in this case.
    }

    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        renderModulation(numSamples);
        const float *pitchMod = pitchModBuffer.getReadPointer(0);        

        const float currentAmp = params.vol.get();
        const float currentPan = params.panDir.get();

        sustainLevel = Param::fromDb(params.envSustain.get());

        // Pan Influence
        const float currentAmpRight = currentAmp + (currentAmp / 100.f * currentPan);
        const float currentAmpLeft = currentAmp - (currentAmp / 100.f * currentPan);

        if (lfo1square.isActive() || lfo1sine.isActive())
        {
            if (tailOff > 0.f)
            {
                for (int s = 0; s < numSamples; ++s)
                {
                    setEnvCoeff();

                    //const float currentSample = (osc1.next(pitchMod[s])) * level * tailOff * currentAmp;
                    const float currentSample = (osc1.next(pitchMod[s])) * level * tailOff * envCoeff;

                    //check if the output is a stereo output
                    if (outputBuffer.getNumChannels() == 2) {
                        outputBuffer.addSample(0, startSample + s, currentSample*currentAmpLeft);
                        outputBuffer.addSample(1, startSample + s, currentSample*currentAmpRight);
                    }
                    else {
                        for (int c = 0; c < outputBuffer.getNumChannels(); ++c)
                            outputBuffer.addSample(c, startSample + s, currentSample * currentAmp);
                    }

                    //tailOff *= 0.99999f;
                    //if (tailOff <= 0.005f)
                    if(releaseSamples <= releaseCounter)
                    {
                        clearCurrentNote();
                        lfo1sine.reset();
                        lfo1square.reset();
                        break;
                    }
                    releaseCounter++;
                }
            }
            else
            {
                for (int s = 0; s < numSamples; ++s)
                {               
                    setEnvCoeff();

                    //const float currentSample = (osc1.next(pitchMod[s])) * level * currentAmp;
                    const float currentSample = (osc1.next(pitchMod[s])) * level * envCoeff;

                    //check if the output is a stereo output
                    if (outputBuffer.getNumChannels() == 2) {
                        outputBuffer.addSample(0, startSample + s, currentSample*currentAmpLeft);
                        outputBuffer.addSample(1, startSample + s, currentSample*currentAmpRight);
                    }
                    else {
                        for (int c = 0; c < outputBuffer.getNumChannels(); ++c)
                            outputBuffer.addSample(c, startSample + s, currentSample * currentAmp);
                    }
                    attackDecayCounter++;
                }
            }
        }
    }

protected:
    /**
    * set envCoeff logarithmically between 0.0f and 1.0f
    */
    void setEnvCoeff() 
    {

        // attack phase goes from 0dB to peak volume
        if (attackDecayCounter <= attackSamples)
        {
            // here envCoeff goes from 0.0f to 1.0f
            envCoeff = 1.0f - interpolateLog(attackDecayCounter, attackSamples);
        }
        else
        {
            // decay phase goes from peak volume to sustain level
            if (attackDecayCounter <= attackSamples + decaySamples)
            {
                // here envCoeff goes from 1.0f to sustain level
                envCoeff = interpolateLog(attackDecayCounter - attackSamples, decaySamples) * (1.0f - sustainLevel) + sustainLevel;
            }

            // if attack and decay phase is over then sustain level
            else
            {
                envCoeff = sustainLevel;
            }
        }

        // release phase
        if (tailOff > 0.f)
        {
            // here envCoeff goes from 1.0f to 0.0f
            tailOff = interpolateLog(releaseCounter, releaseSamples);
        }
    }

    /**
    * help function that interpolates logarithmically from 1.0 to 0.0f in t samples
    */
    float interpolateLog(int curr, int t)
    {
        // coeff of growth, maybe a different one better?
        float k = std::exp(1.0f);

        return std::exp(std::log(1.0f - static_cast<float>(curr) / static_cast<float>(t)) * k);
    }

    void renderModulation(int numSamples) {

        // add pitch wheel values
        float currentPitchInCents = (params.osc1PitchRange.get() * 100) * ((currentPitchValue - 8192.0f) / 8192.0f);

        const float modAmount = params.osc1lfo1depth.get();
        if (params.lfo1wave.get() == 0) // if lfo1wave is 0, lfo is set to sine wave
        {
            for (int s = 0; s < numSamples;++s)
            {
                pitchModBuffer.setSample(0, s, Param::fromSemi(lfo1sine.next()*modAmount) * Param::fromCent(currentPitchInCents));
            }
        }
        else // if lfo1wave is 1, lfo is set to square wave
        {
            for (int s = 0; s < numSamples;++s)
            {
                pitchModBuffer.setSample(0, s, Param::fromSemi(lfo1square.next()*modAmount) * Param::fromCent(currentPitchInCents));
            }
        }
    }

private:
    SynthParams &params;

    Oscillator<&Waveforms::square> osc1;

    Oscillator<&Waveforms::sinus> lfo1sine;
    Oscillator<&Waveforms::square> lfo1square;

    float level, tailOff;

    int currentPitchValue;

    // variables for env
    float envCoeff;
    float sustainLevel;
    int attackSamples;
    int decaySamples;
    int releaseSamples;
    int attackDecayCounter;
    int releaseCounter;

    AudioSampleBuffer pitchModBuffer;
};
