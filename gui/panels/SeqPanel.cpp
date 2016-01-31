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
    seqStep1->setColour (Slider::thumbColourId, Colour (0xff564c43));
    seqStep1->setColour (Slider::trackColourId, Colours::white);
    seqStep1->addListener (this);

    addAndMakeVisible (seqStep2 = new MouseOverKnob ("Step 2"));
    seqStep2->setRange (0, 127, 1);
    seqStep2->setSliderStyle (Slider::LinearVertical);
    seqStep2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep2->setColour (Slider::thumbColourId, Colour (0xff564c43));
    seqStep2->setColour (Slider::trackColourId, Colours::white);
    seqStep2->addListener (this);

    addAndMakeVisible (seqStep3 = new MouseOverKnob ("Step 3"));
    seqStep3->setRange (0, 127, 1);
    seqStep3->setSliderStyle (Slider::LinearVertical);
    seqStep3->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep3->setColour (Slider::thumbColourId, Colour (0xff564c43));
    seqStep3->setColour (Slider::trackColourId, Colours::white);
    seqStep3->addListener (this);

    addAndMakeVisible (seqStep4 = new MouseOverKnob ("Step 4"));
    seqStep4->setRange (0, 127, 1);
    seqStep4->setSliderStyle (Slider::LinearVertical);
    seqStep4->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep4->setColour (Slider::thumbColourId, Colour (0xff564c43));
    seqStep4->setColour (Slider::trackColourId, Colours::white);
    seqStep4->addListener (this);

    addAndMakeVisible (seqStep5 = new MouseOverKnob ("Step 5"));
    seqStep5->setRange (0, 127, 1);
    seqStep5->setSliderStyle (Slider::LinearVertical);
    seqStep5->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep5->setColour (Slider::thumbColourId, Colour (0xff564c43));
    seqStep5->setColour (Slider::trackColourId, Colours::white);
    seqStep5->addListener (this);

    addAndMakeVisible (seqStep6 = new MouseOverKnob ("Step 6"));
    seqStep6->setRange (0, 127, 1);
    seqStep6->setSliderStyle (Slider::LinearVertical);
    seqStep6->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep6->setColour (Slider::thumbColourId, Colour (0xff564c43));
    seqStep6->setColour (Slider::trackColourId, Colours::white);
    seqStep6->addListener (this);

    addAndMakeVisible (seqStep7 = new MouseOverKnob ("Step 7"));
    seqStep7->setRange (0, 127, 1);
    seqStep7->setSliderStyle (Slider::LinearVertical);
    seqStep7->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep7->setColour (Slider::thumbColourId, Colour (0xff564c43));
    seqStep7->setColour (Slider::trackColourId, Colours::white);
    seqStep7->addListener (this);

    addAndMakeVisible (seqStep8 = new MouseOverKnob ("Step 8"));
    seqStep8->setRange (0, 127, 1);
    seqStep8->setSliderStyle (Slider::LinearVertical);
    seqStep8->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep8->setColour (Slider::thumbColourId, Colour (0xff564c43));
    seqStep8->setColour (Slider::trackColourId, Colours::white);
    seqStep8->addListener (this);

    addAndMakeVisible (seqPlay = new TextButton ("play sequencer"));
    seqPlay->setButtonText (TRANS("Play"));
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
    labelButton1->addListener (this);
    labelButton1->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton1->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));
    labelButton1->setColour (TextButton::textColourOnId, Colours::white);
    labelButton1->setColour (TextButton::textColourOffId, Colours::white);

    addAndMakeVisible (labelButton2 = new TextButton ("label button 2"));
    labelButton2->setButtonText (TRANS("D3"));
    labelButton2->addListener (this);
    labelButton2->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton2->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (labelButton3 = new TextButton ("label button 3"));
    labelButton3->setButtonText (TRANS("E3"));
    labelButton3->addListener (this);
    labelButton3->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton3->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (labelButton4 = new TextButton ("label button 4"));
    labelButton4->setButtonText (TRANS("F3"));
    labelButton4->addListener (this);
    labelButton4->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton4->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (labelButton5 = new TextButton ("label button 5"));
    labelButton5->setButtonText (TRANS("G3"));
    labelButton5->addListener (this);
    labelButton5->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton5->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (labelButton6 = new TextButton ("label button 6"));
    labelButton6->setButtonText (TRANS("A3"));
    labelButton6->addListener (this);
    labelButton6->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton6->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (labelButton7 = new TextButton ("label button 7"));
    labelButton7->setButtonText (TRANS("B3"));
    labelButton7->addListener (this);
    labelButton7->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    labelButton7->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (labelButton8 = new TextButton ("label button 8"));
    labelButton8->setButtonText (TRANS("C4"));
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
    randomSeq->setColour (Slider::thumbColourId, Colour (0xff564c43));
    randomSeq->setColour (Slider::trackColourId, Colours::black);
    randomSeq->setColour (Slider::rotarySliderFillColourId, Colours::white);
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

    addAndMakeVisible (triplets = new ToggleButton ("triplets"));
    triplets->setButtonText (TRANS("Triplets"));
    triplets->addListener (this);

    addAndMakeVisible (saveSeq = new TextButton ("save button"));
    saveSeq->setButtonText (TRANS("Save Seq"));
    saveSeq->addListener (this);

    addAndMakeVisible (loadSeq = new TextButton ("load button"));
    loadSeq->setButtonText (TRANS("Load Seq"));
    loadSeq->addListener (this);


    //[UserPreSize]
    registerSlider(seqStep1, &params.seqStep0);
    registerSlider(seqStep2, &params.seqStep1);
    registerSlider(seqStep3, &params.seqStep2);
    registerSlider(seqStep4, &params.seqStep3);
    registerSlider(seqStep5, &params.seqStep4);
    registerSlider(seqStep6, &params.seqStep5);
    registerSlider(seqStep7, &params.seqStep6);
    registerSlider(seqStep8, &params.seqStep7);

    // save some params, sliders and buttons in arrays for easier access
    currMidiStepSeq = { &params.seqStep0,
                        &params.seqStep1,
                        &params.seqStep2,
                        &params.seqStep3,
                        &params.seqStep4,
                        &params.seqStep5,
                        &params.seqStep6,
                        &params.seqStep7 };

    currStepOnOff = { &params.seqStepActive0,
                      &params.seqStepActive1,
                      &params.seqStepActive2,
                      &params.seqStepActive3,
                      &params.seqStepActive4,
                      &params.seqStepActive5,
                      &params.seqStepActive6,
                      &params.seqStepActive7 };

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

    // set initial GUI states
    for (int i = 0; i < 8; ++i)
    {
        labelButtonArray[i]->setToggleState(isStepActive(i), dontSendNotification);
    }
    syncHost->setToggleState(params.seqMode.getStep() == eSeqModes::eSeqSyncHost, dontSendNotification);
    seqPlay->setToggleState(isPlaying(), dontSendNotification);
    playUpDown->setToggleState(params.seqPlayMode.getStep() == eSeqPlayModes::eUpDown, dontSendNotification);
    playRandom->setToggleState(params.seqPlayMode.getStep() == eSeqPlayModes::eRandom, dontSendNotification);
    seqStepSpeed->setText(getStepSpeedAsString(), dontSendNotification);
    seqStepLength->setText(getStepLengthAsString(), dontSendNotification);
    triplets->setToggleState(params.seqTriplets.getStep() == eOnOffToggle::eOn, dontSendNotification);
    seqNumSteps->setText(String(static_cast<int>(params.seqNumSteps.get())), dontSendNotification);
    randomSeq->setMinAndMaxValues(static_cast<int>(params.seqRandomMin.get()), static_cast<int>(params.seqRandomMax.get()));
    randMinLabel->setText("Min: " + MidiMessage::getMidiNoteName(static_cast<int>(params.seqRandomMin.get()), true, true, 3), dontSendNotification);
    randMaxLabel->setText("Max: " + MidiMessage::getMidiNoteName(static_cast<int>(params.seqRandomMax.get()), true, true, 3), dontSendNotification);
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
    triplets = nullptr;
    saveSeq = nullptr;
    loadSeq = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SeqPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff564c43));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SeqPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    // reload GUI states
    for (int i = 0; i < 8; ++i)
    {
        labelButtonArray[i]->setToggleState(isStepActive(i), dontSendNotification);
    }
    syncHost->setToggleState(params.seqMode.getStep() == eSeqModes::eSeqSyncHost, dontSendNotification);
    seqPlay->setToggleState(isPlaying(), dontSendNotification);
    playUpDown->setToggleState(params.seqPlayMode.getStep() == eSeqPlayModes::eUpDown, dontSendNotification);
    playRandom->setToggleState(params.seqPlayMode.getStep() == eSeqPlayModes::eRandom, dontSendNotification);
    seqStepSpeed->setText(getStepSpeedAsString(), dontSendNotification);
    seqStepLength->setText(getStepLengthAsString(), dontSendNotification);
    triplets->setToggleState(params.seqTriplets.getStep() == eOnOffToggle::eOn, dontSendNotification);
    seqNumSteps->setText(String(static_cast<int>(params.seqNumSteps.get())), dontSendNotification);
    randomSeq->setMinAndMaxValues(static_cast<int>(params.seqRandomMin.get()), static_cast<int>(params.seqRandomMax.get()));
    randMinLabel->setText("Min: " + MidiMessage::getMidiNoteName(static_cast<int>(params.seqRandomMin.get()), true, true, 3), dontSendNotification);
    randMaxLabel->setText("Max: " + MidiMessage::getMidiNoteName(static_cast<int>(params.seqRandomMax.get()), true, true, 3), dontSendNotification);
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
    randomSeq->setBounds (20, 245, 250, 48);
    randMinLabel->setBounds (20, 279, 125, 24);
    randMaxLabel->setBounds (145, 279, 125, 24);
    playUpDown->setBounds (140, 50, 120, 24);
    seqStepSpeed->setBounds (25, 140, 64, 20);
    seqStepLength->setBounds (105, 140, 64, 20);
    seqNumSteps->setBounds (185, 140, 64, 20);
    labelSeqSpeed->setBounds (20, 120, 64, 20);
    labelSeqLength->setBounds (100, 120, 64, 20);
    labelSeqStepNum->setBounds (180, 120, 64, 20);
    playRandom->setBounds (140, 80, 120, 24);
    triplets->setBounds (25, 165, 100, 25);
    saveSeq->setBounds (25, 315, 100, 24);
    loadSeq->setBounds (145, 315, 100, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SeqPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    if (sliderThatWasMoved != randomSeq)
    {
        handleSlider(sliderThatWasMoved);
    }
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == seqStep1)
    {
        //[UserSliderCode_seqStep1] -- add your slider handling code here..
        labelButton1->setButtonText(getStepNoteName(0, true, true, 3));
        //[/UserSliderCode_seqStep1]
    }
    else if (sliderThatWasMoved == seqStep2)
    {
        //[UserSliderCode_seqStep2] -- add your slider handling code here..
        labelButton2->setButtonText(getStepNoteName(1, true, true, 3));
        //[/UserSliderCode_seqStep2]
    }
    else if (sliderThatWasMoved == seqStep3)
    {
        //[UserSliderCode_seqStep3] -- add your slider handling code here..
        labelButton3->setButtonText(getStepNoteName(2, true, true, 3));
        //[/UserSliderCode_seqStep3]
    }
    else if (sliderThatWasMoved == seqStep4)
    {
        //[UserSliderCode_seqStep4] -- add your slider handling code here..
        labelButton4->setButtonText(getStepNoteName(3, true, true, 3));
        //[/UserSliderCode_seqStep4]
    }
    else if (sliderThatWasMoved == seqStep5)
    {
        //[UserSliderCode_seqStep5] -- add your slider handling code here..
        labelButton5->setButtonText(getStepNoteName(4, true, true, 3));
        //[/UserSliderCode_seqStep5]
    }
    else if (sliderThatWasMoved == seqStep6)
    {
        //[UserSliderCode_seqStep6] -- add your slider handling code here..
        labelButton6->setButtonText(getStepNoteName(5, true, true, 3));
        //[/UserSliderCode_seqStep6]
    }
    else if (sliderThatWasMoved == seqStep7)
    {
        //[UserSliderCode_seqStep7] -- add your slider handling code here..
        labelButton7->setButtonText(getStepNoteName(6, true, true, 3));
        //[/UserSliderCode_seqStep7]
    }
    else if (sliderThatWasMoved == seqStep8)
    {
        //[UserSliderCode_seqStep8] -- add your slider handling code here..
        labelButton8->setButtonText(getStepNoteName(7, true, true, 3));
        //[/UserSliderCode_seqStep8]
    }
    else if (sliderThatWasMoved == randomSeq)
    {
        //[UserSliderCode_randomSeq] -- add your slider handling code here..
        // set the random slider and refresh note name labels
        params.seqRandomMin.set(static_cast<float>(randomSeq->getMinValue()));
        params.seqRandomMax.set(static_cast<float>(randomSeq->getMaxValue()));
        randMinLabel->setText("Min: " + MidiMessage::getMidiNoteName(static_cast<int>(params.seqRandomMin.get()), true, true, 3), dontSendNotification);
        randMaxLabel->setText("Max: " + MidiMessage::getMidiNoteName(static_cast<int>(params.seqRandomMax.get()), true, true, 3), dontSendNotification);
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
        if (params.seqMode.getStep() != eSeqModes::eSeqSyncHost)
        {
            if (!isPlaying())
            {
                params.seqMode.setStep(eSeqModes::eSeqPlay);
            }
            else
            {
                params.seqMode.setStep(eSeqModes::eSeqStop);
            }
        }
        syncHost->setToggleState(params.seqMode.getStep() == eSeqModes::eSeqSyncHost, dontSendNotification);
        seqPlay->setToggleState(isPlaying(), dontSendNotification);
        //[/UserButtonCode_seqPlay]
    }
    else if (buttonThatWasClicked == syncHost)
    {
        //[UserButtonCode_syncHost] -- add your button handler code here..
        if (!(params.seqMode.getStep() == eSeqModes::eSeqSyncHost))
        {
            params.seqMode.setStep(eSeqModes::eSeqSyncHost);
        }
        else
        {
            params.seqMode.setStep(eSeqModes::eSeqStop);
        }
        syncHost->setToggleState(params.seqMode.getStep() == eSeqModes::eSeqSyncHost, dontSendNotification);
        seqPlay->setToggleState(isPlaying(), dontSendNotification);
        //[/UserButtonCode_syncHost]
    }
    else if (buttonThatWasClicked == labelButton1)
    {
        //[UserButtonCode_labelButton1] -- add your button handler code here..
        setStepActive(0, !isStepActive(0));
        buttonThatWasClicked->setToggleState(isStepActive(0), dontSendNotification);
        //[/UserButtonCode_labelButton1]
    }
    else if (buttonThatWasClicked == labelButton2)
    {
        //[UserButtonCode_labelButton2] -- add your button handler code here..
        setStepActive(1, !isStepActive(1));
        buttonThatWasClicked->setToggleState(isStepActive(1), dontSendNotification);
        //[/UserButtonCode_labelButton2]
    }
    else if (buttonThatWasClicked == labelButton3)
    {
        //[UserButtonCode_labelButton3] -- add your button handler code here..
        setStepActive(2, !isStepActive(2));
        buttonThatWasClicked->setToggleState(isStepActive(2), dontSendNotification);
        //[/UserButtonCode_labelButton3]
    }
    else if (buttonThatWasClicked == labelButton4)
    {
        //[UserButtonCode_labelButton4] -- add your button handler code here..
        setStepActive(3, !isStepActive(3));
        buttonThatWasClicked->setToggleState(isStepActive(3), dontSendNotification);
        //[/UserButtonCode_labelButton4]
    }
    else if (buttonThatWasClicked == labelButton5)
    {
        //[UserButtonCode_labelButton5] -- add your button handler code here..
        setStepActive(4, !isStepActive(4));
        buttonThatWasClicked->setToggleState(isStepActive(4), dontSendNotification);
        //[/UserButtonCode_labelButton5]
    }
    else if (buttonThatWasClicked == labelButton6)
    {
        //[UserButtonCode_labelButton6] -- add your button handler code here..
        setStepActive(5, !isStepActive(5));
        buttonThatWasClicked->setToggleState(isStepActive(5), dontSendNotification);
        //[/UserButtonCode_labelButton6]
    }
    else if (buttonThatWasClicked == labelButton7)
    {
        //[UserButtonCode_labelButton7] -- add your button handler code here..
        setStepActive(6, !isStepActive(6));
        buttonThatWasClicked->setToggleState(isStepActive(6), dontSendNotification);
        //[/UserButtonCode_labelButton7]
    }
    else if (buttonThatWasClicked == labelButton8)
    {
        //[UserButtonCode_labelButton8] -- add your button handler code here..
        setStepActive(7, !isStepActive(7));
        buttonThatWasClicked->setToggleState(isStepActive(7), dontSendNotification);
        //[/UserButtonCode_labelButton8]
    }
    else if (buttonThatWasClicked == genRandom)
    {
        //[UserButtonCode_genRandom] -- add your button handler code here..
        generateRandomSeq();
        //[/UserButtonCode_genRandom]
    }
    else if (buttonThatWasClicked == playUpDown)
    {
        //[UserButtonCode_playUpDown] -- add your button handler code here..
        if (!(params.seqPlayMode.getStep() == eSeqPlayModes::eUpDown))
        {
            params.seqPlayMode.setStep(eSeqPlayModes::eUpDown);
        }
        else
        {
            params.seqPlayMode.setStep(eSeqPlayModes::eSequential);
        }
        playUpDown->setToggleState(params.seqPlayMode.getStep() == eSeqPlayModes::eUpDown, dontSendNotification);
        playRandom->setToggleState(params.seqPlayMode.getStep() == eSeqPlayModes::eRandom, dontSendNotification);
        //[/UserButtonCode_playUpDown]
    }
    else if (buttonThatWasClicked == playRandom)
    {
        //[UserButtonCode_playRandom] -- add your button handler code here..
        if (!(params.seqPlayMode.getStep() == eSeqPlayModes::eRandom))
        {
            params.seqPlayMode.setStep(eSeqPlayModes::eRandom);
        }
        else
        {
            params.seqPlayMode.setStep(eSeqPlayModes::eSequential);
        }
        playUpDown->setToggleState(params.seqPlayMode.getStep() == eSeqPlayModes::eUpDown, dontSendNotification);
        playRandom->setToggleState(params.seqPlayMode.getStep() == eSeqPlayModes::eRandom, dontSendNotification);
        //[/UserButtonCode_playRandom]
    }
    else if (buttonThatWasClicked == triplets)
    {
        //[UserButtonCode_triplets] -- add your button handler code here..
        if (!(params.seqTriplets.getStep() == eOnOffToggle::eOn))
        {
            params.seqTriplets.setStep(eOnOffToggle::eOn);
        }
        else
        {
            params.seqTriplets.setStep(eOnOffToggle::eOff);
        }
        //[/UserButtonCode_triplets]
    }
    else if (buttonThatWasClicked == saveSeq)
    {
        //[UserButtonCode_saveSeq] -- add your button handler code here..
        params.writeXMLPatchStandalone(eSerializationParams::eSequencerOnly);
        //[/UserButtonCode_saveSeq]
    }
    else if (buttonThatWasClicked == loadSeq)
    {
        //[UserButtonCode_loadSeq] -- add your button handler code here..
        params.readXMLPatchStandalone(eSerializationParams::eSequencerOnly);
        resized();
        //[/UserButtonCode_loadSeq]
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
        setStepSpeed(comboBoxThatHasChanged->getText());
        //[/UserComboBoxCode_seqStepSpeed]
    }
    else if (comboBoxThatHasChanged == seqStepLength)
    {
        //[UserComboBoxCode_seqStepLength] -- add your combo box handling code here..
        setStepLength(comboBoxThatHasChanged->getText());
        //[/UserComboBoxCode_seqStepLength]
    }
    else if (comboBoxThatHasChanged == seqNumSteps)
    {
        //[UserComboBoxCode_seqNumSteps] -- add your combo box handling code here..
        params.seqNumSteps.set(jmax(1.0f, jmin(comboBoxThatHasChanged->getText().getFloatValue(), 8.0f)));
        //[/UserComboBoxCode_seqNumSteps]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SeqPanel::timerCallback()
{
    if (isPlaying())
    {
        if (lastSeqNotePos != static_cast<int>(params.seqLastPlayedStep.get()))
        {
            seqPlay->setToggleState(isPlaying(), dontSendNotification);
            // colour current playing seqNote slider
            for (int i = 0; i < 8; ++i)
            {
                seqStepArray[i]->setColour(Slider::trackColourId, Colours::white);
            }

            lastSeqNotePos = static_cast<int>(params.seqLastPlayedStep.get());
            lastSeqNotePos = jmax(0, jmin(lastSeqNotePos, 7));
            seqStepArray[lastSeqNotePos]->setColour(Slider::trackColourId, Colours::olive);
        }
    }
    else
    {
        // reset gui state
        if (lastSeqNotePos != -1)
        {
            seqPlay->setToggleState(isPlaying(), dontSendNotification);
            seqStepArray.at(lastSeqNotePos)->setColour(Slider::trackColourId, Colours::white);
            lastSeqNotePos = -1;
        }
    }

    PanelBase::timerCallback();
}

void SeqPanel::generateRandomSeq()
{
    float min = params.seqRandomMin.get();
    float max = params.seqRandomMax.get();
    Random r = Random();

    for (int i = 0; i < 8; ++i)
    {
        r.setSeedRandomly();
        currMidiStepSeq[i]->set(r.nextFloat() * (max - min) + min, true);
    }
}

void SeqPanel::setStepActive(int step, bool active)
{
    if (active)
    {
        currStepOnOff[jmax(0, jmin(step, 7))]->setStep(eOnOffToggle::eOn);
    }
    else
    {
        currStepOnOff[jmax(0, jmin(step, 7))]->setStep(eOnOffToggle::eOff);
    }
}

bool SeqPanel::isPlaying()
{
    AudioPlayHead::CurrentPositionInfo hostPlayHead = params.positionInfo[params.getAudioIndex()];

    if ((params.seqMode.getStep() == eSeqModes::eSeqPlay) || ((params.seqMode.getStep() == eSeqModes::eSeqSyncHost) && hostPlayHead.isPlaying))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool SeqPanel::isStepActive(int step)
{
    return currStepOnOff[jmax(0, jmin(step, 7))]->getStep() == eOnOffToggle::eOn;
}

String SeqPanel::getStepSpeedAsString()
{
    int denominator = static_cast<int>(4.0f * (1.0f / params.seqStepSpeed.get()));
    return "1/" + String(denominator);
}

String SeqPanel::getStepLengthAsString()
{
    int denominator = static_cast<int>(4.0f * (1.0f / params.seqStepLength.get()));
    return "1/" + String(denominator);
}

String SeqPanel::getStepNoteName(int step, bool sharps, bool octaveNumber, int middleC)
{
    return MidiMessage::getMidiNoteName(static_cast<int>(currMidiStepSeq[jmax(0, jmin(step, 7))]->get()), sharps, octaveNumber, middleC);
}

void SeqPanel::setStepSpeed(const String &stepSpeed)
{
    int denominator = stepSpeed.substring(2).getIntValue();
    params.seqStepSpeed.set(jmax(0.0625f, jmin(4.0f / static_cast<float>(denominator), 4.0f)));
}

void SeqPanel::setStepLength(const String &stepLength)
{
    int denominator = stepLength.substring(2).getIntValue();
    params.seqStepLength.set(jmax(0.0625f, jmin(4.0f / static_cast<float>(denominator), 4.0f)));
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
  <BACKGROUND backgroundColour="ff564c43"/>
  <SLIDER name="Step 1" id="1c1677034c4af23a" memberName="seqStep1" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="336 32 48 264" thumbcol="ff564c43"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 2" id="e3931793046ce084" memberName="seqStep2" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="392 32 48 264" thumbcol="ff564c43"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 3" id="5e31094656fb49f9" memberName="seqStep3" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="448 32 48 264" thumbcol="ff564c43"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 4" id="7025db78c8ff10d4" memberName="seqStep4" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="504 32 48 264" thumbcol="ff564c43"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 5" id="9eba062111540687" memberName="seqStep5" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="560 32 48 264" thumbcol="ff564c43"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 6" id="6a53245b0ddd1528" memberName="seqStep6" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="616 32 48 264" thumbcol="ff564c43"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 7" id="96cbc5e8f38bf170" memberName="seqStep7" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="672 32 48 264" thumbcol="ff564c43"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 8" id="ee7a391120a49428" memberName="seqStep8" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="728 32 48 264" thumbcol="ff564c43"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="play sequencer" id="4552dd6439420b59" memberName="seqPlay"
              virtualName="" explicitFocusOrder="0" pos="20 25 100 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" textColOn="ff000000" buttonText="Play" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="Sync Host" id="2314e559577fe768" memberName="syncHost"
                virtualName="" explicitFocusOrder="0" pos="140 20 120 24" txtcol="ff000000"
                buttonText="Sync with Host" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TEXTBUTTON name="label button 1" id="ecf21a7d0b29e004" memberName="labelButton1"
              virtualName="" explicitFocusOrder="0" pos="336 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" textCol="ffffffff" textColOn="ffffffff" buttonText="C3"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="label button 2" id="f176b3ba0f847a7b" memberName="labelButton2"
              virtualName="" explicitFocusOrder="0" pos="392 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="D3" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="label button 3" id="ed69d74dab8d903d" memberName="labelButton3"
              virtualName="" explicitFocusOrder="0" pos="448 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="E3" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="label button 4" id="c0408fb512684153" memberName="labelButton4"
              virtualName="" explicitFocusOrder="0" pos="504 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="F3" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="label button 5" id="f0140e4ed4b41b2a" memberName="labelButton5"
              virtualName="" explicitFocusOrder="0" pos="559 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="G3" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="label button 6" id="15c066479eacbaf" memberName="labelButton6"
              virtualName="" explicitFocusOrder="0" pos="615 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="A3" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="label button 7" id="eb21806a70e68ca" memberName="labelButton7"
              virtualName="" explicitFocusOrder="0" pos="671 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="B3" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="label button 8" id="5cecbbfbc28cd4a8" memberName="labelButton8"
              virtualName="" explicitFocusOrder="0" pos="727 6 48 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="C4" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="generate random" id="bb20cf6f1f73eff1" memberName="genRandom"
              virtualName="" explicitFocusOrder="0" pos="20 219 100 24" buttonText="Generate Sequence"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="random sequence" id="2cf72626a61379e3" memberName="randomSeq"
          virtualName="" explicitFocusOrder="0" pos="20 245 250 48" thumbcol="ff564c43"
          trackcol="ff000000" rotarysliderfill="ffffffff" min="0" max="127"
          int="0" style="TwoValueHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
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
            virtualName="" explicitFocusOrder="0" pos="25 140 64 20" editable="0"
            layout="36" items="1/64&#10;1/32&#10;1/16&#10;1/8&#10;1/4&#10;1/2&#10;1/1"
            textWhenNonSelected="Step Speed" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="seq step length" id="9cc1e82a498c26a7" memberName="seqStepLength"
            virtualName="" explicitFocusOrder="0" pos="105 140 64 20" editable="0"
            layout="36" items="1/64&#10;1/32&#10;1/16&#10;1/8&#10;1/4&#10;1/2&#10;1/1"
            textWhenNonSelected="Step Length" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="seq num steps" id="cc5278e8668913e9" memberName="seqNumSteps"
            virtualName="" explicitFocusOrder="0" pos="185 140 64 20" editable="0"
            layout="36" items="1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8"
            textWhenNonSelected="Num Steps" textWhenNoItems="(no choices)"/>
  <LABEL name="new seq speed" id="af187074393a392a" memberName="labelSeqSpeed"
         virtualName="" explicitFocusOrder="0" pos="20 120 64 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Step Speed" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new seq length" id="52118a8deceb9da1" memberName="labelSeqLength"
         virtualName="" explicitFocusOrder="0" pos="100 120 64 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Step Length" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" bold="0" italic="0" justification="33"/>
  <LABEL name="new seq step num" id="c5b4cbd8722afa9c" memberName="labelSeqStepNum"
         virtualName="" explicitFocusOrder="0" pos="180 120 64 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Num Steps" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="play random" id="f5db190fb273c40b" memberName="playRandom"
                virtualName="" explicitFocusOrder="0" pos="140 80 120 24" buttonText="Play Random"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="triplets" id="9c9e2393225a5b09" memberName="triplets" virtualName=""
                explicitFocusOrder="0" pos="25 165 100 25" buttonText="Triplets"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTBUTTON name="save button" id="575b7197b656cd01" memberName="saveSeq"
              virtualName="" explicitFocusOrder="0" pos="25 315 100 24" buttonText="Save Seq"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="load button" id="aa37b372c2030ee9" memberName="loadSeq"
              virtualName="" explicitFocusOrder="0" pos="145 315 100 24" buttonText="Load Seq"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
