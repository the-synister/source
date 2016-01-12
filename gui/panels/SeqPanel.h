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

#ifndef __JUCE_HEADER_1700DD60DF66F07A__
#define __JUCE_HEADER_1700DD60DF66F07A__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PanelBase.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SeqPanel  : public PanelBase,
                  public SliderListener,
                  public ButtonListener
{
public:
    //==============================================================================
    SeqPanel (SynthParams &p);
    ~SeqPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> seqStep1;
    ScopedPointer<Slider> seqStep2;
    ScopedPointer<Slider> seqStep3;
    ScopedPointer<Slider> seqStep4;
    ScopedPointer<Slider> seqStep5;
    ScopedPointer<Slider> seqStep6;
    ScopedPointer<Slider> seqStep7;
    ScopedPointer<Slider> seqStep8;
    ScopedPointer<MouseOverKnob> seqStepSpeed;
    ScopedPointer<MouseOverKnob> seqStepLength;
    ScopedPointer<TextButton> seqPlay;
    ScopedPointer<ToggleButton> syncHost;
    ScopedPointer<MouseOverKnob> seqNumSteps;
    ScopedPointer<Label> labelStep1;
    ScopedPointer<Label> labelStep2;
    ScopedPointer<Label> labelStep3;
    ScopedPointer<Label> labelStep4;
    ScopedPointer<Label> labelStep5;
    ScopedPointer<Label> labelStep6;
    ScopedPointer<Label> labelStep7;
    ScopedPointer<Label> labelStep8;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SeqPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_1700DD60DF66F07A__
