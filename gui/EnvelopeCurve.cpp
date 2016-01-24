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

float EnvelopeCurve::getEnvCoef()
{
    float envCoeff;
    float sustainLevel = Param::fromDb(sustain_);
    
    // number of samples for all phases
    // if needed consider key velocity for attack and decay
    int attackSamples = static_cast<int>(1024 * attack_);
    int decaySamples = static_cast<int>(1024 * decay_);
    int releaseSamples = static_cast<int>(1024 * release_);
    
    // get growth/shrink rate from knobs
    float attackGrowthRate = attackShape_;
    float decayShrinkRate = decayShape_;
    float releaseShrinkRate = releaseShape_;
    
    // release phase sets envCoeff from valueAtRelease to 0.0f
    if (releaseCounter_ > -1)
    {
        if (releaseShrinkRate < 1.0f)
        {
            releaseShrinkRate = 1 / releaseShrinkRate;
            envCoeff = valueAtRelease_ * (1 - interpolateLog(releaseCounter_, releaseSamples, releaseShrinkRate, true));
        }
        else
        {
            envCoeff = valueAtRelease_ * interpolateLog(releaseCounter_, releaseSamples, releaseShrinkRate, false);
        }
        releaseCounter_++;
    }
    else
    {
        // attack phase sets envCoeff from 0.0f to 1.0f
        if (attackDecayCounter_ <= attackSamples)
        {
            if (attackGrowthRate < 1.0f)
            {
                attackGrowthRate = 1 / attackGrowthRate;
                envCoeff = interpolateLog(attackDecayCounter_, attackSamples, attackGrowthRate, true);
            }
            else
            {
                envCoeff = 1.0f - interpolateLog(attackDecayCounter_, attackSamples, attackGrowthRate, false);
            }
            valueAtRelease_ = envCoeff;
            attackDecayCounter_++;
        }
        else
        {
            // decay phase sets envCoeff from 1.0f to sustain level
            if (attackDecayCounter_ <= attackSamples + decaySamples)
            {
                if (decayShrinkRate < 1.0f)
                {
                    decayShrinkRate = 1 / decayShrinkRate;
                    envCoeff = 1 - interpolateLog(attackDecayCounter_ - attackSamples, decaySamples, decayShrinkRate, true) * (1.0f - sustainLevel);
                }
                else
                {
                    envCoeff = interpolateLog(attackDecayCounter_ - attackSamples, decaySamples, decayShrinkRate, false) * (1.0f - sustainLevel) + sustainLevel;
                }
                valueAtRelease_ = envCoeff;
                attackDecayCounter_++;
            }
            else // if attack and decay phase is over then sustain level
            {
                envCoeff = sustainLevel;
                valueAtRelease_ = envCoeff;
            }
        }
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
    const int startPointY = getHeight() - 5;
    const int width = getWidth();
    
    curvePath.startNewSubPath(0, startPointY);
    
    for (int i = 1; i < width; ++i) {
        curvePath.lineTo(i, getEnvCoef());
    }
    
    g.setColour(Colours::lightgreen);
    g.strokePath(curvePath, PathStrokeType(2.5f));
 /*

    Path wavePath;
    const float centreY = getHeight() / 2.0f;
    const float amplitude = 0.4f;
    const int width = getWidth();
    const float step = 4*float_Pi / width;
    wavePath.startNewSubPath(0, centreY);
    
    for (float x = 1.0f; x < width; ++x) {
        
        float phs = x * step;
        if (phs > (2 * float_Pi))
            phs = phs - (2 * float_Pi);
        
        switch (m_iWaveformKey)
        {
            case eOscWaves::eOscSquare:
                wavePath.lineTo(x, centreY - amplitude * static_cast<float>(getHeight()) * Waveforms::square(phs, m_fTrngAmount, m_fPulseWidth));
                break;
                
            case eOscWaves::eOscSaw:
                wavePath.lineTo(x, centreY - amplitude * static_cast<float>(getHeight()) * Waveforms::saw(phs, m_fTrngAmount, m_fPulseWidth));
                break;
                
            case eOscWaves::eOscNoise:
                wavePath.lineTo(x, centreY - amplitude * static_cast<float>(getHeight()) * Waveforms::whiteNoise(phs, m_fTrngAmount, m_fPulseWidth));
                break;
                
        }
        
    }*/

}

void EnvelopeCurve::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
