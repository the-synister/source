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
Env1Panel::Env1Panel (SynthParams &p, int envelopeNumber)
    : PanelBase(p),
      env(p.env[envelopeNumber])
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (env2SpeedModSrc1 = new ComboBox ("env2SpeedModSrcBox1"));
    env2SpeedModSrc1->setEditableText (false);
    env2SpeedModSrc1->setJustificationType (Justification::centred);
    env2SpeedModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    env2SpeedModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    env2SpeedModSrc1->addListener (this);

    addAndMakeVisible (env2SpeedModSrc2 = new ComboBox ("env2SpeedModSrcBox2"));
    env2SpeedModSrc2->setEditableText (false);
    env2SpeedModSrc2->setJustificationType (Justification::centred);
    env2SpeedModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    env2SpeedModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    env2SpeedModSrc2->addListener (this);

    addAndMakeVisible (attackTime1 = new MouseOverKnob ("Attack Time"));
    attackTime1->setRange (0.001, 5, 0);
    attackTime1->setSliderStyle (Slider::RotaryVerticalDrag);
    attackTime1->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    attackTime1->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    attackTime1->setColour (Slider::textBoxTextColourId, Colours::white);
    attackTime1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    attackTime1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    attackTime1->addListener (this);
    attackTime1->setSkewFactor (0.5);

    addAndMakeVisible (decayTime1 = new MouseOverKnob ("Decay Time"));
    decayTime1->setRange (0.001, 5, 0);
    decayTime1->setSliderStyle (Slider::RotaryVerticalDrag);
    decayTime1->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    decayTime1->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    decayTime1->setColour (Slider::textBoxTextColourId, Colours::white);
    decayTime1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    decayTime1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    decayTime1->addListener (this);
    decayTime1->setSkewFactor (0.5);

    addAndMakeVisible (sustainLevel1 = new MouseOverKnob ("Sustain"));
    sustainLevel1->setRange (0, 1, 0);
    sustainLevel1->setSliderStyle (Slider::RotaryVerticalDrag);
    sustainLevel1->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    sustainLevel1->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    sustainLevel1->setColour (Slider::textBoxTextColourId, Colours::white);
    sustainLevel1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    sustainLevel1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    sustainLevel1->addListener (this);
    sustainLevel1->setSkewFactor (3);

    addAndMakeVisible (releaseTime1 = new MouseOverKnob ("Release Time"));
    releaseTime1->setRange (0.001, 5, 0);
    releaseTime1->setSliderStyle (Slider::RotaryVerticalDrag);
    releaseTime1->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    releaseTime1->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    releaseTime1->setColour (Slider::textBoxTextColourId, Colours::white);
    releaseTime1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    releaseTime1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    releaseTime1->addListener (this);
    releaseTime1->setSkewFactor (0.5);

    addAndMakeVisible (attackShape1 = new MouseOverKnob ("Attack Shape"));
    attackShape1->setRange (0.01, 10, 0);
    attackShape1->setSliderStyle (Slider::RotaryVerticalDrag);
    attackShape1->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    attackShape1->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    attackShape1->addListener (this);
    attackShape1->setSkewFactor (0.3);

    addAndMakeVisible (decayShape1 = new MouseOverKnob ("Decay Shape"));
    decayShape1->setRange (0.01, 10, 0);
    decayShape1->setSliderStyle (Slider::RotaryVerticalDrag);
    decayShape1->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    decayShape1->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    decayShape1->addListener (this);
    decayShape1->setSkewFactor (0.3);

    addAndMakeVisible (releaseShape1 = new MouseOverKnob ("Release Shape"));
    releaseShape1->setRange (0.01, 10, 0);
    releaseShape1->setSliderStyle (Slider::RotaryVerticalDrag);
    releaseShape1->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    releaseShape1->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    releaseShape1->addListener (this);
    releaseShape1->setSkewFactor (0.3);

    addAndMakeVisible (keyVelToEnv1 = new MouseOverKnob ("Vel to Env"));
    keyVelToEnv1->setRange (0, 1, 0);
    keyVelToEnv1->setSliderStyle (Slider::RotaryVerticalDrag);
    keyVelToEnv1->setTextBoxStyle (Slider::TextBoxBelow, true, 56, 20);
    keyVelToEnv1->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    keyVelToEnv1->setColour (Slider::textBoxTextColourId, Colours::white);
    keyVelToEnv1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    keyVelToEnv1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    keyVelToEnv1->addListener (this);

    addAndMakeVisible (envelopeCurve = new EnvelopeCurve (env.envAttack.get(), env.envDecay.get(), ((env.envSustain.get() - 1) * 96), env.envRelease.get(),  env.envAttackShape.get(), env.envDecayShape.get(), env.envReleaseShape.get()
                                                          ));
    envelopeCurve->setName ("Envelope Curve");

    addAndMakeVisible (shapeLabel1 = new Label ("new label",
                                                TRANS("shape")));
    shapeLabel1->setFont (Font ("Bauhaus 93", 20.00f, Font::plain));
    shapeLabel1->setJustificationType (Justification::centred);
    shapeLabel1->setEditable (false, false, false);
    shapeLabel1->setColour (Label::textColourId, Colours::white);
    shapeLabel1->setColour (TextEditor::textColourId, Colours::black);
    shapeLabel1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    registerSlider(attackTime1, &env.envAttack, std::bind(&Env1Panel::updateCurve, this));
    registerSlider(decayTime1, &env.envDecay, std::bind(&Env1Panel::updateCurve, this));
    registerSlider(sustainLevel1, &env.envSustain, std::bind(&Env1Panel::updateCurve, this));
    registerSlider(releaseTime1, &env.envRelease, std::bind(&Env1Panel::updateCurve, this));
    registerSlider(attackShape1, &env.envAttackShape, std::bind(&Env1Panel::updateCurve, this));
    registerSlider(decayShape1, &env.envDecayShape, std::bind(&Env1Panel::updateCurve, this));
    registerSlider(releaseShape1, &env.envReleaseShape, std::bind(&Env1Panel::updateCurve, this));
    registerSlider(keyVelToEnv1, &env.keyVelToEnv, std::bind(&Env1Panel::updateCurve, this));
    //[/UserPreSize]

    setSize (267, 252);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Env1Panel::~Env1Panel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    env2SpeedModSrc1 = nullptr;
    env2SpeedModSrc2 = nullptr;
    attackTime1 = nullptr;
    decayTime1 = nullptr;
    sustainLevel1 = nullptr;
    releaseTime1 = nullptr;
    attackShape1 = nullptr;
    decayShape1 = nullptr;
    releaseShape1 = nullptr;
    keyVelToEnv1 = nullptr;
    envelopeCurve = nullptr;
    shapeLabel1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Env1Panel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffcbca63));

    //[UserPaint] Add your own custom painting code here..
    drawGroupBorder(g, env.name, 0, 0,
                    this->getWidth(), this->getHeight() - 22, 25.0f, 20.0f, 5.0f, 3.0f, Colour(0xffcbca63));

    int smallBorderHeight = 40;
    drawGroupBorder(g, "", 10, (this->getHeight() - 22) / 2 - (smallBorderHeight - 12) / 2,
                    this->getWidth() - 20, smallBorderHeight, 3.0f, 10.0f, 3.0f, 3.0f, Colour(0xffcbca63));
    //[/UserPaint]
}

void Env1Panel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    env2SpeedModSrc1->setBounds (60, 177, 64, 16);
    env2SpeedModSrc2->setBounds (60, 153, 64, 16);
    attackTime1->setBounds (12, 39, 64, 64);
    decayTime1->setBounds (73, 39, 64, 64);
    sustainLevel1->setBounds (134, 39, 64, 64);
    releaseTime1->setBounds (199, 39, 64, 64);
    attackShape1->setBounds (34, 112, 20, 20);
    decayShape1->setBounds (95, 112, 20, 20);
    releaseShape1->setBounds (220, 112, 20, 20);
    keyVelToEnv1->setBounds (12, 147, 64, 64);
    envelopeCurve->setBounds (121, 147, 128, 64);
    shapeLabel1->setBounds (141, 109, 51, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Env1Panel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == env2SpeedModSrc1)
    {
        //[UserComboBoxCode_env2SpeedModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_env2SpeedModSrc1]
    }
    else if (comboBoxThatHasChanged == env2SpeedModSrc2)
    {
        //[UserComboBoxCode_env2SpeedModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_env2SpeedModSrc2]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
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
void Env1Panel::updateCurve()
{
    envelopeCurve->setAttack(static_cast<float>(attackTime1->getValue()));
    envelopeCurve->setDecay(static_cast<float>(decayTime1->getValue()));
    envelopeCurve->setSustain(static_cast<float>((sustainLevel1->getValue() - 1) * 96));
    envelopeCurve->setRelease(static_cast<float>(releaseTime1->getValue()));
    envelopeCurve->setAttackShape(static_cast<float>(attackShape1->getValue()));
    envelopeCurve->setDecayShape(static_cast<float>(decayShape1->getValue()));
    envelopeCurve->setReleaseShape(static_cast<float>(releaseShape1->getValue()));
    repaint();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Env1Panel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p, int envelopeNumber"
                 variableInitialisers="PanelBase(p), &#10;env(p.env[envelopeNumber])"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="267" initialHeight="252">
  <BACKGROUND backgroundColour="ffcbca63"/>
  <COMBOBOX name="env2SpeedModSrcBox1" id="6dae6bde5fbe8153" memberName="env2SpeedModSrc1"
            virtualName="" explicitFocusOrder="0" pos="60 177 64 16" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="env2SpeedModSrcBox2" id="401dffa72d979c97" memberName="env2SpeedModSrc2"
            virtualName="" explicitFocusOrder="0" pos="60 153 64 16" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <SLIDER name="Attack Time" id="c3597517f8c98b63" memberName="attackTime1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="12 39 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.0010000000000000000208" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Decay Time" id="9731927ce4f75586" memberName="decayTime1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="73 39 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.0010000000000000000208" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Sustain" id="c5800da9b4223b05" memberName="sustainLevel1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="134 39 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="3"/>
  <SLIDER name="Release Time" id="b706f933608906" memberName="releaseTime1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="199 39 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.0010000000000000000208" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Attack Shape" id="bd17ed6e5bdc4910" memberName="attackShape1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="34 112 20 20"
          rotarysliderfill="ffbfa65a" min="0.010000000000000000208" max="10"
          int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="0" textBoxHeight="0" skewFactor="0.2999999999999999889"/>
  <SLIDER name="Decay Shape" id="9bd5989569f5223c" memberName="decayShape1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="95 112 20 20"
          rotarysliderfill="ffbfa65a" min="0.010000000000000000208" max="10"
          int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="0" textBoxHeight="0" skewFactor="0.2999999999999999889"/>
  <SLIDER name="Release Shape" id="fb9fa6b3328d7d27" memberName="releaseShape1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="220 112 20 20"
          rotarysliderfill="ffbfa65a" min="0.010000000000000000208" max="10"
          int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="0" textBoxHeight="0" skewFactor="0.2999999999999999889"/>
  <SLIDER name="Vel to Env" id="bee5e0860811e660" memberName="keyVelToEnv1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="12 147 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="0" textBoxWidth="56"
          textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="Envelope Curve" id="c0212157938fff27" memberName="envelopeCurve"
                    virtualName="EnvelopeCurve" explicitFocusOrder="0" pos="121 147 128 64"
                    class="Component" params="env.envAttack.get(), env.envDecay.get(), ((env.envSustain.get() - 1) * 96), env.envRelease.get(),  env.envAttackShape.get(), env.envDecayShape.get(), env.envReleaseShape.get()&#10;"/>
  <LABEL name="new label" id="79aa8d544da4882d" memberName="shapeLabel1"
         virtualName="" explicitFocusOrder="0" pos="141 109 51 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="shape" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Bauhaus 93"
         fontsize="20" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
