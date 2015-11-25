
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
    , pitchModBuffer(1,blockSize)
    , env1Buffer(1, blockSize)
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
        releaseCounter = -1;

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

        // reset attackDecayCounter
        attackDecayCounter = 0;
    }

    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        if (allowTailOff)
        {
            // start a tail-off by setting this flag. The render callback will pick up on
            // this and do a fade out, calling clearCurrentNote() when it's finished.

            if (releaseCounter == -1) // we only need to begin a tail-off if it's not already doing so - the
            {                         // stopNote method could be called more than once.
                // reset releaseCounter
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
        const float *env1Mod = env1Buffer.getReadPointer(0);

        const float currentAmp = params.vol.get();
        const float currentPan = params.panDir.get();

        // Pan Influence
        const float currentAmpRight = currentAmp + (currentAmp / 100.f * currentPan);
        const float currentAmpLeft = currentAmp - (currentAmp / 100.f * currentPan);

        if (lfo1square.isActive() || lfo1sine.isActive())
        {
            for (int s = 0; s < numSamples; ++s)
            {
                const float currentSample = (osc1.next(pitchMod[s])) * level * env1Mod[s];

                //check if the output is a stereo output
                if (outputBuffer.getNumChannels() == 2) {
                    outputBuffer.addSample(0, startSample + s, currentSample*currentAmpLeft);
                    outputBuffer.addSample(1, startSample + s, currentSample*currentAmpRight);
                }
                else {
                    for (int c = 0; c < outputBuffer.getNumChannels(); ++c)
                        outputBuffer.addSample(c, startSample + s, currentSample * currentAmp);
                }

                if(static_cast<int>(getSampleRate() * params.envRelease.get()) <= releaseCounter)
                {
                    clearCurrentNote();
                    lfo1sine.reset();
                    lfo1square.reset();
                    break;
                }
            }
        }
    }

protected:
    float getEnvCoeff() 
    {
        float envCoeff;
        float sustainLevel = Param::fromDb(params.envSustain.get());

        // number of samples for all phases
        int attackSamples = static_cast<int>(getSampleRate() * params.envAttack.get());
        int decaySamples = static_cast<int>(getSampleRate() * params.envDecay.get());
        int releaseSamples = static_cast<int>(getSampleRate() * params.envRelease.get());

        // release phase sets envCoeff from valueAtRelease to 0.0f
        if (releaseCounter > -1)
        {
            envCoeff = valueAtRelease * interpolateLog(releaseCounter, releaseSamples);
            releaseCounter++;
        }
        else 
        {
            // attack phase sets envCoeff from 0.0f to 1.0f
            if (attackDecayCounter <= attackSamples)
            {
                envCoeff = 1.0f - interpolateLog(attackDecayCounter, attackSamples);
                valueAtRelease = envCoeff;
                attackDecayCounter++;
            }
            else
            {
                // decay phase sets envCoeff from 1.0f to sustain level
                if (attackDecayCounter <= attackSamples + decaySamples)
                {
                    envCoeff = interpolateLog(attackDecayCounter - attackSamples, decaySamples) * (1.0f - sustainLevel) + sustainLevel;
                    valueAtRelease = envCoeff;
                    attackDecayCounter++;
                }

                // if attack and decay phase is over then sustain level
                else
                {
                    envCoeff = sustainLevel;
                }
            }
        }

        return envCoeff;
    }

    /**
    * help function that interpolates logarithmically from 1.0 to 0.0f in t samples
    */
    float interpolateLog(int curr, int t)
    {
        // coeff of growth/shrink, maybe on which depends on time is better?
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
                env1Buffer.setSample(0, s, getEnvCoeff());
            }
        }
        else // if lfo1wave is 1, lfo is set to square wave
        {
            for (int s = 0; s < numSamples;++s)
            {
                pitchModBuffer.setSample(0, s, Param::fromSemi(lfo1square.next()*modAmount) * Param::fromCent(currentPitchInCents));
                env1Buffer.setSample(0, s, getEnvCoeff());
            }
        }
    }

private:
    SynthParams &params;

    Oscillator<&Waveforms::square> osc1;

    Oscillator<&Waveforms::sinus> lfo1sine;
    Oscillator<&Waveforms::square> lfo1square;

    float level;

    int currentPitchValue;

    // variables for env
    float valueAtRelease;
    int attackDecayCounter;
    int releaseCounter;

    AudioSampleBuffer pitchModBuffer;
    AudioSampleBuffer env1Buffer;
};
