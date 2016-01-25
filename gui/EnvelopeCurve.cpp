/*
  ==============================================================================

    EnvelopeCurve.cpp
    Created: 24 Jan 2016 5:27:07pm
    Author:  Juan Cabello

  ==============================================================================
*/

#include "../standalone/JuceLibraryCode/JuceHeader.h"
#include "EnvelopeCurve.h"

//==============================================================================

EnvelopeCurve::~EnvelopeCurve()
{
}

void EnvelopeCurve::setSamples()
{
    sustainLevel_ = Param::fromDb(sustain_);
    
    float samplesSection = getWidth()/4;
    
    attackSamples = (attack_ * samplesSection * .187f) > 0.5f ? static_cast<int>(ceil(attack_ * samplesSection * .187f)) : 1;
    decaySamples = static_cast<int>(decay_ * samplesSection * .213f);
    releaseSamples = (release_ * samplesSection * .187f) > 0.5f ? static_cast<int>(ceil(release_ * samplesSection * .187f)) : 1;
    sustainSamples = static_cast<int>(sustainLevel_ * samplesSection);
    
   /* if ((attackSamples + decaySamples + releaseSamples + sustainSamples) < getWidth())
    {
        int rest = getWidth() - (attackSamples + decaySamples + releaseSamples + sustainSamples);
        rest = static_cast<int>(ceil(rest/4));
        attackSamples += rest;
        decaySamples += rest;
        releaseSamples += rest;
        sustainSamples += rest;
    }*/
    
    releaseCounter_ = 0;
    attackDecayCounter_ = 0;
    sustainCounter_ = 0;

}

void EnvelopeCurve::setAttack(float attack)
{
    attack_ = attack;
}

void EnvelopeCurve::setDecay(float decay)
{
    decay_ = decay;
}

void EnvelopeCurve::setSustain(float sustain)
{
    sustain_ = sustain;
}

void EnvelopeCurve::setRelease(float release)
{
    release_ = release;
}

void EnvelopeCurve::setAttackShape(float attackShape)
{
    attackShape_ = attackShape;
}

void EnvelopeCurve::setDecayShape(float decayShape)
{
    decayShape_ = decayShape;
}

void EnvelopeCurve::setReleaseShape(float releaseShape)
{
    releaseShape_ = releaseShape;
}

float EnvelopeCurve::getEnvCoef()
{
    float envCoeff;
    
    // attack phase sets envCoeff from 0.0f to 1.0f
    if (attackDecayCounter_ <= attackSamples)
    {
        if (attackShape_ < 1.0f)
        {
            float attackGrowthRate = 1 / attackShape_;
            envCoeff = interpolateLog(attackDecayCounter_, attackSamples, attackGrowthRate, true);
        }
        else
        {
            envCoeff = 1.0f - interpolateLog(attackDecayCounter_, attackSamples, attackShape_, false);
        }
        valueAtRelease_ = envCoeff;
        attackDecayCounter_++;
    }
    // decay phase sets envCoeff from 1.0f to sustain level
    else if (attackDecayCounter_ <= attackSamples + decaySamples)
    {
        if (decayShape_ < 1.0f)
        {
            float decayShrinkRate = 1 / decayShape_;
            envCoeff = 1 - interpolateLog(attackDecayCounter_ - attackSamples, decaySamples, decayShrinkRate, true) * (1.0f - sustainLevel_);
        }
        else
        {
            envCoeff = interpolateLog(attackDecayCounter_ - attackSamples, decaySamples, decayShape_, false) * (1.0f - sustainLevel_) + sustainLevel_;
        }
        valueAtRelease_ = envCoeff;
        attackDecayCounter_++;
    }
    // if attack and decay phase is over then sustain level
    else if (sustainCounter_ <= sustainSamples)
    {
        envCoeff = sustainLevel_;
        valueAtRelease_ = envCoeff;
        sustainCounter_++;
    }
    // release phase sets envCoeff from valueAtRelease to 0.0f
    else if (releaseCounter_ <= releaseSamples)
    {
        if (releaseShape_ < 1.0f)
        {
            float releaseShrinkRate = 1 / releaseShape_;
            envCoeff = valueAtRelease_ * (1 - interpolateLog(releaseCounter_, releaseSamples, releaseShrinkRate, true));
        }
        else
        {
            envCoeff = valueAtRelease_ * interpolateLog(releaseCounter_, releaseSamples, releaseShape_, false);
        }
        releaseCounter_++;
    } else {
        return 0.f;
    }
    
    return envCoeff;

}

float EnvelopeCurve::interpolateLog(int c, int t, float k, bool slow)
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


void EnvelopeCurve::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll(Colours::black);
    
    Path curvePath;
    const int width = getWidth();
    setSamples();
    curvePath.startNewSubPath(0, getHeight());
    
    for (float i = 1.0f; i < width; ++i) {
        curvePath.lineTo(i, getHeight()*(1.f - getEnvCoef()));
    }
    
    g.setColour(Colours::lightgreen);
    g.strokePath(curvePath, PathStrokeType(2.5f));
}

void EnvelopeCurve::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
