#pragma once

#include "JuceHeader.h"
#include <cmath>
#include "SynthParams.h"
#include "ModulationMatrix.h"
#include "Envelope.h"
#include "Oscillator.h"
#include "Filter.h"

class Sound : public SynthesiserSound {
public:
    bool appliesToNote(int /*midiNoteNumber*/) override { return true; }
    bool appliesToChannel(int /*midiChannel*/) override { return true; }
};

class Voice : public SynthesiserVoice {
public:
    Voice(SynthParams &p, int blockSize)
    : params(p)
    , filter({ { {p.filter[0],p.filter[1] },{ p.filter[0],p.filter[1] },{ p.filter[0],p.filter[1] } } })
    , envToVolume(getSampleRate(), params.envVol[0].attack, params.envVol[0].decay, params.envVol[0].sustain, params.envVol[0].release,
        params.envVol[0].attackShape, params.envVol[0].decayShape, params.envVol[0].releaseShape, params.envVol[0].keyVelToEnv)
    , env1(getSampleRate(), params.env[0].attack, params.env[0].decay, params.env[0].sustain, params.env[0].release,
        params.env[0].attackShape, params.env[0].decayShape, params.env[0].releaseShape, params.env[0].keyVelToEnv)
    , modMatrix(p.globalModMatrix)
    , filterModBuffer(1, blockSize)
    , totSamples(0)
    , envToVolBuffer(1, blockSize)
    , lfo1Buffer(1, blockSize)
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
#if 0
        //old sytel for reference!!!!
        //set connection bewtween source and matrix here
        //MIDI
        modSources[SOURCE_PITCHBEND] = &pitchBend;
        modSources[SOURCE_MODWHEEL] = &modWheelValue;
        modSources[SOURCE_FOOT] = &footControlValue;
        modSources[SOURCE_EXPPEDAL] = &expPedalValue;
        modSources[SOURCE_AFTERTOUCH] = &channelAfterTouch;
        //INTERNAL
        modSources[SOURCE_LFO1] = lfo1Buffer.getWritePointer(0);
        //modSources[SOURCE_LFO2] = lfo2Buffer.getWritePointer(0);            /*not yet in use*/
        //modSources[SOURCE_LFO3] = lfo3Buffer.getWritePointer(0);            /*not yet in use*/
        modSources[SOURCE_ENV2] = env2Buffer.getWritePointer(0);
        //modSources[SOURCE_ENV3] = env3Buffer.getWritePointer(0);            /*not yet in use*/
#endif

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
        currentVelocity = velocity;

        totSamples = 0;

        // reset attackDecayCounter
        envToVolume.startEnvelope(currentVelocity);
        env1.startEnvelope(currentVelocity);

        // Initialisieren der Parameter hier
        pitchBend = (currentPitchWheelPosition - 8192.0f) / 8192.0f;
#if 0
        // Initialization of midi values
        modWheelValue = 0.f; // TODO: this needs to be changed to the current value
        footControlValue = 0.f;
        expPedalValue = 0.f;
        channelAfterTouch = 0.f;
#endif
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

        for (auto& filters : filter)
        {
            for (Filter& f : filters)
            {
                f.reset(sRate);
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
            for (Osc& o : osc)
            {
                o.square.reset();
                o.saw.reset();
                o.noise.reset();
            }
        }
    }

    void channelPressureChanged(int newValue) override
    {
        channelAfterTouch = static_cast<float>(newValue) / 127.f;
    }

    void pitchWheelMoved(int newValue) override
    {
        pitchBend = (newValue - 8192.f) / 8192.f;
    }

    //Midi Control
    void controllerMoved(int controllerNumber, int newValue) override
    {
        switch(controllerNumber)
        {
        //Modwheel
        case 1:
            modWheelValue = static_cast<float>(newValue) / 127.f;
            break;
        //Foot Controller
        case 4:
            footControlValue = (static_cast<float>(newValue) / 127.f); //TODO: test
            break;
        //Expression Control
        case 11:
            expPedalValue = static_cast<float>(newValue) / 127.f; //TODO: test
            break;
        }
    }

    void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        // if voice active
        if (lfo1square.isActive() || lfo1sine.isActive()) {

            // Modulation
            renderModulation(numSamples);

#if 0
            //not sure if this is obsolete yet ...
            const float *lfo1 = lfo1Buffer.getReadPointer(0);
            //const float *lfo2 = lfo2Buffer.getReadPointer(0);           /*not yet in use*/
            //const float *lfo3 = lfo3Buffer.getReadPointer(0);           /*not yet in use*/
            const float *filterMod = modDestBuffer.getReadPointer(DEST_FILTER_LC);

            const float currentAmp = params.vol.get();
            const float currentPan = params.panDir.get();
#endif

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
                            //deltaWidth = deltaWidth * shapeMod[s] * params.osc[o].shapeModAmount.get();
                            deltaWidth = deltaWidth * shapeMod[s] * params.osc[o].shapeModAmount1.get();
                            // Next sample will be fetched with the new width
                            currentSample = (osc[o].square.next(pitchMod[s], deltaWidth));
                        }
                            //currentSample = (osc1Sine.next(osc1PitchMod[s]));
                            break;
                        case eOscWaves::eOscSaw:
                        {
                            // In case of triangle modulation
                            float deltaTr = osc[o].saw.trngAmount > .5f
                            ? params.osc[o].trngAmount.getMax() - osc[o].saw.trngAmount
                            : osc[o].saw.trngAmount - params.osc[o].trngAmount.getMin();
                            // LFO mod has values [-1 .. 1], max amp for amount = 1
                            //deltaTr = deltaTr * shapeMod[s] * params.osc[o].shapeModAmount.get();
                            deltaTr = deltaTr * shapeMod[s] * params.osc[o].shapeModAmount1.get();
                            // Next sample will be fetch with the new width
                            currentSample = (osc[o].saw.next(pitchMod[s], deltaTr));
                        }
                            break;
                        case eOscWaves::eOscNoise:
                            currentSample = (osc[o].noise.next(pitchMod[s]));
                            break;
                    }

                    // filter
                    for (size_t f = 0;f < params.filter.size();++f) {
                        const float *filterMod = modDestBuffer.getReadPointer(DEST_FILTER1_LC + f);
                        currentSample = filter[o][f].run(currentSample, filterMod[s]);
                    }

                    // gain + pan
                    currentSample *= envToVolMod[s];
                    const float currentAmp = params.osc[o].vol.get();
                    // check if the output is a stereo output
                    if (outputBuffer.getNumChannels() == 2) {
                        // Pan Influence
                        const float currentPan = params.osc[o].panDir.get();
                        const float currentAmpRight = currentAmp + (currentAmp / 100.f * currentPan);
                        const float currentAmpLeft = currentAmp - (currentAmp / 100.f * currentPan);
                        outputBuffer.addSample(0, startSample + s, currentSample*currentAmpLeft);
                        outputBuffer.addSample(1, startSample + s, currentSample*currentAmpRight);
                    }
                    else
                    {
                        for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {
                            outputBuffer.addSample(c, startSample + s, currentSample * currentAmp);
                        }
                    }

                    if (static_cast<int>(getSampleRate() * params.envVol[0].release.get()) <= envToVolume.getReleaseCounter()) {
                        // next osc
                        break;
                    }
                }
            }

            if (static_cast<int>(getSampleRate() * params.envVol[0].release.get()) <= envToVolume.getReleaseCounter()) {
                clearCurrentNote();
                lfo1sine.reset();
                lfo1square.reset();
            }
        }

        //Update of the total samples variable
        totSamples = totSamples + numSamples;
    }



protected:
    void renderModulation(int numSamples) {

        // LFO Fade IN Variables
        const float sRate = static_cast<float>(getSampleRate());    // Sample rate
        float factorFadeInLFO = 1.f;                                // Defaut value of fade in factor is 1 (100%)
        const int samplesFadeInLFO = static_cast<int>(params.lfo[0].fadeIn.get() * sRate);     // Length in samples of the LFO fade in

        const float lfoGain = params.lfo[0].gainModSrc.get() == eModSource::eNone
        ? 1.f
        : *(modSources[static_cast<int>(params.lfo[0].gainModSrc.get()) - 1]);

        //clear the buffers
        modDestBuffer.clear();
        lfo1Buffer.clear();
        env1Buffer.clear();
        //lfo2Buffer.clear();         /*not yet in use*/
        //lfo3Buffer.clear();         /*not yet in use*/
        //env3Buffer.clear();         /*not yet in use*/

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
                    lfo1Buffer.setSample(0, s, lfo1sine.next() * factorFadeInLFO * lfoGain);
                    break;
                case eLfoWaves::eLfoSampleHold:
                    // lfoValue = lfo1random.next();
                    lfo1Buffer.setSample(0, s, lfo1random.next() * factorFadeInLFO * lfoGain);
                    break;
                case eLfoWaves::eLfoSquare:
                    // lfoValue = lfo1square.next();
                    lfo1Buffer.setSample(0, s, lfo1square.next() * factorFadeInLFO * lfoGain);
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

public:

private:
    SynthParams &params;

    struct Osc {
        Oscillator<&Waveforms::square> square;
        Oscillator<&Waveforms::saw> saw;
        Oscillator<&Waveforms::whiteNoise> noise;
    };

    std::array<Osc, 3> osc;
    std::array<std::array<Filter,2>,3> filter;

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

    //Midi Inputs
    float modWheelValue;
    float footControlValue;
    float expPedalValue;
    float channelAfterTouch;

    // Buffers
    AudioSampleBuffer filterModBuffer;
    AudioSampleBuffer lfo1Buffer;
    AudioSampleBuffer envToVolBuffer;
    AudioSampleBuffer env1Buffer;

    AudioSampleBuffer modDestBuffer;
    //AudioSampleBuffer lfo2Buffer;       /*not yet in use*/
    //AudioSampleBuffer lfo3Buffer;       /*not yet in use*/
    //AudioSampleBuffer env3Buffer;       /*not yet in use*/

    ModulationMatrix& modMatrix;

    // Envelopes
    Envelope envToVolume;
    Envelope env1;
};
