/*
==============================================================================

FxDelay.cpp
Created: 30 Nov 2015 6:21:10pm
Author:  nj

==============================================================================
*/

#include "FxDelay.h"

double FxDelay::calcDelayTime(double const &dividendIn, double const & divisorIn, double const &bpmIn)
{
    //double newTimeValue;
    //double bps = (bpmIn / 60.);
    //double beatInMs = 1000 * (2. / bps);
    //newTimeValue = beatInMs * (dividendIn / divisorIn);
    //return newTimeValue;

    return (1000.0 * (2. / (bpmIn / 60.))) * (dividendIn / divisorIn);
}

void FxDelay::renderDelay(AudioSampleBuffer& outputBuffer, int const &startSample, double const &sampleRate, double const &bpmIn)
{
    // check for changes, re-calculate delay time - how slow is this?
    if (params.delaySync.get() > 0.f || bpm != bpmIn || divisor != params.delayDivisor.get() || dividend != params.delayDividend.get()) {
        params.delayTime.set( static_cast<float>((2.f * 1000.0f * (1.f / (static_cast<float>(bpmIn) / 60.f))) * (params.delayDividend.get() / params.delayDivisor.get())) +00001.f);
        bpm = bpmIn;
        divisor = params.delayDivisor.get();
        dividend = params.delayDividend.get();
    }    

    for (int s = 0; s < outputBuffer.getNumSamples(); ++s)
    {
        for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {

            // get new length from UI
            int newLoopLength = static_cast<int>(params.delayTime.get() * (sampleRate / 1000.0));

            // reset the loop position according to the current delay length
            loopPosition %= newLoopLength;

            float currentSample = 0.f;
            float delayedSample = 0.f;

            // clear old material from buffer
            if (newLoopLength < currentDelayLength) { // TODO: this is still a bit messy
                delayBuffer.clear(newLoopLength, delayBuffer.getNumSamples() - currentDelayLength);
            }

            // add new material to buffer
            currentSample = outputBuffer.getSample(c, startSample + s);
            delayedSample = delayBuffer.getSample(c, loopPosition);
            delayBuffer.setSample(c, loopPosition, currentSample);
            delayBuffer.addSample(c, loopPosition, delayedSample * params.delayFeedback.get());
            outputBuffer.addSample(c, startSample + s, delayedSample * params.delayDryWet.get());

            // iterate
            currentDelayLength = newLoopLength;
            ++loopPosition;
        }
    }
}