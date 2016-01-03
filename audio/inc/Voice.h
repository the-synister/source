#pragma once

#include "JuceHeader.h"
#include "SynthParams.h"
#include "ModulationMatrix.h"

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
    Voice(SynthParams &p, int blockSize)
        : lastSample(0.f)
        , inputDelay1(0.f)
        , inputDelay2(0.f)
        , outputDelay1(0.f)
        , outputDelay2(0.f)
        , params(p)
        , level(0.f)
        , ladderOut(0.f)
        , ladderInDelay(0.f)
        , lpOut1(0.f)
        , lpOut2(0.f)
        , lpOut3(0.f)
        , lpOut1Delay(0.f)
        , lpOut2Delay(0.f)
        , lpOut3Delay(0.f)
        , pitchModBuffer(1, blockSize)
        , env1Buffer(1, blockSize)
        , lfo1ModBuffer(1, blockSize)
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
        releaseCounter = -1;

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

        // reset attackDecayCounter
        attackDecayCounter = 0;
            break;
        }
        case 2:
        {
            osc1Saw.phase = 0.f;
            osc1Saw.phaseDelta = freqHz * Param::fromCent(params.osc1fine.get()) / sRate * 2.f * float_Pi;
            osc1Saw.trngAmount = params.osc1trngAmount.get();
            attackDecayCounter = 0;
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
        renderModulation(numSamples);
        const float *noMod = noModBuffer.getReadPointer(0);
        const float *pitchMod = pitchModBuffer.getReadPointer(0);
        const float *lfo1Mod = lfo1ModBuffer.getReadPointer(0);
        const float *env1Mod = env1Buffer.getReadPointer(0);

        std::vector<const float*> modSources(2);
        modSources[0] = noMod;
        modSources[1] = lfo1Mod;

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

                currentSample = ladderFilter(biquadFilter(currentSample, modSources[static_cast<int>(params.lpModSource.get())][s], params.passtype.getStep())) * level * env1Mod[s];

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

                if (static_cast<int>(getSampleRate() * params.envRelease.get()) <= releaseCounter) {
                    clearCurrentNote();
                    lfo1sine.reset();
                    lfo1square.reset();
                    break;
                }
            }
        }
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
                else // if attack and decay phase is over then sustain level
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
    @param c counter of the specific phase
    @param t number of samples after which the specific phase should be over
    @param k coeff of growth/shrink, k=1 for linear
    @param slow how fast is phase applied at the start
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
        if (params.lfo1wave.getStep() == eLfoWaves::eLfoSine)
        {
            for (int s = 0; s < numSamples; ++s)
            {
                pitchModBuffer.setSample(0, s, Param::fromSemi(lfo1sine.next()*modAmount) * Param::fromCent(currentPitchInCents));
                lfo1ModBuffer.setSample(0, s, lfo1sine.next()*0.5f);
            }
        }
        else if (params.lfo1wave.getStep() == eLfoWaves::eLfoSampleHold)
        {
            for (int s = 0; s < numSamples; ++s)
            {
                pitchModBuffer.setSample(0, s, Param::fromSemi(lfo1random.next()*modAmount) * Param::fromCent(currentPitchInCents));
                lfo1ModBuffer.setSample(0, s, lfo1random.next()*0.5f);
            }
        }
        else if (params.lfo1wave.getStep() == eLfoWaves::eLfoSquare)
        {
            for (int s = 0; s < numSamples; ++s)
            {
                pitchModBuffer.setSample(0, s, Param::fromSemi(lfo1square.next()*modAmount) * Param::fromCent(currentPitchInCents));
                lfo1ModBuffer.setSample(0, s, lfo1square.next()*0.5f);
            }
        }
    }

    float biquadFilter(float inputSignal, float modValue, eBiquadFilters filterType) {
        const float sRate = static_cast<float>(getSampleRate());
        
        float moddedFreq = filterType == eBiquadFilters::eLowpass 
            ? params.lpCutoff.get()
            : params.hpCutoff.get();

        if (params.lpModSource.getStep() == eModSource::eLFO1) { // bipolar, full range, logarithmic freq domain
            moddedFreq = (params.lpCutoff.get() + (20000.f * std::log2(1+modValue* params.lpModAmout.get() / 100.f)) );
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

    // variables for env
    float currentVelocity;
    float valueAtRelease;
    int attackDecayCounter;
    int releaseCounter;

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
    AudioSampleBuffer env1Buffer;
    AudioSampleBuffer noModBuffer;
};
