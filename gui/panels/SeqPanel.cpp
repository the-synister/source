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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "SeqPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
StepSequencer *SeqPanel::seq;
//[/MiscUserDefs]

//==============================================================================
SeqPanel::SeqPanel (SynthParams &p)
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (seqStep1 = new MouseOverKnob ("Step 1"));
    seqStep1->setRange (0, 127, 1);
    seqStep1->setSliderStyle (Slider::LinearVertical);
    seqStep1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep1->addListener (this);

    addAndMakeVisible (seqStep2 = new MouseOverKnob ("Step 2"));
    seqStep2->setRange (0, 127, 1);
    seqStep2->setSliderStyle (Slider::LinearVertical);
    seqStep2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep2->addListener (this);

    addAndMakeVisible (seqStep3 = new MouseOverKnob ("Step 3"));
    seqStep3->setRange (0, 127, 1);
    seqStep3->setSliderStyle (Slider::LinearVertical);
    seqStep3->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep3->addListener (this);

    addAndMakeVisible (seqStep4 = new MouseOverKnob ("Step 4"));
    seqStep4->setRange (0, 127, 1);
    seqStep4->setSliderStyle (Slider::LinearVertical);
    seqStep4->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep4->addListener (this);

    addAndMakeVisible (seqStep5 = new MouseOverKnob ("Step 5"));
    seqStep5->setRange (0, 127, 1);
    seqStep5->setSliderStyle (Slider::LinearVertical);
    seqStep5->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep5->addListener (this);

    addAndMakeVisible (seqStep6 = new MouseOverKnob ("Step 6"));
    seqStep6->setRange (0, 127, 1);
    seqStep6->setSliderStyle (Slider::LinearVertical);
    seqStep6->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep6->addListener (this);

    addAndMakeVisible (seqStep7 = new MouseOverKnob ("Step 7"));
    seqStep7->setRange (0, 127, 1);
    seqStep7->setSliderStyle (Slider::LinearVertical);
    seqStep7->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep7->addListener (this);

    addAndMakeVisible (seqStep8 = new MouseOverKnob ("Step 8"));
    seqStep8->setRange (0, 127, 1);
    seqStep8->setSliderStyle (Slider::LinearVertical);
    seqStep8->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep8->addListener (this);

    addAndMakeVisible (seqPlay = new TextButton ("play sequencer"));
    seqPlay->setButtonText (TRANS("Play"));
    seqPlay->setConnectedEdges (Button::ConnectedOnLeft);
    seqPlay->addListener (this);
    seqPlay->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    seqPlay->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));
    seqPlay->setColour (TextButton::textColourOffId, Colours::black);

    addAndMakeVisible (syncHost = new ToggleButton ("Sync Host"));
    syncHost->setButtonText (TRANS("Sync with Host"));
    syncHost->addListener (this);
    syncHost->setColour (ToggleButton::textColourId, Colours::black);

    addAndMakeVisible (labelButton1 = new TextButton ("label button 1"));
    labelButton1->setButtonText (TRANS("C3"));
    labelButton1->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    labelButton1->addListener (this);
    labelButton1->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton1->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));
    labelButton1->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (labelButton2 = new TextButton ("label button 2"));
    labelButton2->setButtonText (TRANS("D3"));
    labelButton2->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    labelButton2->addListener (this);
    labelButton2->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton2->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (labelButton3 = new TextButton ("label button 3"));
    labelButton3->setButtonText (TRANS("E3"));
    labelButton3->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    labelButton3->addListener (this);
    labelButton3->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton3->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (labelButton4 = new TextButton ("label button 4"));
    labelButton4->setButtonText (TRANS("F3"));
    labelButton4->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    labelButton4->addListener (this);
    labelButton4->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton4->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (labelButton5 = new TextButton ("label button 5"));
    labelButton5->setButtonText (TRANS("G3"));
    labelButton5->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    labelButton5->addListener (this);
    labelButton5->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton5->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (labelButton6 = new TextButton ("label button 6"));
    labelButton6->setButtonText (TRANS("A3"));
    labelButton6->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    labelButton6->addListener (this);
    labelButton6->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton6->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (labelButton7 = new TextButton ("label button 7"));
    labelButton7->setButtonText (TRANS("B3"));
    labelButton7->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    labelButton7->addListener (this);
    labelButton7->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton7->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (labelButton8 = new TextButton ("label button 8"));
    labelButton8->setButtonText (TRANS("C4"));
    labelButton8->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    labelButton8->addListener (this);
    labelButton8->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton8->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (genRandom = new TextButton ("generate random"));
    genRandom->setButtonText (TRANS("Generate Sequence"));
    genRandom->addListener (this);

    addAndMakeVisible (randomSeq = new Slider ("random sequence"));
    randomSeq->setRange (0, 127, 0);
    randomSeq->setSliderStyle (Slider::TwoValueHorizontal);
    randomSeq->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    randomSeq->addListener (this);

    addAndMakeVisible (randMinLabel = new Label ("random min label",
                                                 TRANS("Min: C-2")));
    randMinLabel->setFont (Font (16.00f, Font::plain));
    randMinLabel->setJustificationType (Justification::centred);
    randMinLabel->setEditable (false, false, false);
    randMinLabel->setColour (TextEditor::textColourId, Colours::black);
    randMinLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (randMaxLabel = new Label ("random max label",
                                                 TRANS("Max: G8")));
    randMaxLabel->setFont (Font (16.00f, Font::plain));
    randMaxLabel->setJustificationType (Justification::centred);
    randMaxLabel->setEditable (false, false, false);
    randMaxLabel->setColour (TextEditor::textColourId, Colours::black);
    randMaxLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (playUpDown = new ToggleButton ("play up down"));
    playUpDown->setButtonText (TRANS("Play Up/Down"));
    playUpDown->addListener (this);

    addAndMakeVisible (seqStepSpeed = new ComboBox ("seq step speed"));
    seqStepSpeed->setEditableText (false);
    seqStepSpeed->setJustificationType (Justification::centred);
    seqStepSpeed->setTextWhenNothingSelected (TRANS("Step Speed"));
    seqStepSpeed->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    seqStepSpeed->addItem (TRANS("1/64"), 1);
    seqStepSpeed->addItem (TRANS("1/32"), 2);
    seqStepSpeed->addItem (TRANS("1/16"), 3);
    seqStepSpeed->addItem (TRANS("1/8"), 4);
    seqStepSpeed->addItem (TRANS("1/4"), 5);
    seqStepSpeed->addItem (TRANS("1/2"), 6);
    seqStepSpeed->addItem (TRANS("1/1"), 7);
    seqStepSpeed->addListener (this);

    addAndMakeVisible (seqStepLength = new ComboBox ("seq step length"));
    seqStepLength->setEditableText (false);
    seqStepLength->setJustificationType (Justification::centred);
    seqStepLength->setTextWhenNothingSelected (TRANS("Step Length"));
    seqStepLength->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    seqStepLength->addItem (TRANS("1/64"), 1);
    seqStepLength->addItem (TRANS("1/32"), 2);
    seqStepLength->addItem (TRANS("1/16"), 3);
    seqStepLength->addItem (TRANS("1/8"), 4);
    seqStepLength->addItem (TRANS("1/4"), 5);
    seqStepLength->addItem (TRANS("1/2"), 6);
    seqStepLength->addItem (TRANS("1/1"), 7);
    seqStepLength->addListener (this);

    addAndMakeVisible (seqNumSteps = new ComboBox ("seq num steps"));
    seqNumSteps->setEditableText (false);
    seqNumSteps->setJustificationType (Justification::centred);
    seqNumSteps->setTextWhenNothingSelected (TRANS("Num Steps"));
    seqNumSteps->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    seqNumSteps->addItem (TRANS("1"), 1);
    seqNumSteps->addItem (TRANS("2"), 2);
    seqNumSteps->addItem (TRANS("3"), 3);
    seqNumSteps->addItem (TRANS("4"), 4);
    seqNumSteps->addItem (TRANS("5"), 5);
    seqNumSteps->addItem (TRANS("6"), 6);
    seqNumSteps->addItem (TRANS("7"), 7);
    seqNumSteps->addItem (TRANS("8"), 8);
    seqNumSteps->addListener (this);

    addAndMakeVisible (labelSeqSpeed = new Label ("new seq speed",
                                                  TRANS("Step Speed")));
    labelSeqSpeed->setFont (Font (14.00f, Font::plain));
    labelSeqSpeed->setJustificationType (Justification::centredLeft);
    labelSeqSpeed->setEditable (false, false, false);
    labelSeqSpeed->setColour (TextEditor::textColourId, Colours::black);
    labelSeqSpeed->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelSeqLength = new Label ("new seq length",
                                                   TRANS("Step Length")));
    labelSeqLength->setFont (Font (14.00f, Font::plain));
    labelSeqLength->setJustificationType (Justification::centredLeft);
    labelSeqLength->setEditable (false, false, false);
    labelSeqLength->setColour (TextEditor::textColourId, Colours::black);
    labelSeqLength->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelSeqStepNum = new Label ("new seq step num",
                                                    TRANS("Num Steps")));
    labelSeqStepNum->setFont (Font (14.00f, Font::plain));
    labelSeqStepNum->setJustificationType (Justification::centredLeft);
    labelSeqStepNum->setEditable (false, false, false);
    labelSeqStepNum->setColour (TextEditor::textColourId, Colours::black);
    labelSeqStepNum->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (playRandom = new ToggleButton ("play random"));
    playRandom->setButtonText (TRANS("Play Random"));
    playRandom->addListener (this);

    addAndMakeVisible (debugLabel = new Label ("debug label",
                                               TRANS("Debug")));
    debugLabel->setFont (Font (15.00f, Font::plain));
    debugLabel->setJustificationType (Justification::centredLeft);
    debugLabel->setEditable (false, false, false);
    debugLabel->setColour (Label::outlineColourId, Colours::black);
    debugLabel->setColour (TextEditor::textColourId, Colours::black);
    debugLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    seq = PluginAudioProcessor::getSequencer();
    randomSeq->setMinAndMaxValues(seq->getRandMin(), seq->getRandMax());

    registerSlider(seqStep1, &params.seqStep1);
    registerSlider(seqStep2, &params.seqStep2);
    registerSlider(seqStep3, &params.seqStep3);
    registerSlider(seqStep4, &params.seqStep4);
    registerSlider(seqStep5, &params.seqStep5);
    registerSlider(seqStep6, &params.seqStep6);
    registerSlider(seqStep7, &params.seqStep7);
    registerSlider(seqStep8, &params.seqStep8);
    seqStepSpeed->setSelectedItemIndex(static_cast<int>(params.seqStepSpeedIndex.get()));
    seqStepLength->setSelectedItemIndex(static_cast<int>(params.seqStepLengthIndex.get()));
    seqNumSteps->setSelectedItemIndex(static_cast<int>(params.seqNumSteps.get()) - 1);

    // init as activated
    labelButton1->setToggleState(true, dontSendNotification);
    labelButton2->setToggleState(true, dontSendNotification);
    labelButton3->setToggleState(true, dontSendNotification);
    labelButton4->setToggleState(true, dontSendNotification);
    labelButton5->setToggleState(true, dontSendNotification);
    labelButton6->setToggleState(true, dontSendNotification);
    labelButton7->setToggleState(true, dontSendNotification);
    labelButton8->setToggleState(true, dontSendNotification);

    seqStepArray = { seqStep1.get(),
                     seqStep2.get(),
                     seqStep3.get(),
                     seqStep4.get(),
                     seqStep5.get(),
                     seqStep6.get(),
                     seqStep7.get(),
                     seqStep8.get() };

    labelButtonArray = { labelButton1.get(),
                         labelButton2.get(),
                         labelButton3.get(),
                         labelButton4.get(),
                         labelButton5.get(),
                         labelButton6.get(),
                         labelButton7.get(),
                         labelButton8.get() };
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SeqPanel::~SeqPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    for (int i = 0; i < 8; ++i)
    {
        seqStepArray[i].release();
        labelButtonArray[i].release();
    }
    //[/Destructor_pre]

    seqStep1 = nullptr;
    seqStep2 = nullptr;
    seqStep3 = nullptr;
    seqStep4 = nullptr;
    seqStep5 = nullptr;
    seqStep6 = nullptr;
    seqStep7 = nullptr;
    seqStep8 = nullptr;
    seqPlay = nullptr;
    syncHost = nullptr;
    labelButton1 = nullptr;
    labelButton2 = nullptr;
    labelButton3 = nullptr;
    labelButton4 = nullptr;
    labelButton5 = nullptr;
    labelButton6 = nullptr;
    labelButton7 = nullptr;
    labelButton8 = nullptr;
    genRandom = nullptr;
    randomSeq = nullptr;
    randMinLabel = nullptr;
    randMaxLabel = nullptr;
    playUpDown = nullptr;
    seqStepSpeed = nullptr;
    seqStepLength = nullptr;
    seqNumSteps = nullptr;
    labelSeqSpeed = nullptr;
    labelSeqLength = nullptr;
    labelSeqStepNum = nullptr;
    playRandom = nullptr;
    debugLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SeqPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SeqPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    // reload gui states
    for (int i = 0; i < 8; ++i)
    {
        labelButtonArray[i]->setToggleState(!seq->isNoteMuted(i), dontSendNotification);
    }

    syncHost->setToggleState((params.seqMode.getStep() == eSeqModes::seqSyncHost), dontSendNotification);
    seqPlay->setToggleState(seq->isPlaying(), dontSendNotification);
    seqStepSpeed->setSelectedItemIndex(static_cast<int>(params.seqStepSpeedIndex.get()));
    seqStepLength->setSelectedItemIndex(static_cast<int>(params.seqStepLengthIndex.get()));
    seqNumSteps->setSelectedItemIndex(static_cast<int>(params.seqNumSteps.get()) - 1);
    playUpDown->setToggleState(seq->isPlayUpDown(), dontSendNotification);
    playRandom->setToggleState(seq->isPlayRandom(), dontSendNotification);
    randomSeq->setMinAndMaxValues(seq->getRandMin(), seq->getRandMax());
    //[/UserPreResize]

    seqStep1->setBounds (336, 32, 48, 264);
    seqStep2->setBounds (392, 32, 48, 264);
    seqStep3->setBounds (448, 32, 48, 264);
    seqStep4->setBounds (504, 32, 48, 264);
    seqStep5->setBounds (560, 32, 48, 264);
    seqStep6->setBounds (616, 32, 48, 264);
    seqStep7->setBounds (672, 32, 48, 264);
    seqStep8->setBounds (728, 32, 48, 264);
    seqPlay->setBounds (20, 25, 100, 24);
    syncHost->setBounds (140, 20, 120, 24);
    labelButton1->setBounds (336, 6, 48, 24);
    labelButton2->setBounds (392, 6, 48, 24);
    labelButton3->setBounds (448, 6, 48, 24);
    labelButton4->setBounds (504, 6, 48, 24);
    labelButton5->setBounds (559, 6, 48, 24);
    labelButton6->setBounds (615, 6, 48, 24);
    labelButton7->setBounds (671, 6, 48, 24);
    labelButton8->setBounds (727, 6, 48, 24);
    genRandom->setBounds (20, 219, 100, 24);
    randomSeq->setBounds (20, 249, 250, 35);
    randMinLabel->setBounds (20, 279, 125, 24);
    randMaxLabel->setBounds (145, 279, 125, 24);
    playUpDown->setBounds (140, 50, 120, 24);
    seqStepSpeed->setBounds (25, 155, 64, 20);
    seqStepLength->setBounds (105, 155, 64, 20);
    seqNumSteps->setBounds (185, 155, 64, 20);
    labelSeqSpeed->setBounds (20, 135, 64, 20);
    labelSeqLength->setBounds (100, 135, 64, 20);
    labelSeqStepNum->setBounds (180, 135, 64, 20);
    playRandom->setBounds (140, 80, 120, 24);
    debugLabel->setBounds (16, 312, 760, 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SeqPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    int newMidiValue;
    if (sliderThatWasMoved != randomSeq)
    {
        handleSlider(sliderThatWasMoved);
        newMidiValue = static_cast<int>(sliderThatWasMoved->getValue());
    }
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == seqStep1)
    {
        //[UserSliderCode_seqStep1] -- add your slider handling code here..
        labelButton1->setButtonText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3));
        //[/UserSliderCode_seqStep1]
    }
    else if (sliderThatWasMoved == seqStep2)
    {
        //[UserSliderCode_seqStep2] -- add your slider handling code here..
        labelButton2->setButtonText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3));
        //[/UserSliderCode_seqStep2]
    }
    else if (sliderThatWasMoved == seqStep3)
    {
        //[UserSliderCode_seqStep3] -- add your slider handling code here..
        labelButton3->setButtonText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3));
        //[/UserSliderCode_seqStep3]
    }
    else if (sliderThatWasMoved == seqStep4)
    {
        //[UserSliderCode_seqStep4] -- add your slider handling code here..
        labelButton4->setButtonText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3));
        //[/UserSliderCode_seqStep4]
    }
    else if (sliderThatWasMoved == seqStep5)
    {
        //[UserSliderCode_seqStep5] -- add your slider handling code here..
        labelButton5->setButtonText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3));
        //[/UserSliderCode_seqStep5]
    }
    else if (sliderThatWasMoved == seqStep6)
    {
        //[UserSliderCode_seqStep6] -- add your slider handling code here..
        labelButton6->setButtonText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3));
        //[/UserSliderCode_seqStep6]
    }
    else if (sliderThatWasMoved == seqStep7)
    {
        //[UserSliderCode_seqStep7] -- add your slider handling code here..
        labelButton7->setButtonText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3));
        //[/UserSliderCode_seqStep7]
    }
    else if (sliderThatWasMoved == seqStep8)
    {
        //[UserSliderCode_seqStep8] -- add your slider handling code here..
        labelButton8->setButtonText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3));
        //[/UserSliderCode_seqStep8]
    }
    else if (sliderThatWasMoved == randomSeq)
    {
        //[UserSliderCode_randomSeq] -- add your slider handling code here..
        randMinLabel->setText("Min: " + MidiMessage::getMidiNoteName(static_cast<int>(randomSeq->getMinValue()), true, true, 3), dontSendNotification);
        seq->setRandMin(static_cast<int>(randomSeq->getMinValue()));
        randMaxLabel->setText("Max: " + MidiMessage::getMidiNoteName(static_cast<int>(randomSeq->getMaxValue()), true, true, 3), dontSendNotification);
        seq->setRandMax(static_cast<int>(randomSeq->getMaxValue()));
        //[/UserSliderCode_randomSeq]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void SeqPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == seqPlay)
    {
        //[UserButtonCode_seqPlay] -- add your button handler code here..
        if (params.seqMode.getStep() != eSeqModes::seqSyncHost)
        {
            if (params.seqMode.getStep() == eSeqModes::seqStop)
            {
                params.seqMode.setStep(eSeqModes::seqPlay);
            }
            else
            {
                params.seqMode.setStep(eSeqModes::seqStop);
            }
        }
        //[/UserButtonCode_seqPlay]
    }
    else if (buttonThatWasClicked == syncHost)
    {
        //[UserButtonCode_syncHost] -- add your button handler code here..
        if (params.seqMode.getStep() != eSeqModes::seqSyncHost)
        {
            params.seqMode.setStep(eSeqModes::seqSyncHost);
        }
        else
        {
            params.seqMode.setStep(eSeqModes::seqStop);
        }
        //[/UserButtonCode_syncHost]
    }
    else if (buttonThatWasClicked == labelButton1)
    {
        //[UserButtonCode_labelButton1] -- add your button handler code here..
        if (params.seqStepPlay1.getStep() == eOnOffToggle::eOn)
        {
            params.seqStepPlay1.setStep(eOnOffToggle::eOff);
            buttonThatWasClicked->setToggleState(false, dontSendNotification);
        }
        else
        {
            params.seqStepPlay1.setStep(eOnOffToggle::eOn);
            buttonThatWasClicked->setToggleState(true, dontSendNotification);
        }
        //[/UserButtonCode_labelButton1]
    }
    else if (buttonThatWasClicked == labelButton2)
    {
        //[UserButtonCode_labelButton2] -- add your button handler code here..
        if (params.seqStepPlay2.getStep() == eOnOffToggle::eOn)
        {
            params.seqStepPlay2.setStep(eOnOffToggle::eOff);
            buttonThatWasClicked->setToggleState(false, dontSendNotification);
        }
        else
        {
            params.seqStepPlay2.setStep(eOnOffToggle::eOn);
            buttonThatWasClicked->setToggleState(true, dontSendNotification);
        }
        //[/UserButtonCode_labelButton2]
    }
    else if (buttonThatWasClicked == labelButton3)
    {
        //[UserButtonCode_labelButton3] -- add your button handler code here..
        if (params.seqStepPlay3.getStep() == eOnOffToggle::eOn)
        {
            params.seqStepPlay3.setStep(eOnOffToggle::eOff);
            buttonThatWasClicked->setToggleState(false, dontSendNotification);
        }
        else
        {
            params.seqStepPlay3.setStep(eOnOffToggle::eOn);
            buttonThatWasClicked->setToggleState(true, dontSendNotification);
        }
        //[/UserButtonCode_labelButton3]
    }
    else if (buttonThatWasClicked == labelButton4)
    {
        //[UserButtonCode_labelButton4] -- add your button handler code here..
        if (params.seqStepPlay4.getStep() == eOnOffToggle::eOn)
        {
            params.seqStepPlay4.setStep(eOnOffToggle::eOff);
            buttonThatWasClicked->setToggleState(false, dontSendNotification);
        }
        else
        {
            params.seqStepPlay4.setStep(eOnOffToggle::eOn);
            buttonThatWasClicked->setToggleState(true, dontSendNotification);
        }
        //[/UserButtonCode_labelButton4]
    }
    else if (buttonThatWasClicked == labelButton5)
    {
        //[UserButtonCode_labelButton5] -- add your button handler code here..
        if (params.seqStepPlay5.getStep() == eOnOffToggle::eOn)
        {
            params.seqStepPlay5.setStep(eOnOffToggle::eOff);
            buttonThatWasClicked->setToggleState(false, dontSendNotification);
        }
        else
        {
            params.seqStepPlay5.setStep(eOnOffToggle::eOn);
            buttonThatWasClicked->setToggleState(true, dontSendNotification);
        }
        //[/UserButtonCode_labelButton5]
    }
    else if (buttonThatWasClicked == labelButton6)
    {
        //[UserButtonCode_labelButton6] -- add your button handler code here..
        if (params.seqStepPlay6.getStep() == eOnOffToggle::eOn)
        {
            params.seqStepPlay6.setStep(eOnOffToggle::eOff);
            buttonThatWasClicked->setToggleState(false, dontSendNotification);
        }
        else
        {
            params.seqStepPlay6.setStep(eOnOffToggle::eOn);
            buttonThatWasClicked->setToggleState(true, dontSendNotification);
        }
        //[/UserButtonCode_labelButton6]
    }
    else if (buttonThatWasClicked == labelButton7)
    {
        //[UserButtonCode_labelButton7] -- add your button handler code here..
        if (params.seqStepPlay7.getStep() == eOnOffToggle::eOn)
        {
            params.seqStepPlay7.setStep(eOnOffToggle::eOff);
            buttonThatWasClicked->setToggleState(false, dontSendNotification);
        }
        else
        {
            params.seqStepPlay7.setStep(eOnOffToggle::eOn);
            buttonThatWasClicked->setToggleState(true, dontSendNotification);
        }
        //[/UserButtonCode_labelButton7]
    }
    else if (buttonThatWasClicked == labelButton8)
    {
        //[UserButtonCode_labelButton8] -- add your button handler code here..
        if (params.seqStepPlay8.getStep() == eOnOffToggle::eOn)
        {
            params.seqStepPlay8.setStep(eOnOffToggle::eOff);
            buttonThatWasClicked->setToggleState(false, dontSendNotification);
        }
        else
        {
            params.seqStepPlay8.setStep(eOnOffToggle::eOn);
            buttonThatWasClicked->setToggleState(true, dontSendNotification);
        }
        //[/UserButtonCode_labelButton8]
    }
    else if (buttonThatWasClicked == genRandom)
    {
        //[UserButtonCode_genRandom] -- add your button handler code here..
        Random r = Random();

        for (int i = 0; i < 8; ++i)
        {
            r.setSeedRandomly();
            seqStepArray[i]->setValue(r.nextDouble() * (seq->getRandMax() - seq->getRandMin()) + seq->getRandMin());
        }
        //[/UserButtonCode_genRandom]
    }
    else if (buttonThatWasClicked == playUpDown)
    {
        //[UserButtonCode_playUpDown] -- add your button handler code here..
        if (!seq->isPlayUpDown())
        {
            seq->setPlayUpDown(true);
            playUpDown->setToggleState(true, dontSendNotification);
            seq->setPlayRandom(false);
            playRandom->setToggleState(false, dontSendNotification);
        }
        else
        {
            seq->setPlayUpDown(false);
            playUpDown->setToggleState(false, dontSendNotification);
        }
        //[/UserButtonCode_playUpDown]
    }
    else if (buttonThatWasClicked == playRandom)
    {
        //[UserButtonCode_playRandom] -- add your button handler code here..
        if (!seq->isPlayRandom())
        {
            seq->setPlayRandom(true);
            playRandom->setToggleState(true, dontSendNotification);
            seq->setPlayUpDown(false);
            playUpDown->setToggleState(false, dontSendNotification);
            seqNumSteps->setSelectedItemIndex(7);
        }
        else
        {
            seq->setPlayRandom(false);
            playRandom->setToggleState(false, dontSendNotification);
        }
        //[/UserButtonCode_playRandom]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void SeqPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == seqStepSpeed)
    {
        //[UserComboBoxCode_seqStepSpeed] -- add your combo box handling code here..
        params.seqStepSpeedIndex.set(static_cast<float>(comboBoxThatHasChanged->getSelectedItemIndex()));
        //[/UserComboBoxCode_seqStepSpeed]
    }
    else if (comboBoxThatHasChanged == seqStepLength)
    {
        //[UserComboBoxCode_seqStepLength] -- add your combo box handling code here..
        params.seqStepLengthIndex.set(static_cast<float>(comboBoxThatHasChanged->getSelectedItemIndex()));
        //[/UserComboBoxCode_seqStepLength]
    }
    else if (comboBoxThatHasChanged == seqNumSteps)
    {
        //[UserComboBoxCode_seqNumSteps] -- add your combo box handling code here..
        params.seqNumSteps.set(comboBoxThatHasChanged->getText().getFloatValue());
        //[/UserComboBoxCode_seqNumSteps]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SeqPanel::timerCallback()
{
    if (seq->isPlaying())
    {
        seqPlay->setToggleState(true, dontSendNotification);
        if (lastSeqNotePos != seq->getCurrentSeqNote())
        {
            // colour current playing seqNote slider
            for (int i = 0; i < 8; ++i)
            {
                seqStepArray[i]->setColour(Slider::trackColourId, Colour(0x7fffffff));
            }

            lastSeqNotePos = seq->getCurrentSeqNote();
            lastSeqNotePos = jmax(0, jmin(lastSeqNotePos, 7));
            seqStepArray[lastSeqNotePos]->setColour(Slider::trackColourId, Colour(0x7f0000ff));

            // set next random note
            if (seq->isPlayRandom())
            {
                seqNumSteps->setSelectedItemIndex(7);
                Random r = Random();
                r.setSeedRandomly();
                int steps = static_cast<int>(params.seqNumSteps.get());
                seqStepArray[(lastSeqNotePos + 1) % steps]->setValue(r.nextDouble() * (seq->getRandMax() - seq->getRandMin()) + seq->getRandMin());
            }
        }
    }
    else
    {
        // reset gui state
        seqPlay->setToggleState(false, dontSendNotification);
        if (lastSeqNotePos != -1)
        {
            seqStepArray.at(lastSeqNotePos)->setColour(Slider::trackColourId, Colour(0x7fffffff));
            lastSeqNotePos = -1;
        }
    }

    String debugPos = " CurrPos = " + String(seq->getPos());
    debugLabel->setText("|DEBUG| " + debugPos, dontSendNotification);

    PanelBase::timerCallback();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SeqPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Step 1" id="1c1677034c4af23a" memberName="seqStep1" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="336 32 48 264" min="0" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 2" id="e3931793046ce084" memberName="seqStep2" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="392 32 48 264" min="0" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 3" id="5e31094656fb49f9" memberName="seqStep3" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="448 32 48 264" min="0" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 4" id="7025db78c8ff10d4" memberName="seqStep4" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="504 32 48 264" min="0" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 5" id="9eba062111540687" memberName="seqStep5" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="560 32 48 264" min="0" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 6" id="6a53245b0ddd1528" memberName="seqStep6" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="616 32 48 264" min="0" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 7" id="96cbc5e8f38bf170" memberName="seqStep7" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="672 32 48 264" min="0" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 8" id="ee7a391120a49428" memberName="seqStep8" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="728 32 48 264" min="0" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="play sequencer" id="4552dd6439420b59" memberName="seqPlay"
              virtualName="" explicitFocusOrder="0" pos="20 25 100 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" textColOn="ff000000" buttonText="Play" connectedEdges="1"
              needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="Sync Host" id="2314e559577fe768" memberName="syncHost"
                virtualName="" explicitFocusOrder="0" pos="140 20 120 24" txtcol="ff000000"
                buttonText="Sync with Host" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TEXTBUTTON name="label button 1" id="ecf21a7d0b29e004" memberName="labelButton1"
              virtualName="" explicitFocusOrder="0" pos="336 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" textCol="ff000000" buttonText="C3" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="label button 2" id="f176b3ba0f847a7b" memberName="labelButton2"
              virtualName="" explicitFocusOrder="0" pos="392 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="D3" connectedEdges="3" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="label button 3" id="ed69d74dab8d903d" memberName="labelButton3"
              virtualName="" explicitFocusOrder="0" pos="448 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="E3" connectedEdges="3" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="label button 4" id="c0408fb512684153" memberName="labelButton4"
              virtualName="" explicitFocusOrder="0" pos="504 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="F3" connectedEdges="3" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="label button 5" id="f0140e4ed4b41b2a" memberName="labelButton5"
              virtualName="" explicitFocusOrder="0" pos="559 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="G3" connectedEdges="3" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="label button 6" id="15c066479eacbaf" memberName="labelButton6"
              virtualName="" explicitFocusOrder="0" pos="615 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="A3" connectedEdges="3" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="label button 7" id="eb21806a70e68ca" memberName="labelButton7"
              virtualName="" explicitFocusOrder="0" pos="671 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="B3" connectedEdges="3" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="label button 8" id="5cecbbfbc28cd4a8" memberName="labelButton8"
              virtualName="" explicitFocusOrder="0" pos="727 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="C4" connectedEdges="3" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="generate random" id="bb20cf6f1f73eff1" memberName="genRandom"
              virtualName="" explicitFocusOrder="0" pos="20 219 100 24" buttonText="Generate Sequence"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="random sequence" id="2cf72626a61379e3" memberName="randomSeq"
          virtualName="" explicitFocusOrder="0" pos="20 249 250 35" min="0"
          max="127" int="0" style="TwoValueHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="random min label" id="4207acbbe3318ad" memberName="randMinLabel"
         virtualName="" explicitFocusOrder="0" pos="20 279 125 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Min: C-2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="16"
         bold="0" italic="0" justification="36"/>
  <LABEL name="random max label" id="b241e58f05db2570" memberName="randMaxLabel"
         virtualName="" explicitFocusOrder="0" pos="145 279 125 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Max: G8" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="16"
         bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="play up down" id="92757ac860e48d18" memberName="playUpDown"
                virtualName="" explicitFocusOrder="0" pos="140 50 120 24" buttonText="Play Up/Down"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="seq step speed" id="b920cb2140721231" memberName="seqStepSpeed"
            virtualName="" explicitFocusOrder="0" pos="25 155 64 20" editable="0"
            layout="36" items="1/64&#10;1/32&#10;1/16&#10;1/8&#10;1/4&#10;1/2&#10;1/1"
            textWhenNonSelected="Step Speed" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="seq step length" id="9cc1e82a498c26a7" memberName="seqStepLength"
            virtualName="" explicitFocusOrder="0" pos="105 155 64 20" editable="0"
            layout="36" items="1/64&#10;1/32&#10;1/16&#10;1/8&#10;1/4&#10;1/2&#10;1/1"
            textWhenNonSelected="Step Length" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="seq num steps" id="cc5278e8668913e9" memberName="seqNumSteps"
            virtualName="" explicitFocusOrder="0" pos="185 155 64 20" editable="0"
            layout="36" items="1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8"
            textWhenNonSelected="Num Steps" textWhenNoItems="(no choices)"/>
  <LABEL name="new seq speed" id="af187074393a392a" memberName="labelSeqSpeed"
         virtualName="" explicitFocusOrder="0" pos="20 135 64 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Step Speed" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new seq length" id="52118a8deceb9da1" memberName="labelSeqLength"
         virtualName="" explicitFocusOrder="0" pos="100 135 64 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Step Length" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" bold="0" italic="0" justification="33"/>
  <LABEL name="new seq step num" id="c5b4cbd8722afa9c" memberName="labelSeqStepNum"
         virtualName="" explicitFocusOrder="0" pos="180 135 64 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Num Steps" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="play random" id="f5db190fb273c40b" memberName="playRandom"
                virtualName="" explicitFocusOrder="0" pos="140 80 120 24" buttonText="Play Random"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="debug label" id="1d1ce00e4e7ffaf8" memberName="debugLabel"
         virtualName="" explicitFocusOrder="0" pos="16 312 760 32" outlineCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="Debug" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
