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
    Envelope(SynthParams::EnvBase &_env, Param &_sustain, double _sampleRate)
        : releaseCounter(-1)
        , attackDecayCounter(0)
        , sampleRate(_sampleRate)
        , env(_env)
        , sustain(_sustain)
    {
    }

    //! Enevelope destructor
    ~Envelope(){}

    //! resets the sample counters and sets the current velocity for each new note
    void startEnvelope();

    //! get and reset the release counters for the volume envelope
    int getReleaseCounter() const { return releaseCounter; }
    int getReleaseSamples() const { return releaseSamples; }
    void resetReleaseCounter();


    //! calculation of the volume envelope coefficients (with shape control)
    void calcEnvCoeff(float modValue1, float modValue2, bool isUnipolar1, bool isUnipolar2);

    float getNextEnvCoeff();

    static float interpolateLog(int c, int t, float k, bool slow); //!< interpolates logarithmically from 1.0 to 0.0f in t samples (with shape control)

private:
    inline int calcModRange(float modValue, float modAmount, int sInput, bool isUnipolar) {

        float intensity;
        if (isUnipolar) {
            // if the source is unipolar, transform the intensity to bipolar
            intensity = toBipolar(env.speedModAmount1.getMin(), env.speedModAmount1.getMax(), modAmount);
        }
        else {
            // else the source is bipolar, transform the intensity to unipolar
            intensity = toUnipolar(env.speedModAmount1.getMin(), env.speedModAmount1.getMax(), modAmount);
        }
        float dModValue = modValue*intensity;

        int samples = static_cast<int>(sInput * std::pow(2.f, env.speedModAmount1.getMax() * dModValue));
        int maxSamples = static_cast<int>(env.speedModAmount1.getMax() * sampleRate);

        samples = samples > maxSamples
            ? maxSamples
            : samples;
        samples = samples <= 0
            ? 0
            : samples;

        return samples;
    }
    
    SynthParams::EnvBase& env;   //!< local params
    Param& sustain;         
    double sampleRate;       //!< sample rate
    float valueAtRelease;   //!< amplitude value once release phase starts
    int attackDecayCounter; //!< sample counter during the attack and decay phase
    int attackSamples;
    int decaySamples;
    int releaseSamples;     //!< total Amount of release samples
    int releaseCounter;     //!< sample counter during the release phase
};


inline void Envelope::calcEnvCoeff(float modValue1, float modValue2, bool isUnipolar1, bool isUnipolar2)
{
    // speed mod calculation
    attackSamples = calcModRange(modValue1, env.speedModAmount1.get(), static_cast<int>(sampleRate * env.attack.get()), isUnipolar1);
    attackSamples = calcModRange(modValue2, env.speedModAmount2.get(), attackSamples, isUnipolar2);
    
    decaySamples = calcModRange(modValue1, env.speedModAmount1.get(), static_cast<int>(sampleRate * env.decay.get()), isUnipolar1);
    decaySamples = calcModRange(modValue2, env.speedModAmount1.get(), decaySamples, isUnipolar2);
    
    releaseSamples = calcModRange(modValue1, env.speedModAmount1.get(), static_cast<int>(sampleRate * env.release.get()), isUnipolar1);
    releaseSamples = calcModRange(modValue2, env.speedModAmount1.get(), releaseSamples, isUnipolar2);
    
}


inline float Envelope::getNextEnvCoeff() {
    // get growth/shrink rate from knobs
    float attackGrowthRate = env.attackShape.get();
    float decayShrinkRate = env.decayShape.get();
    float releaseShrinkRate = env.releaseShape.get();
    
    // release phase sets envCoeff from valueAtRelease to 0.0f
    float envCoeff;
    if (releaseCounter > -1)
    {
        if (releaseShrinkRate < 1.0f)
        {
            releaseShrinkRate = 1 / releaseShrinkRate;
            envCoeff = releaseCounter >= releaseSamples
            ? 0.f
            : valueAtRelease * (1 - interpolateLog(releaseCounter, releaseSamples, releaseShrinkRate, true));
        }
        else
        {
            envCoeff = releaseCounter >= releaseSamples
            ? 0.f
            : valueAtRelease * interpolateLog(releaseCounter, releaseSamples, releaseShrinkRate, false);
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
        else{
            
            float sustainLevel = sustain.get();
            // decay phase sets envCoeff from 1.0f to sustain level
            if (attackDecayCounter <= attackSamples + decaySamples){
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
}

#endif  // ENVELOPE_H_INCLUDED
