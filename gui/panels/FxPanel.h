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

#ifndef __JUCE_HEADER_514EB6F5B07AB0C4__
#define __JUCE_HEADER_514EB6F5B07AB0C4__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PanelBase.h"
#include "FxDelay.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class FxPanel  : public PanelBase,
                 public SliderListener,
                 public ButtonListener,
                 public ComboBoxListener
{
public:
    //==============================================================================
    FxPanel (SynthParams &p);
    ~FxPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    FxDelay *delay;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<MouseOverKnob> feedbackSlider;
    ScopedPointer<MouseOverKnob> dryWetSlider;
    ScopedPointer<MouseOverKnob> timeSlider;
    ScopedPointer<ToggleButton> syncToggle;
    ScopedPointer<ComboBox> dividend;
    ScopedPointer<ComboBox> divisor;
    ScopedPointer<MouseOverKnob> cutoffSlider;
    ScopedPointer<MouseOverKnob> resSlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FxPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_514EB6F5B07AB0C4__
