/*
==============================================================================

FxDelay.cpp
Created: 30 Nov 2015 6:21:10pm
Author:  nj

==============================================================================
*/

#include "FxDelay.h"

void FxDelay::calcDelayTime(double bpmIn)
{
    // check for changes, re-calculate delay time - how slow is this?
    if (params.delaySync.get() > 0 ||
        bpm != bpmIn ||
        divisor != params.delayDivisor.get() ||
        dividend != params.delayDividend.get()) {

        // TODO: check for very high bpm
        params.delayTime.set(static_cast<float>(4. * 1000.0 * (1. / (bpmIn / 60.)) *
            static_cast<double>(params.delayDividend.get() / params.delayDivisor.get())));
        bpm = bpmIn;
        divisor = params.delayDivisor.get();
        dividend = params.delayDividend.get();
    }
}

void FxDelay::renderDelay(AudioSampleBuffer& outputBuffer, int startSample, double sampleRate, double bpmIn)
{
    int newLoopLength;
    calcDelayTime(bpmIn);

    for (int s = 0; s < outputBuffer.getNumSamples(); ++s)
    {
        // get new length from UI
        newLoopLength = static_cast<int>(params.delayTime.get() * (sampleRate / 1000.0));

        for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {

            // reset the loop position according to the current delay length
            loopPosition %= newLoopLength;

            // clear old material from buffer
            if (newLoopLength < currentDelayLength) { // TODO: this is still a bit messy
                delayBuffer.clear(newLoopLength, delayBuffer.getNumSamples() - currentDelayLength);
            }

            // add new material to buffer
            float currentSample = outputBuffer.getSample(c, startSample + s);
            float delayedSample = delayBuffer.getSample(c, loopPosition);
            delayBuffer.setSample(c, loopPosition, currentSample);
            delayBuffer.addSample(c, loopPosition, delayedSample * params.delayFeedback.get());
            outputBuffer.addSample(c, startSample + s, delayedSample * params.delayDryWet.get());

            // iterate
            currentDelayLength = newLoopLength;
            ++loopPosition;
        }
    }
}