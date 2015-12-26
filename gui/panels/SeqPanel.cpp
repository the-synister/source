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
    seq = PluginAudioProcessor::getSequencer();
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

    addAndMakeVisible (seqStepSpeed = new MouseOverKnob ("Step Speed"));
    seqStepSpeed->setRange (0.125, 4, 0.125);
    seqStepSpeed->setSliderStyle (Slider::RotaryVerticalDrag);
    seqStepSpeed->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStepSpeed->addListener (this);

    addAndMakeVisible (seqStepLength = new MouseOverKnob ("Step Length"));
    seqStepLength->setRange (0.125, 4, 0.125);
    seqStepLength->setSliderStyle (Slider::RotaryVerticalDrag);
    seqStepLength->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStepLength->addListener (this);

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

    addAndMakeVisible (seqNumSteps = new MouseOverKnob ("Stepnumber"));
    seqNumSteps->setRange (1, 8, 1);
    seqNumSteps->setSliderStyle (Slider::RotaryVerticalDrag);
    seqNumSteps->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqNumSteps->addListener (this);

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

    addAndMakeVisible (playRandSeq = new TextButton ("play random sequence"));
    playRandSeq->setButtonText (TRANS("Play Random Seq"));
    playRandSeq->setConnectedEdges (Button::ConnectedOnLeft);
    playRandSeq->addListener (this);
    playRandSeq->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    playRandSeq->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

    addAndMakeVisible (playRandomNotes = new TextButton ("play random notes"));
    playRandomNotes->setButtonText (TRANS("Play Random Notes"));
    playRandomNotes->setConnectedEdges (Button::ConnectedOnLeft);
    playRandomNotes->addListener (this);
    playRandomNotes->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    playRandomNotes->setColour (TextButton::buttonOnColourId, Colour (0xff60ff60));

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


    //[UserPreSize]
    registerSlider(seqNumSteps, &params.seqNumSteps);
    registerSlider(seqStepSpeed, &params.seqStepSpeed);
    registerSlider(seqStepLength, &params.seqStepLength);
    registerSlider(seqStep1, &params.seqStep1);
    registerSlider(seqStep2, &params.seqStep2);
    registerSlider(seqStep3, &params.seqStep3);
    registerSlider(seqStep4, &params.seqStep4);
    registerSlider(seqStep5, &params.seqStep5);
    registerSlider(seqStep6, &params.seqStep6);
    registerSlider(seqStep7, &params.seqStep7);
    registerSlider(seqStep8, &params.seqStep8);

    // init as activated
    labelButton1->setToggleState(true, dontSendNotification);
    labelButton2->setToggleState(true, dontSendNotification);
    labelButton3->setToggleState(true, dontSendNotification);
    labelButton4->setToggleState(true, dontSendNotification);
    labelButton5->setToggleState(true, dontSendNotification);
    labelButton6->setToggleState(true, dontSendNotification);
    labelButton7->setToggleState(true, dontSendNotification);
    labelButton8->setToggleState(true, dontSendNotification);

    randomSeq->setMinAndMaxValues(0, 127);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    sliderArray = {seqStep1.get(),
                   seqStep2.get(),
                   seqStep3.get(),
                   seqStep4.get(),
                   seqStep5.get(),
                   seqStep6.get(),
                   seqStep7.get(),
                   seqStep8.get()};
    //[/Constructor]
}

SeqPanel::~SeqPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    sliderArray.at(0).release();
    sliderArray.at(1).release();
    sliderArray.at(2).release();
    sliderArray.at(3).release();
    sliderArray.at(4).release();
    sliderArray.at(5).release();
    sliderArray.at(6).release();
    sliderArray.at(7).release();
    //[/Destructor_pre]

    seqStep1 = nullptr;
    seqStep2 = nullptr;
    seqStep3 = nullptr;
    seqStep4 = nullptr;
    seqStep5 = nullptr;
    seqStep6 = nullptr;
    seqStep7 = nullptr;
    seqStep8 = nullptr;
    seqStepSpeed = nullptr;
    seqStepLength = nullptr;
    seqPlay = nullptr;
    syncHost = nullptr;
    seqNumSteps = nullptr;
    labelButton1 = nullptr;
    labelButton2 = nullptr;
    labelButton3 = nullptr;
    labelButton4 = nullptr;
    labelButton5 = nullptr;
    labelButton6 = nullptr;
    labelButton7 = nullptr;
    labelButton8 = nullptr;
    genRandom = nullptr;
    playRandSeq = nullptr;
    playRandomNotes = nullptr;
    randomSeq = nullptr;
    randMinLabel = nullptr;
    randMaxLabel = nullptr;


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

    // state of syncHost and play button
    params.seqMode.getStep() == eSeqModes::seqSyncHost ? syncHost->setToggleState(true, dontSendNotification) :
        params.seqMode.getStep() == eSeqModes::seqStop ? seqPlay->setToggleState(false, dontSendNotification) :
            seqPlay->setToggleState(true, dontSendNotification);

    // seqNotes muted states
    seq->isNoteMuted(0) ? labelButton1->setToggleState(false, dontSendNotification) :
        labelButton1->setToggleState(true, dontSendNotification);
    seq->isNoteMuted(1) ? labelButton2->setToggleState(false, dontSendNotification) :
        labelButton2->setToggleState(true, dontSendNotification);
    seq->isNoteMuted(2) ? labelButton3->setToggleState(false, dontSendNotification) :
        labelButton3->setToggleState(true, dontSendNotification);
    seq->isNoteMuted(3) ? labelButton4->setToggleState(false, dontSendNotification) :
        labelButton4->setToggleState(true, dontSendNotification);
    seq->isNoteMuted(4) ? labelButton5->setToggleState(false, dontSendNotification) :
        labelButton5->setToggleState(true, dontSendNotification);
    seq->isNoteMuted(5) ? labelButton6->setToggleState(false, dontSendNotification) :
        labelButton6->setToggleState(true, dontSendNotification);
    seq->isNoteMuted(6) ? labelButton7->setToggleState(false, dontSendNotification) :
        labelButton7->setToggleState(true, dontSendNotification);
    seq->isNoteMuted(7) ? labelButton8->setToggleState(false, dontSendNotification) :
        labelButton8->setToggleState(true, dontSendNotification);

    // TODO other button states

    //[/UserPreResize]

    seqStep1->setBounds (336, 32, 48, 264);
    seqStep2->setBounds (392, 32, 48, 264);
    seqStep3->setBounds (448, 32, 48, 264);
    seqStep4->setBounds (504, 32, 48, 264);
    seqStep5->setBounds (560, 32, 48, 264);
    seqStep6->setBounds (616, 32, 48, 264);
    seqStep7->setBounds (672, 32, 48, 264);
    seqStep8->setBounds (728, 32, 48, 264);
    seqStepSpeed->setBounds (20, 140, 64, 64);
    seqStepLength->setBounds (92, 140, 64, 64);
    seqPlay->setBounds (148, 28, 100, 24);
    syncHost->setBounds (20, 56, 120, 24);
    seqNumSteps->setBounds (164, 140, 64, 64);
    labelButton1->setBounds (336, 6, 48, 24);
    labelButton2->setBounds (392, 6, 48, 24);
    labelButton3->setBounds (448, 6, 48, 24);
    labelButton4->setBounds (504, 6, 48, 24);
    labelButton5->setBounds (559, 6, 48, 24);
    labelButton6->setBounds (615, 6, 48, 24);
    labelButton7->setBounds (671, 6, 48, 24);
    labelButton8->setBounds (727, 6, 48, 24);
    genRandom->setBounds (20, 261, 100, 24);
    playRandSeq->setBounds (148, 56, 100, 24);
    playRandomNotes->setBounds (148, 84, 100, 24);
    randomSeq->setBounds (20, 292, 200, 35);
    randMinLabel->setBounds (20, 325, 100, 24);
    randMaxLabel->setBounds (120, 325, 100, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SeqPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    int newMidiValue = static_cast<int>(sliderThatWasMoved->getValue());
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
    else if (sliderThatWasMoved == seqStepSpeed)
    {
        //[UserSliderCode_seqStepSpeed] -- add your slider handling code here..
        //[/UserSliderCode_seqStepSpeed]
    }
    else if (sliderThatWasMoved == seqStepLength)
    {
        //[UserSliderCode_seqStepLength] -- add your slider handling code here..
        //[/UserSliderCode_seqStepLength]
    }
    else if (sliderThatWasMoved == seqNumSteps)
    {
        //[UserSliderCode_seqNumSteps] -- add your slider handling code here..
        //[/UserSliderCode_seqNumSteps]
    }
    else if (sliderThatWasMoved == randomSeq)
    {
        //[UserSliderCode_randomSeq] -- add your slider handling code here..
        randMinLabel->setText("Min: " + MidiMessage::getMidiNoteName(static_cast<int>(randomSeq->getMinValue()), true, true, 3), dontSendNotification);
        randomMin = static_cast<int>(randomSeq->getMinValue());
        randMaxLabel->setText("Max: " + MidiMessage::getMidiNoteName(static_cast<int>(randomSeq->getMaxValue()), true, true, 3), dontSendNotification);
        randomMax = static_cast<int>(randomSeq->getMaxValue());
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
                seqPlay->setToggleState(true, dontSendNotification);
            }
            else
            {
                params.seqMode.setStep(eSeqModes::seqStop);
                seqPlay->setToggleState(false, dontSendNotification);
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
        seqPlay->setToggleState(false, dontSendNotification);
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
        //seqStep1->setValue(r.nextDouble() * (randomMax - randomMin) + randomMin);
        ////r.setSeedRandomly();
        //seqStep2->setValue(r.nextDouble() * (randomMax - randomMin) + randomMin);
        ////r.setSeedRandomly();
        //seqStep3->setValue(r.nextDouble() * (randomMax - randomMin) + randomMin);
        ////r.setSeedRandomly();
        //seqStep4->setValue(r.nextDouble() * (randomMax - randomMin) + randomMin);
        ////r.setSeedRandomly();
        //seqStep5->setValue(r.nextDouble() * (randomMax - randomMin) + randomMin);
        ////r.setSeedRandomly();
        //seqStep6->setValue(r.nextDouble() * (randomMax - randomMin) + randomMin);
        ////r.setSeedRandomly();
        //seqStep7->setValue(r.nextDouble() * (randomMax - randomMin) + randomMin);
        ////r.setSeedRandomly();
        //seqStep8->setValue(r.nextDouble() * (randomMax - randomMin) + randomMin);

        for (int i = 0; i < 8; ++i)
        {
            r.setSeedRandomly();
            sliderArray.at(i)->setValue(r.nextDouble() * (randomMax - randomMin) + randomMin);
        }
        //[/UserButtonCode_genRandom]
    }
    else if (buttonThatWasClicked == playRandSeq)
    {
        //[UserButtonCode_playRandSeq] -- add your button handler code here..
        //[/UserButtonCode_playRandSeq]
    }
    else if (buttonThatWasClicked == playRandomNotes)
    {
        //[UserButtonCode_playRandomNotes] -- add your button handler code here..
        //[/UserButtonCode_playRandomNotes]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
// called periodicaly to check note position while playing
void SeqPanel::timerCallback()
{
    // vllt trennen host/sync wegen current bei hostmode anzeigen
    if (seq->isPlaying())
    {
        if (lastSeqNotePos != seq->getCurrentSeqNote())
        {
            seqStep1->setColour(Slider::trackColourId, Colour(0x7fffffff));
            seqStep2->setColour(Slider::trackColourId, Colour(0x7fffffff));
            seqStep3->setColour(Slider::trackColourId, Colour(0x7fffffff));
            seqStep4->setColour(Slider::trackColourId, Colour(0x7fffffff));
            seqStep5->setColour(Slider::trackColourId, Colour(0x7fffffff));
            seqStep6->setColour(Slider::trackColourId, Colour(0x7fffffff));
            seqStep7->setColour(Slider::trackColourId, Colour(0x7fffffff));
            seqStep8->setColour(Slider::trackColourId, Colour(0x7fffffff));
            lastSeqNotePos = seq->getCurrentSeqNote();
            lastSeqNotePos = jmax(0, jmin(lastSeqNotePos, 7));

            sliderArray.at(lastSeqNotePos)->setColour(Slider::trackColourId, Colour(0x7f0000ff));

            lastSeqNotePos = seq->getCurrentSeqNote();
        }
    }
    else
    {
        if (lastSeqNotePos != -1)
        {
            sliderArray.at(lastSeqNotePos)->setColour(Slider::trackColourId, Colour(0x7fffffff));
            lastSeqNotePos = -1;
        }
    }
    //PanelBase::timerCallback();
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
  <SLIDER name="Step Speed" id="6f57522c914edf53" memberName="seqStepSpeed"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="20 140 64 64"
          min="0.125" max="4" int="0.125" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step Length" id="e0d84d227ff04bc4" memberName="seqStepLength"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="92 140 64 64"
          min="0.125" max="4" int="0.125" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="play sequencer" id="4552dd6439420b59" memberName="seqPlay"
              virtualName="" explicitFocusOrder="0" pos="148 28 100 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" textColOn="ff000000" buttonText="Play" connectedEdges="1"
              needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="Sync Host" id="2314e559577fe768" memberName="syncHost"
                virtualName="" explicitFocusOrder="0" pos="20 56 120 24" txtcol="ff000000"
                buttonText="Sync with Host" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <SLIDER name="Stepnumber" id="5a9417ec3a4f18b3" memberName="seqNumSteps"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="164 140 64 64"
          min="1" max="8" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
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
              virtualName="" explicitFocusOrder="0" pos="20 261 100 24" buttonText="Generate Sequence"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="play random sequence" id="7812f2e99405e440" memberName="playRandSeq"
              virtualName="" explicitFocusOrder="0" pos="148 56 100 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="Play Random Seq" connectedEdges="1"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="play random notes" id="cb741932faf16384" memberName="playRandomNotes"
              virtualName="" explicitFocusOrder="0" pos="148 84 100 24" bgColOff="ff9a9a9a"
              bgColOn="ff60ff60" buttonText="Play Random Notes" connectedEdges="1"
              needsCallback="1" radioGroupId="0"/>
  <SLIDER name="random sequence" id="2cf72626a61379e3" memberName="randomSeq"
          virtualName="" explicitFocusOrder="0" pos="20 292 200 35" min="0"
          max="127" int="0" style="TwoValueHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="random min label" id="4207acbbe3318ad" memberName="randMinLabel"
         virtualName="" explicitFocusOrder="0" pos="20 325 100 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Min: C-2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="16"
         bold="0" italic="0" justification="36"/>
  <LABEL name="random max label" id="b241e58f05db2570" memberName="randMaxLabel"
         virtualName="" explicitFocusOrder="0" pos="120 325 100 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Max: G8" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="16"
         bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
