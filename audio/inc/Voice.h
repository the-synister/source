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

struct Lfo {
    Lfo(int blockSize)
        : audioBuffer(1, blockSize)
    {
        reset();
    }
    Oscillator<&Waveforms::sinus> sine;
    Oscillator<&Waveforms::square> square;
    RandomOscillator<&Waveforms::square> random;
    AudioSampleBuffer audioBuffer;
    
    void reset() {
        sine.reset();
        square.reset();
        random.reset();
    }
};

class Voice : public SynthesiserVoice {
public:
    Voice(SynthParams &p, int blockSize)
    : params(p)
    , filter({ { {p.filter[0],p.filter[1] },{ p.filter[0],p.filter[1] },{ p.filter[0],p.filter[1] } } })
    , envToVolume(p.envVol[0], p.envVol[0].sustain, getSampleRate())
    , env2(p.env[0], p.env[0].sustain, getSampleRate())
    , env3(p.env[1], p.env[1].sustain, getSampleRate())
    , modMatrix(p.globalModMatrix)
    , envToVolBuffer(1, blockSize)
    , env2Buffer(1, blockSize)
    , env3Buffer(1, blockSize)
    , zeroMod(0.f)
    , totalVoiceSamples(0)
    , modDestBuffer(destinations::MAX_DESTINATIONS, blockSize)
    , lfo({ { { blockSize},{ blockSize },{ blockSize } } })
    {
        std::fill(modSources.begin(), modSources.end(), &zeroMod);
        std::fill(modDestinations.begin(), modDestinations.end(), nullptr);

        //set connection bewtween source and matrix here
        // midi
        modSources[eModSource::eAftertouch] = &channelAfterTouch;
        modSources[eModSource::eKeyBipolar] = &keyBipolar;
        modSources[eModSource::eInvertedVelocity] = &currentInvertedVelocity;
        modSources[eModSource::eVelocity] = &currentVelocity;
        modSources[eModSource::eFoot] = &footControlValue;
        modSources[eModSource::eExpPedal] = &expPedalValue;
        modSources[eModSource::eModwheel] = &modWheelValue;
        modSources[eModSource::ePitchbend] = &pitchBend;
        // internal
        modSources[eModSource::eLFO1] = lfo[0].audioBuffer.getWritePointer(0);
        modSources[eModSource::eLFO2] = lfo[1].audioBuffer.getWritePointer(0);
        modSources[eModSource::eLFO3] = lfo[2].audioBuffer.getWritePointer(0);
        modSources[eModSource::eVolEnv] = envToVolBuffer.getWritePointer(0);
        modSources[eModSource::eEnv2] = env2Buffer.getWritePointer(0);
        modSources[eModSource::eEnv3] = env3Buffer.getWritePointer(0);

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
        SynthesiserSound*, int currentPitchWheelPosition) override {

        totalVoiceSamples = 0;

        // Initialization of midi values
        channelAfterTouch = params.midiState.get(MidiState::eAftertouch)/128.f;
        keyBipolar = (static_cast<float>(midiNoteNumber) - 64.f) / 64.f;
        currentInvertedVelocity = 1.f - velocity;
        currentVelocity = velocity;
        footControlValue = params.midiState.get(MidiState::eFoot) / 128.f;
        expPedalValue = params.midiState.get(MidiState::eExpPedal) / 128.f;
        modWheelValue = params.midiState.get(MidiState::eModwheel) / 128.f;
        pitchBend = (currentPitchWheelPosition - 8192.0f) / 8192.0f;

        const float sRate = static_cast<float>(getSampleRate());
        const float bpm = static_cast<float>(params.positionInfo[params.getGUIIndex()].bpm);
        float freqHz = static_cast<float>(MidiMessage::getMidiNoteInHertz(midiNoteNumber, params.freq.get()));

        // change the phases of both lfo waveforms, in case the user switches them during a note
        for (size_t l = 0; l < lfo.size(); ++l) {
            if (params.lfo[l].tempSync.getStep() == eOnOffToggle::eOn) {

                float coeff = 1.0f;
                if (params.lfo[l].lfoDottedLength.getStep() == eOnOffToggle::eOn) {
                    coeff /= 1.5f;
                }
                if (params.lfo[l].lfoTriplets.getStep() == eOnOffToggle::eOn) {
                    coeff /= (2.0f / 3.0f);
                }

                lfo[l].sine.phase = .5f*float_Pi;
                lfo[l].square.phase = 0.f;
                lfo[l].random.phase = 0.f;

                lfo[l].sine.phaseDelta = static_cast<float>(params.positionInfo[params.getGUIIndex()].bpm) /
                    (60.f*sRate)*(params.lfo[l].noteLength.get() / 4.f)*2.f*float_Pi * coeff;
                lfo[l].square.phaseDelta = static_cast<float>(params.positionInfo[params.getGUIIndex()].bpm) /
                    (60.f*sRate)*(params.lfo[l].noteLength.get() / 4.f)*2.f*float_Pi * coeff;
                lfo[l].random.phaseDelta = static_cast<float>(params.positionInfo[params.getGUIIndex()].bpm) /
                    (60.f*sRate)*(params.lfo[l].noteLength.get() / 4.f)*2.f*float_Pi * coeff;
                lfo[l].random.heldValue = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f)) - 1.f;
            } else {
                lfo[l].sine.phase = .5f*float_Pi;
                lfo[l].sine.phaseDelta = params.lfo[l].freq.get() / sRate * 2.f * float_Pi;
                lfo[l].square.phase = .5f*float_Pi;
                lfo[l].square.phaseDelta = params.lfo[l].freq.get() / sRate * 2.f * float_Pi;

                lfo[l].random.phase = 0.f;
                lfo[l].random.phaseDelta = params.lfo[l].freq.get() / sRate * 2.f * float_Pi;
                lfo[l].random.heldValue = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f)) - 1.f;
            }
        }

        // reset attackDecayCounter
        envToVolume.startEnvelope();
        envToVolume.calcEnvCoeff(*(modSources[static_cast<int>(params.envVol[0].speedModSrc1.get())]),
                                 *(modSources[static_cast<int>(params.envVol[0].speedModSrc2.get())]), isUnipolar(params.envVol[0].speedModSrc1.getStep()), isUnipolar(params.envVol[0].speedModSrc2.getStep()));
        env2.startEnvelope();
        env2.calcEnvCoeff(*(modSources[static_cast<int>(params.env[0].speedModSrc1.get())]),
                          *(modSources[static_cast<int>(params.env[0].speedModSrc2.get())]), isUnipolar(params.env[0].speedModSrc1.getStep()), isUnipolar(params.env[0].speedModSrc2.getStep()));
        env3.startEnvelope();
        env3.calcEnvCoeff(*(modSources[static_cast<int>(params.env[1].speedModSrc1.get())]),
                          *(modSources[static_cast<int>(params.env[1].speedModSrc2.get())]), isUnipolar(params.env[1].speedModSrc1.getStep()), isUnipolar(params.env[1].speedModSrc2.getStep()));

        for (size_t o = 0; o < osc.size(); ++o) {

            switch (params.osc[o].waveForm.getStep()) {
                case eOscWaves::eOscSquare:
                    osc[o].square.phase = 0.f;
                    osc[o].square.phaseDelta = freqHz * Param::fromCent(params.osc[o].fine.get()) * 
                                                Param::fromSemi(params.osc[o].coarse.get()) / sRate * 2.f * float_Pi;
                    osc[o].square.width = params.osc[o].pulseWidth.get();
                break;
                case eOscWaves::eOscSaw:
                    osc[o].saw.phase = 0.f;
                    osc[o].saw.phaseDelta = freqHz * Param::fromCent(params.osc[o].fine.get()) * 
                                                Param::fromSemi(params.osc[o].coarse.get()) / sRate * 2.f * float_Pi;
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

    void stopNote(float /*velocity*/, bool allowTailOff) override{
        if (allowTailOff){

            // start a tail-off by setting this flag. The render callback will pick up on
            // this and do a fade out, calling clearCurrentNote() when it's finished.

            // we only need to begin a tail-off if it's not already doing so - the
            // stopNote method could be called more than once.
            if (envToVolume.getReleaseCounter() == -1)      
            {                                               
                envToVolume.resetReleaseCounter();
                env2.resetReleaseCounter();
                env3.resetReleaseCounter();
            }
        }
        else
        {
            // we're being told to stop playing immediately, so reset everything..
            clearCurrentNote();

            for (Lfo& l : lfo) {
                l.reset();
            }

            for (Osc& o : osc) 
            {
                o.square.reset();
                o.saw.reset();
                o.noise.reset();
            }
        }
    }

    void channelPressureChanged(int newValue) override {
        channelAfterTouch = static_cast<float>(newValue) / 128.f;
    }

    void pitchWheelMoved(int newValue) override{
        pitchBend = (newValue - 8192.f) / 8192.0f;
    }

    //Midi Control
    void controllerMoved(int controllerNumber, int newValue) override{

        switch(controllerNumber){
        //Modwheel
        case 1:
            modWheelValue = static_cast<float>(newValue) / 128.f;
            break;
        //Foot Controller
        case 4:
            footControlValue = (static_cast<float>(newValue) / 128.f); //TODO: test
            break;
        //Expression Control
        case 11:
            expPedalValue = static_cast<float>(newValue) / 128.f; //TODO: test
            break;
        }
    }

    void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override{
        // if voice active
        if (lfo[0].sine.isActive() || lfo[0].square.isActive() ||
            lfo[1].sine.isActive() || lfo[1].square.isActive() ||
            lfo[2].sine.isActive() || lfo[2].square.isActive() ){

            // Modulation
            renderModulation(numSamples);

            const float *envToVolMod = envToVolBuffer.getReadPointer(0);

            // oscillators
            for (size_t o = 0; o < params.osc.size(); ++o) {

                const float *pitchMod = modDestBuffer.getReadPointer(DEST_OSC1_PI + o);
                const float *shapeMod = modDestBuffer.getReadPointer(DEST_OSC1_PW + o);
                const float *panMod = modDestBuffer.getReadPointer(DEST_OSC1_PAN + o);
                const float *gainMod = modDestBuffer.getReadPointer(DEST_OSC1_GAIN + o);

                for (int s = 0; s < numSamples; ++s) {

                    float currentSample = 0.0f;

                    switch (params.osc[o].waveForm.getStep()){
                        case eOscWaves::eOscSquare:
                        {
                            // In case of pulse width modulation
                            float deltaWidth = osc[o].square.width > .5f
                                ? params.osc[o].pulseWidth.getMax() - osc[o].square.width
                                : osc[o].square.width - params.osc[o].pulseWidth.getMin();
                            // Pulse width must not reach 0 or 1
                            if (deltaWidth > (.5f - params.osc[o].pulseWidth.getMin()) && deltaWidth < 
                                (.5f + params.osc[o].pulseWidth.getMin())) {
                                deltaWidth = .49f;
                            }
                            // LFO mod has values [-1 .. 1], max amp for amount = 1
                            deltaWidth = deltaWidth * shapeMod[s];
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
                                deltaTr = deltaTr * shapeMod[s];
                                // Next sample will be fetch with the new width
                                currentSample = (osc[o].saw.next(pitchMod[s], deltaTr));
                        }
                        break;
                        case eOscWaves::eOscNoise:
                                currentSample = (osc[o].noise.next(pitchMod[s]));
                                break;
                    }

                    // filter
                    for (size_t f = 0; f < params.filter.size(); ++f) 
                    {
                        if(params.filter[f].filterActivation.getStep() == eOnOffToggle::eOn) {
                            const float *filterLCMod = modDestBuffer.getReadPointer(DEST_FILTER1_LC + f);
                            const float *filterHCMod = modDestBuffer.getReadPointer(DEST_FILTER1_HC + f);
                            const float *resMod = modDestBuffer.getReadPointer(DEST_FILTER1_RES + f);
                            currentSample = filter[o][f].run(currentSample, filterLCMod[s], filterHCMod[s], resMod[s]);
                            //currentSample = filter[o][f].run(currentSample, filterLCMod[s], 0.f, 0.f);
                        }
                    }

                    // gain + pan
                    const float currentAmp =    params.osc[o].vol.get() * Param::fromDb(gainMod[s] * 
                                                params.osc[o].gainModAmount1.getMax()) * envToVolMod[s];

                    // check if the output is a stereo output
                    if (outputBuffer.getNumChannels() == 2){
                        // Pan Influence
                        const float currentPan = params.osc[o].panDir.get() + panMod[s] * 100.f;
                        //const float currentPan = panMod[s] * 100.f;
                        const float currentAmpRight = currentAmp + (currentAmp / 100.f * currentPan);
                        const float currentAmpLeft = currentAmp - (currentAmp / 100.f * currentPan);
                        outputBuffer.addSample(0, startSample + s, currentSample*currentAmpLeft);
                        outputBuffer.addSample(1, startSample + s, currentSample*currentAmpRight);
                    }
                    else {
                        for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {
                            outputBuffer.addSample(c, startSample + s, currentSample * currentAmp);
                        }
                    }
                    if (envToVolume.getReleaseSamples() <= envToVolume.getReleaseCounter()) {
                        // next osc 
                        break;
                    }
                }
            }

            if (envToVolume.getReleaseSamples() <= envToVolume.getReleaseCounter()){
                clearCurrentNote();
                for (size_t l = 0; l < lfo.size(); ++l) {
                    lfo[l].sine.reset();
                    lfo[l].square.reset();
                }
            }
            totalVoiceSamples += numSamples;
        }
    }

protected:

    float calcModVal(ParamStepped<eModSource>& _source, Param& _intensity) {

        float source = *(modSources[static_cast<int>(_source.get())]);
        float intensity = _intensity.get();

        float min = _intensity.getMin();
        float max = _intensity.getMax();

        if (isUnipolar(_source.getStep()))
        {
            intensity = toBipolar(min, max, intensity);
        }
        else
        {
            intensity = toUnipolar(min, max, intensity);
        }

        return source * intensity;
    }

    void renderModulation(int numSamples) {

        const float sRate = static_cast<float>(getSampleRate());
        int samplesFadeIn[3] = { 0,0,0 };
        float lfoGain[3] = { 0.f, 0.f, 0.f };
        float lfoFreqMod[3] = {0.f, 0.f, 0.f};

        // Init
        for (size_t l = 0; l < lfo.size(); ++l) {
            lfo[l].audioBuffer.clear();
            
            //Set the deltaPhase for realtime LFO Changes
            if (params.lfo[l].tempSync.getStep() == eOnOffToggle::eOn) {

                float coeff = 1.0f;
                if (params.lfo[l].lfoDottedLength.getStep() == eOnOffToggle::eOn) {
                    coeff /= 1.5f;
                }
                if (params.lfo[l].lfoTriplets.getStep() == eOnOffToggle::eOn) {
                    coeff /= (2.0f / 3.0f);
                }

                lfo[l].sine.phaseDelta = static_cast<float>(params.positionInfo[params.getGUIIndex()].bpm) /
                    (60.f*sRate)*(params.lfo[l].noteLength.get() / 4.f)*2.f*float_Pi * coeff;
                lfo[l].square.phaseDelta = static_cast<float>(params.positionInfo[params.getGUIIndex()].bpm) /
                    (60.f*sRate)*(params.lfo[l].noteLength.get() / 4.f)*2.f*float_Pi * coeff;
                lfo[l].random.phaseDelta = static_cast<float>(params.positionInfo[params.getGUIIndex()].bpm) /
                    (60.f*sRate)*(params.lfo[l].noteLength.get() / 4.f)*2.f*float_Pi * coeff;
            }
            else 
            {
                lfo[l].sine.phaseDelta = params.lfo[l].freq.get() / sRate * 2.f * float_Pi;
                lfo[l].square.phaseDelta = params.lfo[l].freq.get() / sRate * 2.f * float_Pi;
                lfo[l].random.phaseDelta = params.lfo[l].freq.get() / sRate * 2.f * float_Pi;
            }

            // Length in samples of the LFO fade in
            samplesFadeIn[l] = static_cast<int>(params.lfo[l].fadeIn.get() * sRate);
            
            // Lfo Gain
            lfoGain[l] = params.lfo[l].gainModSrc.get() == eModSource::eNone
            ? 1.f
                : *(modSources[static_cast<int>(params.lfo[l].gainModSrc.get())]);
            
            // Lfo FreqMod
            float freqModVal1 = calcModVal(params.lfo[l].freqModSrc1, params.lfo[l].freqModAmount1);
            float freqModVal2 = calcModVal(params.lfo[l].freqModSrc2, params.lfo[l].freqModAmount2);

            lfoFreqMod[l] = std::pow(2.f, (freqModVal1 + freqModVal2) * params.lfo[l].freqModAmount1.getMax());
        }

        //clear the buffers
        modDestBuffer.clear();
        envToVolBuffer.clear();
        env2Buffer.clear();
        env3Buffer.clear();

        //set the write point in the buffers
        for (size_t u = 0; u < MAX_DESTINATIONS; ++u) {
            modDestinations[u] = modDestBuffer.getWritePointer(u);
        }

        modSources[eModSource::eLFO1] = lfo[0].audioBuffer.getWritePointer(0);
        modSources[eModSource::eLFO2] = lfo[1].audioBuffer.getWritePointer(0);
        modSources[eModSource::eLFO3] = lfo[2].audioBuffer.getWritePointer(0);
        modSources[eModSource::eVolEnv] = envToVolBuffer.getWritePointer(0);
        modSources[eModSource::eEnv2] = env2Buffer.getWritePointer(0);
        modSources[eModSource::eEnv3] = env3Buffer.getWritePointer(0);

        //for each sample
        for (int s = 0; s < numSamples; ++s) {

            //calc lfo stuff
            for (size_t l = 0; l < lfo.size(); ++l) {
                
                float factorFadeIn = 1.f;

                if (samplesFadeIn[l] != 0 && (totalVoiceSamples + s < samplesFadeIn[l])){
                // If the fade in is reached or no fade in is set, the factor is 1 (100%)
                    factorFadeIn = static_cast<float>(totalVoiceSamples + s) / static_cast<float>(samplesFadeIn[l]);
                }

                // calculate lfo values and fill the buffers
                switch (params.lfo[l].wave.getStep()) {
                    case eLfoWaves::eLfoSine:
                        lfo[l].audioBuffer.setSample(0, s, lfo[l].sine.next(lfoFreqMod[l]) * factorFadeIn * lfoGain[l]);
                        break;
                    case eLfoWaves::eLfoSampleHold:
                        lfo[l].audioBuffer.setSample(0, s, lfo[l].random.next(lfoFreqMod[l]) * factorFadeIn * lfoGain[l]);
                        break;
                    case eLfoWaves::eLfoSquare:
                        lfo[l].audioBuffer.setSample(0, s, lfo[l].square.next(lfoFreqMod[l]) * factorFadeIn * lfoGain[l]);
                        break;
                }
            }

            // Calculate the Envelope coefficients and fill the buffers
            // alternative: second matrix with external controls only
            envToVolBuffer.setSample(0, s, envToVolume.getNextEnvCoeff());
            env2Buffer.setSample(0, s, env2.getNextEnvCoeff());
            env3Buffer.setSample(0, s, env3.getNextEnvCoeff());

            //run the matrix
            modMatrix.doModulationsMatrix(&*modSources.begin(), &*modDestinations.begin());

            for (size_t u = 0; u < MAX_DESTINATIONS; ++u) {
                ++modDestinations[u];
            }

            // internal modSources
            ++modSources[eModSource::eLFO1];
            ++modSources[eModSource::eLFO2];
            ++modSources[eModSource::eLFO3];
            ++modSources[eModSource::eVolEnv];
            ++modSources[eModSource::eEnv2];
            ++modSources[eModSource::eEnv3];

            //! \todo check whether this should be at the place where the values are actually used
            modDestBuffer.setSample(DEST_OSC1_PI, s, Param::fromSemi(modDestBuffer.getSample(DEST_OSC1_PI, s) * 
                                    params.osc[0].pitchModAmount1.getMax()));
            modDestBuffer.setSample(DEST_OSC2_PI, s, Param::fromSemi(modDestBuffer.getSample(DEST_OSC2_PI, s) * 
                                    params.osc[1].pitchModAmount1.getMax()));
            modDestBuffer.setSample(DEST_OSC3_PI, s, Param::fromSemi(modDestBuffer.getSample(DEST_OSC3_PI, s) * 
                                    params.osc[2].pitchModAmount1.getMax()));

            //do the same for filters
            modDestBuffer.setSample(DEST_FILTER1_LC, s, Param::bipolarToFreq(modDestBuffer.getSample(DEST_FILTER1_LC, s), params.filter[0].lpCutoff.get(), params.filter[0].lpModAmount1.getMax()));
            modDestBuffer.setSample(DEST_FILTER2_LC, s, Param::bipolarToFreq(modDestBuffer.getSample(DEST_FILTER2_LC, s), params.filter[1].lpCutoff.get(), params.filter[1].lpModAmount1.getMax()));
            modDestBuffer.setSample(DEST_FILTER1_HC, s, Param::bipolarToFreq(modDestBuffer.getSample(DEST_FILTER1_HC, s), params.filter[0].hpCutoff.get(), params.filter[0].hpModAmount1.getMax()));
            modDestBuffer.setSample(DEST_FILTER2_HC, s, Param::bipolarToFreq(modDestBuffer.getSample(DEST_FILTER2_HC, s), params.filter[1].hpCutoff.get(), params.filter[1].hpModAmount1.getMax()));
            modDestBuffer.setSample(DEST_FILTER1_RES, s, (params.filter[0].resonance.get() + modDestBuffer.getSample(DEST_FILTER1_RES, s) * params.filter[0].resModAmount1.getMax()));
            modDestBuffer.setSample(DEST_FILTER2_RES, s, (params.filter[1].resonance.get() + modDestBuffer.getSample(DEST_FILTER2_RES, s) * params.filter[1].resModAmount1.getMax()));
        }
    }
private:
    SynthParams &params;
    int totalVoiceSamples;
    std::array<Lfo, 3> lfo;

    struct Osc {
        Oscillator<&Waveforms::square> square;
        Oscillator<&Waveforms::saw> saw;
        Oscillator<&Waveforms::whiteNoise> noise;
        float level;
    };
    std::array<Osc, 3> osc;

    std::array<std::array<Filter,2>,3> filter;
    std::array<const float*, eModSource::nSteps> modSources;
    std::array<float*, MAX_DESTINATIONS> modDestinations;

    // Midi
    float channelAfterTouch;
    float keyBipolar;
    float currentInvertedVelocity;
    float currentVelocity;
    float footControlValue;
    float expPedalValue;
    float modWheelValue;
    float pitchBend;

    //Mod matrix
    ModulationMatrix& modMatrix;
    float zeroMod;

    // Buffers
    AudioSampleBuffer modDestBuffer;
    AudioSampleBuffer envToVolBuffer;
    AudioSampleBuffer env2Buffer;
    AudioSampleBuffer env3Buffer;
    // Envelopes
    Envelope envToVolume;
    Envelope env2;
    Envelope env3;
};
