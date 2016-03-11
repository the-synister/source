/*
  ==============================================================================

    FxDelay.h
    Created: 30 Nov 2015 6:21:10pm
    Author:  nj

  ==============================================================================
*/

#ifndef FXDELAY_H_INCLUDED
#define FXDELAY_H_INCLUDED

#include "SynthParams.h"

//! FxDelay Class: Delay Effect
/*! The delay effect adds a delayed signal to the current audiobuffer.
    The time can be set manually or synced in note values to the host.
    A simple filter can get applied to the feedback loop.
    The delay buffer can be read in both direction to add a reverse mode.
*/

class FxDelay {
public:
    //! FxDelay constructor.
    FxDelay(SynthParams &p)
        : params(p)
        , loopPosition(0)
        , bpm(120)
        , divisor(0)
        , dividend(0)
        , fLastSample(0.f)
        , fInputDelay1(0.f)
        , fInputDelay2(0.f)
        , fOutputDelay1(0.f)
        , fOutputDelay2(0.f)
        , delayBuffer()
        , maxDelayLength(20000)
    {}
    //! FxDelay destructor.
    ~FxDelay(){}

    //! delay rendering.
    /*!
    The public function render can be called to add a delay to a processed audio block.
    This functions calls calcTime(), to determine the delay length, adds the (filtered)
    signal to the delay and output buffer and takes care of the current position and
    direction inside the ring buffer (feedback loop).
    @param outputBuffer a reference to the current block. the delay gets added to it
    @param startSample needed for sudden (midi) parameter changes
    @param numSamplesIn the current block size
    */
    void render(AudioSampleBuffer& outputBuffer, int startSample, int numSamplesIn);

    //! delay initialization.
    /*!
    The init function sets up the audio buffer size, sample rate, maximum length and channels.
    @param channelsIn the amount of audio channels
    @param sampleRateIn the current sample rate
    */
    void init(int channelsIn, double sampleRateIn);

private:
    //! delay time calculation.
    /*!
    Calcutates the delay time in case of changes
    of the host tempo or user input.
    */
    void calcTime();

    //! delay filter.
    /*!
    The private filter function add the possibility to apply a lowpass filter
    to the delayed signal. The cutoff frequency can be set by the user.
    The filter changes can be applied to the feedback while reading: realtime,
    or while writing to the buffer. This "records" changes into the delay.
    @param inputSignal the current input sample
    returns the filtered inputSignal
    */
    float filter(float inputSignal);

    SynthParams &params;            //!< local params reference
    AudioSampleBuffer delayBuffer;  //!< delay audio buffer
    double sampleRate;              //!< current sammple rate
    int channels;                   //!< channel amount, 2 stereo
    int loopPosition;               //!< the current loop position
    int currentDelayLength;         //!< delay length, or delay time in samples
    int maxDelayLength;             //!< maximum delay length in samples
    double bpm;                     //!< current beats per minute, temp storage
    float divisor;                  //!< user set delay time divisor, temp storage
    float dividend;                 //!< user set delay time dividend, temp storage
    float fLastSample;              //!< filter sample storage
    float fInputDelay1;             //!< filter sample storage
    float fInputDelay2;             //!< filter sample storage
    float fOutputDelay1;            //!< filter sample storage
    float fOutputDelay2;            //!< filter sample storage
    eOnOffToggle triplet;           //!< user set triplet mode, on==1 or off==0
};
#endif  // FXDELAY_H_INCLUDED
