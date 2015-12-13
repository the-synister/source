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
    Envelope(SynthParams &p, float sampleRate, float currentVelocity)
        :params(p)
        ,releaseCounter(-1)
        ,freeEnv1ReleaseCounter(-1)
        ,attackDecayCounter(0)
        ,freeEnv1AttackDecayCounter(0)
        ,sampleRate(sampleRate)
        ,currentVelocity(currentVelocity)
    {
        
    }
    
    //Destructor
    ~Envelope(){}
    
    float getEnv1Coeff();
    float getEnvCoeff();
    float interpolateLog(int curr, int t);
    float interpolateLog(int c, int t, float k, bool slow);
    void resetAllCounters();
    int getReleaseCounter();
    void resetReleaseCounter();
    int getfreeEnv1ReleaseCounter();
    void resetfreeEnv1ReleaseCounter();

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
};

#endif  // ENVELOPE_H_INCLUDED
