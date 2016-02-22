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
    void updateToggleState();
    void updateNoteNameLabels();
    void updateMinMaxLabels();
    void drawPics(Graphics& g, ScopedPointer<Slider>& seqPlayMode, ScopedPointer<ToggleButton>& syncT, ScopedPointer<ToggleButton>& tripletT);

    /**
    * timerCallback() is needed here to display the currently playing note step.
    */
    virtual void timerCallback() override;

    /**
    * Is true if stepSequencer is playing with or without host.
    */
    bool isPlaying();

    /**
    * Get the note name as a string of a specific step by using MidiMessage::getMidiNoteName().
    @param step in range [0..7]
    @param sharps if true use sharps and flats
    @octaveNumber if true display octave number
    @middleC number to use for middle c
    */
    String getStepNoteName(int step, bool sharps, bool octaveNumber, int middleC);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Image syncPic, tripletPic, sequentialPic, upDownPic, randomPic;

    std::array<ScopedPointer<Slider>, 8> seqStepArray;
    std::array<ScopedPointer<TextButton>, 8> labelButtonArray;

    std::array<Param*, 8> currMidiStepSeq;
    std::array<ParamStepped<eOnOffToggle>*, 8> currStepOnOff;

    int lastSeqNotePos = -1;
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
    ScopedPointer<IncDecDropDown> seqStepSpeed;
    ScopedPointer<IncDecDropDown> seqStepLength;
    ScopedPointer<IncDecDropDown> seqNumSteps;
    ScopedPointer<Label> labelSeqSpeed;
    ScopedPointer<Label> labelSeqLength;
    ScopedPointer<Label> labelSeqStepNum;
    ScopedPointer<ToggleButton> triplets;
    ScopedPointer<TextButton> saveSeq;
    ScopedPointer<TextButton> loadSeq;
    ScopedPointer<Slider> playModes;
    ScopedPointer<ToggleButton> dottedNotes;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SeqPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_1700DD60DF66F07A__
