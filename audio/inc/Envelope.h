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
    /*const float calcEnvCoeff()
    {
        float envCoeff;
        float sustainLevel;
        
        // check the unit of the envelope
        if (sustain.getUnit() == "dB") {
            sustainLevel = Param::fromDb(sustain.get());
        }
        else {
            sustainLevel = sustain.get();
        }

        // number of samples for all phases
        int attackSamples = static_cast<int>(sampleRate * attack.get() * (1.0f - currentVelocity * keyVelToEnv.get()));
        int decaySamples = static_cast<int>(sampleRate * decay.get() * (1.0f - currentVelocity * keyVelToEnv.get()));
        int releaseSamples = static_cast<int>(sampleRate * release.get());

        // get growth/shrink rate from knobs
        float attackGrowthRate = attackShape.get();
        float decayShrinkRate = decayShape.get();
        float releaseShrinkRate = releaseShape.get();

        // release phase sets envCoeff from valueAtRelease to 0.0f
        if (releaseCounter > -1)
        {
            if (releaseShrinkRate < 1.0f)
            {
                releaseShrinkRate = 1 / releaseShrinkRate;
                envCoeff = valueAtRelease * (1 - interpolateLog(releaseCounter, releaseSamples, releaseShrinkRate, true));
            }
            else
            {
                envCoeff = valueAtRelease * interpolateLog(releaseCounter, releaseSamples, releaseShrinkRate, false);
            }
            releaseCounter++;
        }
        else
        {
            // attack phase sets envCoeff from 0.0f to 1.0f
            if (attackDecayCounter <= attackSamples)
            {
                if (attackGrowthRate < 1.0f)
                {
                    attackGrowthRate = 1 / attackGrowthRate;
                    envCoeff = interpolateLog(attackDecayCounter, attackSamples, attackGrowthRate, true);
                }
                else
                {
                    envCoeff = 1.0f - interpolateLog(attackDecayCounter, attackSamples, attackGrowthRate, false);
                }
                valueAtRelease = envCoeff;
                attackDecayCounter++;
            }
            else
            {
                // decay phase sets envCoeff from 1.0f to sustain level
                if (attackDecayCounter <= attackSamples + decaySamples)
                {
                    if (decayShrinkRate < 1.0f)
                    {
                        decayShrinkRate = 1 / decayShrinkRate;
                        envCoeff = 1 - interpolateLog(attackDecayCounter - attackSamples, decaySamples, decayShrinkRate, true) * (1.0f - sustainLevel);
                    }
                    else
                    {
                        envCoeff = interpolateLog(attackDecayCounter - attackSamples, decaySamples, decayShrinkRate, false) * (1.0f - sustainLevel) + sustainLevel;
                    }
                    valueAtRelease = envCoeff;
                    attackDecayCounter++;
                }
                else // if attack and decay phase is over then sustain level
                {
                    envCoeff = sustainLevel;
                    valueAtRelease = envCoeff;
                }
            }
        }
        return envCoeff;
    }*/

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
