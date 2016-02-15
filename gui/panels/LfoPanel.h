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

#ifndef __JUCE_HEADER_9F090381585CF062__
#define __JUCE_HEADER_9F090381585CF062__

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
class LfoPanel  : public PanelBase,
                  public SliderListener,
                  public ButtonListener,
                  public ComboBoxListener
{
public:
    //==============================================================================
    LfoPanel (SynthParams &p, int lfoNumber);
    ~LfoPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    String getNoteLengthAsString();
    void drawWaves(Graphics& g, ScopedPointer<Slider>& _waveformSwitch, ScopedPointer<ComboBox>& _gainBox);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Image sineWave, squareWave, sampleHold, gainSign;

    SynthParams::Lfo& lfo;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<MouseOverKnob> freq;
    ScopedPointer<Slider> wave;
    ScopedPointer<ToggleButton> tempoSyncSwitch;
    ScopedPointer<MouseOverKnob> lfoFadeIn;
    ScopedPointer<ToggleButton> triplets;
    ScopedPointer<IncDecDropDown> noteLength;
    ScopedPointer<MouseOverKnob> freqModAmount1;
    ScopedPointer<MouseOverKnob> freqModAmount2;
    ScopedPointer<ComboBox> freqModSrc1;
    ScopedPointer<ComboBox> freqModSrc2;
    ScopedPointer<ComboBox> lfoGain;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LfoPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_9F090381585CF062__
