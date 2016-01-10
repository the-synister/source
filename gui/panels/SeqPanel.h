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
#include "../audio/inc/PluginProcessor.h"
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
                  public ButtonListener,
                  public ComboBoxListener
{
public:
    //==============================================================================
    SeqPanel (SynthParams &p);
    ~SeqPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    virtual void timerCallback() override;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    static StepSequencer* seq;
    std::array<ScopedPointer<MouseOverKnob>, 8> seqStepArray;
    std::array<ScopedPointer<TextButton>, 8> labelButtonArray;

    int lastSeqNotePos = -1;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<MouseOverKnob> seqStep1;
    ScopedPointer<MouseOverKnob> seqStep2;
    ScopedPointer<MouseOverKnob> seqStep3;
    ScopedPointer<MouseOverKnob> seqStep4;
    ScopedPointer<MouseOverKnob> seqStep5;
    ScopedPointer<MouseOverKnob> seqStep6;
    ScopedPointer<MouseOverKnob> seqStep7;
    ScopedPointer<MouseOverKnob> seqStep8;
    ScopedPointer<TextButton> seqPlay;
    ScopedPointer<ToggleButton> syncHost;
    ScopedPointer<TextButton> labelButton1;
    ScopedPointer<TextButton> labelButton2;
    ScopedPointer<TextButton> labelButton3;
    ScopedPointer<TextButton> labelButton4;
    ScopedPointer<TextButton> labelButton5;
    ScopedPointer<TextButton> labelButton6;
    ScopedPointer<TextButton> labelButton7;
    ScopedPointer<TextButton> labelButton8;
    ScopedPointer<TextButton> genRandom;
    ScopedPointer<Slider> randomSeq;
    ScopedPointer<Label> randMinLabel;
    ScopedPointer<Label> randMaxLabel;
    ScopedPointer<ToggleButton> playUpDown;
    ScopedPointer<ComboBox> seqStepSpeed;
    ScopedPointer<ComboBox> seqStepLength;
    ScopedPointer<ComboBox> seqNumSteps;
    ScopedPointer<Label> labelSeqSpeed;
    ScopedPointer<Label> labelSeqLength;
    ScopedPointer<Label> labelSeqStepNum;
    ScopedPointer<ToggleButton> playRandom;
    ScopedPointer<ToggleButton> triplets;
    ScopedPointer<TextButton> saveSeq;
    ScopedPointer<TextButton> loadSeq;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SeqPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_1700DD60DF66F07A__
