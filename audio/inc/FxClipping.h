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
    FxClipping(SynthParams& p)
    : params(p)
    {}
    
    ~FxClipping();
    
    void clipSignal(AudioSampleBuffer&, int, int);

protected:
     SynthParams &params;
    
};


#endif  // FXCLIPPING_H_INCLUDED
