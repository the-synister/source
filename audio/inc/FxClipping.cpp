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

void FxClipping::clipSignal(AudioSampleBuffer& outputBuffer)
{
    for (int s = 0; s < outputBuffer.getNumSamples(); ++s) {
        for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {
            currentSample = outputBuffer.getSample(c, s);
            amplifiedSample = currentSample * params.clippingFactor.get();
            
            if (amplifiedSample > 0 && amplifiedSample > threshold) {
                outputBuffer.clear(c, s, 1);
                outputBuffer.setSample(c, s, threshold);
            } else if (amplifiedSample < 0 && amplifiedSample < -threshold) {
                outputBuffer.clear(c, s, 1);
                outputBuffer.setSample(c, s, -threshold);
            }
        }
    }

             //for (int s = 0; s < numSamples;++s)
                //{
                  //  pitchModBuffer.setSample(0, s, Param::fromSemi(lfo1sine.next()*modAmount) * Param::fromCent(currentPitchInCents));
                //}
}