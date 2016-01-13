/*
  ==============================================================================

    Envelope.h
    Created: 11 Dec 2015 3:13:56pm
    Author:  Nhat Duc Tran and Anton Schmied 

  ==============================================================================
*/

#ifndef ENVELOPE_H_INCLUDED
#define ENVELOPE_H_INCLUDED

#include "Synthparams.h"
#include "Param.h"

//! Envelope Class: Envelope
/*! An ADSR implementation with A,D and R shape control and an additional
    feature of "Key Velocity to Envelope", which can be regulated on the 
    corresponding Panel.
    The Envelope is currently controling the amplitude (Env Panel) or can be
    can be use to modulate the cutoff frequency of the lowpass filter
*/

class Envelope{
    public:
    Envelope(float _sampleRate, Param &_attack, Param &_decay, Param &_sustain, Param &_release, 
        Param &_attackShape, Param &_decayShape, Param &_releaseShape, Param &_keyVelToEnv)
        :releaseCounter(-1)
        ,attackDecayCounter(0)
        ,sampleRate(_sampleRate)
        ,attack(_attack)
        ,decay(_decay)
        ,sustain(_sustain)
        ,release(_release)
        ,attackShape(_attackShape)
        ,decayShape(_decayShape)
        ,releaseShape(_releaseShape)
        ,keyVelToEnv(_keyVelToEnv)
    {
        
    }
    
    //! Enevelope destructor
    ~Envelope(){}

    //! resets the sample counters and sets the current velocity for each new note
    void startEnvelope(float currVel);

    //! get and reset the release counters for the volume envelope
    int getReleaseCounter() const { return releaseCounter; } 
    void resetReleaseCounter();

    
    //! calculation of the volume envelope coefficients (with shape control)
    const float calcEnvCoeff();

    //! sets the passed buffer for the modulation depending on calculated coefficients
    void render(AudioSampleBuffer &buffer, int numSamples);

    private:
    
    //References for required Params for the envelope
    Param &attack;          //!< attack reference
    Param &decay;           //!< decay reference
    Param &sustain;         //!< sustain reference
    Param &release;         //!< release reference
    Param &attackShape;     //!< attack shape reference
    Param &decayShape;      //!< decay shape reference
    Param &releaseShape;    //!< release shape reference

    Param &keyVelToEnv;     //!< key velocity to envelope reference

    float sampleRate;       //!< sample rate
    float currentVelocity;  //!< current Veloctiy
    
    float valueAtRelease;   //!< amplitude value once release phase starts
    int attackDecayCounter; //!< sample counter during the attack and decay phase
    int releaseCounter;     //!< sample counter during the release phase

    static float interpolateLog(int c, int t, float k, bool slow); //!< interpolates logarithmically from 1.0 to 0.0f in t samples (with shape control)
};

#endif  // ENVELOPE_H_INCLUDED
