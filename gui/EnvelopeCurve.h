/*
  ==============================================================================

    EnvelopeCurve.h
    Created: 24 Jan 2016 5:27:07pm
    Author:  Juan Cabello

  ==============================================================================
*/

#ifndef ENVELOPECURVE_H_INCLUDED
#define ENVELOPECURVE_H_INCLUDED

#include "JuceHeader.h"
#include "SynthParams.h"

//==============================================================================
/*
*/
class EnvelopeCurve    : public Component
{
public:
    EnvelopeCurve(float attack, float decay, float sustain, float release, float attackShape, float decayShape, float releaseShape)
    : attack_(attack)
    , decay_(decay)
    , sustain_(sustain)
    , release_(release)
    , attackShape_(attackShape)
    , decayShape_(decayShape)
    , releaseShape_(releaseShape)
    , samplesCounter_(0)
    {};
    ~EnvelopeCurve();

    void setAttack(float);
    void setDecay(float);
    void setRelease(float);
    void setSustain(float);
    void setAttackShape(float);
    void setDecayShape(float);
    void setReleaseShape(float);

    void paint (Graphics&);
    void resized();

private:
    float attack_;
    float decay_;
    float sustain_;
    float release_;
    float attackShape_;
    float decayShape_;
    float releaseShape_;
    float valueAtRelease_;
    float sustainLevel_;
    int samplesCounter_;

    int attackSamples;
    int decaySamples;
    int releaseSamples;
    int sustainSamples;

    float getEnvCoef();
    void setSamples();

    float interpolateLog(int c, int t, float k, bool slow);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeCurve)
};


#endif  // ENVELOPECURVE_H_INCLUDED
