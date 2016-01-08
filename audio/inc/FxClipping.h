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

//! FxDelay Class: Clipping Effect

/*! The clipping effect trims the samples that surpass the threshold of 1 or -1.
    It does that by multiplying the sample with an overload factor and if the value,
    are bigger than 1 or lower than -1, then will be 1 or -1 respectively.
*/
class FxClipping
{
public:
    //! FxDelay constructor.
    FxClipping(SynthParams& p)
    : params(p)
    {}
    
    //! FxDelay destructor.
    ~FxClipping();
    
    //! Signal clipping
    /*!
     This public function holds the actual "clipping" of the signal. 
     The clipped signal will be given through 3 parameters:
     AudioSampleBuffer& outputBuffer - instance of the AudioSampleBuffer is an output buffer, which must be the buffer where the voices had been processed and added.
     int startSample, needed for sudden (midi) parameter changes
     int numSamplesIn, the current block size
     */
    void clipSignal(AudioSampleBuffer&, int, int);

protected:
     SynthParams &params; //!< local params reference
    
};


#endif  // FXCLIPPING_H_INCLUDED
