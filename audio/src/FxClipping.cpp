/*
  ==============================================================================

    FxClipping.cpp
    Created: 5 Dec 2015 7:36:15pm
    Author:  Juan Cabello

  ==============================================================================
*/

#include "FxClipping.h"

//FxClipping::FxClipping(){};
FxClipping::~FxClipping(){};

void FxClipping::clipSignal(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    for (int s = 0; s < numSamples; ++s) {
        for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {
            currentSample = outputBuffer.getSample(c, startSample + s);
            FloatVectorOperations::multiply(&amplifiedSample, &currentSample, params.clippingFactor.get(), 1);
            FloatVectorOperations::clip(&amplifiedSample, &amplifiedSample, -1.f, 1.f, 1);
            outputBuffer.setSample(c, startSample + s, amplifiedSample);
        }
    }
}