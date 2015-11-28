#pragma once

#include "JuceHeader.h"
#include "SynthParams.h"

class Sound : public SynthesiserSound {
public:
    bool appliesToNote(int /*midiNoteNumber*/) override { return true; }
    bool appliesToChannel(int /*midiChannel*/) override { return true; }
};

struct Waveforms {
    static float sinus(float phs, float trngAmount, float width)  { 
        ignoreUnused(trngAmount, width);
        return std::sin(phs); 
    }
    static float square(float phs, float trngAmount, float width) {
        ignoreUnused(trngAmount, width);
        //square wave with duty cycle
        if (phs < 2.f * float_Pi * width) {
            return 1.f;
        } else {
            return -1.f;
        }
        //return std::copysign(1.f, float_Pi - phs);
    }
    static float saw(float phs, float trngAmount, float width) {
        ignoreUnused(width);
        //return (1 - trngAmount) * phs / (float_Pi*2.f) - .5f + trngAmount * (-abs(float_Pi - phs))*(1 / float_Pi) + .5f;
        if (phs < trngAmount*float_Pi) { return (.5f - 1.f / (trngAmount*float_Pi) * phs); }
        else { return (-.5f + 1.f / (2.f*float_Pi - trngAmount*float_Pi) * (phs-trngAmount*float_Pi)); }
    }
};


template<float(*_waveform)(float, float, float)>
struct Oscillator {
    float phase;
    float phaseDelta;
    float trngAmount;
    float width;

    Oscillator() : phase(0.f), phaseDelta(0.f) {}

    void reset() {
        phase = 0.f;
        phaseDelta = 0.f;
    }

    bool isActive() const {
        return phaseDelta > 0.f;
    }

    float next() {
        const float result = _waveform(phase, trngAmount, width);
        phase = std::fmod(phase + phaseDelta, float_Pi * 2.0f);
        return result;
    }

    float next(float pitchMod) {
        const float result = _waveform(phase, trngAmount, width);
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
        currentVelocity = velocity;
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
        osc1.phaseDelta = freqHz * (Param::fromCent(params.osc1fine.get()) * Param::fromSemi(params.osc1coarse.get())) / sRate * 2.f * float_Pi;
        osc1.trngAmount = params.osc1trngAmount.get();
        osc1.width = params.osc1pulsewidth.get();
        lfo1square.width = params.osc1pulsewidth.get();
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
                else 
                {
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
        // if needed consider key velocity for attack and decay
        int attackSamples = static_cast<int>(getSampleRate() * params.envAttack.get() * (1.0f - currentVelocity * params.keyVelToEnv.get()));
        int decaySamples = static_cast<int>(getSampleRate() * params.envDecay.get() * (1.0f - currentVelocity * params.keyVelToEnv.get()));
        int releaseSamples = static_cast<int>(getSampleRate() * params.envRelease.get());
        
        // get growth/shrink rate from knobs
        float attackGrowthRate = params.envAttackShape.get();
        float decayShrinkRate = params.envDecayShape.get();
        float releaseShrinkRate = params.envReleaseShape.get();

        // release phase sets envCoeff from valueAtRelease to 0.0f
        if (releaseCounter > -1)
        {
            if (releaseShrinkRate < 1.0f)
            {
                releaseShrinkRate = 1 / releaseShrinkRate;
                envCoeff = valueAtRelease * (1 - interpolateLog(releaseCounter, releaseSamples, releaseShrinkRate, true));
            }
            else
            {
                envCoeff = valueAtRelease * interpolateLog(releaseCounter, releaseSamples, releaseShrinkRate, false);
            }
            releaseCounter++;
        }
        else
        {
            // attack phase sets envCoeff from 0.0f to 1.0f
            if (attackDecayCounter <= attackSamples)
            {
                if (attackGrowthRate < 1.0f)
                {
                    attackGrowthRate = 1 / attackGrowthRate;
                    envCoeff = interpolateLog(attackDecayCounter, attackSamples, attackGrowthRate, true);
                }
                else
                {
                    envCoeff = 1.0f - interpolateLog(attackDecayCounter, attackSamples, attackGrowthRate, false);
                }
                valueAtRelease = envCoeff;
                attackDecayCounter++;
            }
            else
            {
                // decay phase sets envCoeff from 1.0f to sustain level
                if (attackDecayCounter <= attackSamples + decaySamples)
                {
                    if (decayShrinkRate < 1.0f)
                    {
                        decayShrinkRate = 1 / decayShrinkRate;
                        envCoeff = 1 - interpolateLog(attackDecayCounter - attackSamples, decaySamples, decayShrinkRate, true) * (1.0f - sustainLevel);
                    }
                    else
                    {
                        envCoeff = interpolateLog(attackDecayCounter - attackSamples, decaySamples, decayShrinkRate, false) * (1.0f - sustainLevel) + sustainLevel;
                    }
                    valueAtRelease = envCoeff;
                    attackDecayCounter++;
                }

                // if attack and decay phase is over then sustain level
                else
                {
                    envCoeff = sustainLevel;
                    valueAtRelease = envCoeff;
                }
            }
        }
        return envCoeff;
    }

    /**
    * interpolate logarithmically from 1.0 to 0.0f in t samples
    @c counter of the specific phase
    @t number of samples after which the specific phase should be over
    @k coeff of growth/shrink, k=1 for linear
    @slow slow start of phase
    */
    float interpolateLog(int c, int t, float k, bool slow)
    {
        if (slow)
        {
            return std::exp(std::log(static_cast<float>(c) / static_cast<float>(t)) * k);
        }
        else
        {
            return std::exp(std::log(1.0f - static_cast<float>(c) / static_cast<float>(t)) * k);
        }
    }

    void renderModulation(int numSamples) {

        // set the env1buffer
        for (int s = 0; s < numSamples; ++s)
        {
            env1Buffer.setSample(0, s, getEnvCoeff());
        }

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

    float level;

    int currentPitchValue;

    // variables for env
    float currentVelocity;
    float valueAtRelease;
    int attackDecayCounter;
    int releaseCounter;

    AudioSampleBuffer pitchModBuffer;
    AudioSampleBuffer env1Buffer;
};
