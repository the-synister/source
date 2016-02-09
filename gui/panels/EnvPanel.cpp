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
    sustainLevel1->setRange (-96, 0, 0);
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

    addAndMakeVisible (envelopeCurve1 = new EnvelopeCurve (params.envAttack1.get(), params.envDecay1.get(), params.envSustain1.get(), params.envRelease1.get(),  params.envAttackShape1.get(), params.envDecayShape1.get(), params.envReleaseShape1.get()
                                                           ));
    envelopeCurve1->setName ("Envelope Curve");

    addAndMakeVisible (shapeLabel1 = new Label ("new label",
                                                TRANS("shape")));
    shapeLabel1->setFont (Font ("Bauhaus 93", 20.00f, Font::plain));
    shapeLabel1->setJustificationType (Justification::centred);
    shapeLabel1->setEditable (false, false, false);
    shapeLabel1->setColour (Label::textColourId, Colours::white);
    shapeLabel1->setColour (TextEditor::textColourId, Colours::black);
    shapeLabel1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    registerSlider(attackTime1, &params.envAttack1, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(decayTime1, &params.envDecay1, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(sustainLevel1, &params.envSustain1, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(releaseTime1, &params.envRelease1, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(attackShape1, &params.envAttackShape1, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(decayShape1, &params.envDecayShape1, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(releaseShape1, &params.envReleaseShape1, std::bind(&EnvPanel::updateCurve, this));
    registerSlider(keyVelToEnv1, &params.keyVelToEnv1);
    attackShape1->setPopupDisplayEnabled(true, this);
    decayShape1->setPopupDisplayEnabled(true, this);
    releaseShape1->setPopupDisplayEnabled(true, this);

    // TODO: Delete

    //[/UserPreSize]

    setSize (267, 252);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

EnvPanel::~EnvPanel()
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
    envelopeCurve1 = nullptr;
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

    attackTime1->setBounds (8, 38, 64, 64);
    decayTime1->setBounds (69, 38, 64, 64);
    sustainLevel1->setBounds (130, 38, 64, 64);
    releaseTime1->setBounds (195, 38, 64, 64);
    attackShape1->setBounds (30, 111, 20, 20);
    decayShape1->setBounds (91, 111, 20, 20);
    releaseShape1->setBounds (216, 111, 20, 20);
    keyVelToEnv1->setBounds (8, 146, 64, 64);
    envelopeCurve1->setBounds (117, 146, 128, 64);
    shapeLabel1->setBounds (137, 108, 51, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void EnvPanel::sliderValueChanged (Slider* sliderThatWasMoved)
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
void EnvPanel::updateCurve()
{
    envelopeCurve1->setAttack(static_cast<float>(attackTime1->getValue()));
    envelopeCurve1->setDecay(static_cast<float>(decayTime1->getValue()));
    envelopeCurve1->setSustain(static_cast<float>(sustainLevel1->getValue()));
    envelopeCurve1->setRelease(static_cast<float>(releaseTime1->getValue()));
    envelopeCurve1->setAttackShape(static_cast<float>(attackShape1->getValue()));
    envelopeCurve1->setDecayShape(static_cast<float>(decayShape1->getValue()));
    envelopeCurve1->setReleaseShape(static_cast<float>(releaseShape1->getValue()));
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
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="800"
                 initialHeight="252">
  <BACKGROUND backgroundColour="ffcbca63"/>
  <SLIDER name="Attack Time" id="3c32cde7173ddbe6" memberName="attackTime1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.0010000000000000000208" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Decay Time" id="84a4159bee0728d6" memberName="decayTime1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="69 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.0010000000000000000208" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Sustain" id="4bc867c016d7595f" memberName="sustainLevel1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="130 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-96" max="0" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="3"/>
  <SLIDER name="Release Time" id="c8bc1120a33101cd" memberName="releaseTime1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="195 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.0010000000000000000208" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Attack Shape" id="27ef7f1857e5d79b" memberName="attackShape1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="30 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.010000000000000000208" max="10"
          int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="0" textBoxHeight="0" skewFactor="0.2999999999999999889"/>
  <SLIDER name="Decay Shape" id="18adbff3650623b1" memberName="decayShape1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="91 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.010000000000000000208" max="10"
          int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="0" textBoxHeight="0" skewFactor="0.2999999999999999889"/>
  <SLIDER name="Release Shape" id="adb5f4f555fb76d1" memberName="releaseShape1"
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
  <GENERICCOMPONENT name="Envelope Curve" id="c0212157938fff27" memberName="envelopeCurve1"
                    virtualName="EnvelopeCurve" explicitFocusOrder="0" pos="117 146 128 64"
                    class="Component" params="params.envAttack1.get(), params.envDecay1.get(), params.envSustain1.get(), params.envRelease1.get(),  params.envAttackShape1.get(), params.envDecayShape1.get(), params.envReleaseShape1.get()&#10;"/>
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
