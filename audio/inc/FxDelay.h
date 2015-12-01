/*
  ==============================================================================

    FxDelay.h
    Created: 30 Nov 2015 6:21:10pm
    Author:  nj

  ==============================================================================
*/

#ifndef FXDELAY_H_INCLUDED
#define FXDELAY_H_INCLUDED

#include "SynthParams.h"

class FxDelay {
public:
    FxDelay(SynthParams &p, int channels, double sampleRate)
        : params(p)
        , loopPosition(0)
        , delayBuffer(AudioSampleBuffer(channels, static_cast<int>(sampleRate * 5.0)))
        , currentDelayLength(static_cast<int>(params.delayTime.get()*(sampleRate / 1000.0)))
        , bpm(120)
    {
        for (int c = 0; c < channels; ++c) {
            delayBuffer.clear(c, 0, delayBuffer.getNumSamples());
        }
    }

    double calcDelayTime(double dividendIn, double divisorIn, double bpmIn);
    void renderDelay(AudioSampleBuffer& outputBuffer, int startSample, int numSamples, double sampleRate);

private:
    SynthParams &params;
    AudioSampleBuffer delayBuffer;
    int loopPosition;
    int currentDelayLength;
    double delayTime;
    double bpm;
    std::atomic<bool> bpmDirty;
};
#endif  // FXDELAY_H_INCLUDED