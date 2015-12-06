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

    addAndMakeVisible (seqStep1 = new MouseOverKnob ("Step 1"));
    seqStep1->setRange (-1, 127, 1);
    seqStep1->setSliderStyle (Slider::RotaryVerticalDrag);
    seqStep1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep1->addListener (this);

    addAndMakeVisible (seqStep2 = new MouseOverKnob ("Step 2"));
    seqStep2->setRange (-1, 127, 1);
    seqStep2->setSliderStyle (Slider::RotaryVerticalDrag);
    seqStep2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep2->addListener (this);

    addAndMakeVisible (seqPlay = new TextButton ("Play Seq"));
    seqPlay->setButtonText (TRANS("Play"));
    seqPlay->setConnectedEdges (Button::ConnectedOnLeft);
    seqPlay->addListener (this);
    seqPlay->setColour (TextButton::buttonColourId, Colour (0xff9a9a9a));
    seqPlay->setColour (TextButton::buttonOnColourId, Colours::lime);
    seqPlay->setColour (TextButton::textColourOffId, Colours::black);

    addAndMakeVisible (syncHost = new ToggleButton ("Sync Host"));
    syncHost->setButtonText (TRANS("Sync with Host"));
    syncHost->addListener (this);
    syncHost->setColour (ToggleButton::textColourId, Colours::black);

    addAndMakeVisible (seqStep3 = new MouseOverKnob ("Step 3"));
    seqStep3->setRange (-1, 127, 1);
    seqStep3->setSliderStyle (Slider::RotaryVerticalDrag);
    seqStep3->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep3->addListener (this);

    addAndMakeVisible (seqStep4 = new MouseOverKnob ("Step 4"));
    seqStep4->setRange (-1, 127, 1);
    seqStep4->setSliderStyle (Slider::RotaryVerticalDrag);
    seqStep4->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep4->addListener (this);

    addAndMakeVisible (seqNumSteps = new MouseOverKnob ("Stepnumber"));
    seqNumSteps->setRange (1, 8, 1);
    seqNumSteps->setSliderStyle (Slider::RotaryVerticalDrag);
    seqNumSteps->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqNumSteps->addListener (this);

    addAndMakeVisible (seqStep5 = new MouseOverKnob ("Step 5"));
    seqStep5->setRange (-1, 127, 1);
    seqStep5->setSliderStyle (Slider::RotaryVerticalDrag);
    seqStep5->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep5->addListener (this);

    addAndMakeVisible (seqStep6 = new MouseOverKnob ("Step 6"));
    seqStep6->setRange (-1, 127, 1);
    seqStep6->setSliderStyle (Slider::RotaryVerticalDrag);
    seqStep6->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep6->addListener (this);

    addAndMakeVisible (seqStep7 = new MouseOverKnob ("Step 7"));
    seqStep7->setRange (-1, 127, 1);
    seqStep7->setSliderStyle (Slider::RotaryVerticalDrag);
    seqStep7->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep7->addListener (this);

    addAndMakeVisible (seqStep8 = new MouseOverKnob ("Step 8"));
    seqStep8->setRange (-1, 127, 1);
    seqStep8->setSliderStyle (Slider::RotaryVerticalDrag);
    seqStep8->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqStep8->addListener (this);


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

    seqStepSpeed = nullptr;
    seqStepLength = nullptr;
    seqStep1 = nullptr;
    seqStep2 = nullptr;
    seqPlay = nullptr;
    syncHost = nullptr;
    seqStep3 = nullptr;
    seqStep4 = nullptr;
    seqNumSteps = nullptr;
    seqStep5 = nullptr;
    seqStep6 = nullptr;
    seqStep7 = nullptr;
    seqStep8 = nullptr;


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
    //[/UserPreResize]

    seqStepSpeed->setBounds (7, 128, 64, 64);
    seqStepLength->setBounds (79, 128, 64, 64);
    seqStep1->setBounds (7, 8, 64, 64);
    seqStep2->setBounds (79, 8, 64, 64);
    seqPlay->setBounds (144, 88, 64, 24);
    syncHost->setBounds (16, 88, 120, 24);
    seqStep3->setBounds (152, 8, 64, 64);
    seqStep4->setBounds (224, 8, 64, 64);
    seqNumSteps->setBounds (152, 128, 64, 64);
    seqStep5->setBounds (296, 8, 64, 64);
    seqStep6->setBounds (368, 8, 64, 64);
    seqStep7->setBounds (440, 8, 64, 64);
    seqStep8->setBounds (512, 8, 64, 64);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SeqPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == seqStepSpeed)
    {
        //[UserSliderCode_seqStepSpeed] -- add your slider handling code here..
        //[/UserSliderCode_seqStepSpeed]
    }
    else if (sliderThatWasMoved == seqStepLength)
    {
        //[UserSliderCode_seqStepLength] -- add your slider handling code here..
        //[/UserSliderCode_seqStepLength]
    }
    else if (sliderThatWasMoved == seqStep1)
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
    else if (sliderThatWasMoved == seqNumSteps)
    {
        //[UserSliderCode_seqNumSteps] -- add your slider handling code here..
        //[/UserSliderCode_seqNumSteps]
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
                seqPlay->setColour(TextButton::buttonColourId, Colours::dimgrey);
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
            seqPlay->setColour(TextButton::buttonColourId, Colours::dimgrey);
        }
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
  <SLIDER name="Step Speed" id="6f57522c914edf53" memberName="seqStepSpeed"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="7 128 64 64"
          min="0.125" max="4" int="0.125" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step Length" id="e0d84d227ff04bc4" memberName="seqStepLength"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="79 128 64 64"
          min="0.125" max="4" int="0.125" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 1" id="1c1677034c4af23a" memberName="seqStep1" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="7 8 64 64" min="-1" max="127" int="1"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 2" id="e3931793046ce084" memberName="seqStep2" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="79 8 64 64" min="-1" max="127" int="1"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="Play Seq" id="4552dd6439420b59" memberName="seqPlay" virtualName=""
              explicitFocusOrder="0" pos="144 88 64 24" bgColOff="ff9a9a9a"
              bgColOn="ff00ff00" textColOn="ff000000" buttonText="Play" connectedEdges="1"
              needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="Sync Host" id="2314e559577fe768" memberName="syncHost"
                virtualName="" explicitFocusOrder="0" pos="16 88 120 24" txtcol="ff000000"
                buttonText="Sync with Host" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <SLIDER name="Step 3" id="5e31094656fb49f9" memberName="seqStep3" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="152 8 64 64" min="-1" max="127" int="1"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 4" id="7025db78c8ff10d4" memberName="seqStep4" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="224 8 64 64" min="-1" max="127" int="1"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Stepnumber" id="5a9417ec3a4f18b3" memberName="seqNumSteps"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="152 128 64 64"
          min="1" max="8" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 5" id="9eba062111540687" memberName="seqStep5" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="296 8 64 64" min="-1" max="127" int="1"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 6" id="6a53245b0ddd1528" memberName="seqStep6" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="368 8 64 64" min="-1" max="127" int="1"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 7" id="96cbc5e8f38bf170" memberName="seqStep7" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="440 8 64 64" min="-1" max="127" int="1"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Step 8" id="ee7a391120a49428" memberName="seqStep8" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="512 8 64 64" min="-1" max="127" int="1"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
