/*
  ==============================================================================

    FxClipping.h
    Created: 5 Dec 2015 7:36:15pm
    Author:  Juan Cabello

  ==============================================================================
*/

#ifndef FXCLIPPING_H_INCLUDED
#define FXCLIPPING_H_INCLUDED

#include "SynthParams.h"

class FxClipping
{
public:
    FxClipping(SynthParams& p) : params(p)
                               , threshold(1.f)
                               , currentSample(0.f)
                               , amplifiedSample(0.f)
                               {};
    ~FxClipping();
    
    SynthParams &params;
    float threshold;
    float currentSample;
    float amplifiedSample;
    void clipSignal(AudioSampleBuffer&);
};



#endif  // FXCLIPPING_H_INCLUDED
