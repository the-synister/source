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

#include "EnvPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
EnvPanel::EnvPanel (SynthParams &p)
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (attackTime = new MouseOverKnob ("Attack Time"));
    attackTime->setRange (0.001, 5, 0);
    attackTime->setSliderStyle (Slider::RotaryVerticalDrag);
    attackTime->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    attackTime->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    attackTime->setColour (Slider::textBoxTextColourId, Colours::white);
    attackTime->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    attackTime->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    attackTime->addListener (this);
    attackTime->setSkewFactor (0.5);

    addAndMakeVisible (decayTime = new MouseOverKnob ("Decay Time"));
    decayTime->setRange (0.001, 5, 0);
    decayTime->setSliderStyle (Slider::RotaryVerticalDrag);
    decayTime->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    decayTime->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    decayTime->setColour (Slider::textBoxTextColourId, Colours::white);
    decayTime->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    decayTime->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    decayTime->addListener (this);
    decayTime->setSkewFactor (0.5);

    addAndMakeVisible (sustainLevel = new MouseOverKnob ("Sustain"));
    sustainLevel->setRange (-96, 0, 0);
    sustainLevel->setSliderStyle (Slider::RotaryVerticalDrag);
    sustainLevel->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    sustainLevel->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    sustainLevel->setColour (Slider::textBoxTextColourId, Colours::white);
    sustainLevel->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    sustainLevel->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    sustainLevel->addListener (this);
    sustainLevel->setSkewFactor (3);

    addAndMakeVisible (releaseTime = new MouseOverKnob ("Release Time"));
    releaseTime->setRange (0.001, 5, 0);
    releaseTime->setSliderStyle (Slider::RotaryVerticalDrag);
    releaseTime->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    releaseTime->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    releaseTime->setColour (Slider::textBoxTextColourId, Colours::white);
    releaseTime->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    releaseTime->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    releaseTime->addListener (this);
    releaseTime->setSkewFactor (0.5);

    addAndMakeVisible (attackShape = new MouseOverKnob ("Attack Shape"));
    attackShape->setRange (0.01, 10, 0);
    attackShape->setSliderStyle (Slider::RotaryVerticalDrag);
    attackShape->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    attackShape->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    attackShape->addListener (this);
    attackShape->setSkewFactor (0.3);

    addAndMakeVisible (decayShape = new MouseOverKnob ("Decay Shape"));
    decayShape->setRange (0.01, 10, 0);
    decayShape->setSliderStyle (Slider::RotaryVerticalDrag);
    decayShape->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    decayShape->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    decayShape->addListener (this);
    decayShape->setSkewFactor (0.3);

    addAndMakeVisible (releaseShape = new MouseOverKnob ("Release Shape"));
    releaseShape->setRange (0.01, 10, 0);
    releaseShape->setSliderStyle (Slider::RotaryVerticalDrag);
    releaseShape->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    releaseShape->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    releaseShape->addListener (this);
    releaseShape->setSkewFactor (0.3);

    addAndMakeVisible (keyVelToEnv1 = new MouseOverKnob ("Vel to Env"));
    keyVelToEnv1->setRange (0, 1, 0);
    keyVelToEnv1->setSliderStyle (Slider::RotaryVerticalDrag);
    keyVelToEnv1->setTextBoxStyle (Slider::TextBoxBelow, true, 56, 20);
    keyVelToEnv1->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    keyVelToEnv1->setColour (Slider::textBoxTextColourId, Colours::white);
    keyVelToEnv1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    keyVelToEnv1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    keyVelToEnv1->addListener (this);

    addAndMakeVisible (envelopeCurve = new EnvelopeCurve (params.envAttack.get(), params.envDecay.get(), params.envSustain.get(), params.envRelease.get(),  params.envAttackShape.get(), params.envDecayShape.get(), params.envReleaseShape.get()
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
    registerSlider(attackTime, &params.envAttack, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(decayTime, &params.envDecay, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(sustainLevel, &params.envSustain, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(releaseTime, &params.envRelease, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(attackShape, &params.envAttackShape, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(decayShape, &params.envDecayShape, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(releaseShape, &params.envReleaseShape, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(keyVelToEnv1, &params.keyVelToEnv1);
    attackShape->setPopupDisplayEnabled(true, this);
    decayShape->setPopupDisplayEnabled(true, this);
    releaseShape->setPopupDisplayEnabled(true, this);

    //[/UserPreSize]

    setSize (266, 252);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

EnvPanel::~EnvPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    attackTime = nullptr;
    decayTime = nullptr;
    sustainLevel = nullptr;
    releaseTime = nullptr;
    attackShape = nullptr;
    decayShape = nullptr;
    releaseShape = nullptr;
    keyVelToEnv1 = nullptr;
    envelopeCurve = nullptr;
    shapeLabel1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void EnvPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffcbca63));

    //[UserPaint] Add your own custom painting code here..
    drawGroupBorder(g, "vol env", 0, 0,
        this->getWidth(), this->getHeight() - 22, 25.0f, 20.0f, 5.0f, 3.0f, Colour(0xffcbca63));

    int smallBorderHeight = 40;
    drawGroupBorder(g, "", 10, (this->getHeight() - 22) / 2 - (smallBorderHeight - 12) / 2,
        this->getWidth() - 20, smallBorderHeight, 3.0f, 10.0f, 3.0f, 3.0f, Colour(0xffcbca63));
    // NOTE: debug
    // TODO: panel is cutoff 22 pixel from below
    //g.setColour(Colours::red);
    //g.drawRect(0, 0, 10, 178);
    //g.drawRect(15, 0, 10, 200); // this (or height = 199) should be completely visible
    //g.drawRect(30, 0, 10, 222);
    //[/UserPaint]
}

void EnvPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    attackTime->setBounds (8, 38, 64, 64);
    decayTime->setBounds (69, 38, 64, 64);
    sustainLevel->setBounds (130, 38, 64, 64);
    releaseTime->setBounds (195, 38, 64, 64);
    attackShape->setBounds (30, 111, 20, 20);
    decayShape->setBounds (91, 111, 20, 20);
    releaseShape->setBounds (216, 111, 20, 20);
    keyVelToEnv1->setBounds (8, 146, 64, 64);
    envelopeCurve->setBounds (117, 146, 128, 64);
    shapeLabel1->setBounds (137, 108, 51, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void EnvPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == attackTime)
    {
        //[UserSliderCode_attackTime] -- add your slider handling code here..
        //[/UserSliderCode_attackTime]
    }
    else if (sliderThatWasMoved == decayTime)
    {
        //[UserSliderCode_decayTime] -- add your slider handling code here..
        //[/UserSliderCode_decayTime]
    }
    else if (sliderThatWasMoved == sustainLevel)
    {
        //[UserSliderCode_sustainLevel] -- add your slider handling code here..
        //[/UserSliderCode_sustainLevel]
    }
    else if (sliderThatWasMoved == releaseTime)
    {
        //[UserSliderCode_releaseTime] -- add your slider handling code here..
        //[/UserSliderCode_releaseTime]
    }
    else if (sliderThatWasMoved == attackShape)
    {
        //[UserSliderCode_attackShape] -- add your slider handling code here..
        //[/UserSliderCode_attackShape]
    }
    else if (sliderThatWasMoved == decayShape)
    {
        //[UserSliderCode_decayShape] -- add your slider handling code here..
        //[/UserSliderCode_decayShape]
    }
    else if (sliderThatWasMoved == releaseShape)
    {
        //[UserSliderCode_releaseShape] -- add your slider handling code here..
        //[/UserSliderCode_releaseShape]
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
void EnvPanel::updateCurve()
{
    envelopeCurve->setAttack(static_cast<float>(attackTime->getValue()));
    envelopeCurve->setDecay(static_cast<float>(decayTime->getValue()));
    envelopeCurve->setSustain(static_cast<float>(sustainLevel->getValue()));
    envelopeCurve->setRelease(static_cast<float>(releaseTime->getValue()));
    envelopeCurve->setAttackShape(static_cast<float>(attackShape->getValue()));
    envelopeCurve->setDecayShape(static_cast<float>(decayShape->getValue()));
    envelopeCurve->setReleaseShape(static_cast<float>(releaseShape->getValue()));
    repaint();
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="EnvPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="266"
                 initialHeight="252">
  <BACKGROUND backgroundColour="ffcbca63"/>
  <SLIDER name="Attack Time" id="3c32cde7173ddbe6" memberName="attackTime"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.0010000000000000000208" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Decay Time" id="84a4159bee0728d6" memberName="decayTime"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="69 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.0010000000000000000208" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Sustain" id="4bc867c016d7595f" memberName="sustainLevel"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="130 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-96" max="0" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="3"/>
  <SLIDER name="Release Time" id="c8bc1120a33101cd" memberName="releaseTime"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="195 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.0010000000000000000208" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Attack Shape" id="27ef7f1857e5d79b" memberName="attackShape"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="30 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.010000000000000000208" max="10"
          int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="0" textBoxHeight="0" skewFactor="0.2999999999999999889"/>
  <SLIDER name="Decay Shape" id="18adbff3650623b1" memberName="decayShape"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="91 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.010000000000000000208" max="10"
          int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="0" textBoxHeight="0" skewFactor="0.2999999999999999889"/>
  <SLIDER name="Release Shape" id="adb5f4f555fb76d1" memberName="releaseShape"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="216 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.010000000000000000208" max="10"
          int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="0" textBoxHeight="0" skewFactor="0.2999999999999999889"/>
  <SLIDER name="Vel to Env" id="595a20e744f094d5" memberName="keyVelToEnv1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 146 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="0" textBoxWidth="56"
          textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="Envelope Curve" id="c0212157938fff27" memberName="envelopeCurve"
                    virtualName="EnvelopeCurve" explicitFocusOrder="0" pos="117 146 128 64"
                    class="Component" params="params.envAttack.get(), params.envDecay.get(), params.envSustain.get(), params.envRelease.get(),  params.envAttackShape.get(), params.envDecayShape.get(), params.envReleaseShape.get()&#10;"/>
  <LABEL name="new label" id="79aa8d544da4882d" memberName="shapeLabel1"
         virtualName="" explicitFocusOrder="0" pos="137 108 51 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="shape" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Bauhaus 93"
         fontsize="20" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
