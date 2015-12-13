/*
  ==============================================================================

    Envelope.cpp
    Created: 11 Dec 2015 3:14:14pm
    Author:  Anton

  ==============================================================================
*/

#include "Envelope.h"

int Envelope::getfreeEnv1ReleaseCounter()
{
    return freeEnv1ReleaseCounter;
}

void Envelope::resetfreeEnv1ReleaseCounter()
{
    freeEnv1ReleaseCounter = 0;
}

int Envelope::getReleaseCounter()
{
    return releaseCounter;
}

void Envelope::resetReleaseCounter()
{
    releaseCounter = 0;
}

void Envelope::resetAllCounters()
{
    releaseCounter = -1;
    attackDecayCounter = 0;
    freeEnv1ReleaseCounter = -1;
    freeEnv1AttackDecayCounter = 0;
}

float Envelope::getEnv1Coeff()
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
        if(freeEnv1AttackDecayCounter <= attackSamples)
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
    
    float Envelope::getEnvCoeff() 
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

    /**
    * interpolate logarithmically from 1.0 to 0.0f in t samples
    @param c counter of the specific phase
    @param t number of samples after which the specific phase should be over
    @param k coeff of growth/shrink, k=1 for linear
    @param slow how fast is phase applied at the start
    */
    float Envelope::interpolateLog(int c, int t, float k, bool slow)
    {
        if (slow)
        {
            return std::exp(std::log(static_cast<float>(c) / static_cast<float>(t)) * k);
        }
        else
        {
            return std::exp(std::log(1.0f - static_cast<float>(c) / static_cast<float>(t)) * k);
        }
    }

    /**
    * interpolate logarithmically from 1.0 to 0.0f in t samples
    without the ADSR Shape control
    */
    float Envelope::interpolateLog(int curr, int t)
    {
        // coeff of growth/shrink, maybe on which depends on time is better?
        float k = std::exp(1.0f);

        return std::exp(std::log(1.0f - static_cast<float>(curr) / static_cast<float>(t)) * k);
    }