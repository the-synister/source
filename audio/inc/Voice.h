#pragma once

#include "JuceHeader.h"
#include "SynthParams.h"
#include "Envelope.h"

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
    
    Oscillator() : phase(0.f)
                 , phaseDelta(0.f)
    {}

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

template<float(*_waveform)(float, float, float)>
struct RandomOscillator : Oscillator<&Waveforms::square>
{
    float heldValue;
    
    RandomOscillator() : Oscillator()
                       , heldValue(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2.f)) - 1.f)
                      {}
    
    void reset()
    {
        phase = 0.f;
        phaseDelta = 0.f;
        heldValue = 0.f;
    }
    
    float next()
    {
        if (phase + phaseDelta > 2.0f * float_Pi) {
             heldValue = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2.f)) - 1.f;
        }
        
        phase = std::fmod(phase + phaseDelta, float_Pi * 2.0f);
        return heldValue;
    }

};

class Voice : public SynthesiserVoice {
public:
    Voice(SynthParams &p, int blockSize) 
    : lastSample(0.f)
    , inputDelay1(0.f)
    , inputDelay2(0.f)
    , outputDelay1(0.f)
    , outputDelay2(0.f)
    , params(p)
    , env(p, getSampleRate())
    , level (0.f)
    , pitchModBuffer(1,blockSize)
    , lfo1ModBuffer(1, blockSize)
    , env1Buffer(1, blockSize)
    , freeEnv1Buffer(1, blockSize)
    , noModBuffer(1, blockSize)
    {

        for (int s = 0; s < blockSize; ++s) {
            noModBuffer.setSample(0, s, 0.f);
        }
        
    }


    bool canPlaySound (SynthesiserSound* sound) override
    {
        ignoreUnused(sound);
        return true;
    }

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int currentPitchWheelPosition) override
    {
        lastSample = 0.f;
        inputDelay1 = 0.f;
        inputDelay2 = 0.f;
        outputDelay1 = 0.f;
        outputDelay2 = 0.f;
        
        level = velocity * 0.15f;
        env.resetAllCounters();
        //env.releaseCounter = -1;
        //freeEnv1ReleaseCounter = -1;

        currentPitchValue = currentPitchWheelPosition;

        const float sRate = static_cast<float>(getSampleRate());
        float freqHz = static_cast<float>(MidiMessage::getMidiNoteInHertz (midiNoteNumber, params.freq.get()));

        // change the phases of both lfo waveforms, in case the user switches them during a note
        lfo1sine.phase = 0.f;
        lfo1sine.phaseDelta = params.lfo1freq.get() / sRate * 2.f * float_Pi;
        lfo1square.phase = 0.f;
        lfo1square.phaseDelta = params.lfo1freq.get() / sRate * 2.f * float_Pi;
        
        lfo1random.phase = 0.f;
        lfo1random.phaseDelta = params.lfo1freq.get() / sRate * 2.f * float_Pi;
        lfo1random.heldValue = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2.f)) - 1.f;

        osc1.phase = 0.f;
        osc1.phaseDelta = freqHz * (Param::fromCent(params.osc1fine.get()) * Param::fromSemi(params.osc1coarse.get())) / sRate * 2.f * float_Pi;
        osc1.trngAmount = params.osc1trngAmount.get();
        osc1.width = params.osc1pulsewidth.get();
        lfo1square.width = params.osc1pulsewidth.get();
        osc1.phaseDelta = freqHz * Param::fromCent(params.osc1fine.get()) / sRate * 2.f * float_Pi;

        // reset attackDecayCounter
        //attackDecayCounter = 0;
        //freeEnv1AttackDecayCounter = 0;
        testCnt = 0;
    }

    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        if (allowTailOff)
        {
            // start a tail-off by setting this flag. The render callback will pick up on
            // this and do a fade out, calling clearCurrentNote() when it's finished.

            if (env.getReleaseCounter() == -1) // we only need to begin a tail-off if it's not already doing so - the
            {                         // stopNote method could be called more than once.
                // reset releaseCounter
                //releaseCounter = 0;
                env.resetReleaseCounter();
            }

            if (env.getfreeEnv1ReleaseCounter() == -1)
            {
                env.resetfreeEnv1ReleaseCounter();
        }
        }
        else
        {
            // we're being told to stop playing immediately, so reset everything..
            clearCurrentNote();
            lfo1sine.reset();
            lfo1square.reset();
            lfo1random.reset();
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
        const float *noMod = noModBuffer.getReadPointer(0);
        const float *pitchMod = pitchModBuffer.getReadPointer(0);
        const float *lfo1Mod = lfo1ModBuffer.getReadPointer(0);
        const float *env1Mod = env1Buffer.getReadPointer(0);
        const float *filterEnvMod = freeEnv1Buffer.getReadPointer(0);

        std::vector<const float*> modSources(3);
        modSources[0] = noMod;
        modSources[1] = lfo1Mod;
        modSources[2] = filterEnvMod;

        const float currentAmp = params.vol.get();
        const float currentPan = params.panDir.get();

        // Pan Influence
        const float currentAmpRight = currentAmp + (currentAmp / 100.f * currentPan);
        const float currentAmpLeft = currentAmp - (currentAmp / 100.f * currentPan);

        if (lfo1square.isActive() || lfo1sine.isActive())
        {
            for (int s = 0; s < numSamples; ++s)
            {
                const float currentSample = biquadLowpass(osc1.next(pitchMod[s]), modSources[static_cast<int>(params.lpModSource.get())][s]) * level * env1Mod[s];
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
                if (static_cast<int>(getSampleRate() * params.envRelease.get()) <= env.getReleaseCounter() || static_cast<int>(getSampleRate() * params.freeEnv1Release.get()) <= env.getfreeEnv1ReleaseCounter())
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
/*    float getEnv1Coeff()
    {
        float freeEnvCoeff;
        float sustainLevel = params.freeEnv1Sustain.get(); // / static_cast<float>(getSampleRate());

        //number of all samples for all phases
        int attackSamples = static_cast<int>(getSampleRate() * params.freeEnv1Attack.get());
        int decaySamples = static_cast<int>(getSampleRate() * params.freeEnv1Decay.get());
        int releaseSamples = static_cast<int>(getSampleRate() * params.freeEnv1Release.get());

        if (freeEnv1ReleaseCounter > -1)
        {
            freeEnvCoeff = freeEnv1ValueAtRelease * interpolateLog(freeEnv1ReleaseCounter, releaseSamples);
            freeEnv1ReleaseCounter++;
        }
        else
        {
            if(freeEnv1AttackDecayCounter <= attackSamples)
            {
                freeEnvCoeff = 1.0f - interpolateLog(freeEnv1AttackDecayCounter, attackSamples);
                freeEnv1ValueAtRelease = freeEnvCoeff;
                freeEnv1AttackDecayCounter++;
            }
            else
            {
                if (freeEnv1AttackDecayCounter <= attackSamples + decaySamples)
                {
                    freeEnvCoeff = interpolateLog(freeEnv1AttackDecayCounter - attackSamples, decaySamples) * (1.0f - sustainLevel) + sustainLevel;
                    freeEnv1ValueAtRelease = freeEnvCoeff;
                    freeEnv1AttackDecayCounter++;
                }

                else
                {
                    freeEnvCoeff = sustainLevel;
                }
            }
        
        }
        //jassert(isfinite(filterEnvCoeff));
        return freeEnvCoeff;
    }
    
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
        //std::cout << envCoeff;
        return envCoeff;
    }*/

    /**
    * help function that interpolates logarithmically from 1.0 to 0.0f in t samples
    */
    /*float interpolateLog(int curr, int t)
    {
        // coeff of growth/shrink, maybe on which depends on time is better?
        float k = std::exp(1.0f);

        return std::exp(std::log(1.0f - static_cast<float>(curr) / static_cast<float>(t)) * k);
    }*/

    void renderModulation(int numSamples) {

        // set the env1buffer - for Volume
        for (int s = 0; s < numSamples; ++s)
        {
            env1Buffer.setSample(0, s, env.getEnvCoeff());
        }

        // set the filterEnvBuffer - for freeEnvelope
        for (int s = 0; s < numSamples; ++s)
        {
            freeEnv1Buffer.setSample(0, s, env.getEnv1Coeff());
        }

        // add pitch wheel values
        float currentPitchInCents = (params.osc1PitchRange.get() * 100) * ((currentPitchValue - 8192.0f) / 8192.0f);

        const float modAmount = params.osc1lfo1depth.get();
        if (params.lfo1wave.get() == 0) // if lfo1wave is 0, lfo is set to sine wave
        {
            for (int s = 0; s < numSamples;++s)
            {
                pitchModBuffer.setSample(0, s, Param::fromSemi(lfo1sine.next()*modAmount) * Param::fromCent(currentPitchInCents));
                lfo1ModBuffer.setSample(0, s, lfo1sine.next()*0.5f );
            }
        }
        else if (params.lfo1wave.get() == 1) // if lfo1wave is 1, lfo is set to random wave
        {
            for (int s = 0; s < numSamples; ++s)
            {
                pitchModBuffer.setSample(0, s, Param::fromSemi(lfo1random.next()*modAmount) * Param::fromCent(currentPitchInCents));
                lfo1ModBuffer.setSample(0, s, lfo1random.next()*0.5f);
            }
        }
        else if (params.lfo1wave.get() == 2)// if lfo1wave is 2, lfo is set to square wave
        {

            for (int s = 0; s < numSamples;++s)
            {
                pitchModBuffer.setSample(0, s, Param::fromSemi(lfo1square.next()*modAmount) * Param::fromCent(currentPitchInCents));
                lfo1ModBuffer.setSample(0, s, lfo1square.next()*0.5f);
            }
        }
    }
    
    float biquadLowpass(float inputSignal, float modValue) {
        const float sRate = static_cast<float>(getSampleRate());

        //New Filter Design: Biquad (2 delays) Source: http://www.musicdsp.org/showArchiveComment.php?ArchiveID=259
        float k, coeff1, coeff2, coeff3, b0, b1, b2, a1, a2;
        //float value;

        // mod to frequency calculation
        float moddedFreq = params.lpCutoff.get();
        float moddedMaxFreq = params.lpCutoff.getMax() * params.lpModAmout.get() / 100.f;
        //float freqAtSustain = params.lpCutoff.getMax() * pow(params.freeEnv1Sustain.get(), 2.f);

        //int attackSamples = static_cast<int>(getSampleRate() * params.freeEnv1Attack.get());
        //int decaySamples = static_cast<int>(getSampleRate() * params.freeEnv1Decay.get());
        
        if (params.lpModSource.get() == 1) { //bipolar (lfo) modValues
        
            moddedFreq = (params.lpCutoff.get() + (20000.f * (modValue - 0.5f) * params.lpModAmout.get() / 100.f)  );
        }
        else if (params.lpModSource.get() == 2) { // env
            //moddedFreq = (params.lpCutoff.get() + (20000.f * (modValue) * params.lpModAmout.get() / 100.f));
            if (testCnt <= static_cast<int>(getSampleRate() * params.freeEnv1Attack.get()))
            {
                moddedFreq = params.lpCutoff.get() + (moddedMaxFreq - params.lpCutoff.get()) * modValue;
                testCnt++;
            }
            //else if (testCnt <= attackSamples+decaySamples)
            else
            {
                // Sustain value is dependant on moddedMaxFreq ... not so cool ...
                // and the sustain knob should be logorythmic ...
                moddedFreq = moddedMaxFreq * modValue;
            }
        }
        
        if (moddedFreq < params.lpCutoff.getMin()) {
            moddedFreq = params.lpCutoff.getMin();
        }
        else if (moddedFreq > params.lpCutoff.getMax()) {
            moddedFreq = params.lpCutoff.getMax();
        }

        const float currentLowcutFreq = (moddedFreq / sRate);

        //if (params.lpModAmout.get() > 0.f) {
        //    currentLowcutFreq *= modValue;
        //}

        const float currentResonance = pow(10.f, -params.lpResonance.get() / 20.f);

        // coefficients for lowpass, depending on resonance and lowcut frequency
        k = 0.5f * currentResonance * sin(2.f * float_Pi * currentLowcutFreq);
        coeff1 = 0.5f * (1.f - k) / (1.f + k);
        coeff2 = (0.5f + coeff1) * cos(2.f * float_Pi * currentLowcutFreq);
        coeff3 = (0.5f + coeff1 - coeff2) * 0.25f;

        b0 = 2.f * coeff3;
        b1 = 2.f * 2.f * coeff3;
        b2 = 2.f * coeff3;
        a1 = 2.f * -coeff2;
        a2 = 2.f * coeff1;

        lastSample = inputSignal;
        
        inputSignal = b0*inputSignal + b1*inputDelay1 + b2*inputDelay2 - a1*outputDelay1 - a2*outputDelay2;
        
        //delaying samples
        inputDelay2 = inputDelay1;
        inputDelay1 = lastSample;
        outputDelay2 = outputDelay1;
        outputDelay1 = inputSignal;
        
        if (inputSignal > 1.f) {
            inputSignal = 1.f;
        }
        
        return inputSignal;
    }


private:
    
    //New Filter Design
    float lastSample, inputDelay1, inputDelay2, outputDelay1, outputDelay2;
    
    SynthParams &params;

    Oscillator<&Waveforms::square> osc1;

    Oscillator<&Waveforms::sinus> lfo1sine;
    Oscillator<&Waveforms::square> lfo1square;
    RandomOscillator<&Waveforms::square> lfo1random;
    
    float level;

    int currentPitchValue;

    // variables for env
    //float valueAtRelease;
    //int attackDecayCounter;
    //int releaseCounter;

    //variables for filter env
    //float freeEnv1ValueAtRelease;
    //int freeEnv1AttackDecayCounter;
    //int freeEnv1ReleaseCounter;
    int testCnt;

    AudioSampleBuffer pitchModBuffer;
    AudioSampleBuffer lfo1ModBuffer;
    AudioSampleBuffer env1Buffer;
    AudioSampleBuffer noModBuffer;
    AudioSampleBuffer freeEnv1Buffer;
    
    Envelope env;
};


