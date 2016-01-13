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
                  public ButtonListener,
                  public ComboBoxListener
{
public:
    //==============================================================================
    SeqPanel (SynthParams &p);
    ~SeqPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    /**
    * timerCallback() is needed here to display the currently playing note step.
    */
    virtual void timerCallback() override;

    /**
    * Generate a random sequence by setting each step random.
    The lowest and highest random note can be set with provided functions.
    */
    void generateRandomSeq();

    /**
    * Function to set a specific step as activated or mute.
    @param step the (step+1)th sequence note in range of [0..7]
    @param active false->mute
    */
    void setStepActive(int step, bool active);

    /**
    * Is true if stepSequencer is playing with or without host.
    */
    bool isPlaying();

    /**
    * Is true if specific step is activated and should play.
    @param step in range [0..7]
    */
    bool isStepActive(int step);

    /**
    * Get current step speed as a string in format '1/denominator'
    with denominator in {1, 2, 4, 8, 16, 32, 64}.
    */
    String getStepSpeedAsString();

    /**
    * Get current step length as a string in format '1/denominator'
    with denominator in {1, 2, 4, 8, 16, 32, 64}.
    */
    String getStepLengthAsString();

    /**
    * Get the note name as a string of a specific step by using MidiMessage::getMidiNoteName().
    @param step in range [0..7]
    @param sharps if true use sharps and flats
    @octaveNumber if true display octave number
    @middleC number to use for middle c
    */
    String getStepNoteName(int step, bool sharps, bool octaveNumber, int middleC);

    /**
    * Set step speed from a string representing note length (e.g 1/4, 1/16 ...).
    @param stepSpeed is assumed to be in the proper format; the function only takes the String after '/',
    converts it to an int to use that as the denominator.
    The denominator should be of {1, 2, 4, 8, 16, 32, 64}, the nominator will be ignored.
    */
    void setStepSpeed(const String stepSpeed);

    /**
    * Set step length from a string representing note length (e.g 1/4, 1/16 ...).
    @param stepLength is assumed to be in the proper format; the function only takes the String after '/',
    converts it to an int to use that as the denominator.
    The denominator should be of {1, 2, 4, 8, 16, 32, 64}, the nominator will be ignored.
    */
    void setStepLength(const String stepLength);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    std::array<ScopedPointer<MouseOverKnob>, 8> seqStepArray;
    std::array<ScopedPointer<TextButton>, 8> labelButtonArray;

    std::array<Param*, 8> currMidiStepSeq;
    std::array<ParamStepped<eOnOffToggle>*, 8> currStepOnOff;

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
