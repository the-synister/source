/*
  ==============================================================================

    LowFidelity.h
    Created: 1 Feb 2016 10:06:14pm
    Author:  Luc

  ==============================================================================
*/

#ifndef LOWFIDELITY_H_INCLUDED
#define LOWFIDELITY_H_INCLUDED

#include "SynthParams.h"

//! LowFidelity Class: Low fidelity effects

/*! The low fidelity effects deteriorate the quality of the signal.
*/
class LowFidelity
{
public:
    //! LowFidelity constructor.
    LowFidelity(SynthParams& p)
        : params(p)
    {}

    //! LowFidelity destructor.
    ~LowFidelity();

    //! Bit reduction
    /*!
    A sample is usually coded with 16 bits.
    The bit degradation enables reducing this value (1 bit per sample minimum)
    1 parameters:
    @params AudioSampleBuffer - instance of the AudioSampleBuffer is an output buffer, which must be the buffer where the voices had been processed and added.
    */
    void bitReduction(AudioSampleBuffer&);

protected:
    SynthParams &params; //!< local params reference

};


#endif  // LOWFIDELITY_H_INCLUDED
