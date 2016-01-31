#pragma once

#include "JuceHeader.h"
#include "SynthParams.h"
#include "ModulationMatrix.h"
#include "Envelope.h"
/*the following is for the leak detector, vld must be installed on the computer
    and path must be added to library path!!*/
//#include "vld.h"

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
        if (phs < trngAmount*float_Pi) { return (1.f - 2.f / (trngAmount*float_Pi) * phs); }
        else { return (-1.f + 2.f / (2.f*float_Pi - trngAmount*float_Pi) * (phs - trngAmount*float_Pi)); }
    }
    
    static float whiteNoise(float phs, float trngAmount, float width) {
        return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f)) - 1.f;
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
    Voice(SynthParams &p, int blockSize, ModulationMatrix *globalModMatrix_)
    : lastSample(0.f)
    , inputDelay1(0.f)
    , inputDelay2(0.f)
    , outputDelay1(0.f)
    , outputDelay2(0.f)
    , bandpassDelay1(0.f)
    , bandpassDelay2(0.f)
    , params(p)
    , envToVolume(getSampleRate(), params.envAttack, params.envDecay, params.envSustain, params.envRelease,
        params.envAttackShape, params.envDecayShape, params.envReleaseShape, params.keyVelToEnv)
    , env1(getSampleRate(), params.env1Attack, params.env1Decay, params.env1Sustain, params.env1Release,
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
    , modMatrix(globalModMatrix_) //local Matrix initialisation
    , osc1PitchModBuffer(1, blockSize)
    , filterModBuffer(1, blockSize)
    , totSamples(0)
    , envToVolBuffer(1, blockSize)
    , lfo1Buffer(1,blockSize)
    , env1Buffer(1, blockSize)
    , noModBuffer(1, blockSize)
    {
        noModBuffer.clear();
        
        for(float*& pSource : modSources) {
            pSource = nullptr;
        }
        for(float*& pDest : modDestinations) {
            pDest = nullptr;
        }

        //set connection bewtween source and matrix here
        modSources[SOURCE_LFO1] = lfo1Buffer.getWritePointer(0);
        modSources[SOURCE_ENV1] = env1Buffer.getWritePointer(0);
        
        //set connection between destination and matrix here
        modDestinations[DEST_OSC1_PITCH] = osc1PitchModBuffer.getWritePointer(0);
        modDestinations[DEST_FILT_FC] = filterModBuffer.getWritePointer(0);
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

        bandpassDelay1 = 0.f;
        bandpassDelay2 = 0.f;

        currentVelocity = velocity;

        level = Param::fromDb((velocity - 1.f) * params.keyVelocityLevel.get());

        totSamples = 0;

        // reset attackDecayCounter
        envToVolume.startEnvelope(currentVelocity);
        env1.startEnvelope(currentVelocity);

        // Initialisieren der Parameter hier
        pitchBend = (currentPitchWheelPosition - 8192.0f) / 8192.0f;

        const float sRate = static_cast<float>(getSampleRate());
        float freqHz = static_cast<float>(MidiMessage::getMidiNoteInHertz(midiNoteNumber, params.freq.get()));

        // change the phases of both lfo waveforms, in case the user switches them during a note

        if (params.lfo1TempSync.get() == 1.f) {

            lfo1sine.phase = .5f*float_Pi;
            lfo1square.phase = 0.f;
            lfo1random.phase = 0.f;

            lfo1sine.phaseDelta = params.positionInfo[params.getGUIIndex()].bpm / (60.f*sRate)*(params.noteLength.get() / 4.f)*2.f*float_Pi;
            lfo1square.phaseDelta = params.positionInfo[params.getGUIIndex()].bpm / (60.f*sRate)*(params.noteLength.get() / 4.f)*2.f*float_Pi;
            lfo1random.phaseDelta = params.positionInfo[params.getGUIIndex()].bpm / (60.f*sRate)*(params.noteLength.get() / 4.f)*2.f*float_Pi;
            lfo1random.heldValue = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f)) - 1.f;
        }
        else {

            lfo1sine.phase = .5f*float_Pi;
            lfo1sine.phaseDelta = params.lfo1freq.get() / sRate * 2.f * float_Pi;
            lfo1square.phase = .5f*float_Pi;
            lfo1square.phaseDelta = params.lfo1freq.get() / sRate * 2.f * float_Pi;
        
            lfo1random.phase = 0.f;
            lfo1random.phaseDelta = params.lfo1freq.get() / sRate * 2.f * float_Pi;
            lfo1random.heldValue = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2.f)) - 1.f;
        }

        switch (params.osc1Waveform.getStep())
        {
            case eOscWaves::eOscSquare:
            {
                osc1Sine.phase = 0.f;
                osc1Sine.phaseDelta = freqHz * (Param::fromCent(params.osc1fine.get()) * Param::fromSemi(params.osc1coarse.get())) / sRate * 2.f * float_Pi;
                osc1Sine.width = params.osc1pulsewidth.get();
                lfo1square.width = params.osc1pulsewidth.get();
                //osc1.phaseDelta = freqHz * Param::fromCent(params.osc1fine.get()) / sRate * 2.f * float_Pi;
                break;
            }
            case eOscWaves::eOscSaw:
            {
                osc1Saw.phase = 0.f;
                osc1Saw.phaseDelta = freqHz * Param::fromCent(params.osc1fine.get()) / sRate * 2.f * float_Pi;
                osc1Saw.trngAmount = params.osc1trngAmount.get();
                break;
            }
            case eOscWaves::eOscNoise:
            {
                osc1WhiteNoise.phase = 0.f;
                osc1WhiteNoise.phaseDelta = freqHz * Param::fromCent(params.osc1fine.get()) / sRate * 2.f * float_Pi;
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

            if (env1.getReleaseCounter() == -1)
            {
                env1.resetReleaseCounter();
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
            osc1WhiteNoise.reset();
        }
    }

    void pitchWheelMoved(int newValue) override
    {
        pitchBend = (newValue - 8192.f) / 8192.f;
    }

    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override
    {
        // not interested in controllers in this case.
    }

    void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        // Modulation
        renderModulation(numSamples);
        const float *noMod = noModBuffer.getReadPointer(0);
        const float *osc1PitchMod = osc1PitchModBuffer.getReadPointer(0);
        const float *envToVolMod = envToVolBuffer.getReadPointer(0);
        
        // Not using the following in the same manner as before, everything is part of the pitchmod now!
        //const float *lfo1Mod = lfo1ModBuffer.getReadPointer(0);
        //const float *env1Mod = env1Buffer.getReadPointer(0);

#if 0
        // this probably will be obsolete ...
        std::vector<const float*> modSources(3);
        modSources[0] = noMod;
        modSources[1] = lfo1Mod;
        modSources[2] = env1Mod;
#endif

        const float currentAmp = params.vol.get();
        const float currentPan = params.panDir.get();

        // Pan Influence
        const float currentAmpRight = currentAmp + (currentAmp / 100.f * currentPan);
        const float currentAmpLeft = currentAmp - (currentAmp / 100.f * currentPan);

        if (lfo1square.isActive() || lfo1sine.isActive()) {
            for (int s = 0; s < numSamples; ++s) {
                //const float currentSample = (osc1.next(pitchMod[s])) * level * tailOff * currentAmp;
                
                float currentSample;
                switch (params.osc1Waveform.getStep())
                {
                case eOscWaves::eOscSquare:
                    currentSample = (osc1Sine.next(osc1PitchMod[s]));
                    break;
                case eOscWaves::eOscSaw:
                    currentSample = (osc1Saw.next(osc1PitchMod[s]));
                    break;
                case eOscWaves::eOscNoise:
                    currentSample = (osc1WhiteNoise.next(osc1PitchMod[s]));
                    break;
                }

                currentSample = biquadFilter(currentSample, params.passtype.getStep());
                currentSample = ladderFilter(currentSample) * level * envToVolMod[s];

                //check if the output is a stereo output
                if (outputBuffer.getNumChannels() == 2) {
                    outputBuffer.addSample(0, startSample + s, currentSample*currentAmpLeft);
                    outputBuffer.addSample(1, startSample + s, currentSample*currentAmpRight);
                }
                else 
                {
                    for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {
                        outputBuffer.addSample(c, startSample + s, currentSample * currentAmp);
                    }
                }
                if (static_cast<int>(getSampleRate() * params.envRelease.get()) <= envToVolume.getReleaseCounter() || static_cast<int>(getSampleRate() * params.env1Release.get()) <= env1.getReleaseCounter())
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

void renderModulation(int numSamples) {

        // LFO Fade IN Variables
        const float sRate = static_cast<float>(getSampleRate());    // Sample rate
        float factorFadeInLFO = 1.f;                                // Defaut value of fade in factor is 1 (100%)
        const int samplesFadeInLFO = static_cast<int>(params.lfoFadein.get() * sRate);     // Length in samples of the LFO fade in

        //clear the buffers
        osc1PitchModBuffer.clear();
        filterModBuffer.clear();
        lfo1Buffer.clear();
        env1Buffer.clear();

        //set the write point in the buffers
        modDestinations[DEST_OSC1_PITCH] = osc1PitchModBuffer.getWritePointer(0);
        modDestinations[DEST_FILT_FC] = filterModBuffer.getWritePointer(0);
        modSources[SOURCE_ENV1] = env1Buffer.getWritePointer(0);
        modSources[SOURCE_LFO1] = lfo1Buffer.getWritePointer(0);
        
        for (int s = 0; s < numSamples; ++s) {

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

            // calculate lfo values and fill the buffers
            // lfoValue = 0.f;
            switch (params.lfo1wave.getStep()) {
            case eLfoWaves::eLfoSine:
                // lfoValue = lfo1sine.next();
                lfo1Buffer.setSample(0, s, lfo1sine.next() * factorFadeInLFO);
                break;
            case eLfoWaves::eLfoSampleHold:
                // lfoValue = lfo1random.next();
                lfo1Buffer.setSample(0, s, lfo1random.next() * factorFadeInLFO);
                break;
            case eLfoWaves::eLfoSquare:
                // lfoValue = lfo1square.next();
                lfo1Buffer.setSample(0, s, lfo1square.next() * factorFadeInLFO);
                break;
            }

            // Calculate the Envelope coefficients and fill the buffers
            env1Buffer.setSample(0, s, env1.calcEnvCoeff());
            envToVolBuffer.setSample(0, s, envToVolume.calcEnvCoeff());
        }

        //calculate modulation values for the buffers
        for (int s = 0; s < numSamples; ++s) {
        
            modMatrix->doModulationsMatrix(0, modSources, modDestinations);

            ++modDestinations[DEST_OSC1_PITCH];
            ++modDestinations[DEST_FILT_FC];
            ++modSources[SOURCE_ENV1];
            ++modSources[SOURCE_LFO1];
        }


        //case example: LFO/Envelope and PitchBend have influence on the pitch
        for (int s = 0; s < numSamples; ++s) {

            osc1PitchModBuffer.setSample(0, s, Param::fromSemi(osc1PitchModBuffer.getSample(0,s) * 12.f) * Param::fromCent(params.osc1PitchRange.get() * 100 * pitchBend));
        }
}


float biquadFilter(float inputSignal, eBiquadFilters filterType) {
    
    const float sRate = static_cast<float>(getSampleRate());

    float currentCutoff = filterType == eBiquadFilters::eLowpass
        ? params.lpCutoff.get()
        : params.hpCutoff.get();

        modMatrix->destinations[DEST_FILT_FC] = currentCutoff;
        //float testVal = localModMatrix->destinations[DEST_FILT_FC];
        //float moddedMaxFreq = params.lpCutoff.getMax() * localModMatrix->destinations[DEST_FILT_FC];

        //float moddedMaxFreq = params.lpCutoff.getMax() * params.lpModAmout.get() / 100.f;

        return inputSignal;
}

#if 0
    float biquadFilter(float inputSignal, float modValue, eBiquadFilters filterType) {
        const float sRate = static_cast<float>(getSampleRate());
        
        float moddedFreq;
        switch (filterType) {
            case eBiquadFilters::eLowpass:
                moddedFreq = params.lpCutoff.get();
                break;
            case eBiquadFilters::eHighpass:
                moddedFreq = params.hpCutoff.get();
                break;
            case eBiquadFilters::eBandpass:
                moddedFreq = (params.lpCutoff.get() + params.hpCutoff.get()) / 2.f;
                if (params.lpCutoff.get() < params.hpCutoff.get()){
                    return 0.f;
                }
                break;
            default: // should never happen if everybody uses it correctly! but in case it does, don't crash but return no sound instead 
                return 0.f;
        }

        float moddedMaxFreq = params.lpCutoff.getMax() * params.lpModAmount.get() / 100.f;
        
        if (params.lpModSource.getStep() == eModSource::eLFO1) { // bipolar, full range
            moddedFreq += (20000.f * (modValue) * params.lpModAmount.get() / 100.f);
        }
        else if (params.lpModSource.getStep() == eModSource::eEnv) { // env

            moddedFreq += moddedFreq + (params.lpCutoff.getMax() - moddedFreq) * modValue * params.lpModAmount.get() / 100.f;
        }
        
        if (moddedFreq < params.lpCutoff.getMin()) { // assuming that min/max are identical for low and high pass filters
            moddedFreq = params.lpCutoff.getMin();
        }
        else if (moddedFreq > params.lpCutoff.getMax()) {
            moddedFreq = params.lpCutoff.getMax();
        }
        
        moddedFreq /= sRate;

        // LP and HP: Filter Design: Biquad (2 delays) Source: http://www.musicdsp.org/showArchiveComment.php?ArchiveID=259
        // BP: based on http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt, except for bw calculation
        float k, coeff1, coeff2, coeff3, b0, b1, b2, a0, a1, a2, bw, w0;

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
        } else if (filterType == eBiquadFilters::eBandpass) {
            // coefficients for bandpass, depending on low- and highcut frequency
            w0 = 2.f * float_Pi*moddedFreq;
            bw = (log2(params.lpCutoff.get() / params.hpCutoff.get())); // bandwidth in octaves
            coeff1 = sin(w0)*sinh(log10(2.f) / 2.f * bw * w0 / sin(w0)); // intermediate value for coefficient calc

            b0 = coeff1;
            b1 = 0.f;
            b2 = -coeff1;
            a0 = 1.f + coeff1;
            a1 = -2.f * cos(w0);
            a2 = 1.f - coeff1;
        }

        lastSample = inputSignal;
        
        // different biquad form for bandpass filter, it has more coefficients as well
        if (filterType == eBiquadFilters::eBandpass) {
            inputSignal = (b0 / a0)* inputSignal + (b1 / a0)*inputDelay1 + (b2 / a0)*inputDelay2 - (a1 / a0)*outputDelay1 - (a2 / a0)*outputDelay2;
        } else {
        inputSignal = b0*inputSignal + b1*inputDelay1 + b2*inputDelay2 - a1*outputDelay1 - a2*outputDelay2;
        }
        
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
#endif 

public:

private:
    SynthParams &params;
    //New Filter Design
    float lastSample, inputDelay1, inputDelay2, outputDelay1, outputDelay2, bandpassDelay1, bandpassDelay2;
    
    Oscillator<&Waveforms::square> osc1Sine;
    Oscillator<&Waveforms::saw> osc1Saw;
    Oscillator<&Waveforms::whiteNoise> osc1WhiteNoise;

    Oscillator<&Waveforms::sinus> lfo1sine;
    Oscillator<&Waveforms::square> lfo1square;
    RandomOscillator<&Waveforms::square> lfo1random;
    
    float level;

    float pitchBend;
    //float currentPitchInCents;
    //float lfoValue;
    //float env1Coeff;
    
    float* modSources[MAX_SOURCES];
    float* modDestinations[MAX_DESTINATIONS];
    
    int totSamples;

    // variable for env
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

    // Buffers
    AudioSampleBuffer osc1PitchModBuffer;
    AudioSampleBuffer filterModBuffer;
    AudioSampleBuffer lfo1Buffer;
    AudioSampleBuffer noModBuffer;
    AudioSampleBuffer envToVolBuffer;
    AudioSampleBuffer env1Buffer;
    
    ModulationMatrix* modMatrix; //pointer to the global Matrix
    //modMatrixRow* modMatrixRow;
    float filter1Fc;

    // Envelopes 
    Envelope envToVolume;
    Envelope env1;
};
