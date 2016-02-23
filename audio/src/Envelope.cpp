/*
==============================================================================

Envelope.cpp
Created: 11 Dec 2015 3:14:14pm
Author:  Nhat Duc Tran and Anton Schmied

==============================================================================
*/

#include "Envelope.h"

void Envelope::resetReleaseCounter()
{
    releaseCounter = 0;
}

void Envelope::startEnvelope()
{
    releaseCounter = -1;
    attackDecayCounter = 0;
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
    float coefficent = static_cast<float>(c) / static_cast<float>(t);
    
    return std::exp(std::log((slow) ? coefficent : 1.0f - coefficent) * k);
}