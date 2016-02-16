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

#ifndef __JUCE_HEADER_7B9503E899CF8C9A__
#define __JUCE_HEADER_7B9503E899CF8C9A__

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
class FiltPanel  : public PanelBase,
                   public SliderListener,
                   public ComboBoxListener
{
public:
    //==============================================================================
    FiltPanel (SynthParams &p, int filterNumber);
    ~FiltPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void onOffSwitchChanged();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SynthParams::Filter& filter;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<MouseOverKnob> cutoffSlider;
    ScopedPointer<MouseOverKnob> resonanceSlider;
    ScopedPointer<MouseOverKnob> cutoffSlider2;
    ScopedPointer<Slider> passtype;
    ScopedPointer<MouseOverKnob> lpModAmount1;
    ScopedPointer<ComboBox> lp1ModSrc1;
    ScopedPointer<ComboBox> hp1ModSrc1;
    ScopedPointer<ComboBox> lp1ModSrc2;
    ScopedPointer<ComboBox> hp1ModSrc2;
    ScopedPointer<ComboBox> res1ModSrc1;
    ScopedPointer<ComboBox> res1ModSrc2;
    ScopedPointer<MouseOverKnob> lpModAmount2;
    ScopedPointer<Label> ladderLabel;
    ScopedPointer<Label> bandpassLabel;
    ScopedPointer<Label> highpassLabel;
    ScopedPointer<Label> lowpassLabel;
    ScopedPointer<MouseOverKnob> hpModAmount1;
    ScopedPointer<MouseOverKnob> hpModAmount2;
    ScopedPointer<MouseOverKnob> resModAmount1;
    ScopedPointer<MouseOverKnob> resModAmount2;
    ScopedPointer<Slider> onOffSwitch;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FiltPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_7B9503E899CF8C9A__
