/*
  ==============================================================================

    EnvelopeCurve.cpp
    Created: 24 Jan 2016 5:27:07pm
    Author:  Juan Cabello

  ==============================================================================
*/

#include "EnvelopeCurve.h"

//==============================================================================

EnvelopeCurve::~EnvelopeCurve()
{
}

void EnvelopeCurve::setSamples()
{

    sustainLevel_ = (96.f + sustain_) / 96.f;

    float samplesSection = getWidth() / 4.0f;

    attackSamples = (attack_ * samplesSection/4) != 0.f ?
    static_cast<int>(ceil(attack_ * samplesSection/4)) :
    1;

    decaySamples = static_cast<int>(decay_ * samplesSection/4);
    releaseSamples = (release_ * (samplesSection)/4 ) != 0.f ?
    static_cast<int>(ceil(release_ * samplesSection/4)) :
    1;

    // NOTE: the 2 at the end are responsible for the ending of the curve
    sustainSamples = getWidth() - (attackSamples + decaySamples + releaseSamples + 2);

    samplesCounter_ = 0;

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
    if (samplesCounter_ <= attackSamples)
    {
        if (attackShape_ < 1.0f)
        {
            float attackGrowthRate = 1 / attackShape_;
            envCoeff = Envelope::interpolateLog(samplesCounter_, attackSamples, attackGrowthRate, true);
        }
        else
        {
            envCoeff = 1.0f - Envelope::interpolateLog(samplesCounter_, attackSamples, attackShape_, false);
        }
        valueAtRelease_ = envCoeff;
        samplesCounter_++;
    }
    // decay phase sets envCoeff from 1.0f to sustain level
    else if (samplesCounter_ <= attackSamples + decaySamples)
    {
        if (decayShape_ < 1.0f)
        {
            float decayShrinkRate = 1 / decayShape_;
            envCoeff = 1 - Envelope::interpolateLog(samplesCounter_ - attackSamples, decaySamples, decayShrinkRate, true) * (1.0f - sustainLevel_);
        }
        else
        {
            envCoeff = Envelope::interpolateLog(samplesCounter_ - attackSamples, decaySamples, decayShape_, false) * (1.0f - sustainLevel_) + sustainLevel_;

        }
        valueAtRelease_ = envCoeff;
        samplesCounter_++;
    }
    // if attack and decay phase is over then sustain level
    else if (samplesCounter_ <= attackSamples + decaySamples + sustainSamples)
    {
        envCoeff = sustainLevel_;
        valueAtRelease_ = envCoeff;
        samplesCounter_++;
    }
    // release phase sets envCoeff from valueAtRelease to 0.0f
    else if (samplesCounter_ <= attackSamples + decaySamples + sustainSamples + releaseSamples)
    {
        if (releaseShape_ < 1.0f)
        {
            float releaseShrinkRate = 1 / releaseShape_;
            envCoeff = valueAtRelease_ * (1 - Envelope::interpolateLog(samplesCounter_ - attackSamples - decaySamples - sustainSamples, releaseSamples, releaseShrinkRate, true));
        }
        else
        {
            envCoeff = valueAtRelease_ * Envelope::interpolateLog(samplesCounter_ - attackSamples - decaySamples - sustainSamples, releaseSamples, releaseShape_, false);
        }
        samplesCounter_++;
    }
    else
    {
        return 0.f;
    }

    return envCoeff;

}

void EnvelopeCurve::paint (Graphics& g)
{
    // TODO: gradient for less than 1 samples
    FillType backgroundFill = FillType(SynthParams::envelopeCurveBackground);
    backgroundFill.setOpacity(1.0f);
    g.setFillType(backgroundFill);
    g.fillAll();

    Path curvePath;
    const int width = getWidth();
    setSamples();
    curvePath.startNewSubPath(0.0f, static_cast<float>(getHeight()));

    for (float i = 1.0f; i < width; ++i) {
        curvePath.lineTo(i, (getHeight())*(1.013f - getEnvCoef()));
    }

    g.setColour(SynthParams::envelopeCurveLine);
    g.strokePath(curvePath, PathStrokeType(2.5f));
}

void EnvelopeCurve::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
