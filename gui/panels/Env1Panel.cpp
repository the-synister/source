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

#include "Env1Panel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Env1Panel::Env1Panel (SynthParams &p)
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (attackTime1 = new MouseOverKnob ("Attack Time"));
    attackTime1->setRange (0.001, 5, 0);
    attackTime1->setSliderStyle (Slider::RotaryVerticalDrag);
    attackTime1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    attackTime1->addListener (this);
    attackTime1->setSkewFactor (0.5);

    addAndMakeVisible (decayTime1 = new MouseOverKnob ("Decay Time"));
    decayTime1->setRange (0.001, 5, 0);
    decayTime1->setSliderStyle (Slider::RotaryVerticalDrag);
    decayTime1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    decayTime1->addListener (this);
    decayTime1->setSkewFactor (0.5);

    addAndMakeVisible (sustainLevel1 = new MouseOverKnob ("Sustain"));
    sustainLevel1->setRange (-96, 0, 0);
    sustainLevel1->setSliderStyle (Slider::RotaryVerticalDrag);
    sustainLevel1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sustainLevel1->addListener (this);
    sustainLevel1->setSkewFactor (3);

    addAndMakeVisible (releaseTime1 = new MouseOverKnob ("Release Time"));
    releaseTime1->setRange (0.001, 5, 0);
    releaseTime1->setSliderStyle (Slider::RotaryVerticalDrag);
    releaseTime1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    releaseTime1->addListener (this);
    releaseTime1->setSkewFactor (0.5);

    addAndMakeVisible (attackShape1 = new MouseOverKnob ("Attack Shape"));
    attackShape1->setRange (0.01, 10, 0);
    attackShape1->setSliderStyle (Slider::RotaryVerticalDrag);
    attackShape1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    attackShape1->addListener (this);
    attackShape1->setSkewFactor (0.3);

    addAndMakeVisible (decayShape1 = new MouseOverKnob ("Decay Shape"));
    decayShape1->setRange (0.01, 10, 0);
    decayShape1->setSliderStyle (Slider::RotaryVerticalDrag);
    decayShape1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    decayShape1->addListener (this);
    decayShape1->setSkewFactor (0.3);

    addAndMakeVisible (releaseShape1 = new MouseOverKnob ("Release Shape"));
    releaseShape1->setRange (0.01, 10, 0);
    releaseShape1->setSliderStyle (Slider::RotaryVerticalDrag);
    releaseShape1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    releaseShape1->addListener (this);
    releaseShape1->setSkewFactor (0.3);

    addAndMakeVisible (keyVelToEnv1 = new MouseOverKnob ("Vel to Env"));
    keyVelToEnv1->setRange (0, 1, 0);
    keyVelToEnv1->setSliderStyle (Slider::RotaryVerticalDrag);
    keyVelToEnv1->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    keyVelToEnv1->addListener (this);

    addAndMakeVisible (Env1Label = new Label ("Envelope_1",
                                              TRANS("Envelope 1")));
    Env1Label->setFont (Font (15.00f, Font::plain));
    Env1Label->setJustificationType (Justification::centredLeft);
    Env1Label->setEditable (false, false, false);
    Env1Label->setColour (TextEditor::textColourId, Colours::black);
    Env1Label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    registerSlider(attackTime1, &params.env1Attack);
    registerSlider(decayTime1, &params.env1Decay);
    registerSlider(sustainLevel1, &params.env1Sustain);
    registerSlider(releaseTime1, &params.env1Release);
    registerSlider(attackShape1, &params.env1AttackShape);
    registerSlider(decayShape1, &params.env1DecayShape);
    registerSlider(releaseShape1, &params.env1ReleaseShape);
    registerSlider(keyVelToEnv1, &params.keyVelToEnv1);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Env1Panel::~Env1Panel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    attackTime1 = nullptr;
    decayTime1 = nullptr;
    sustainLevel1 = nullptr;
    releaseTime1 = nullptr;
    attackShape1 = nullptr;
    decayShape1 = nullptr;
    releaseShape1 = nullptr;
    keyVelToEnv1 = nullptr;
    Env1Label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Env1Panel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Env1Panel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    attackTime1->setBounds (8, 32, 64, 64);
    decayTime1->setBounds (80, 32, 64, 64);
    sustainLevel1->setBounds (152, 32, 64, 64);
    releaseTime1->setBounds (224, 32, 64, 64);
    attackShape1->setBounds (8, 104, 64, 64);
    decayShape1->setBounds (80, 104, 64, 64);
    releaseShape1->setBounds (224, 104, 64, 64);
    keyVelToEnv1->setBounds (296, 32, 64, 64);
    Env1Label->setBounds (8, 8, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Env1Panel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == attackTime1)
    {
        //[UserSliderCode_attackTime1] -- add your slider handling code here..
        //[/UserSliderCode_attackTime1]
    }
    else if (sliderThatWasMoved == decayTime1)
    {
        //[UserSliderCode_decayTime1] -- add your slider handling code here..
        //[/UserSliderCode_decayTime1]
    }
    else if (sliderThatWasMoved == sustainLevel1)
    {
        //[UserSliderCode_sustainLevel1] -- add your slider handling code here..
        //[/UserSliderCode_sustainLevel1]
    }
    else if (sliderThatWasMoved == releaseTime1)
    {
        //[UserSliderCode_releaseTime1] -- add your slider handling code here..
        //[/UserSliderCode_releaseTime1]
    }
    else if (sliderThatWasMoved == attackShape1)
    {
        //[UserSliderCode_attackShape1] -- add your slider handling code here..
        //[/UserSliderCode_attackShape1]
    }
    else if (sliderThatWasMoved == decayShape1)
    {
        //[UserSliderCode_decayShape1] -- add your slider handling code here..
        //[/UserSliderCode_decayShape1]
    }
    else if (sliderThatWasMoved == releaseShape1)
    {
        //[UserSliderCode_releaseShape1] -- add your slider handling code here..
        //[/UserSliderCode_releaseShape1]
    }
    else if (sliderThatWasMoved == keyVelToEnv1)
    {
        //[UserSliderCode_keyVelToEnv1] -- add your slider handling code here..
        //[/UserSliderCode_keyVelToEnv1]
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

<JUCER_COMPONENT documentType="Component" className="Env1Panel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)&#10;" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Attack Time" id="3c32cde7173ddbe6" memberName="attackTime1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 32 64 64"
          min="0.001" max="5" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Decay Time" id="84a4159bee0728d6" memberName="decayTime1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="80 32 64 64"
          min="0.001" max="5" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Sustain" id="4bc867c016d7595f" memberName="sustainLevel1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="152 32 64 64"
          min="-96" max="0" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="3"/>
  <SLIDER name="Release Time" id="c8bc1120a33101cd" memberName="releaseTime1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="224 32 64 64"
          min="0.001" max="5" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Attack Shape" id="27ef7f1857e5d79b" memberName="attackShape1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 104 64 64"
          min="0.01" max="10" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.29999999999999999"/>
  <SLIDER name="Decay Shape" id="18adbff3650623b1" memberName="decayShape1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="80 104 64 64"
          min="0.01" max="10" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.29999999999999999"/>
  <SLIDER name="Release Shape" id="adb5f4f555fb76d1" memberName="releaseShape1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="224 104 64 64"
          min="0.01" max="10" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.29999999999999999"/>
  <SLIDER name="Vel to Env" id="595a20e744f094d5" memberName="keyVelToEnv1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="296 32 64 64"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Envelope_1" id="a3abaef13a231d86" memberName="Env1Label"
         virtualName="" explicitFocusOrder="0" pos="8 8 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Envelope 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
