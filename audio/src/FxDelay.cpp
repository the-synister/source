/*
==============================================================================

FxDelay.cpp
Created: 30 Nov 2015 6:21:10pm
Author:  nj

==============================================================================
*/

#include "FxDelay.h"

float FxDelay::filterDelay(float inputSignal, const double sRate) {

    //New Filter Design: Biquad (2 delays) Source: http://www.musicdsp.org/showArchiveComment.php?ArchiveID=259
    float k, coeff1, coeff2, coeff3, b0, b1, b2, a1, a2;

    const float currentLowcutFreq = params.delayCutoff.get() / static_cast<float>(sRate);
    const float currentResonance = pow(10.f, -params.delayResonance.get() / 20.f);

    // coefficients for lowpass, depending on resonance and lowcut frequency
    k = 0.5f * currentResonance * sin(2.f * float_Pi * currentLowcutFreq);
    coeff1 = 0.5f * (1.f - k) / (1.f + k);
    coeff2 = (0.5f + coeff1) * cos(2.f * float_Pi * currentLowcutFreq);
    coeff3 = (0.5f + coeff1 - coeff2) * 0.25f;

    b0 = 2.f * coeff3;
    b1 = 2.f * 2.f * coeff3;
    b2 = 2.f * coeff3;
    a1 = 2.f * -coeff2;
    a2 = 2.f * coeff1;

    lastSample = inputSignal;

    inputSignal = b0*inputSignal + b1*inputDelay1 + b2*inputDelay2 - a1*outputDelay1 - a2*outputDelay2;

    //delaying samples
    inputDelay2 = inputDelay1;
    inputDelay1 = lastSample;
    outputDelay2 = outputDelay1;
    outputDelay1 = inputSignal;

    return inputSignal;
}

void FxDelay::calcDelayTime(double bpmIn)
{
    // check for changes, re-calculate delay time - how slow is this?
    if (params.delaySync.get() > 0 ||
        bpm != bpmIn ||
        divisor != params.delayDivisor.get() ||
        dividend != params.delayDividend.get()) {

        // TODO: check for very high bpm
        params.delayTime.set(static_cast<float>(2. * 1000.0 * (1. / (bpmIn / 60.)) *
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

        // reset the loop position according to the current delay length
        loopPosition %= newLoopLength;

        // clear old material from buffer
        if (newLoopLength < currentDelayLength) { // TODO: this is still a bit messy
            delayBuffer.clear(newLoopLength, delayBuffer.getNumSamples() - currentDelayLength);
        }

        for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {

            // add new material to buffer
            float currentSample = outputBuffer.getSample(c, startSample + s);
            float delayedSample = delayBuffer.getSample(c, loopPosition);
            delayBuffer.setSample(c, loopPosition, currentSample);
            //delayBuffer.setSample(c, newLoopLength - loopPosition, currentSample); // reverse + overflow
            delayedSample = filterDelay(delayedSample, sampleRate); // here it does record the filter
            delayBuffer.addSample(c, loopPosition, delayedSample * params.delayFeedback.get());
            //delayedSample = filterDelay(delayedSample, sampleRate); // here it does not record the filter
            outputBuffer.addSample(c, startSample + s, delayedSample * params.delayDryWet.get());

        }
        // iterate
        currentDelayLength = newLoopLength;
        ++loopPosition;
    }
}