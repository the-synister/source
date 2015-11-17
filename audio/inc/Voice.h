
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
    , lastSample(0.f)
    , inputDelay1(0.f)
    , inputDelay2(0.f)
    , outputDelay1(0.f)
    , outputDelay2(0.f)
    , currentLadderCutoffFreq(params.ladderCutoff.get())
    {
        setButterCoefficients();
    }


    bool canPlaySound (SynthesiserSound* sound) override
    {
        ignoreUnused(sound);
        return true;
    }

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {
        lastSample = 0.f, inputDelay1 = 0.f, inputDelay2 = 0.f, outputDelay1 = 0.f, outputDelay2 = 0.f;
        level = velocity * 0.15f;
        tailOff = 0.f;

        //calculate butterworth coefficients
        setButterCoefficients();

        const float sRate = static_cast<float>(getSampleRate());
        float freqHz = static_cast<float>(MidiMessage::getMidiNoteInHertz (midiNoteNumber, params.freq.get()));

        lfo1.phase = 0.f;
        lfo1.phaseDelta = params.lfo1freq.get() / sRate * 2.f * float_Pi;

        osc1.phase = 0.f;
        osc1.phaseDelta = freqHz * Param::fromCent(params.osc1fine.get()) / sRate * 2.f * float_Pi;
    }

    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        if (allowTailOff)
        {
            // start a tail-off by setting this flag. The render callback will pick up on
            // this and do a fade out, calling clearCurrentNote() when it's finished.

            if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
                                // stopNote method could be called more than once.
                tailOff = 1.0;
        }
        else
        {
            // we're being told to stop playing immediately, so reset everything..
            clearCurrentNote();
            lfo1.reset();
            osc1.reset();
        }
    }

    void pitchWheelMoved (int /*newValue*/) override
    {
        // can't be bothered implementing this for the demo!
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

        if(lfo1.isActive())
        {
            if (tailOff > 0.f)
            {
                for (int s = 0; s < numSamples;++s)
                {
                    //TODO - check if ladder filter is on!
                    const float currentSample = filterLP(osc1.next(pitchMod[s]))* level * tailOff * currentAmp;
                    //const float currentSample = (osc1.next(pitchMod[s])) * level * tailOff * currentAmp;

                    for (int c = 0; c < outputBuffer.getNumChannels(); ++c)
                        outputBuffer.addSample (c, startSample+s, currentSample);

                    tailOff *= 0.99999f;
                    if (tailOff <= 0.005f)
                    {
                        clearCurrentNote();
                        lfo1.reset();
                        break;
                    }
                }
            }
            else
            {
                for (int s = 0; s < numSamples;++s)
                {
                    //TODO - check if ladder filter is on!
                    const float currentSample = filterLP(osc1.next(pitchMod[s]))* level * tailOff * currentAmp;
                    //const float currentSample = (osc1.next(pitchMod[s])) * level * currentAmp;

                    for (int c = 0; c < outputBuffer.getNumChannels(); ++c)
                        outputBuffer.addSample(c, startSample+s, currentSample);
                }
            }
        }
    }

    // Calculates coefficients for second order Butterworth lowpass
    void setButterCoefficients() {

        //const float currentResonance = pow(10.f, -params.ladderRes.get() / 20.f);
        const float cutoffFreq = params.ladderCutoff.get();
        const float sRate = static_cast<float>(getSampleRate());

        const float interVar = 1.f / (tanf(float_Pi*cutoffFreq / sRate));

        butterCoeffs[0] = 1.f / (1.0f + sqrt(2.0f)*interVar + pow(interVar,2.f));
        butterCoeffs[1] = 2.f*butterCoeffs[0];
        butterCoeffs[2] = butterCoeffs[0];
        butterCoeffs[3] = 2.f*butterCoeffs[0] * (1.f - pow(interVar, 2));
        butterCoeffs[4] = butterCoeffs[0] * (1.0f - sqrt(2.0f)*interVar + pow(interVar,2.f));

    }

    //apply Lowpass Filter to the current Sample in renderNextBlock()
    float filterLP(float currentSample){

        if (currentLadderCutoffFreq != params.ladderCutoff.get())
        {
            setButterCoefficients();
            currentLadderCutoffFreq = params.ladderCutoff.get();
        }

        currentSample = *(butterCoeffs)*currentSample + *(butterCoeffs+1)*inputDelay1 + *(butterCoeffs+2)*inputDelay2
            - *(butterCoeffs+3)*outputDelay1 - *(butterCoeffs+4)*outputDelay2;

        //delaying samples
        inputDelay2 = inputDelay1;
        inputDelay1 = lastSample;
        outputDelay2 = outputDelay1;
        outputDelay1 = currentSample;

        return currentSample;
    }

protected:
    void renderModulation(int numSamples) {
        //! \todo add pitch wheel values

        const float modAmount = params.osc1lfo1depth.get();
        for (int s = 0; s < numSamples;++s)
        {
            pitchModBuffer.setSample(0, s, Param::fromSemi(lfo1.next()*modAmount));
        }
    }


private:
    SynthParams &params;

    Oscillator<&Waveforms::square> osc1;

    Oscillator<&Waveforms::sinus> lfo1;

    float level, tailOff;

    AudioSampleBuffer pitchModBuffer;

    //Filter initialisation
    float lastSample, inputDelay1, inputDelay2, outputDelay1, outputDelay2, currentLadderCutoffFreq;
    float butterCoeffs[5];

};
