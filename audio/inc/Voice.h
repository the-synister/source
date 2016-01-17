#pragma once

#include "JuceHeader.h"
#include "SynthParams.h"
#include "ModulationMatrix.h"
#include "Envelope.h"

// 46.881879936465680 semitones = semitonesBetweenFrequencies(80, 18000.0)/2.0
#define FILTER_FC_MOD_RANGE 46.881879936465680f

class Sound : public SynthesiserSound {
public:
    bool appliesToNote(int /*midiNoteNumber*/) override { return true; }
    bool appliesToChannel(int /*midiChannel*/) override { return true; }
};

struct Waveforms {
    static float sinus(float phs, float trngAmount, float width) {
        ignoreUnused(trngAmount, width);
        return std::sin(phs);
    }
    static float square(float phs, float trngAmount, float width) {
        ignoreUnused(trngAmount, width);
        //square wave with duty cycle
        if (phs < 2.f * float_Pi * width) {
            return 1.f;
        }
        else {
            return -1.f;
        }
        //return std::copysign(1.f, float_Pi - phs);
    }

    static float saw(float phs, float trngAmount, float width) {
        ignoreUnused(width);
        //return (1 - trngAmount) * phs / (float_Pi*2.f) - .5f + trngAmount * (-abs(float_Pi - phs))*(1 / float_Pi) + .5f;
        if (phs < trngAmount*float_Pi) { return (.5f - 1.f / (trngAmount*float_Pi) * phs); }
        else { return (-.5f + 1.f / (2.f*float_Pi - trngAmount*float_Pi) * (phs - trngAmount*float_Pi)); }
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
        , heldValue(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f)) - 1.f)
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
            heldValue = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f)) - 1.f;
        }

        phase = std::fmod(phase + phaseDelta, float_Pi * 2.0f);
        return heldValue;
    }

};

class Voice : public SynthesiserVoice {
public:
    Voice(SynthParams &p, int blockSize, ModulationMatrix &globalModMatrix_)
    : lastSample(0.f)
    , inputDelay1(0.f)
    , inputDelay2(0.f)
    , outputDelay1(0.f)
    , outputDelay2(0.f)
    , params(p)
    , envToVolume(getSampleRate(), params.envDecay, params.envAttack, params.envSustain, params.envRelease,
        params.envAttackShape, params.envDecayShape, params.envReleaseShape, params.keyVelToEnv)
    , envToCutoff(getSampleRate(), params.env1Decay, params.env1Attack, params.env1Sustain, params.env1Release,
        params.env1AttackShape, params.env1DecayShape, params.env1ReleaseShape, params.keyVelToEnv1)
    , envToPitch(getSampleRate(), params.env1Decay, params.env1Attack, params.env1Sustain, params.env1Release,
        params.env1AttackShape, params.env1DecayShape, params.env1ReleaseShape, params.keyVelToEnv1)
    , level (0.f)
    , ladderOut(0.f)
    , ladderInDelay(0.f)
    , lpOut1(0.f)
    , lpOut2(0.f)
    , lpOut3(0.f)
    , lpOut1Delay(0.f)
    , lpOut2Delay(0.f)
    , lpOut3Delay(0.f)
    , globalModMatrix(globalModMatrix_)
    , pitchModBuffer(1, blockSize)
    , totSamples(0)
    , envToVolBuffer(1, blockSize)
    , lfo1ModBuffer(1,blockSize)
    , envToCutoffBuffer(1, blockSize)
    , noModBuffer(1, blockSize)
    {
        noModBuffer.clear();
    }


    bool canPlaySound(SynthesiserSound* sound) override
    {
        ignoreUnused(sound);
        return true;
    }

    void startNote(int midiNoteNumber, float velocity,
        SynthesiserSound*, int currentPitchWheelPosition) override
    {
        //for ladder filter
        ladderOut = 0.f;
        ladderInDelay = 0.f;
        lpOut1 = 0.f;
        lpOut2 = 0.f;
        lpOut3 = 0.f;
        lpOut1Delay = 0.f;
        lpOut2Delay = 0.f;
        lpOut3Delay = 0.f;

        lastSample = 0.f;
        inputDelay1 = 0.f;
        inputDelay2 = 0.f;
        outputDelay1 = 0.f;
        outputDelay2 = 0.f;

        currentVelocity = velocity;

        level = velocity * 0.15f;

        // reset attackDecayCounter
        envToVolume.startEnvelope(currentVelocity);
        envToCutoff.startEnvelope(currentVelocity);
        envToPitch.startEnvelope(currentVelocity);

        currentPitchValue = currentPitchWheelPosition;

        const float sRate = static_cast<float>(getSampleRate());
        float freqHz = static_cast<float>(MidiMessage::getMidiNoteInHertz(midiNoteNumber, params.freq.get()));

        // change the phases of both lfo waveforms, in case the user switches them during a note
        lfo1sine.phase = 0.f;
        lfo1sine.phaseDelta = params.lfo1freq.get() / sRate * 2.f * float_Pi;
        lfo1square.phase = 0.f;
        lfo1square.phaseDelta = params.lfo1freq.get() / sRate * 2.f * float_Pi;

        lfo1random.phase = 0.f;
        lfo1random.phaseDelta = params.lfo1freq.get() / sRate * 2.f * float_Pi;
        lfo1random.heldValue = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f)) - 1.f;


        int wf = static_cast<int>(params.osc1WaveForm.get());
        switch (wf)
        {
        case 1:
        {
            osc1Sine.phase = 0.f;
            osc1Sine.phaseDelta = freqHz * (Param::fromCent(params.osc1fine.get()) * Param::fromSemi(params.osc1coarse.get())) / sRate * 2.f * float_Pi;
            osc1Sine.width = params.osc1pulsewidth.get();
            lfo1square.width = params.osc1pulsewidth.get();
            //osc1.phaseDelta = freqHz * Param::fromCent(params.osc1fine.get()) / sRate * 2.f * float_Pi;
            break;
        }
        case 2:
        {
            osc1Saw.phase = 0.f;
            osc1Saw.phaseDelta = freqHz * Param::fromCent(params.osc1fine.get()) / sRate * 2.f * float_Pi;
            osc1Saw.trngAmount = params.osc1trngAmount.get();
            break;
        }
        }
    }

    void stopNote(float /*velocity*/, bool allowTailOff) override
    {
        if (allowTailOff)
        {
            // start a tail-off by setting this flag. The render callback will pick up on
            // this and do a fade out, calling clearCurrentNote() when it's finished.

            if (envToVolume.getReleaseCounter() == -1)      // we only need to begin a tail-off if it's not already doing so - the
            {                                       // stopNote method could be called more than once.
                envToVolume.resetReleaseCounter();
        }

            if (envToCutoff.getReleaseCounter() == -1)
            {
                envToCutoff.resetReleaseCounter();
        }

            if (envToPitch.getReleaseCounter() == -1)
            {
                envToPitch.resetReleaseCounter();
            }
        }
        else
        {
            // we're being told to stop playing immediately, so reset everything..
            clearCurrentNote();
            lfo1sine.reset();
            lfo1square.reset();
            lfo1random.reset();
            osc1Sine.reset();
            osc1Saw.reset();
        }
    }

    void pitchWheelMoved(int newValue) override
    {
        currentPitchValue = newValue;
    }

    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override
    {
        // not interested in controllers in this case.
    }

    void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        // Modulation
        renderModulation2(numSamples);
        const float *noMod = noModBuffer.getReadPointer(0);
        const float *pitchMod = pitchModBuffer.getReadPointer(0);
        const float *envToVolMod = envToVolBuffer.getReadPointer(0);
        const float *lfo1Mod = lfo1ModBuffer.getReadPointer(0);
        const float *envToCutoffMod = envToCutoffBuffer.getReadPointer(0);

        std::vector<const float*> modSources(3);
        modSources[0] = noMod;
        modSources[1] = lfo1Mod;
        modSources[2] = envToCutoffMod;

        const float currentAmp = params.vol.get();
        const float currentPan = params.panDir.get();

        // Pan Influence
        const float currentAmpRight = currentAmp + (currentAmp / 100.f * currentPan);
        const float currentAmpLeft = currentAmp - (currentAmp / 100.f * currentPan);

        if (lfo1square.isActive() || lfo1sine.isActive()) {
            for (int s = 0; s < numSamples; ++s) {
                //const float currentSample = (osc1.next(pitchMod[s])) * level * tailOff * currentAmp;
                int wf = static_cast<int>(params.osc1WaveForm.get());
                float currentSample;
                switch (wf)
                {
                case 1:
                    currentSample = (osc1Sine.next(pitchMod[s]));
                    break;
                case 2:
                    currentSample = (osc1Saw.next(pitchMod[s]));
                    break;
                }

                currentSample = ladderFilter(biquadFilter2(currentSample, params.passtype.getStep())) * level * envToVolMod[s];

                //check if the output is a stereo output
                if (outputBuffer.getNumChannels() == 2) {
                    outputBuffer.addSample(0, startSample + s, currentSample*currentAmpLeft);
                    outputBuffer.addSample(1, startSample + s, currentSample*currentAmpRight);
                }
                else {
                    for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {
                        outputBuffer.addSample(c, startSample + s, currentSample * currentAmp);
                    }
                }
                if (static_cast<int>(getSampleRate() * params.envRelease.get()) <= envToVolume.getReleaseCounter() || static_cast<int>(getSampleRate() * params.env1Release.get()) <= envToCutoff.getReleaseCounter())
                {
                    clearCurrentNote();
                    lfo1sine.reset();
                    lfo1square.reset();
                    break;
                }
            }
        }
        //Update of the total samples variable
        totSamples = totSamples + numSamples;
    }

    //apply ladder filter to the current Sample in renderNextBlock() - Zavalishin approach
    //naive 1 pole filters wigh a hyperbolic tangent saturator
    float ladderFilter(float ladderIn)
    {

        const float sRate = static_cast<float>(getSampleRate());

        //float currentResonance = pow(10.f, params.ladderRes.get() / 20.f);
        float currentLadderCutoffFreq = params.ladderCutoff.get();

        //coeffecients and parameters
        float omega_c = 2.f*float_Pi*currentLadderCutoffFreq / sRate;
        float g = omega_c / 2.f;
        float a = (1.f - g) / (1.f + g);
        float b = g / (1.f + g);

        // subtract the feedback
        // inverse hyperbolic Sinus
        // ladderIn = tanh(ladderIn) - asinh(params.ladderRes.get() * ladderOut);
        // hyperbolic tangent
        ladderIn = tanh(ladderIn) - tanh(params.ladderRes.get() * ladderOut);

        // proecess through 1 pole Filters 4 times
        lpOut1 = b*(ladderIn + ladderInDelay) + a*tanh(lpOut1);
        ladderInDelay = ladderIn;

        lpOut2 = b*(lpOut1 + lpOut1Delay) + a* tanh(lpOut2);
        lpOut1Delay = lpOut1;

        lpOut3 = b*(lpOut2 + lpOut2Delay) + a* tanh(lpOut3);
        lpOut2Delay = lpOut2;

        ladderOut = b*(lpOut3 + lpOut3Delay) + a* tanh(ladderOut);
        lpOut3Delay = lpOut3;

        return ladderOut;
    }

protected:
    void renderModulation2(int numSamples) {
        const float sRate = static_cast<float>(getSampleRate());    // Sample rate
        float factorFadeInLFO = 1.f;                                // Defaut value of fade in factor is 1 (100%)
        float modAmount = params.osc1lfo1depth.get();               // Default value of modAmount is the value from the slider
        const int samplesFadeInLFO = static_cast<int>(params.lfoFadein.get() * sRate);     // Length in samples of the LFO fade in

                                                                                           // set the env1buffer - for Volume
        for (int s = 0; s < numSamples; ++s)
        {
            envToVolBuffer.setSample(0, s, envToVolume.calcEnvCoeff());
        }

        // set the filterEnvBuffer - for Filter
        for (int s = 0; s < numSamples; ++s)
        {
            envToCutoffBuffer.setSample(0, s, envToCutoff.calcEnvCoeff());
        }

        // add pitch wheel values
        float currentPitchInCents = (params.osc1PitchRange.get() * 100) * ((currentPitchValue - 8192.0f) / 8192.0f);


        for (int s = 0; s < numSamples; ++s)
        {
            float lfoVal = 0.f;
            switch (params.lfo1wave.getStep()) {
            case eLfoWaves::eLfoSine:
                lfoVal = lfo1sine.next();
                break;
            case eLfoWaves::eLfoSampleHold:
                lfoVal = lfo1random.next();
                break;
            case eLfoWaves::eLfoSquare:
                lfoVal = lfo1square.next();
                break;
            }

            // Fade in factor calculation
            if (samplesFadeInLFO == 0 || (totSamples + s > samplesFadeInLFO))
            {
                // If the fade in is reached or no fade in is set, the factor is 1 (100%)
                factorFadeInLFO = 1.f;
            }
            else
            {
                // Otherwise the factor is determined
                factorFadeInLFO = static_cast<float>(totSamples + s) / static_cast<float>(samplesFadeInLFO);
            }

            // Update of the modulation amount value
            modAmount = params.osc1lfo1depth.get() * factorFadeInLFO;
            // Next sample modulated with the updated amount
            if (params.osc1ModSource.getStep() == eModSource::eEnv)
            {
                pitchModBuffer.setSample(0, s, Param::fromSemi(lfoVal*modAmount) * Param::fromCent(currentPitchInCents)*envToPitch.calcEnvCoeff());
            }
            else
            {
                pitchModBuffer.setSample(0, s, Param::fromSemi(lfoVal*modAmount) * Param::fromCent(currentPitchInCents));
            }
        }
    }
    void renderModulation(int numSamples) {

        const float sRate = static_cast<float>(getSampleRate());    // Sample rate
        float factorFadeInLFO = 1.f;                                // Defaut value of fade in factor is 1 (100%)
        float modAmount = params.osc1lfo1depth.get();               // Default value of modAmount is the value from the slider
        const int samplesFadeInLFO = static_cast<int>(params.lfoFadein.get() * sRate);     // Length in samples of the LFO fade in


        // set the env1buffer - for Volume
        for (int s = 0; s < numSamples; ++s)
            {
            envToVolBuffer.setSample(0, s, envToVolume.calcEnvCoeff());
                }

        // set the filterEnvBuffer - for Filter
        for (int s = 0; s < numSamples; ++s)
        {
            envToCutoffBuffer.setSample(0, s, envToCutoff.calcEnvCoeff());
        }

        // add pitch wheel values
        float currentPitchInCents = (params.osc1PitchRange.get() * 100) * ((currentPitchValue - 8192.0f) / 8192.0f);


        for (int s = 0; s < numSamples; ++s)
        {
            float lfoVal = 0.f;
            switch (params.lfo1wave.getStep()) {
            case eLfoWaves::eLfoSine:
                lfoVal = lfo1sine.next();
                break;
            case eLfoWaves::eLfoSampleHold:
                lfoVal = lfo1random.next();
                break;
            case eLfoWaves::eLfoSquare:
                lfoVal = lfo1square.next();
                break;
            }

            // Fade in factor calculation
            if (samplesFadeInLFO == 0 || (totSamples + s > samplesFadeInLFO))  
            {
                // If the fade in is reached or no fade in is set, the factor is 1 (100%)
                factorFadeInLFO = 1.f;          
            }
            else                                   
            {
                // Otherwise the factor is determined
                factorFadeInLFO = static_cast<float>(totSamples + s) / static_cast<float>(samplesFadeInLFO);
            }

            lfo1ModBuffer.setSample(0, s, lfoVal);

            // Update of the modulation amount value
            modAmount = params.osc1lfo1depth.get() * factorFadeInLFO;      
            // Next sample modulated with the updated amount
            if (params.osc1ModSource.getStep() == eModSource::eEnv)
            {
                pitchModBuffer.setSample(0, s, Param::fromSemi(lfoVal*modAmount) * Param::fromCent(currentPitchInCents)*envToPitch.calcEnvCoeff());
            }
            else
            {
                pitchModBuffer.setSample(0, s, Param::fromSemi(lfoVal*modAmount) * Param::fromCent(currentPitchInCents));
            }
        }
    }

    float biquadFilter2(float inputSignal, eBiquadFilters filterType) {

        return inputSignal;
    }

    float biquadFilter(float inputSignal, float modValue, eBiquadFilters filterType) {
        const float sRate = static_cast<float>(getSampleRate());
        
        float moddedFreq = filterType == eBiquadFilters::eLowpass 
            ? params.lpCutoff.get()
            : params.hpCutoff.get();

        float moddedMaxFreq = params.lpCutoff.getMax() * params.lpModAmout.get() / 100.f;
        
        if (params.lpModSource.getStep() == eModSource::eLFO1) { // bipolar, full range
            moddedFreq += (20000.f * (modValue) * params.lpModAmout.get() / 100.f);
        }
        else if (params.lpModSource.getStep() == eModSource::eEnv) { // env

            moddedFreq = params.lpCutoff.get() + (moddedMaxFreq - params.lpCutoff.get()) * modValue;
        }
        
        if (moddedFreq < params.lpCutoff.getMin()) { // assuming that min/max are identical for low and high pass filters
            moddedFreq = params.lpCutoff.getMin();
        }
        else if (moddedFreq > params.lpCutoff.getMax()) {
            moddedFreq = params.lpCutoff.getMax();
        }
        moddedFreq /= sRate;

        //New Filter Design: Biquad (2 delays) Source: http://www.musicdsp.org/showArchiveComment.php?ArchiveID=259
        float k, coeff1, coeff2, coeff3, b0, b1, b2, a1, a2;

        const float currentResonance = pow(10.f, -params.biquadResonance.get() / 20.f);

        if (filterType == eBiquadFilters::eLowpass) {

            // coefficients for lowpass, depending on resonance and lowcut frequency
            k = 0.5f * currentResonance * sin(2.f * float_Pi * moddedFreq);
            coeff1 = 0.5f * (1.f - k) / (1.f + k);
            coeff2 = (0.5f + coeff1) * cos(2.f * float_Pi * moddedFreq);
            coeff3 = (0.5f + coeff1 - coeff2) * 0.25f;

            b0 = 2.f * coeff3;
            b1 = 2.f * 2.f * coeff3;
            b2 = 2.f * coeff3;
            a1 = 2.f * -coeff2;
            a2 = 2.f * coeff1;
        } else if (filterType == eBiquadFilters::eHighpass) {

            // coefficients for highpass, depending on resonance and highcut frequency
            k = 0.5f * currentResonance * sin(float_Pi * moddedFreq);
            coeff1 = 0.5f * (1.f - k) / (1.f + k);
            coeff2 = (0.5f + coeff1) * cos(float_Pi * moddedFreq);
            coeff3 = (0.5f + coeff1 + coeff2) * 0.25f;

            b0 = 2.f * coeff3;
            b1 = -4.f * coeff3;
            b2 = 2.f * coeff3;
            a1 = -2.f * coeff2;
            a2 = 2.f * coeff1;
        }

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
        else if (inputSignal < -1.f) {
            inputSignal = -1.f;
        }
        
        return inputSignal;
    }

private:
    SynthParams &params;
    //New Filter Design
    float lastSample, inputDelay1, inputDelay2, outputDelay1, outputDelay2;
    
    Oscillator<&Waveforms::square> osc1Sine;
    Oscillator<&Waveforms::saw> osc1Saw;

    Oscillator<&Waveforms::sinus> lfo1sine;
    Oscillator<&Waveforms::square> lfo1square;
    RandomOscillator<&Waveforms::square> lfo1random;

    float level;

    int currentPitchValue;
    int totSamples;

    float currentVelocity;

    //for the lader filter
    float ladderOut;
    float ladderInDelay;
    float lpOut1;
    float lpOut2;
    float lpOut3;
    float lpOut1Delay;
    float lpOut2Delay;
    float lpOut3Delay;

    AudioSampleBuffer pitchModBuffer;
    AudioSampleBuffer lfo1ModBuffer;
    AudioSampleBuffer noModBuffer;
    AudioSampleBuffer envToVolBuffer;
    AudioSampleBuffer envToCutoffBuffer;

    ModulationMatrix &globalModMatrix;
    modMatrixRow* modMatrixRow;
    float filter1Fc;

    Envelope envToCutoff;
    Envelope envToVolume;
    Envelope envToPitch;
};
