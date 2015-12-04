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

#include "OscPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
OscPanel::OscPanel (SynthParams &p)
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (ftune1 = new MouseOverKnob ("fine tune 1"));
    ftune1->setRange (-100, 100, 0);
    ftune1->setSliderStyle (Slider::RotaryVerticalDrag);
    ftune1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    ftune1->addListener (this);

    addAndMakeVisible (lfo1depth1 = new MouseOverKnob ("LFO depth 1"));
    lfo1depth1->setRange (0, 12, 0);
    lfo1depth1->setSliderStyle (Slider::RotaryVerticalDrag);
    lfo1depth1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    lfo1depth1->addListener (this);

    addAndMakeVisible (osc1trngAmount = new MouseOverKnob ("Osc1 Triangle Amount"));
    osc1trngAmount->setRange (0, 1, 0);
    osc1trngAmount->setSliderStyle (Slider::RotaryVerticalDrag);
    osc1trngAmount->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    osc1trngAmount->addListener (this);

    addAndMakeVisible (pulsewidth = new MouseOverKnob ("Pulse Width"));
    pulsewidth->setRange (0.01, 0.99, 0);
    pulsewidth->setSliderStyle (Slider::RotaryVerticalDrag);
    pulsewidth->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    pulsewidth->addListener (this);

    addAndMakeVisible (pitchRange = new MouseOverKnob ("pitch range"));
    pitchRange->setRange (0, 12, 0);
    pitchRange->setSliderStyle (Slider::RotaryVerticalDrag);
    pitchRange->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    pitchRange->addListener (this);

    addAndMakeVisible (ctune1 = new MouseOverKnob ("coarse tune 1"));
    ctune1->setRange (-11, 11, 1);
    ctune1->setSliderStyle (Slider::RotaryVerticalDrag);
    ctune1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    ctune1->addListener (this);

    addAndMakeVisible (seqSpeed = new MouseOverKnob ("Seq Speed"));
    seqSpeed->setRange (0.125, 4, 0.125);
    seqSpeed->setSliderStyle (Slider::RotaryVerticalDrag);
    seqSpeed->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqSpeed->addListener (this);

    addAndMakeVisible (seqNoteLength = new MouseOverKnob ("Seq Note Length"));
    seqNoteLength->setRange (0.125, 4, 0.125);
    seqNoteLength->setSliderStyle (Slider::RotaryVerticalDrag);
    seqNoteLength->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqNoteLength->addListener (this);

    addAndMakeVisible (seqNote1 = new MouseOverKnob ("Seq Note 1"));
    seqNote1->setRange (-1, 127, 1);
    seqNote1->setSliderStyle (Slider::RotaryVerticalDrag);
    seqNote1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqNote1->addListener (this);

    addAndMakeVisible (seqNote2 = new MouseOverKnob ("Seq Note 2"));
    seqNote2->setRange (-1, 127, 1);
    seqNote2->setSliderStyle (Slider::RotaryVerticalDrag);
    seqNote2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqNote2->addListener (this);

    addAndMakeVisible (seqNote3 = new MouseOverKnob ("Seq Note 3"));
    seqNote3->setRange (-1, 127, 1);
    seqNote3->setSliderStyle (Slider::RotaryVerticalDrag);
    seqNote3->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqNote3->addListener (this);

    addAndMakeVisible (seqNote4 = new MouseOverKnob ("Seq Note 4"));
    seqNote4->setRange (-1, 127, 1);
    seqNote4->setSliderStyle (Slider::RotaryVerticalDrag);
    seqNote4->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    seqNote4->addListener (this);


    //[UserPreSize]
    registerSlider(ftune1, &params.osc1fine);
    registerSlider(lfo1depth1, &params.osc1lfo1depth);
    registerSlider(osc1trngAmount, &params.osc1trngAmount);
    registerSlider(pitchRange, &params.osc1PitchRange);
    registerSlider(pulsewidth, &params.osc1pulsewidth);
    registerSlider(ctune1, &params.osc1coarse);

    registerSlider(seqSpeed, &params.seqSpeed);
    registerSlider(seqNoteLength, &params.seqNoteLength);
    registerSlider(seqNote1, &params.SeqNote1);
    registerSlider(seqNote2, &params.SeqNote2);
    registerSlider(seqNote3, &params.SeqNote3);
    registerSlider(seqNote4, &params.SeqNote4);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

OscPanel::~OscPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    ftune1 = nullptr;
    lfo1depth1 = nullptr;
    osc1trngAmount = nullptr;
    pulsewidth = nullptr;
    pitchRange = nullptr;
    ctune1 = nullptr;
    seqSpeed = nullptr;
    seqNoteLength = nullptr;
    seqNote1 = nullptr;
    seqNote2 = nullptr;
    seqNote3 = nullptr;
    seqNote4 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void OscPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void OscPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    ftune1->setBounds (80, 8, 64, 64);
    lfo1depth1->setBounds (224, 8, 64, 64);
    osc1trngAmount->setBounds (296, 8, 64, 64);
    pulsewidth->setBounds (368, 8, 64, 64);
    pitchRange->setBounds (152, 8, 64, 64);
    ctune1->setBounds (8, 8, 64, 64);
    seqSpeed->setBounds (8, 144, 64, 64);
    seqNoteLength->setBounds (80, 144, 64, 64);
    seqNote1->setBounds (8, 216, 64, 64);
    seqNote2->setBounds (80, 216, 64, 64);
    seqNote3->setBounds (152, 216, 64, 64);
    seqNote4->setBounds (224, 216, 64, 64);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void OscPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == ftune1)
    {
        //[UserSliderCode_ftune1] -- add your slider handling code here..
        //[/UserSliderCode_ftune1]
    }
    else if (sliderThatWasMoved == lfo1depth1)
    {
        //[UserSliderCode_lfo1depth1] -- add your slider handling code here..
        //[/UserSliderCode_lfo1depth1]
    }
    else if (sliderThatWasMoved == osc1trngAmount)
    {
        //[UserSliderCode_osc1trngAmount] -- add your slider handling code here..
        //[/UserSliderCode_osc1trngAmount]
    }
    else if (sliderThatWasMoved == pulsewidth)
    {
        //[UserSliderCode_pulsewidth] -- add your slider handling code here..
        //[/UserSliderCode_pulsewidth]
    }
    else if (sliderThatWasMoved == pitchRange)
    {
        //[UserSliderCode_pitchRange] -- add your slider handling code here..
        //[/UserSliderCode_pitchRange]
    }
    else if (sliderThatWasMoved == ctune1)
    {
        //[UserSliderCode_ctune1] -- add your slider handling code here..
        //[/UserSliderCode_ctune1]
    }
    else if (sliderThatWasMoved == seqSpeed)
    {
        //[UserSliderCode_seqSpeed] -- add your slider handling code here..
        //[/UserSliderCode_seqSpeed]
    }
    else if (sliderThatWasMoved == seqNoteLength)
    {
        //[UserSliderCode_seqNoteLength] -- add your slider handling code here..
        //[/UserSliderCode_seqNoteLength]
    }
    else if (sliderThatWasMoved == seqNote1)
    {
        //[UserSliderCode_seqNote1] -- add your slider handling code here..
        //[/UserSliderCode_seqNote1]
    }
    else if (sliderThatWasMoved == seqNote2)
    {
        //[UserSliderCode_seqNote2] -- add your slider handling code here..
        //[/UserSliderCode_seqNote2]
    }
    else if (sliderThatWasMoved == seqNote3)
    {
        //[UserSliderCode_seqNote3] -- add your slider handling code here..
        //[/UserSliderCode_seqNote3]
    }
    else if (sliderThatWasMoved == seqNote4)
    {
        //[UserSliderCode_seqNote4] -- add your slider handling code here..
        //[/UserSliderCode_seqNote4]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="OscPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="fine tune 1" id="3c32cde7173ddbe6" memberName="ftune1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="80 8 64 64"
          min="-100" max="100" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="LFO depth 1" id="523b9024be39c1b" memberName="lfo1depth1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="224 8 64 64"
          min="0" max="12" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc1 Triangle Amount" id="d81a0f8c69078b3c" memberName="osc1trngAmount"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="296 8 64 64"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Pulse Width" id="96badb5ea7640431" memberName="pulsewidth"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="368 8 64 64"
          min="0.01" max="0.98999999999999999" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="pitch range" id="29275125e377aaa" memberName="pitchRange"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="152 8 64 64"
          min="0" max="12" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="coarse tune 1" id="52a6628a22cee304" memberName="ctune1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 8 64 64"
          min="-11" max="11" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Seq Speed" id="6f57522c914edf53" memberName="seqSpeed"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 144 64 64"
          min="0.125" max="4" int="0.125" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Seq Note Length" id="e0d84d227ff04bc4" memberName="seqNoteLength"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="80 144 64 64"
          min="0.125" max="4" int="0.125" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Seq Note 1" id="1c1677034c4af23a" memberName="seqNote1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 216 64 64"
          min="-1" max="127" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Seq Note 2" id="e3931793046ce084" memberName="seqNote2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="80 216 64 64"
          min="-1" max="127" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Seq Note 3" id="efd5900fdafdcd9c" memberName="seqNote3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="152 216 64 64"
          min="-1" max="127" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Seq Note 4" id="35bc6ff00546280f" memberName="seqNote4"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="224 216 64 64"
          min="-1" max="127" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
