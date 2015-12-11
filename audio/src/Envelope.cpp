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
    freeEnv1ReleaseCounter = -1;
    attackDecayCounter = 0;
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
        //jassert(isfinite(filterEnvCoeff));
        return freeEnvCoeff;
    }
    
    float Envelope::getEnvCoeff() 
    {
        float envCoeff;
        float sustainLevel = Param::fromDb(params.envSustain.get());

        // number of samples for all phases
        int attackSamples = static_cast<int>(sampleRate * params.envAttack.get());
        int decaySamples = static_cast<int>(sampleRate * params.envDecay.get());
        int releaseSamples = static_cast<int>(sampleRate * params.envRelease.get());

        // release phase sets envCoeff from valueAtRelease to 0.0f
        if (releaseCounter > -1)
        {
            envCoeff = valueAtRelease * interpolateLog(releaseCounter, releaseSamples);
            releaseCounter++;
        }
        else
        {
            // attack phase sets envCoeff from 0.0f to 1.0f
            if (attackDecayCounter <= attackSamples)
            {
                envCoeff = 1.0f - interpolateLog(attackDecayCounter, attackSamples);
                valueAtRelease = envCoeff;
                attackDecayCounter++;
            }
            else
            {
                // decay phase sets envCoeff from 1.0f to sustain level
                if (attackDecayCounter <= attackSamples + decaySamples)
                {
                    envCoeff = interpolateLog(attackDecayCounter - attackSamples, decaySamples) * (1.0f - sustainLevel) + sustainLevel;
                    valueAtRelease = envCoeff;
                    attackDecayCounter++;
                }

                // if attack and decay phase is over then sustain level
                else
                {
                    envCoeff = sustainLevel;
                }
            }
        }
        //std::cout << envCoeff;
        return envCoeff;
    }

    float Envelope::interpolateLog(int curr, int t)
    {
        // coeff of growth/shrink, maybe on which depends on time is better?
        float k = std::exp(1.0f);

        return std::exp(std::log(1.0f - static_cast<float>(curr) / static_cast<float>(t)) * k);
    }