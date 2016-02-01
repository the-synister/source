/*
  ==============================================================================

    LowFidelity.cpp
    Created: 1 Feb 2016 10:06:00pm
    Author:  Luc

  ==============================================================================
*/

#include "LowFidelity.h"

LowFidelity::~LowFidelity() {};

void LowFidelity::bitReduction(AudioSampleBuffer& outputBuffer)
{
    // coeff = 2^(nBitsLowFi-1)
    float coeff = pow(2.f, params.nBitsLowFi.get() - 1.f);

    //For all the outputs
    for (int c = 0; c < outputBuffer.getNumChannels(); ++c)
    {
        // Bit degradation
        for (int s = 0; s < outputBuffer.getNumSamples(); ++s)
        {
            float newSampleVal = floor(coeff * (outputBuffer.getSample(c, s)) + 0.5f) / coeff;
            outputBuffer.setSample(c, s, newSampleVal);
        }

    }
}
