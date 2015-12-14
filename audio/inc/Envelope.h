/*
  ==============================================================================

    Envelope.h
    Created: 11 Dec 2015 3:13:56pm
    Author:  Anton

  ==============================================================================
*/

#ifndef ENVELOPE_H_INCLUDED
#define ENVELOPE_H_INCLUDED

#include "Synthparams.h"
#include "Param.h"

class Envelope{
    public:
    //Constructor
    Envelope(SynthParams &p, float sampleRate)
        :params(p)
        ,releaseCounter(-1)
        ,freeEnv1ReleaseCounter(-1)
        ,attackDecayCounter(0)
        ,freeEnv1AttackDecayCounter(0)
        ,sampleRate(sampleRate)
    {
        
    }
    
    //Destructor
    ~Envelope(){}

    //void resetAllCounters();
    void startEnvelope(float currentVelocity);

    int getReleaseCounter();
    void resetReleaseCounter();

    int getfreeEnv1ReleaseCounter();
    void resetfreeEnv1ReleaseCounter();

    const float getEnv1Coeff()
    {
        float freeEnvCoeff;
        float sustainLevel = params.freeEnv1Sustain.get();

        //number of all samples for all phases
        int attackSamples = static_cast<int>(sampleRate * params.freeEnv1Attack.get());
        int decaySamples = static_cast<int>(sampleRate * params.freeEnv1Decay.get());
        int releaseSamples = static_cast<int>(sampleRate * params.freeEnv1Release.get());

        if (freeEnv1ReleaseCounter > -1)
        {
            freeEnvCoeff = freeEnv1ValueAtRelease * interpolateLog(freeEnv1ReleaseCounter, releaseSamples);
            freeEnv1ReleaseCounter++;
        }
        else
        {
            if (freeEnv1AttackDecayCounter <= attackSamples)
            {
                freeEnvCoeff = 1.0f - interpolateLog(freeEnv1AttackDecayCounter, attackSamples);
                freeEnv1ValueAtRelease = freeEnvCoeff;
                freeEnv1AttackDecayCounter++;
            }
            else
            {
                if (freeEnv1AttackDecayCounter <= attackSamples + decaySamples)
                {
                    freeEnvCoeff = interpolateLog(freeEnv1AttackDecayCounter - attackSamples, decaySamples) * (1.0f - sustainLevel) + sustainLevel;
                    freeEnv1ValueAtRelease = freeEnvCoeff;
                    freeEnv1AttackDecayCounter++;
                }

                else
                {
                    freeEnvCoeff = sustainLevel;
                }
            }
        }
        return freeEnvCoeff;
    }
    
    
    const float getEnvCoeff()
    {
        float envCoeff;
        float sustainLevel = Param::fromDb(params.envSustain.get());

        // number of samples for all phases
        // if needed consider key velocity for attack and decay
        int attackSamples = static_cast<int>(sampleRate * params.envAttack.get() * (1.0f - currentVelocity * params.keyVelToEnv.get()));
        int decaySamples = static_cast<int>(sampleRate * params.envDecay.get() * (1.0f - currentVelocity * params.keyVelToEnv.get()));
        int releaseSamples = static_cast<int>(sampleRate * params.envRelease.get());

        // get growth/shrink rate from knobs
        float attackGrowthRate = params.envAttackShape.get();
        float decayShrinkRate = params.envDecayShape.get();
        float releaseShrinkRate = params.envReleaseShape.get();

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
    }

    private:

    SynthParams &params;

    float sampleRate;
    float currentVelocity;
    
    float valueAtRelease;
    int attackDecayCounter;
    int releaseCounter;

    float freeEnv1ValueAtRelease;
    int freeEnv1AttackDecayCounter;
    int freeEnv1ReleaseCounter;

    static float interpolateLog(int curr, int t);
    static float interpolateLog(int c, int t, float k, bool slow);
};

#endif  // ENVELOPE_H_INCLUDED
