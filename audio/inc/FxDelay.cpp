/*
  ==============================================================================

    FxDelay.cpp
    Created: 30 Nov 2015 6:21:10pm
    Author:  nj

  ==============================================================================
*/

#include "FxDelay.h"

double FxDelay::calcDelayTime(double dividendIn, double divisorIn, double bpmIn)
{

    //double newTimeValue;
    //double bps = (bpmIn / 60.);
    //double beatInMs = 1000 * (2. / bps);
    //newTimeValue = beatInMs * (dividendIn / divisorIn);
    //return newTimeValue;

    return (1000.0 * (2. / (bpmIn / 60.))) * (dividendIn / divisorIn);
}

void FxDelay::renderDelay(AudioSampleBuffer& outputBuffer, int startSample, int numSamples, double sampleRate)
{
    for (int s = 0; s < numSamples; ++s)
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