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

    addAndMakeVisible (seqStep1 = new Slider ("Step 1"));
    seqStep1->setRange (0, 127, 1);
    seqStep1->setSliderStyle (Slider::LinearVertical);
    seqStep1->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    seqStep1->setColour (Slider::thumbColourId, Colours::grey);
    seqStep1->setColour (Slider::trackColourId, Colours::white);
    seqStep1->addListener (this);

    addAndMakeVisible (seqStep2 = new Slider ("Step 2"));
    seqStep2->setRange (0, 127, 1);
    seqStep2->setSliderStyle (Slider::LinearVertical);
    seqStep2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    seqStep2->setColour (Slider::thumbColourId, Colours::grey);
    seqStep2->setColour (Slider::trackColourId, Colours::white);
    seqStep2->addListener (this);

    addAndMakeVisible (seqStep3 = new Slider ("Step 3"));
    seqStep3->setRange (0, 127, 1);
    seqStep3->setSliderStyle (Slider::LinearVertical);
    seqStep3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    seqStep3->setColour (Slider::thumbColourId, Colours::grey);
    seqStep3->setColour (Slider::trackColourId, Colours::white);
    seqStep3->addListener (this);

    addAndMakeVisible (seqStep4 = new Slider ("Step 4"));
    seqStep4->setRange (0, 127, 1);
    seqStep4->setSliderStyle (Slider::LinearVertical);
    seqStep4->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    seqStep4->setColour (Slider::thumbColourId, Colours::grey);
    seqStep4->setColour (Slider::trackColourId, Colours::white);
    seqStep4->addListener (this);

    addAndMakeVisible (seqStep5 = new Slider ("Step 5"));
    seqStep5->setRange (0, 127, 1);
    seqStep5->setSliderStyle (Slider::LinearVertical);
    seqStep5->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    seqStep5->setColour (Slider::thumbColourId, Colours::grey);
    seqStep5->setColour (Slider::trackColourId, Colours::white);
    seqStep5->addListener (this);

    addAndMakeVisible (seqStep6 = new Slider ("Step 6"));
    seqStep6->setRange (0, 127, 1);
    seqStep6->setSliderStyle (Slider::LinearVertical);
    seqStep6->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    seqStep6->setColour (Slider::thumbColourId, Colours::grey);
    seqStep6->setColour (Slider::trackColourId, Colours::white);
    seqStep6->addListener (this);

    addAndMakeVisible (seqStep7 = new Slider ("Step 7"));
    seqStep7->setRange (0, 127, 1);
    seqStep7->setSliderStyle (Slider::LinearVertical);
    seqStep7->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    seqStep7->setColour (Slider::thumbColourId, Colours::grey);
    seqStep7->setColour (Slider::trackColourId, Colours::white);
    seqStep7->addListener (this);

    addAndMakeVisible (seqStep8 = new Slider ("Step 8"));
    seqStep8->setRange (0, 127, 1);
    seqStep8->setSliderStyle (Slider::LinearVertical);
    seqStep8->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    seqStep8->setColour (Slider::thumbColourId, Colours::grey);
    seqStep8->setColour (Slider::trackColourId, Colours::white);
    seqStep8->addListener (this);

    addAndMakeVisible (seqPlay = new TextButton ("play sequencer"));
    seqPlay->setButtonText (TRANS("play"));
    seqPlay->addListener (this);
    seqPlay->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    seqPlay->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));
    seqPlay->setColour (TextButton::textColourOnId, Colours::white);
    seqPlay->setColour (TextButton::textColourOffId, Colours::white);

    addAndMakeVisible (syncHost = new ToggleButton ("Sync Host"));
    syncHost->setButtonText (String::empty);
    syncHost->addListener (this);
    syncHost->setColour (ToggleButton::textColourId, Colours::black);

    addAndMakeVisible (labelButton1 = new TextButton ("label button 1"));
    labelButton1->setButtonText (TRANS("C3"));
    labelButton1->addListener (this);
    labelButton1->setColour (TextButton::buttonColourId, Colour (0x00ffffff));
    labelButton1->setColour (TextButton::buttonOnColourId, Colour (0x00ffffff));
    labelButton1->setColour (TextButton::textColourOnId, Colours::white);
    labelButton1->setColour (TextButton::textColourOffId, Colours::grey);

    addAndMakeVisible (labelButton2 = new TextButton ("label button 2"));
    labelButton2->setButtonText (TRANS("D3"));
    labelButton2->addListener (this);
    labelButton2->setColour (TextButton::buttonColourId, Colour (0x00ffffff));
    labelButton2->setColour (TextButton::buttonOnColourId, Colour (0x00ffffff));
    labelButton2->setColour (TextButton::textColourOnId, Colours::white);
    labelButton2->setColour (TextButton::textColourOffId, Colours::grey);

    addAndMakeVisible (labelButton3 = new TextButton ("label button 3"));
    labelButton3->setButtonText (TRANS("E3"));
    labelButton3->addListener (this);
    labelButton3->setColour (TextButton::buttonColourId, Colour (0x00ffffff));
    labelButton3->setColour (TextButton::buttonOnColourId, Colour (0x00ffffff));
    labelButton3->setColour (TextButton::textColourOnId, Colours::white);
    labelButton3->setColour (TextButton::textColourOffId, Colours::grey);

    addAndMakeVisible (labelButton4 = new TextButton ("label button 4"));
    labelButton4->setButtonText (TRANS("F3"));
    labelButton4->addListener (this);
    labelButton4->setColour (TextButton::buttonColourId, Colour (0x00ffffff));
    labelButton4->setColour (TextButton::buttonOnColourId, Colour (0x00ffffff));
    labelButton4->setColour (TextButton::textColourOnId, Colours::white);
    labelButton4->setColour (TextButton::textColourOffId, Colours::grey);

    addAndMakeVisible (labelButton5 = new TextButton ("label button 5"));
    labelButton5->setButtonText (TRANS("G3"));
    labelButton5->addListener (this);
    labelButton5->setColour (TextButton::buttonColourId, Colour (0x00ffffff));
    labelButton5->setColour (TextButton::buttonOnColourId, Colour (0x00ffffff));
    labelButton5->setColour (TextButton::textColourOnId, Colours::white);
    labelButton5->setColour (TextButton::textColourOffId, Colours::grey);

    addAndMakeVisible (labelButton6 = new TextButton ("label button 6"));
    labelButton6->setButtonText (TRANS("A3"));
    labelButton6->addListener (this);
    labelButton6->setColour (TextButton::buttonColourId, Colour (0x00ffffff));
    labelButton6->setColour (TextButton::buttonOnColourId, Colour (0x00ffffff));
    labelButton6->setColour (TextButton::textColourOnId, Colours::white);
    labelButton6->setColour (TextButton::textColourOffId, Colours::grey);

    addAndMakeVisible (labelButton7 = new TextButton ("label button 7"));
    labelButton7->setButtonText (TRANS("B3"));
    labelButton7->addListener (this);
    labelButton7->setColour (TextButton::buttonColourId, Colour (0x00ffffff));
    labelButton7->setColour (TextButton::buttonOnColourId, Colour (0x00ffffff));
    labelButton7->setColour (TextButton::textColourOnId, Colours::white);
    labelButton7->setColour (TextButton::textColourOffId, Colours::grey);

    addAndMakeVisible (labelButton8 = new TextButton ("label button 8"));
    labelButton8->setButtonText (TRANS("C4"));
    labelButton8->addListener (this);
    labelButton8->setColour (TextButton::buttonColourId, Colour (0x00ffffff));
    labelButton8->setColour (TextButton::buttonOnColourId, Colour (0x00ffffff));
    labelButton8->setColour (TextButton::textColourOnId, Colours::white);
    labelButton8->setColour (TextButton::textColourOffId, Colours::grey);

    addAndMakeVisible (genRandom = new TextButton ("generate random"));
    genRandom->setButtonText (TRANS("generate sequence"));
    genRandom->addListener (this);
    genRandom->setColour (TextButton::buttonColourId, Colour (0xff564c43));
    genRandom->setColour (TextButton::textColourOnId, Colours::white);
    genRandom->setColour (TextButton::textColourOffId, Colours::white);

    addAndMakeVisible (randomSeq = new Slider ("random sequence"));
    randomSeq->setRange (0, 127, 1);
    randomSeq->setSliderStyle (Slider::TwoValueHorizontal);
    randomSeq->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    randomSeq->setColour (Slider::thumbColourId, Colours::grey);
    randomSeq->setColour (Slider::trackColourId, Colours::black);
    randomSeq->setColour (Slider::rotarySliderFillColourId, Colours::white);
    randomSeq->addListener (this);

    addAndMakeVisible (randMinLabel = new Label ("random min label",
                                                 TRANS("C-2")));
    randMinLabel->setFont (Font (24.00f, Font::bold));
    randMinLabel->setJustificationType (Justification::centred);
    randMinLabel->setEditable (false, false, false);
    randMinLabel->setColour (TextEditor::textColourId, Colours::black);
    randMinLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (randMaxLabel = new Label ("random max label",
                                                 TRANS("G8")));
    randMaxLabel->setFont (Font (24.00f, Font::bold));
    randMaxLabel->setJustificationType (Justification::centred);
    randMaxLabel->setEditable (false, false, false);
    randMaxLabel->setColour (TextEditor::textColourId, Colours::black);
    randMaxLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (seqStepSpeed = new IncDecDropDown ("seq step speed"));
    seqStepSpeed->setEditableText (false);
    seqStepSpeed->setJustificationType (Justification::centred);
    seqStepSpeed->setTextWhenNothingSelected (TRANS("Step Speed"));
    seqStepSpeed->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    seqStepSpeed->addItem (TRANS("1/1"), 1);
    seqStepSpeed->addItem (TRANS("1/2"), 2);
    seqStepSpeed->addItem (TRANS("1/4"), 3);
    seqStepSpeed->addItem (TRANS("1/8"), 4);
    seqStepSpeed->addItem (TRANS("1/16"), 5);
    seqStepSpeed->addItem (TRANS("1/32"), 6);
    seqStepSpeed->addItem (TRANS("1/64"), 7);
    seqStepSpeed->addListener (this);

    addAndMakeVisible (seqStepLength = new IncDecDropDown ("seq step length"));
    seqStepLength->setEditableText (false);
    seqStepLength->setJustificationType (Justification::centred);
    seqStepLength->setTextWhenNothingSelected (TRANS("Step Length"));
    seqStepLength->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    seqStepLength->addItem (TRANS("1/1"), 1);
    seqStepLength->addItem (TRANS("1/2"), 2);
    seqStepLength->addItem (TRANS("1/4"), 3);
    seqStepLength->addItem (TRANS("1/8"), 4);
    seqStepLength->addItem (TRANS("1/16"), 5);
    seqStepLength->addItem (TRANS("1/32"), 6);
    seqStepLength->addItem (TRANS("1/64"), 7);
    seqStepLength->addListener (this);

    addAndMakeVisible (seqNumSteps = new IncDecDropDown ("seq num steps"));
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
                                                  TRANS("step speed")));
    labelSeqSpeed->setFont (Font (18.00f, Font::plain));
    labelSeqSpeed->setJustificationType (Justification::centredLeft);
    labelSeqSpeed->setEditable (false, false, false);
    labelSeqSpeed->setColour (Label::textColourId, Colours::white);
    labelSeqSpeed->setColour (TextEditor::textColourId, Colours::black);
    labelSeqSpeed->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelSeqLength = new Label ("new seq length",
                                                   TRANS("step length")));
    labelSeqLength->setFont (Font (18.00f, Font::plain));
    labelSeqLength->setJustificationType (Justification::centredLeft);
    labelSeqLength->setEditable (false, false, false);
    labelSeqLength->setColour (Label::textColourId, Colours::white);
    labelSeqLength->setColour (TextEditor::textColourId, Colours::black);
    labelSeqLength->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelSeqStepNum = new Label ("new seq step num",
                                                    TRANS("numb. steps")));
    labelSeqStepNum->setFont (Font (18.00f, Font::plain));
    labelSeqStepNum->setJustificationType (Justification::centredLeft);
    labelSeqStepNum->setEditable (false, false, false);
    labelSeqStepNum->setColour (Label::textColourId, Colours::white);
    labelSeqStepNum->setColour (TextEditor::textColourId, Colours::black);
    labelSeqStepNum->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (triplets = new ToggleButton ("triplets"));
    triplets->setButtonText (String::empty);
    triplets->addListener (this);

    addAndMakeVisible (saveSeq = new TextButton ("save button"));
    saveSeq->setButtonText (TRANS("save seq"));
    saveSeq->addListener (this);
    saveSeq->setColour (TextButton::buttonColourId, Colours::white);
    saveSeq->setColour (TextButton::textColourOnId, Colours::grey);
    saveSeq->setColour (TextButton::textColourOffId, Colours::grey);

    addAndMakeVisible (loadSeq = new TextButton ("load button"));
    loadSeq->setButtonText (TRANS("load seq"));
    loadSeq->addListener (this);
    loadSeq->setColour (TextButton::buttonColourId, Colours::white);
    loadSeq->setColour (TextButton::textColourOnId, Colours::grey);
    loadSeq->setColour (TextButton::textColourOffId, Colours::grey);

    addAndMakeVisible (playModes = new Slider ("playModes"));
    playModes->setRange (0, 2, 1);
    playModes->setSliderStyle (Slider::LinearHorizontal);
    playModes->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    playModes->setColour (Slider::thumbColourId, Colour (0xff564c43));
    playModes->setColour (Slider::trackColourId, Colours::white);
    playModes->addListener (this);

    addAndMakeVisible (dottedNotes = new ToggleButton ("dottedNotes"));
    dottedNotes->setButtonText (TRANS("dot"));
    dottedNotes->addListener (this);
    dottedNotes->setColour (ToggleButton::textColourId, Colours::white);


    //[UserPreSize]
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

    for (int i = 0; i < 8; ++i)
    {
        registerSlider(seqStepArray[i], currMidiStepSeq[i], std::bind(&SeqPanel::updateNoteNameLabels, this));
        registerToggle(labelButtonArray[i], currStepOnOff[i]);
    }
    registerSlider(playModes, &params.seqPlayMode);
    registerSlider(randomSeq, &params.seqPlaceHolder, std::bind(&SeqPanel::updateMinMaxLabels, this), &params.seqRandomMin, &params.seqRandomMax);

    registerToggle(syncHost, &params.seqPlaySyncHost, std::bind(&SeqPanel::updateToggleState, this));
    registerToggle(triplets, &params.seqTriplets);
    registerToggle(dottedNotes, &params.seqDottedLength);

    registerDropDowns(seqNumSteps, &params.seqNumSteps);
    registerNoteLength(seqStepSpeed, &params.seqStepSpeed);
    registerNoteLength(seqStepLength, &params.seqStepLength);
    //[/UserPreSize]

    setSize (800, 300);


    //[Constructor] You can add your own custom stuff here..
    syncPic = ImageCache::getFromMemory(BinaryData::tempoSync_png, BinaryData::tempoSync_pngSize);
    tripletPic = ImageCache::getFromMemory(BinaryData::triplets_png, BinaryData::triplets_pngSize);
    sequentialPic = ImageCache::getFromMemory(BinaryData::seqSequential_png, BinaryData::seqSequential_pngSize);
    upDownPic = ImageCache::getFromMemory(BinaryData::seqUpDown_png, BinaryData::seqUpDown_pngSize);
    randomPic = ImageCache::getFromMemory(BinaryData::seqRandom_png, BinaryData::seqRandom_pngSize);

    genRandom->setAlwaysOnTop(true);
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
    currMidiStepSeq = { nullptr };
    currStepOnOff = { nullptr };
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
    seqStepSpeed = nullptr;
    seqStepLength = nullptr;
    seqNumSteps = nullptr;
    labelSeqSpeed = nullptr;
    labelSeqLength = nullptr;
    labelSeqStepNum = nullptr;
    triplets = nullptr;
    saveSeq = nullptr;
    loadSeq = nullptr;
    playModes = nullptr;
    dottedNotes = nullptr;


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
    drawGroupBorder(g, "step sequencer", 0, 0,
        this->getWidth(), this->getHeight(), 30.0f, 30.0f, 5.0f, 3.0f, SynthParams::stepSeqColour);
    drawPics(g, playModes, syncHost, triplets);
    //[/UserPaint]
}

void SeqPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    seqPlay->setToggleState(isPlaying(), dontSendNotification);
    seqNumSteps->setText(String(static_cast<int>(params.seqNumSteps.get())), dontSendNotification);
    //[/UserPreResize]

    seqStep1->setBounds (452, 68, 40, 210);
    seqStep2->setBounds (492, 68, 40, 210);
    seqStep3->setBounds (532, 68, 40, 210);
    seqStep4->setBounds (572, 68, 40, 210);
    seqStep5->setBounds (612, 68, 40, 210);
    seqStep6->setBounds (652, 68, 40, 210);
    seqStep7->setBounds (692, 68, 40, 210);
    seqStep8->setBounds (732, 68, 40, 210);
    seqPlay->setBounds (55, 7, 100, 23);
    syncHost->setBounds (326, 53, 64, 30);
    labelButton1->setBounds (448, 42, 48, 24);
    labelButton2->setBounds (488, 42, 48, 24);
    labelButton3->setBounds (528, 42, 48, 24);
    labelButton4->setBounds (568, 42, 48, 24);
    labelButton5->setBounds (608, 42, 48, 24);
    labelButton6->setBounds (648, 42, 48, 24);
    labelButton7->setBounds (688, 42, 48, 24);
    labelButton8->setBounds (728, 42, 48, 24);
    genRandom->setBounds (118, 207, 150, 30);
    randomSeq->setBounds (40, 231, 300, 50);
    randMinLabel->setBounds (24, 207, 80, 36);
    randMaxLabel->setBounds (280, 207, 80, 36);
    seqStepSpeed->setBounds (142, 102, 98, 28);
    seqStepLength->setBounds (142, 145, 98, 28);
    seqNumSteps->setBounds (142, 59, 98, 28);
    labelSeqSpeed->setBounds (33, 106, 103, 20);
    labelSeqLength->setBounds (33, 149, 103, 20);
    labelSeqStepNum->setBounds (33, 63, 103, 20);
    triplets->setBounds (326, 87, 64, 30);
    saveSeq->setBounds (170, 7, 100, 23);
    loadSeq->setBounds (280, 7, 100, 23);
    playModes->setBounds (328, 175, 64, 24);
    dottedNotes->setBounds (326, 121, 64, 30);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SeqPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == seqStep1)
    {
        //[UserSliderCode_seqStep1] -- add your slider handling code here..
        //[/UserSliderCode_seqStep1]
    }
    else if (sliderThatWasMoved == seqStep2)
    {
        //[UserSliderCode_seqStep2] -- add your slider handling code here..
        //[/UserSliderCode_seqStep2]
    }
    else if (sliderThatWasMoved == seqStep3)
    {
        //[UserSliderCode_seqStep3] -- add your slider handling code here..
        //[/UserSliderCode_seqStep3]
    }
    else if (sliderThatWasMoved == seqStep4)
    {
        //[UserSliderCode_seqStep4] -- add your slider handling code here..
        //[/UserSliderCode_seqStep4]
    }
    else if (sliderThatWasMoved == seqStep5)
    {
        //[UserSliderCode_seqStep5] -- add your slider handling code here..
        //[/UserSliderCode_seqStep5]
    }
    else if (sliderThatWasMoved == seqStep6)
    {
        //[UserSliderCode_seqStep6] -- add your slider handling code here..
        //[/UserSliderCode_seqStep6]
    }
    else if (sliderThatWasMoved == seqStep7)
    {
        //[UserSliderCode_seqStep7] -- add your slider handling code here..
        //[/UserSliderCode_seqStep7]
    }
    else if (sliderThatWasMoved == seqStep8)
    {
        //[UserSliderCode_seqStep8] -- add your slider handling code here..
        //[/UserSliderCode_seqStep8]
    }
    else if (sliderThatWasMoved == randomSeq)
    {
        //[UserSliderCode_randomSeq] -- add your slider handling code here..
        //[/UserSliderCode_randomSeq]
    }
    else if (sliderThatWasMoved == playModes)
    {
        //[UserSliderCode_playModes] -- add your slider handling code here..
        //[/UserSliderCode_playModes]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void SeqPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    if ((buttonThatWasClicked != seqPlay) && (buttonThatWasClicked != genRandom) && (buttonThatWasClicked != saveSeq) && (buttonThatWasClicked != loadSeq))
    {
        handleToggle(buttonThatWasClicked);
    }
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == seqPlay)
    {
        //[UserButtonCode_seqPlay] -- add your button handler code here..
        if (params.seqPlaySyncHost.getStep() != eOnOffToggle::eOn)
        {
            if (!isPlaying())
            {
                params.seqPlayNoHost.setStep(eOnOffToggle::eOn);
            }
            else
            {
                params.seqPlayNoHost.setStep(eOnOffToggle::eOff);
            }
        }
        syncHost->setToggleState(params.seqPlaySyncHost.getStep() == eOnOffToggle::eOn, dontSendNotification);
        seqPlay->setToggleState(isPlaying(), dontSendNotification);
        //[/UserButtonCode_seqPlay]
    }
    else if (buttonThatWasClicked == syncHost)
    {
        //[UserButtonCode_syncHost] -- add your button handler code here..
        //[/UserButtonCode_syncHost]
    }
    else if (buttonThatWasClicked == labelButton1)
    {
        //[UserButtonCode_labelButton1] -- add your button handler code here..
        //[/UserButtonCode_labelButton1]
    }
    else if (buttonThatWasClicked == labelButton2)
    {
        //[UserButtonCode_labelButton2] -- add your button handler code here..
        //[/UserButtonCode_labelButton2]
    }
    else if (buttonThatWasClicked == labelButton3)
    {
        //[UserButtonCode_labelButton3] -- add your button handler code here..
        //[/UserButtonCode_labelButton3]
    }
    else if (buttonThatWasClicked == labelButton4)
    {
        //[UserButtonCode_labelButton4] -- add your button handler code here..
        //[/UserButtonCode_labelButton4]
    }
    else if (buttonThatWasClicked == labelButton5)
    {
        //[UserButtonCode_labelButton5] -- add your button handler code here..
        //[/UserButtonCode_labelButton5]
    }
    else if (buttonThatWasClicked == labelButton6)
    {
        //[UserButtonCode_labelButton6] -- add your button handler code here..
        //[/UserButtonCode_labelButton6]
    }
    else if (buttonThatWasClicked == labelButton7)
    {
        //[UserButtonCode_labelButton7] -- add your button handler code here..
        //[/UserButtonCode_labelButton7]
    }
    else if (buttonThatWasClicked == labelButton8)
    {
        //[UserButtonCode_labelButton8] -- add your button handler code here..
        //[/UserButtonCode_labelButton8]
    }
    else if (buttonThatWasClicked == genRandom)
    {
        //[UserButtonCode_genRandom] -- add your button handler code here..
        float min = params.seqRandomMin.get();
        float max = params.seqRandomMax.get();
        Random r = Random();

        for (int i = 0; i < 8; ++i)
        {
            r.setSeedRandomly();
            currMidiStepSeq[i]->set(r.nextFloat() * (max - min) + min, true);
        }
        //[/UserButtonCode_genRandom]
    }
    else if (buttonThatWasClicked == triplets)
    {
        //[UserButtonCode_triplets] -- add your button handler code here..
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
        //[/UserButtonCode_loadSeq]
    }
    else if (buttonThatWasClicked == dottedNotes)
    {
        //[UserButtonCode_dottedNotes] -- add your button handler code here..
        //[/UserButtonCode_dottedNotes]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void SeqPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    if (comboBoxThatHasChanged == seqNumSteps)
    {
        handleDropDowns(comboBoxThatHasChanged);
    }
    else
    {
        handleNoteLength(comboBoxThatHasChanged);
    }
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == seqStepSpeed)
    {
        //[UserComboBoxCode_seqStepSpeed] -- add your combo box handling code here..
        //[/UserComboBoxCode_seqStepSpeed]
    }
    else if (comboBoxThatHasChanged == seqStepLength)
    {
        //[UserComboBoxCode_seqStepLength] -- add your combo box handling code here..
        //[/UserComboBoxCode_seqStepLength]
    }
    else if (comboBoxThatHasChanged == seqNumSteps)
    {
        //[UserComboBoxCode_seqNumSteps] -- add your combo box handling code here..
        //[/UserComboBoxCode_seqNumSteps]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SeqPanel::updateToggleState()
{
    params.seqPlayNoHost.setStep(eOnOffToggle::eOff);
    seqPlay->setToggleState(isPlaying(), dontSendNotification);
    seqPlay->setEnabled(params.seqPlaySyncHost.getStep() == eOnOffToggle::eOff);
}

void SeqPanel::updateNoteNameLabels()
{
    labelButton1->setButtonText(getStepNoteName(0, true, true, 3));
    labelButton2->setButtonText(getStepNoteName(1, true, true, 3));
    labelButton3->setButtonText(getStepNoteName(2, true, true, 3));
    labelButton4->setButtonText(getStepNoteName(3, true, true, 3));
    labelButton5->setButtonText(getStepNoteName(4, true, true, 3));
    labelButton6->setButtonText(getStepNoteName(5, true, true, 3));
    labelButton7->setButtonText(getStepNoteName(6, true, true, 3));
    labelButton8->setButtonText(getStepNoteName(7, true, true, 3));
}

void SeqPanel::updateMinMaxLabels()
{
    randMinLabel->setText(MidiMessage::getMidiNoteName(static_cast<int>(params.seqRandomMin.get()), true, true, 3), dontSendNotification);
    randMaxLabel->setText(MidiMessage::getMidiNoteName(static_cast<int>(params.seqRandomMax.get()), true, true, 3), dontSendNotification);
}

void SeqPanel::drawPics(Graphics& g, ScopedPointer<Slider>& seqPlayMode, ScopedPointer<ToggleButton>& syncT, ScopedPointer<ToggleButton>& tripletT)
{
    int centerX = seqPlayMode->getX() + seqPlayMode->getWidth() / 2;
    int centerY = seqPlayMode->getY() + seqPlayMode->getHeight() / 2;

    g.drawImageWithin(sequentialPic, seqPlayMode->getX() - 22, centerY - 8, 20, 15, RectanglePlacement::centred); //16x14 -> 20x15
    g.drawImageWithin(upDownPic, centerX - 8, seqPlayMode->getY() - 17, 20, 15, RectanglePlacement::centred); // 17x13 -> 20x15
    g.drawImageWithin(randomPic, seqPlayMode->getX() + seqPlayMode->getWidth() + 2, centerY - 13, 15, 25, RectanglePlacement::centred);// 12x20 -> 15x25

    g.drawImageWithin(syncPic, syncT->getX() + 22, syncT->getY() + syncT->getHeight() / 2 - 12, 34, 23, Justification::centred); // 34x23
    g.drawImageWithin(tripletPic, tripletT->getX() + 22, tripletT->getY() + tripletT->getHeight() / 2 - 15, 39, 30, Justification::centred); // 39x30
}

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
                seqStepArray[i]->setColour(Slider::thumbColourId, Colours::grey);
            }

            lastSeqNotePos = static_cast<int>(params.seqLastPlayedStep.get());
            lastSeqNotePos = jmax(0, jmin(lastSeqNotePos, 7));
            seqStepArray[lastSeqNotePos]->setColour(Slider::thumbColourId, Colour(0xff60ff60));
        }
    }
    else
    {
        // reset gui state
        if (lastSeqNotePos != -1)
        {
            seqPlay->setToggleState(isPlaying(), dontSendNotification);
            seqStepArray.at(lastSeqNotePos)->setColour(Slider::thumbColourId, Colours::grey);
            lastSeqNotePos = -1;
        }
    }
    PanelBase::timerCallback();
}

bool SeqPanel::isPlaying()
{
    AudioPlayHead::CurrentPositionInfo hostPlayHead = params.positionInfo[params.getAudioIndex()];

    if ((params.seqPlayNoHost.getStep() == eOnOffToggle::eOn) || ((params.seqPlaySyncHost.getStep() == eOnOffToggle::eOn) && hostPlayHead.isPlaying))
    {
        return true;
    }
    else
    {
        return false;
    }
}

String SeqPanel::getStepNoteName(int step, bool sharps, bool octaveNumber, int middleC)
{
    return MidiMessage::getMidiNoteName(static_cast<int>(currMidiStepSeq[jmax(0, jmin(step, 7))]->get()), sharps, octaveNumber, middleC);
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
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="800"
                 initialHeight="300">
  <BACKGROUND backgroundColour="ff564c43"/>
  <SLIDER name="Step 1" id="1c1677034c4af23a" memberName="seqStep1" virtualName="Slider"
          explicitFocusOrder="0" pos="452 68 40 210" thumbcol="ff808080"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 2" id="e3931793046ce084" memberName="seqStep2" virtualName="Slider"
          explicitFocusOrder="0" pos="492 68 40 210" thumbcol="ff808080"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 3" id="5e31094656fb49f9" memberName="seqStep3" virtualName="Slider"
          explicitFocusOrder="0" pos="532 68 40 210" thumbcol="ff808080"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 4" id="7025db78c8ff10d4" memberName="seqStep4" virtualName="Slider"
          explicitFocusOrder="0" pos="572 68 40 210" thumbcol="ff808080"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 5" id="9eba062111540687" memberName="seqStep5" virtualName="Slider"
          explicitFocusOrder="0" pos="612 68 40 210" thumbcol="ff808080"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 6" id="6a53245b0ddd1528" memberName="seqStep6" virtualName="Slider"
          explicitFocusOrder="0" pos="652 68 40 210" thumbcol="ff808080"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 7" id="96cbc5e8f38bf170" memberName="seqStep7" virtualName="Slider"
          explicitFocusOrder="0" pos="692 68 40 210" thumbcol="ff808080"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 8" id="ee7a391120a49428" memberName="seqStep8" virtualName="Slider"
          explicitFocusOrder="0" pos="732 68 40 210" thumbcol="ff808080"
          trackcol="ffffffff" min="0" max="127" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="play sequencer" id="4552dd6439420b59" memberName="seqPlay"
              virtualName="" explicitFocusOrder="0" pos="55 7 100 23" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" textCol="ffffffff" textColOn="ffffffff" buttonText="play"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="Sync Host" id="2314e559577fe768" memberName="syncHost"
                virtualName="" explicitFocusOrder="0" pos="326 53 64 30" txtcol="ff000000"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TEXTBUTTON name="label button 1" id="ecf21a7d0b29e004" memberName="labelButton1"
              virtualName="" explicitFocusOrder="0" pos="448 42 48 24" bgColOff="ffffff"
              bgColOn="ffffff" textCol="ffffffff" textColOn="ff808080" buttonText="C3"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="label button 2" id="f176b3ba0f847a7b" memberName="labelButton2"
              virtualName="" explicitFocusOrder="0" pos="488 42 48 24" bgColOff="ffffff"
              bgColOn="ffffff" textCol="ffffffff" textColOn="ff808080" buttonText="D3"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="label button 3" id="ed69d74dab8d903d" memberName="labelButton3"
              virtualName="" explicitFocusOrder="0" pos="528 42 48 24" bgColOff="ffffff"
              bgColOn="ffffff" textCol="ffffffff" textColOn="ff808080" buttonText="E3"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="label button 4" id="c0408fb512684153" memberName="labelButton4"
              virtualName="" explicitFocusOrder="0" pos="568 42 48 24" bgColOff="ffffff"
              bgColOn="ffffff" textCol="ffffffff" textColOn="ff808080" buttonText="F3"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="label button 5" id="f0140e4ed4b41b2a" memberName="labelButton5"
              virtualName="" explicitFocusOrder="0" pos="608 42 48 24" bgColOff="ffffff"
              bgColOn="ffffff" textCol="ffffffff" textColOn="ff808080" buttonText="G3"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="label button 6" id="15c066479eacbaf" memberName="labelButton6"
              virtualName="" explicitFocusOrder="0" pos="648 42 48 24" bgColOff="ffffff"
              bgColOn="ffffff" textCol="ffffffff" textColOn="ff808080" buttonText="A3"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="label button 7" id="eb21806a70e68ca" memberName="labelButton7"
              virtualName="" explicitFocusOrder="0" pos="688 42 48 24" bgColOff="ffffff"
              bgColOn="ffffff" textCol="ffffffff" textColOn="ff808080" buttonText="B3"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="label button 8" id="5cecbbfbc28cd4a8" memberName="labelButton8"
              virtualName="" explicitFocusOrder="0" pos="728 42 48 24" bgColOff="ffffff"
              bgColOn="ffffff" textCol="ffffffff" textColOn="ff808080" buttonText="C4"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="generate random" id="bb20cf6f1f73eff1" memberName="genRandom"
              virtualName="" explicitFocusOrder="0" pos="118 207 150 30" bgColOff="ff564c43"
              textCol="ffffffff" textColOn="ffffffff" buttonText="generate sequence"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="random sequence" id="2cf72626a61379e3" memberName="randomSeq"
          virtualName="" explicitFocusOrder="0" pos="40 231 300 50" thumbcol="ff808080"
          trackcol="ff000000" rotarysliderfill="ffffffff" min="0" max="127"
          int="1" style="TwoValueHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="random min label" id="4207acbbe3318ad" memberName="randMinLabel"
         virtualName="" explicitFocusOrder="0" pos="24 207 80 36" edTextCol="ff000000"
         edBkgCol="0" labelText="C-2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24"
         bold="1" italic="0" justification="36"/>
  <LABEL name="random max label" id="b241e58f05db2570" memberName="randMaxLabel"
         virtualName="" explicitFocusOrder="0" pos="280 207 80 36" edTextCol="ff000000"
         edBkgCol="0" labelText="G8" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24"
         bold="1" italic="0" justification="36"/>
  <COMBOBOX name="seq step speed" id="b920cb2140721231" memberName="seqStepSpeed"
            virtualName="IncDecDropDown" explicitFocusOrder="0" pos="142 102 98 28"
            editable="0" layout="36" items="1/1&#10;1/2&#10;1/4&#10;1/8&#10;1/16&#10;1/32&#10;1/64"
            textWhenNonSelected="Step Speed" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="seq step length" id="9cc1e82a498c26a7" memberName="seqStepLength"
            virtualName="IncDecDropDown" explicitFocusOrder="0" pos="142 145 98 28"
            editable="0" layout="36" items="1/1&#10;1/2&#10;1/4&#10;1/8&#10;1/16&#10;1/32&#10;1/64"
            textWhenNonSelected="Step Length" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="seq num steps" id="cc5278e8668913e9" memberName="seqNumSteps"
            virtualName="IncDecDropDown" explicitFocusOrder="0" pos="142 59 98 28"
            editable="0" layout="36" items="1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8"
            textWhenNonSelected="Num Steps" textWhenNoItems="(no choices)"/>
  <LABEL name="new seq speed" id="af187074393a392a" memberName="labelSeqSpeed"
         virtualName="" explicitFocusOrder="0" pos="33 106 103 20" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="step speed" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="18" bold="0" italic="0" justification="33"/>
  <LABEL name="new seq length" id="52118a8deceb9da1" memberName="labelSeqLength"
         virtualName="" explicitFocusOrder="0" pos="33 149 103 20" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="step length" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="18" bold="0" italic="0" justification="33"/>
  <LABEL name="new seq step num" id="c5b4cbd8722afa9c" memberName="labelSeqStepNum"
         virtualName="" explicitFocusOrder="0" pos="33 63 103 20" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="numb. steps" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="18" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="triplets" id="9c9e2393225a5b09" memberName="triplets" virtualName=""
                explicitFocusOrder="0" pos="326 87 64 30" buttonText="" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTBUTTON name="save button" id="575b7197b656cd01" memberName="saveSeq"
              virtualName="" explicitFocusOrder="0" pos="170 7 100 23" bgColOff="ffffffff"
              textCol="ff808080" textColOn="ff808080" buttonText="save seq"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="load button" id="aa37b372c2030ee9" memberName="loadSeq"
              virtualName="" explicitFocusOrder="0" pos="280 7 100 23" bgColOff="ffffffff"
              textCol="ff808080" textColOn="ff808080" buttonText="load seq"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="playModes" id="8b30775dcc59763b" memberName="playModes"
          virtualName="" explicitFocusOrder="0" pos="328 175 64 24" thumbcol="ff564c43"
          trackcol="ffffffff" min="0" max="2" int="1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="dottedNotes" id="ef5b938fe294c4b4" memberName="dottedNotes"
                virtualName="" explicitFocusOrder="0" pos="326 121 64 30" txtcol="ffffffff"
                buttonText="dot" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
