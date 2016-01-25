/*
  ==============================================================================

    FxClipping.cpp
    Created: 5 Dec 2015 7:36:15pm
    Author:  Juan Cabello

  ==============================================================================
*/

#include "FxClipping.h"

FxClipping::~FxClipping(){};

void FxClipping::clipSignal(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    float clipFactor = params.clippingFactor.get();
    for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {
        FloatVectorOperations::multiply(outputBuffer.getWritePointer(c, startSample), clipFactor, numSamples);
        FloatVectorOperations::clip(outputBuffer.getWritePointer(c, startSample), outputBuffer.getReadPointer(c, startSample), -1.f, 1.f, numSamples);
    }
}