#pragma once

#include "JuceHeader.h"
#include "SynthParams.h"
#include "ModulationMatrix.h"
#include "Envelope.h"
#include "Oscillator.h"

class Sound : public SynthesiserSound {
public:
    bool appliesToNote(int /*midiNoteNumber*/) override { return true; }
    bool appliesToChannel(int /*midiChannel*/) override { return true; }
};

class Voice : public SynthesiserVoice {
public:
    Voice(SynthParams &p, int blockSize)
    : lastSample(0.f)
    , inputDelay1(0.f)
    , inputDelay2(0.f)
    , outputDelay1(0.f)
    , outputDelay2(0.f)
    , bandpassDelay1(0.f)
    , bandpassDelay2(0.f)
    , params(p)
    , envToVolume(getSampleRate(), params.envVol[0].envAttack, params.envVol[0].envDecay, params.envVol[0].envSustain, params.envVol[0].envRelease,
        params.envVol[0].envAttackShape, params.envVol[0].envDecayShape, params.envVol[0].envReleaseShape, params.envVol[0].keyVelToEnv)
    , env1(getSampleRate(), params.env[0].envAttack, params.env[0].envDecay, params.env[0].envSustain, params.env[0].envRelease,
        params.env[0].envAttackShape, params.env[0].envDecayShape, params.env[0].envReleaseShape, params.env[0].keyVelToEnv)
    , ladderOut(0.f)
    , ladderInDelay(0.f)
    , lpOut1(0.f)
    , lpOut2(0.f)
    , lpOut3(0.f)
    , lpOut1Delay(0.f)
    , lpOut2Delay(0.f)
    , lpOut3Delay(0.f)
    , modMatrix(p.globalModMatrix)
    , filterModBuffer(1, blockSize)
    , totSamples(0)
    , envToVolBuffer(1, blockSize)
    , lfo1Buffer(1,blockSize)
    , env1Buffer(1, blockSize)
    , modDestBuffer(destinations::MAX_DESTINATIONS, blockSize)
    {
        // set all to velocity so that the modulation matrix does not crash
        std::fill(modSources.begin(), modSources.end(), &currentVelocity);
        //std::fill(modSources.begin(), modSources.end(), nullptr);
        std::fill(modDestinations.begin(), modDestinations.end(), nullptr);

        //set connection bewtween source and matrix here
        modSources[eModSource::eVelocity] = &currentVelocity;
        modSources[eModSource::ePitchbend] = &pitchBend;
        modSources[eModSource::eLFO1] = lfo1Buffer.getWritePointer(0);
        modSources[eModSource::eVolEnv] = env1Buffer.getWritePointer(0);

        //set connection between destination and matrix here
        for (size_t u = 0; u < MAX_DESTINATIONS; ++u) {
            modDestinations[u] = modDestBuffer.getWritePointer(u);
        }
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

        totSamples = 0;

        // reset attackDecayCounter
        envToVolume.startEnvelope(currentVelocity);
        env1.startEnvelope(currentVelocity);

        // Initialisieren der Parameter hier
        pitchBend = (currentPitchWheelPosition - 8192.0f) / 8192.0f;

        const float sRate = static_cast<float>(getSampleRate());
        float freqHz = static_cast<float>(MidiMessage::getMidiNoteInHertz(midiNoteNumber, params.freq.get()));

        // change the phases of both lfo waveforms, in case the user switches them during a note

        if (params.lfo[0].tempSync.get() == 1.f) {

            lfo1sine.phase = .5f*float_Pi;
            lfo1square.phase = 0.f;
            lfo1random.phase = 0.f;

            lfo1sine.phaseDelta = static_cast<float>(params.positionInfo[params.getGUIIndex()].bpm) / (60.f*sRate)*(params.lfo[0].noteLength.get() / 4.f)*2.f*float_Pi;
            lfo1square.phaseDelta = static_cast<float>(params.positionInfo[params.getGUIIndex()].bpm) / (60.f*sRate)*(params.lfo[0].noteLength.get() / 4.f)*2.f*float_Pi;
            lfo1random.phaseDelta = static_cast<float>(params.positionInfo[params.getGUIIndex()].bpm) / (60.f*sRate)*(params.lfo[0].noteLength.get() / 4.f)*2.f*float_Pi;
            lfo1random.heldValue = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f)) - 1.f;
        }
        else{

            lfo1sine.phase = .5f*float_Pi;
            lfo1sine.phaseDelta = params.lfo[0].freq.get() / sRate * 2.f * float_Pi;
            lfo1square.phase = .5f*float_Pi;
            lfo1square.phaseDelta = params.lfo[0].freq.get() / sRate * 2.f * float_Pi;

            lfo1random.phase = 0.f;
            lfo1random.phaseDelta = params.lfo[0].freq.get() / sRate * 2.f * float_Pi;
            lfo1random.heldValue = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2.f)) - 1.f;
        }

        for (size_t o=0; o < params.osc.size(); ++o) {
            osc[o].level = Param::fromDb((velocity - 1.f) * params.osc[o].volModAmount1.get());

            switch (params.osc[o].waveForm.getStep())
            {
            case eOscWaves::eOscSquare:
                osc[o].square.phase = 0.f;
                osc[o].square.phaseDelta = freqHz * Param::fromCent(params.osc[o].fine.get()) * Param::fromSemi(params.osc[o].coarse.get()) / sRate * 2.f * float_Pi;
                osc[o].square.width = params.osc[o].pulseWidth.get();
                break;
            case eOscWaves::eOscSaw:
                osc[o].saw.phase = 0.f;
                osc[o].saw.phaseDelta = freqHz * Param::fromCent(params.osc[o].fine.get()) * Param::fromSemi(params.osc[o].coarse.get()) / sRate * 2.f * float_Pi;
                osc[o].saw.trngAmount = params.osc[o].trngAmount.get();
                break;
            case eOscWaves::eOscNoise:
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
            {                                               // stopNote method could be called more than once.
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
            for (Osc& o : osc) {
                o.square.reset();
                o.saw.reset();
                o.noise.reset();
            }
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
        // if voice active
        if (lfo1square.isActive() || lfo1sine.isActive()) {

            // Modulation
            renderModulation(numSamples);
            const float *envToVolMod = envToVolBuffer.getReadPointer(0);

            // oscillators
            for (size_t o = 0; o < params.osc.size(); ++o) {

                const float *pitchMod = modDestBuffer.getReadPointer(DEST_OSC1_PI + o);
                const float *shapeMod = modDestBuffer.getReadPointer(DEST_OSC1_PW + o);

                for (int s = 0; s < numSamples; ++s) {
                    float currentSample = 0.0f;

                    switch (params.osc[o].waveForm.getStep())
                    {
                    case eOscWaves::eOscSquare:
                    {
                        // In case of pulse width modulation
                        float deltaWidth = osc[o].square.width > .5f
                            ? params.osc[o].pulseWidth.getMax() - osc[o].square.width
                            : osc[o].square.width - params.osc[o].pulseWidth.getMin();
                        // Pulse width must not reach 0 or 1
                        if (deltaWidth > (.5f - params.osc[o].pulseWidth.getMin()) && deltaWidth < (.5f + params.osc[o].pulseWidth.getMin())) {
                            deltaWidth = .49f;
                        }
                        // LFO mod has values [-1 .. 1], max amp for amount = 1
                        deltaWidth = deltaWidth * shapeMod[s] * params.osc[o].shapeModAmount.get();
                        // Next sample will be fetched with the new width
                        currentSample = (osc[o].square.next(pitchMod[s], deltaWidth));
                    }
                        break;
                    case eOscWaves::eOscSaw:
                    {
                        // In case of triangle modulation
                        float deltaTr = osc[o].saw.trngAmount > .5f
                            ? params.osc[o].trngAmount.getMax() - osc[o].saw.trngAmount
                            : osc[o].saw.trngAmount - params.osc[o].trngAmount.getMin();
                        // LFO mod has values [-1 .. 1], max amp for amount = 1
                        deltaTr = deltaTr * shapeMod[s] * params.osc[o].shapeModAmount.get();
                        // Next sample will be fetch with the new width
                        currentSample = (osc[o].saw.next(pitchMod[s], deltaTr));
                    }
                        break;
                    case eOscWaves::eOscNoise:
                        currentSample = (osc[o].noise.next(pitchMod[s]));
                        break;
                    }

#if 0
                    // filter
                    const float *filterMod = modDestBuffer.getReadPointer(DEST_FILTER1_LC);
                    if (params.filter[0].passtype.getStep() == eBiquadFilters::eLadder) {
                        currentSample = ladderFilter(currentSample, filterMod[s]);
                    } else {
                        currentSample = biquadFilter(currentSample, filterMod[s]);
                    }
#endif

                    // gain + pan
                    currentSample *= (osc[o].level * envToVolMod[s]);
                    const float currentAmp = params.osc[o].vol.get();
                    // check if the output is a stereo output
                    if (outputBuffer.getNumChannels() == 2) {
                        // Pan Influence
                        const float currentPan = params.osc[o].panDir.get();
                        const float currentAmpRight = currentAmp + (currentAmp / 100.f * currentPan);
                        const float currentAmpLeft = currentAmp - (currentAmp / 100.f * currentPan);
                        outputBuffer.addSample(0, startSample + s, currentSample*currentAmpLeft);
                        outputBuffer.addSample(1, startSample + s, currentSample*currentAmpRight);
                    } else {
                        for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {
                            outputBuffer.addSample(c, startSample + s, currentSample * currentAmp);
                        }
                    }
                }
            }

            if (static_cast<int>(getSampleRate() * params.envVol[0].envRelease.get()) <= envToVolume.getReleaseCounter()) {
                clearCurrentNote();
                lfo1sine.reset();
                lfo1square.reset();
            }
        }
        //Update of the total samples variable
        totSamples = totSamples + numSamples;
    }

    //apply ladder filter to the current Sample in renderNextBlock() - Zavalishin approach
    //naive 1 pole filters wigh a hyperbolic tangent saturator
    float ladderFilter(float ladderIn, float modValue)
    {
        const float sRate = static_cast<float>(getSampleRate());

        float cutoffFreq = params.filter[0].lpCutoff.get();
        float currentResonance = params.filter[0].resonance.get();

        cutoffFreq = Param::bipolarToFreq(modValue, cutoffFreq, 8.f);

        // TODO can't this be shortened?
        if (cutoffFreq < params.filter[0].lpCutoff.getMin()) { // assuming that min/max are identical for low and high pass filters
            cutoffFreq = params.filter[0].lpCutoff.getMin();
        }
        else if (cutoffFreq > params.filter[0].lpCutoff.getMax()) {
            cutoffFreq = params.filter[0].lpCutoff.getMax();
        }

        //coeffecients and parameters
        float omega_c = 2.f * float_Pi * cutoffFreq / sRate;
        float g = omega_c / 2.f;
        float a = (1.f - g) / (1.f + g);
        float b = g / (1.f + g);

        // subtract the feedback
        // inverse hyperbolic Sinus
        // ladderIn = tanh(ladderIn) - asinh(currentResonance * ladderOut);
        // hyperbolic tangent
        ladderIn = tanh(ladderIn) - tanh(currentResonance * ladderOut);

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
        const int samplesFadeInLFO = static_cast<int>(params.lfo[0].fadeIn.get() * sRate);     // Length in samples of the LFO fade in

        //clear the buffers
        modDestBuffer.clear();
        lfo1Buffer.clear();
        env1Buffer.clear();

        //set the write point in the buffers
        for (size_t u = 0; u < MAX_DESTINATIONS; ++u) {
            modDestinations[u] = modDestBuffer.getWritePointer(u);
        }
        modSources[eModSource::eLFO1] = lfo1Buffer.getWritePointer(0);
        modSources[eModSource::eVolEnv] = env1Buffer.getWritePointer(0);

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
            switch (params.lfo[0].wave.getStep()) {
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

            modMatrix.doModulationsMatrix(&*modSources.begin(), &*modDestinations.begin());

            for (size_t u = 0; u < MAX_DESTINATIONS; ++u) {
                ++modDestinations[u];
            }
            ++modSources[eModSource::eLFO1];
            ++modSources[eModSource::eVolEnv];
        }

        //! \todo 12 st must come from somewhere else, e.g. max value of the respective Param
        //! \todo check whether this should be at the place where the values are actually used
        for (int s = 0; s < numSamples; ++s) {
            modDestBuffer.setSample(DEST_OSC1_PI, s, Param::fromSemi(modDestBuffer.getSample(DEST_OSC1_PI, s) * 12.f));
            modDestBuffer.setSample(DEST_OSC2_PI, s, Param::fromSemi(modDestBuffer.getSample(DEST_OSC2_PI, s) * 12.f));
            modDestBuffer.setSample(DEST_OSC3_PI, s, Param::fromSemi(modDestBuffer.getSample(DEST_OSC2_PI, s) * 12.f));
        }
    }

    float biquadFilter(float inputSignal, float modValue) {

        // get mod frequency from active filter type
        float cutoffFreq;
        switch (params.filter[0].passtype.getStep()) {
            case eBiquadFilters::eLowpass:
                cutoffFreq = params.filter[0].lpCutoff.get();
                break;
            case eBiquadFilters::eHighpass:
                cutoffFreq = params.filter[0].hpCutoff.get();
                break;
            case eBiquadFilters::eBandpass:
                cutoffFreq = (params.filter[0].lpCutoff.get() + params.filter[0].hpCutoff.get()) / 2.f;
                if (params.filter[0].lpCutoff.get() < params.filter[0].hpCutoff.get()){
                    return 0.f;
                }
                break;
            default: // should never happen if everybody uses it correctly! but in case it does, don't crash but return no sound instead
                return 0.f;
        }

        //! \todo mod range must come from somewhere else
        cutoffFreq = Param::bipolarToFreq(modValue, cutoffFreq, 8.f);

        // check range
        if (cutoffFreq < params.filter[0].lpCutoff.getMin()) { // assuming that min/max are identical for low and high pass filters
            cutoffFreq = params.filter[0].lpCutoff.getMin();
        }
        else if (cutoffFreq > params.filter[0].lpCutoff.getMax()) {
            cutoffFreq = params.filter[0].lpCutoff.getMax();
        }

        const float sRate = static_cast<float>(getSampleRate());
        cutoffFreq /= sRate;

        // LP and HP: Filter Design: Biquad (2 delays) Source: http://www.musicdsp.org/showArchiveComment.php?ArchiveID=259
        // BP: based on http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt, except for bw calculation
        float k, coeff1, coeff2, coeff3, b0 = 0.0f, b1 = 0.0f, b2 = 0.0f, a0 = 0.0f, a1 = 0.0f, a2 = 0.0f, bw, w0;

        const float currentResonance = pow(10.f, (-params.filter[0].resonance.get() * 2.5f) / 20.f); /*so ist die resonanz bei 10 maximal*/

        if (static_cast<eBiquadFilters>(params.filter[0].passtype.getStep()) == eBiquadFilters::eLowpass) {

            // coefficients for lowpass, depending on resonance and lowcut frequency
            k = 0.5f * currentResonance * sin(2.f * float_Pi * cutoffFreq);
                coeff1 = 0.5f * (1.f - k) / (1.f + k);
            coeff2 = (0.5f + coeff1) * cos(2.f * float_Pi * cutoffFreq);
                    coeff3 = (0.5f + coeff1 - coeff2) * 0.25f;

            b0 = 2.f * coeff3;
            b1 = 2.f * 2.f * coeff3;
            b2 = 2.f * coeff3;
            a1 = 2.f * -coeff2;
            a2 = 2.f * coeff1;

        } else if (params.filter[0].passtype.getStep() == eBiquadFilters::eHighpass) {

            // coefficients for highpass, depending on resonance and highcut frequency
            k = 0.5f * currentResonance * sin(float_Pi * cutoffFreq);
            coeff1 = 0.5f * (1.f - k) / (1.f + k);
            coeff2 = (0.5f + coeff1) * cos(float_Pi * cutoffFreq);
            coeff3 = (0.5f + coeff1 + coeff2) * 0.25f;

            b0 = 2.f * coeff3;
            b1 = -4.f * coeff3;
            b2 = 2.f * coeff3;
            a1 = -2.f * coeff2;
            a2 = 2.f * coeff1;

        } else if (params.filter[0].passtype.getStep() == eBiquadFilters::eBandpass) {

            // coefficients for bandpass, depending on low- and highcut frequency
            w0 = 2.f * float_Pi*cutoffFreq;
            bw = (log2(params.filter[0].lpCutoff.get() / params.filter[0].hpCutoff.get())); // bandwidth in octaves
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
        if (params.filter[0].passtype.getStep() == eBiquadFilters::eBandpass) {
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

public:

private:
    SynthParams &params;
    //New Filter Design
    float lastSample, inputDelay1, inputDelay2, outputDelay1, outputDelay2, bandpassDelay1, bandpassDelay2;

    struct Osc {
        Oscillator<&Waveforms::square> square;
        Oscillator<&Waveforms::saw> saw;
        Oscillator<&Waveforms::whiteNoise> noise;
        float level;
    };
    std::array<Osc, 3> osc;

    Oscillator<&Waveforms::sinus> lfo1sine;
    Oscillator<&Waveforms::square> lfo1square;
    RandomOscillator<&Waveforms::square> lfo1random;

    float pitchBend;
    //float currentPitchInCents;
    //float lfoValue;
    //float env1Coeff;

    std::array<float*, eModSource::nSteps> modSources;
    std::array<float*, MAX_DESTINATIONS> modDestinations;

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
    AudioSampleBuffer filterModBuffer;
    AudioSampleBuffer lfo1Buffer;
    AudioSampleBuffer envToVolBuffer;
    AudioSampleBuffer env1Buffer;

    AudioSampleBuffer modDestBuffer;

    ModulationMatrix& modMatrix;

    // Envelopes
    Envelope envToVolume;
    Envelope env1;
};
