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
#include "ModulationMatrix.h"

//! Envelope Class: Envelope
/*! An ADSR implementation with A,D and R shape control and an additional
    feature of "Key Velocity to Envelope", which can be regulated on the 
    corresponding Panel.
    The Envelope is currently controling the amplitude (Env Panel) or can be
    can be use to modulate the cutoff frequency of the lowpass filter
*/

class Envelope{
    public:
    Envelope(float sampleRate, Param &decay, Param &attack, Param &sustain, Param &release, 
        Param &attackShape, Param &decayShape, Param &releaseShape, Param &keyVelToEnv)
        :releaseCounter(-1)
        ,attackDecayCounter(0)
        ,sampleRate(sampleRate)
        ,attack(attack)
        ,decay(decay)
        ,sustain(sustain)
        ,release(release)
        ,attackShape(attackShape)
        ,decayShape(decayShape)
        ,releaseShape(releaseShape)
        ,keyVelToEnv(keyVelToEnv)
        ,modSourceFo(DEST_NONE)
        ,modSourcePulseWidth(DEST_NONE)
        ,modDestOutput1(DEST_NONE)
        ,modDestOutput2(DEST_NONE)
        ,modSourceAmp(DEST_NONE)
    {
    }
    
    //! Enevelope sestructor
    ~Envelope(){}

    //! resets the sample counters and sets the current velocity for each new note
    void startEnvelope(float currVel);

    //! get and reset the release counters for the volume envelope
    int getReleaseCounter() const { return releaseCounter; } 
    void resetReleaseCounter();

    
    //! calculation of the volume envelope coefficients (with shape control)
    const float calcEnvCoeff();
 
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


    // TODO the matrix stuff
    ModulationMatrix* modulationMatrix;

    int modSourceFo;
    int modSourcePulseWidth;
    int modSourceAmp;

    int modDestOutput1;
    int modDestOutput2;
};

#endif  // ENVELOPE_H_INCLUDED
