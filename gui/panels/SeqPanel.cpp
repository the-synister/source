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
    seqStep1->setRange (-1, 127, 1);
    seqStep1->setSliderStyle (Slider::LinearVertical);
    seqStep1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep1->addListener (this);

    addAndMakeVisible (seqStep2 = new Slider ("Step 2"));
    seqStep2->setRange (-1, 127, 1);
    seqStep2->setSliderStyle (Slider::LinearVertical);
    seqStep2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep2->addListener (this);

    addAndMakeVisible (seqStep3 = new Slider ("Step 3"));
    seqStep3->setRange (-1, 127, 1);
    seqStep3->setSliderStyle (Slider::LinearVertical);
    seqStep3->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep3->addListener (this);

    addAndMakeVisible (seqStep4 = new Slider ("Step 4"));
    seqStep4->setRange (-1, 127, 1);
    seqStep4->setSliderStyle (Slider::LinearVertical);
    seqStep4->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep4->addListener (this);

    addAndMakeVisible (seqStep5 = new Slider ("Step 5"));
    seqStep5->setRange (-1, 127, 1);
    seqStep5->setSliderStyle (Slider::LinearVertical);
    seqStep5->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep5->addListener (this);

    addAndMakeVisible (seqStep6 = new Slider ("Step 6"));
    seqStep6->setRange (-1, 127, 1);
    seqStep6->setSliderStyle (Slider::LinearVertical);
    seqStep6->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep6->addListener (this);

    addAndMakeVisible (seqStep7 = new Slider ("Step 7"));
    seqStep7->setRange (-1, 127, 1);
    seqStep7->setSliderStyle (Slider::LinearVertical);
    seqStep7->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep7->addListener (this);

    addAndMakeVisible (seqStep8 = new Slider ("Step 8"));
    seqStep8->setRange (-1, 127, 1);
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

    addAndMakeVisible (seqPlay = new TextButton ("Play Seq"));
    seqPlay->setButtonText (TRANS("Play No Host"));
    seqPlay->addListener (this);
    seqPlay->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    seqPlay->setColour (TextButton::buttonOnColourId, Colours::lime);
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

    addAndMakeVisible (labelStep1 = new Label ("label step 1",
                                               TRANS("C3")));
    labelStep1->setFont (Font (Font::getDefaultMonospacedFontName(), 16.00f, Font::plain));
    labelStep1->setJustificationType (Justification::centred);
    labelStep1->setEditable (false, false, false);
    labelStep1->setColour (TextEditor::textColourId, Colours::black);
    labelStep1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelStep2 = new Label ("label step 2",
                                               TRANS("D3")));
    labelStep2->setFont (Font (Font::getDefaultMonospacedFontName(), 16.00f, Font::plain));
    labelStep2->setJustificationType (Justification::centred);
    labelStep2->setEditable (false, false, false);
    labelStep2->setColour (TextEditor::textColourId, Colours::black);
    labelStep2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelStep3 = new Label ("label step 3",
                                               TRANS("E3")));
    labelStep3->setFont (Font (Font::getDefaultMonospacedFontName(), 16.00f, Font::plain));
    labelStep3->setJustificationType (Justification::centred);
    labelStep3->setEditable (false, false, false);
    labelStep3->setColour (TextEditor::textColourId, Colours::black);
    labelStep3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelStep4 = new Label ("label step 4",
                                               TRANS("F3")));
    labelStep4->setFont (Font (Font::getDefaultMonospacedFontName(), 16.00f, Font::plain));
    labelStep4->setJustificationType (Justification::centred);
    labelStep4->setEditable (false, false, false);
    labelStep4->setColour (TextEditor::textColourId, Colours::black);
    labelStep4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelStep5 = new Label ("label step 5",
                                               TRANS("G3")));
    labelStep5->setFont (Font (Font::getDefaultMonospacedFontName(), 16.00f, Font::plain));
    labelStep5->setJustificationType (Justification::centred);
    labelStep5->setEditable (false, false, false);
    labelStep5->setColour (TextEditor::textColourId, Colours::black);
    labelStep5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelStep6 = new Label ("label step 6",
                                               TRANS("A3")));
    labelStep6->setFont (Font (Font::getDefaultMonospacedFontName(), 16.00f, Font::plain));
    labelStep6->setJustificationType (Justification::centred);
    labelStep6->setEditable (false, false, false);
    labelStep6->setColour (TextEditor::textColourId, Colours::black);
    labelStep6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelStep7 = new Label ("label step 7",
                                               TRANS("A3")));
    labelStep7->setFont (Font (Font::getDefaultMonospacedFontName(), 16.00f, Font::plain));
    labelStep7->setJustificationType (Justification::centred);
    labelStep7->setEditable (false, false, false);
    labelStep7->setColour (TextEditor::textColourId, Colours::black);
    labelStep7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelStep8 = new Label ("label step 8",
                                               TRANS("C4")));
    labelStep8->setFont (Font (Font::getDefaultMonospacedFontName(), 16.00f, Font::plain));
    labelStep8->setJustificationType (Justification::centred);
    labelStep8->setEditable (false, false, false);
    labelStep8->setColour (TextEditor::textColourId, Colours::black);
    labelStep8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


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
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SeqPanel::~SeqPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
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
    labelStep1 = nullptr;
    labelStep2 = nullptr;
    labelStep3 = nullptr;
    labelStep4 = nullptr;
    labelStep5 = nullptr;
    labelStep6 = nullptr;
    labelStep7 = nullptr;
    labelStep8 = nullptr;


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
    if (params.seqMode.get() < 1.5f)
    {
        if (params.seqMode.get() < 0.5f)
        {
            seqPlay->setColour(TextButton::buttonColourId, Colours::grey);
        }
        else
        {
            seqPlay->setColour(TextButton::buttonColourId, Colours::lightgreen);
        }
    }
    else
    {
        syncHost->setToggleState(true, dontSendNotification);
    }
    //[/UserPreResize]

    seqStep1->setBounds (264, 48, 48, 264);
    seqStep2->setBounds (320, 48, 48, 264);
    seqStep3->setBounds (376, 48, 48, 264);
    seqStep4->setBounds (432, 48, 48, 264);
    seqStep5->setBounds (488, 48, 48, 264);
    seqStep6->setBounds (544, 48, 48, 264);
    seqStep7->setBounds (600, 48, 48, 264);
    seqStep8->setBounds (656, 48, 48, 264);
    seqStepSpeed->setBounds (27, 92, 64, 64);
    seqStepLength->setBounds (99, 92, 64, 64);
    seqPlay->setBounds (148, 52, 92, 24);
    syncHost->setBounds (20, 52, 120, 24);
    seqNumSteps->setBounds (172, 92, 64, 64);
    labelStep1->setBounds (264, 16, 48, 24);
    labelStep2->setBounds (320, 16, 48, 24);
    labelStep3->setBounds (376, 16, 48, 24);
    labelStep4->setBounds (432, 16, 48, 24);
    labelStep5->setBounds (488, 16, 48, 24);
    labelStep6->setBounds (544, 16, 48, 24);
    labelStep7->setBounds (600, 16, 48, 24);
    labelStep8->setBounds (656, 16, 48, 24);
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
        labelStep1->setText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3), dontSendNotification);
        //[/UserSliderCode_seqStep1]
    }
    else if (sliderThatWasMoved == seqStep2)
    {
        //[UserSliderCode_seqStep2] -- add your slider handling code here..
        labelStep2->setText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3), dontSendNotification);
        //[/UserSliderCode_seqStep2]
    }
    else if (sliderThatWasMoved == seqStep3)
    {
        //[UserSliderCode_seqStep3] -- add your slider handling code here..
        labelStep3->setText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3), dontSendNotification);
        //[/UserSliderCode_seqStep3]
    }
    else if (sliderThatWasMoved == seqStep4)
    {
        //[UserSliderCode_seqStep4] -- add your slider handling code here..
        labelStep4->setText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3), dontSendNotification);
        //[/UserSliderCode_seqStep4]
    }
    else if (sliderThatWasMoved == seqStep5)
    {
        //[UserSliderCode_seqStep5] -- add your slider handling code here..
        labelStep5->setText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3), dontSendNotification);
        //[/UserSliderCode_seqStep5]
    }
    else if (sliderThatWasMoved == seqStep6)
    {
        //[UserSliderCode_seqStep6] -- add your slider handling code here..
        labelStep6->setText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3), dontSendNotification);
        //[/UserSliderCode_seqStep6]
    }
    else if (sliderThatWasMoved == seqStep7)
    {
        //[UserSliderCode_seqStep7] -- add your slider handling code here..
        labelStep7->setText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3), dontSendNotification);
        //[/UserSliderCode_seqStep7]
    }
    else if (sliderThatWasMoved == seqStep8)
    {
        //[UserSliderCode_seqStep8] -- add your slider handling code here..
        labelStep8->setText(MidiMessage::getMidiNoteName(newMidiValue, true, true, 3), dontSendNotification);
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
        if (params.seqMode.get() < 1.5f)
        {
            if (params.seqMode.get() < 0.5f)
            {
                params.seqMode.set(1.0f);
                seqPlay->setColour(TextButton::buttonColourId, Colours::lightgreen);
            }
            else
            {
                params.seqMode.set(0.0f);
                seqPlay->setColour(TextButton::buttonColourId, Colours::grey);
            }
        }
        //[/UserButtonCode_seqPlay]
    }
    else if (buttonThatWasClicked == syncHost)
    {
        //[UserButtonCode_syncHost] -- add your button handler code here..
        if (params.seqMode.get() < 1.5f)
        {
            params.seqMode.set(2.0f);
        }
        else
        {
            params.seqMode.set(0.0f);
        }
        seqPlay->setColour(TextButton::buttonColourId, Colours::grey);
        //[/UserButtonCode_syncHost]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
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
  <SLIDER name="Step 1" id="1c1677034c4af23a" memberName="seqStep1" virtualName="Slider"
          explicitFocusOrder="0" pos="264 48 48 264" min="-1" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 2" id="e3931793046ce084" memberName="seqStep2" virtualName="Slider"
          explicitFocusOrder="0" pos="320 48 48 264" min="-1" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 3" id="5e31094656fb49f9" memberName="seqStep3" virtualName="Slider"
          explicitFocusOrder="0" pos="376 48 48 264" min="-1" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 4" id="7025db78c8ff10d4" memberName="seqStep4" virtualName="Slider"
          explicitFocusOrder="0" pos="432 48 48 264" min="-1" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 5" id="9eba062111540687" memberName="seqStep5" virtualName="Slider"
          explicitFocusOrder="0" pos="488 48 48 264" min="-1" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 6" id="6a53245b0ddd1528" memberName="seqStep6" virtualName="Slider"
          explicitFocusOrder="0" pos="544 48 48 264" min="-1" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 7" id="96cbc5e8f38bf170" memberName="seqStep7" virtualName="Slider"
          explicitFocusOrder="0" pos="600 48 48 264" min="-1" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 8" id="ee7a391120a49428" memberName="seqStep8" virtualName="Slider"
          explicitFocusOrder="0" pos="656 48 48 264" min="-1" max="127"
          int="1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step Speed" id="6f57522c914edf53" memberName="seqStepSpeed"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="27 92 64 64"
          min="0.125" max="4" int="0.125" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step Length" id="e0d84d227ff04bc4" memberName="seqStepLength"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="99 92 64 64"
          min="0.125" max="4" int="0.125" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="Play Seq" id="4552dd6439420b59" memberName="seqPlay" virtualName=""
              explicitFocusOrder="0" pos="148 52 92 24" bgColOff="ff9a9a9a"
              bgColOn="ff00ff00" textColOn="ff000000" buttonText="Play No Host"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="Sync Host" id="2314e559577fe768" memberName="syncHost"
                virtualName="" explicitFocusOrder="0" pos="20 52 120 24" txtcol="ff000000"
                buttonText="Sync with Host" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <SLIDER name="Stepnumber" id="5a9417ec3a4f18b3" memberName="seqNumSteps"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="172 92 64 64"
          min="1" max="8" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="label step 1" id="e768c24b3cbc5668" memberName="labelStep1"
         virtualName="" explicitFocusOrder="0" pos="264 16 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="C3" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="16"
         bold="0" italic="0" justification="36"/>
  <LABEL name="label step 2" id="5faecdd601753ab8" memberName="labelStep2"
         virtualName="" explicitFocusOrder="0" pos="320 16 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="D3" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="16"
         bold="0" italic="0" justification="36"/>
  <LABEL name="label step 3" id="a34ebc62f3b5064f" memberName="labelStep3"
         virtualName="" explicitFocusOrder="0" pos="376 16 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="E3" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="16"
         bold="0" italic="0" justification="36"/>
  <LABEL name="label step 4" id="c5d1a250cd2a49f5" memberName="labelStep4"
         virtualName="" explicitFocusOrder="0" pos="432 16 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="F3" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="16"
         bold="0" italic="0" justification="36"/>
  <LABEL name="label step 5" id="99588be5eac2123b" memberName="labelStep5"
         virtualName="" explicitFocusOrder="0" pos="488 16 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="G3" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="16"
         bold="0" italic="0" justification="36"/>
  <LABEL name="label step 6" id="506d14d658b53e67" memberName="labelStep6"
         virtualName="" explicitFocusOrder="0" pos="544 16 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="A3" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="16"
         bold="0" italic="0" justification="36"/>
  <LABEL name="label step 7" id="5dfc661e87e30bc0" memberName="labelStep7"
         virtualName="" explicitFocusOrder="0" pos="600 16 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="A3" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="16"
         bold="0" italic="0" justification="36"/>
  <LABEL name="label step 8" id="a5a3bd127e329108" memberName="labelStep8"
         virtualName="" explicitFocusOrder="0" pos="656 16 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="C4" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="16"
         bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
