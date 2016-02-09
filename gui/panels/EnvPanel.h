/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_B8FE7FA7A346D8E2__
#define __JUCE_HEADER_B8FE7FA7A346D8E2__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PanelBase.h"
#include "EnvelopeCurve.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
An auto-generated component, created by the Introjucer.

Describe your class and how it works here!
                                                                    //[/Comments]
*/
class EnvPanel  : public PanelBase,
                  public SliderListener
{
public:
    //==============================================================================
    EnvPanel (SynthParams &p);
    ~EnvPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void updateCurve();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<MouseOverKnob> attackTime1;
    ScopedPointer<MouseOverKnob> decayTime1;
    ScopedPointer<MouseOverKnob> sustainLevel1;
    ScopedPointer<MouseOverKnob> releaseTime1;
    ScopedPointer<MouseOverKnob> attackShape1;
    ScopedPointer<MouseOverKnob> decayShape1;
    ScopedPointer<MouseOverKnob> releaseShape1;
    ScopedPointer<MouseOverKnob> keyVelToEnv1;
    ScopedPointer<EnvelopeCurve> envelopeCurve1;
    ScopedPointer<Label> shapeLabel1;
    ScopedPointer<MouseOverKnob> attackTime2;
    ScopedPointer<MouseOverKnob> decayTime2;
    ScopedPointer<MouseOverKnob> sustainLevel2;
    ScopedPointer<MouseOverKnob> releaseTime2;
    ScopedPointer<MouseOverKnob> attackShape2;
    ScopedPointer<MouseOverKnob> decayShape2;
    ScopedPointer<MouseOverKnob> releaseShape2;
    ScopedPointer<MouseOverKnob> keyVelToEnv2;
    ScopedPointer<EnvelopeCurve> envelopeCurve2;
    ScopedPointer<Label> shapeLabel2;
    ScopedPointer<MouseOverKnob> attackTime3;
    ScopedPointer<MouseOverKnob> decayTime3;
    ScopedPointer<MouseOverKnob> sustainLevel3;
    ScopedPointer<MouseOverKnob> releaseTime3;
    ScopedPointer<MouseOverKnob> attackShape3;
    ScopedPointer<MouseOverKnob> decayShape3;
    ScopedPointer<MouseOverKnob> releaseShape3;
    ScopedPointer<MouseOverKnob> keyVelToEnv3;
    ScopedPointer<EnvelopeCurve> envelopeCurve3;
    ScopedPointer<Label> shapeLabel3;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_B8FE7FA7A346D8E2__
