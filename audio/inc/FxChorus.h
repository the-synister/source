#ifndef FXCHORUS_H_INCLUDED
#define FXCHORUS_H_INCLUDED


#include "SynthParams.h"
#include "Oscillator.h"


class FxChorus
{
public:
    FxChorus(SynthParams &p)
        : params(p)
        , loopPosition(0)
        //, chorDelayLength(.02f)
        //, modulationDepth(.01f)
        //, modulationRate(.5f)
        //, chorDryWet(.8)
    {

    }
    ~FxChorus();

    void init(int channelsIn, double sampleRateIn);
    void render(AudioSampleBuffer& outputBuffer, int startSample);

private:
    SynthParams &params;
    AudioSampleBuffer chorusBuffer;
    Oscillator<&Waveforms::sinus> modSine1;
    Oscillator<&Waveforms::sinus> modSine2;
    Oscillator<&Waveforms::sinus> modSine3;
    Oscillator<&Waveforms::sinus> modSine4;
    Oscillator<&Waveforms::sinus> modSine5;
    float sampleRate;
    int channels;
    int currentDelayLength;
    int loopPosition;

};


#endif
