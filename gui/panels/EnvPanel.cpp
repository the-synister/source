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

    addAndMakeVisible (attackTime2 = new MouseOverKnob ("Attack Time"));
    attackTime2->setRange (0.001, 5, 0);
    attackTime2->setSliderStyle (Slider::RotaryVerticalDrag);
    attackTime2->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    attackTime2->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    attackTime2->setColour (Slider::textBoxTextColourId, Colours::white);
    attackTime2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    attackTime2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    attackTime2->addListener (this);
    attackTime2->setSkewFactor (0.5);

    addAndMakeVisible (decayTime2 = new MouseOverKnob ("Decay Time"));
    decayTime2->setRange (0.001, 5, 0);
    decayTime2->setSliderStyle (Slider::RotaryVerticalDrag);
    decayTime2->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    decayTime2->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    decayTime2->setColour (Slider::textBoxTextColourId, Colours::white);
    decayTime2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    decayTime2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    decayTime2->addListener (this);
    decayTime2->setSkewFactor (0.5);

    addAndMakeVisible (sustainLevel2 = new MouseOverKnob ("Sustain"));
    sustainLevel2->setRange (-96, 0, 0);
    sustainLevel2->setSliderStyle (Slider::RotaryVerticalDrag);
    sustainLevel2->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    sustainLevel2->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    sustainLevel2->setColour (Slider::textBoxTextColourId, Colours::white);
    sustainLevel2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    sustainLevel2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    sustainLevel2->addListener (this);
    sustainLevel2->setSkewFactor (3);

    addAndMakeVisible (releaseTime2 = new MouseOverKnob ("Release Time"));
    releaseTime2->setRange (0.001, 5, 0);
    releaseTime2->setSliderStyle (Slider::RotaryVerticalDrag);
    releaseTime2->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    releaseTime2->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    releaseTime2->setColour (Slider::textBoxTextColourId, Colours::white);
    releaseTime2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    releaseTime2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    releaseTime2->addListener (this);
    releaseTime2->setSkewFactor (0.5);

    addAndMakeVisible (attackShape2 = new MouseOverKnob ("Attack Shape"));
    attackShape2->setRange (0.01, 10, 0);
    attackShape2->setSliderStyle (Slider::RotaryVerticalDrag);
    attackShape2->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    attackShape2->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    attackShape2->addListener (this);
    attackShape2->setSkewFactor (0.3);

    addAndMakeVisible (decayShape2 = new MouseOverKnob ("Decay Shape"));
    decayShape2->setRange (0.01, 10, 0);
    decayShape2->setSliderStyle (Slider::RotaryVerticalDrag);
    decayShape2->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    decayShape2->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    decayShape2->addListener (this);
    decayShape2->setSkewFactor (0.3);

    addAndMakeVisible (releaseShape2 = new MouseOverKnob ("Release Shape"));
    releaseShape2->setRange (0.01, 10, 0);
    releaseShape2->setSliderStyle (Slider::RotaryVerticalDrag);
    releaseShape2->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    releaseShape2->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    releaseShape2->addListener (this);
    releaseShape2->setSkewFactor (0.3);

    addAndMakeVisible (keyVelToEnv2 = new MouseOverKnob ("Vel to Env"));
    keyVelToEnv2->setRange (0, 1, 0);
    keyVelToEnv2->setSliderStyle (Slider::RotaryVerticalDrag);
    keyVelToEnv2->setTextBoxStyle (Slider::TextBoxBelow, true, 56, 20);
    keyVelToEnv2->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    keyVelToEnv2->setColour (Slider::textBoxTextColourId, Colours::white);
    keyVelToEnv2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    keyVelToEnv2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    keyVelToEnv2->addListener (this);

    addAndMakeVisible (envelopeCurve2 = new EnvelopeCurve (params.envAttack2.get(), params.envDecay2.get(), params.envSustain2.get(), params.envRelease2.get(),  params.envAttackShape2.get(), params.envDecayShape2.get(), params.envReleaseShape2.get()
                                                           ));
    envelopeCurve2->setName ("Envelope Curve");

    addAndMakeVisible (shapeLabel2 = new Label ("new label",
                                                TRANS("shape")));
    shapeLabel2->setFont (Font ("Bauhaus 93", 20.00f, Font::plain));
    shapeLabel2->setJustificationType (Justification::centred);
    shapeLabel2->setEditable (false, false, false);
    shapeLabel2->setColour (Label::textColourId, Colours::white);
    shapeLabel2->setColour (TextEditor::textColourId, Colours::black);
    shapeLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attackTime3 = new MouseOverKnob ("Attack Time"));
    attackTime3->setRange (0.001, 5, 0);
    attackTime3->setSliderStyle (Slider::RotaryVerticalDrag);
    attackTime3->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    attackTime3->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    attackTime3->setColour (Slider::textBoxTextColourId, Colours::white);
    attackTime3->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    attackTime3->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    attackTime3->addListener (this);
    attackTime3->setSkewFactor (0.5);

    addAndMakeVisible (decayTime3 = new MouseOverKnob ("Decay Time"));
    decayTime3->setRange (0.001, 5, 0);
    decayTime3->setSliderStyle (Slider::RotaryVerticalDrag);
    decayTime3->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    decayTime3->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    decayTime3->setColour (Slider::textBoxTextColourId, Colours::white);
    decayTime3->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    decayTime3->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    decayTime3->addListener (this);
    decayTime3->setSkewFactor (0.5);

    addAndMakeVisible (sustainLevel3 = new MouseOverKnob ("Sustain"));
    sustainLevel3->setRange (-96, 0, 0);
    sustainLevel3->setSliderStyle (Slider::RotaryVerticalDrag);
    sustainLevel3->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    sustainLevel3->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    sustainLevel3->setColour (Slider::textBoxTextColourId, Colours::white);
    sustainLevel3->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    sustainLevel3->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    sustainLevel3->addListener (this);
    sustainLevel3->setSkewFactor (3);

    addAndMakeVisible (releaseTime3 = new MouseOverKnob ("Release Time"));
    releaseTime3->setRange (0.001, 5, 0);
    releaseTime3->setSliderStyle (Slider::RotaryVerticalDrag);
    releaseTime3->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    releaseTime3->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    releaseTime3->setColour (Slider::textBoxTextColourId, Colours::white);
    releaseTime3->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    releaseTime3->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    releaseTime3->addListener (this);
    releaseTime3->setSkewFactor (0.5);

    addAndMakeVisible (attackShape3 = new MouseOverKnob ("Attack Shape"));
    attackShape3->setRange (0.01, 10, 0);
    attackShape3->setSliderStyle (Slider::RotaryVerticalDrag);
    attackShape3->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    attackShape3->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    attackShape3->addListener (this);
    attackShape3->setSkewFactor (0.3);

    addAndMakeVisible (decayShape3 = new MouseOverKnob ("Decay Shape"));
    decayShape3->setRange (0.01, 10, 0);
    decayShape3->setSliderStyle (Slider::RotaryVerticalDrag);
    decayShape3->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    decayShape3->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    decayShape3->addListener (this);
    decayShape3->setSkewFactor (0.3);

    addAndMakeVisible (releaseShape3 = new MouseOverKnob ("Release Shape"));
    releaseShape3->setRange (0.01, 10, 0);
    releaseShape3->setSliderStyle (Slider::RotaryVerticalDrag);
    releaseShape3->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    releaseShape3->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    releaseShape3->addListener (this);
    releaseShape3->setSkewFactor (0.3);

    addAndMakeVisible (keyVelToEnv3 = new MouseOverKnob ("Vel to Env"));
    keyVelToEnv3->setRange (0, 1, 0);
    keyVelToEnv3->setSliderStyle (Slider::RotaryVerticalDrag);
    keyVelToEnv3->setTextBoxStyle (Slider::TextBoxBelow, true, 56, 20);
    keyVelToEnv3->setColour (Slider::rotarySliderFillColourId, Colour (0xffbfa65a));
    keyVelToEnv3->setColour (Slider::textBoxTextColourId, Colours::white);
    keyVelToEnv3->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    keyVelToEnv3->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    keyVelToEnv3->addListener (this);

    addAndMakeVisible (envelopeCurve3 = new EnvelopeCurve (params.envAttack3.get(), params.envDecay3.get(), params.envSustain3.get(), params.envRelease3.get(),  params.envAttackShape3.get(), params.envDecayShape3.get(), params.envReleaseShape3.get()
                                                           ));
    envelopeCurve3->setName ("Envelope Curve");

    addAndMakeVisible (shapeLabel3 = new Label ("new label",
                                                TRANS("shape")));
    shapeLabel3->setFont (Font ("Bauhaus 93", 20.00f, Font::plain));
    shapeLabel3->setJustificationType (Justification::centred);
    shapeLabel3->setEditable (false, false, false);
    shapeLabel3->setColour (Label::textColourId, Colours::white);
    shapeLabel3->setColour (TextEditor::textColourId, Colours::black);
    shapeLabel3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    registerSlider(attackTime1, &params.envAttack1);
    registerSlider(decayTime1, &params.envDecay1);
    registerSlider(sustainLevel1, &params.envSustain1);
    registerSlider(releaseTime1, &params.envRelease1);
    registerSlider(attackShape1, &params.envAttackShape1);
    registerSlider(decayShape1, &params.envDecayShape1);
    registerSlider(releaseShape1, &params.envReleaseShape1);
    registerSlider(keyVelToEnv1, &params.keyVelToEnv1);
    attackShape1->setPopupDisplayEnabled(true, this);
    decayShape1->setPopupDisplayEnabled(true, this);
    releaseShape1->setPopupDisplayEnabled(true, this);

    registerSlider(attackTime2, &params.envAttack2);
    registerSlider(decayTime2, &params.envDecay2);
    registerSlider(sustainLevel2, &params.envSustain2);
    registerSlider(releaseTime2, &params.envRelease2);
    registerSlider(attackShape2, &params.envAttackShape2);
    registerSlider(decayShape2, &params.envDecayShape2);
    registerSlider(releaseShape2, &params.envReleaseShape2);
    registerSlider(keyVelToEnv2, &params.keyVelToEnv2);
    attackShape2->setPopupDisplayEnabled(true, this);
    decayShape2->setPopupDisplayEnabled(true, this);
    releaseShape2->setPopupDisplayEnabled(true, this);

    registerSlider(attackTime3, &params.envAttack3);
    registerSlider(decayTime3, &params.envDecay3);
    registerSlider(sustainLevel3, &params.envSustain3);
    registerSlider(releaseTime3, &params.envRelease3);
    registerSlider(attackShape3, &params.envAttackShape3);
    registerSlider(decayShape3, &params.envDecayShape3);
    registerSlider(releaseShape3, &params.envReleaseShape3);
    registerSlider(keyVelToEnv3, &params.keyVelToEnv3);
    attackShape3->setPopupDisplayEnabled(true, this);
    decayShape3->setPopupDisplayEnabled(true, this);
    releaseShape3->setPopupDisplayEnabled(true, this);
    //[/UserPreSize]

    setSize (800, 252);


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
    attackTime2 = nullptr;
    decayTime2 = nullptr;
    sustainLevel2 = nullptr;
    releaseTime2 = nullptr;
    attackShape2 = nullptr;
    decayShape2 = nullptr;
    releaseShape2 = nullptr;
    keyVelToEnv2 = nullptr;
    envelopeCurve2 = nullptr;
    shapeLabel2 = nullptr;
    attackTime3 = nullptr;
    decayTime3 = nullptr;
    sustainLevel3 = nullptr;
    releaseTime3 = nullptr;
    attackShape3 = nullptr;
    decayShape3 = nullptr;
    releaseShape3 = nullptr;
    keyVelToEnv3 = nullptr;
    envelopeCurve3 = nullptr;
    shapeLabel3 = nullptr;


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
        this->getWidth() / 3, this->getHeight(), 25.0f, 20.0f, 5.0f, 3.0f, Colour(0xffcbca63));
    drawGroupBorder(g, "env 1", this->getWidth() / 3, 0,
        this->getWidth() / 3, this->getHeight(), 25.0f, 20.0f, 5.0f, 3.0f, Colour(0xffcbca63));
    drawGroupBorder(g, "env 2", this->getWidth() / 3 * 2, 0,
        this->getWidth() / 3, this->getHeight(), 25.0f, 20.0f, 5.0f, 3.0f, Colour(0xffcbca63));

    int smallBorderHeight = 40;
    drawGroupBorder(g, "", 10, this->getHeight() / 2 - (smallBorderHeight - 12) / 2,
        this->getWidth() / 3 - 20, smallBorderHeight, 3.0f, 10.0f, 3.0f, 3.0f, Colour(0xffcbca63));
    drawGroupBorder(g, "", this->getWidth() / 3 + 10, this->getHeight() / 2 - (smallBorderHeight - 12) / 2,
        this->getWidth() / 3 - 20, smallBorderHeight, 3.0f, 10.0f, 3.0f, 3.0f, Colour(0xffcbca63));
    drawGroupBorder(g, "", this->getWidth() / 3 * 2 + 10, this->getHeight() / 2 - (smallBorderHeight - 12) / 2,
        this->getWidth() / 3 - 20, smallBorderHeight, 3.0f, 10.0f, 3.0f, 3.0f, Colour(0xffcbca63));

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
    attackTime2->setBounds (274, 38, 64, 64);
    decayTime2->setBounds (335, 38, 64, 64);
    sustainLevel2->setBounds (396, 38, 64, 64);
    releaseTime2->setBounds (461, 38, 64, 64);
    attackShape2->setBounds (296, 111, 20, 20);
    decayShape2->setBounds (357, 111, 20, 20);
    releaseShape2->setBounds (482, 111, 20, 20);
    keyVelToEnv2->setBounds (274, 146, 64, 64);
    envelopeCurve2->setBounds (383, 146, 128, 64);
    shapeLabel2->setBounds (403, 108, 51, 24);
    attackTime3->setBounds (543, 38, 64, 64);
    decayTime3->setBounds (604, 38, 64, 64);
    sustainLevel3->setBounds (665, 38, 64, 64);
    releaseTime3->setBounds (730, 38, 64, 64);
    attackShape3->setBounds (565, 111, 20, 20);
    decayShape3->setBounds (626, 111, 20, 20);
    releaseShape3->setBounds (751, 111, 20, 20);
    keyVelToEnv3->setBounds (543, 146, 64, 64);
    envelopeCurve3->setBounds (650, 146, 128, 64);
    shapeLabel3->setBounds (672, 108, 51, 24);
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
        envelopeCurve1->setAttack(static_cast<float>(attackTime1->getValue()));
        envelopeCurve1->repaint();
        //[/UserSliderCode_attackTime1]
    }
    else if (sliderThatWasMoved == decayTime1)
    {
        //[UserSliderCode_decayTime1] -- add your slider handling code here..
        envelopeCurve1->setDecay(static_cast<float>(decayTime1->getValue()));
        envelopeCurve1->repaint();
        //[/UserSliderCode_decayTime1]
    }
    else if (sliderThatWasMoved == sustainLevel1)
    {
        //[UserSliderCode_sustainLevel1] -- add your slider handling code here..
        envelopeCurve1->setSustain(static_cast<float>(sustainLevel1->getValue()));
        envelopeCurve1->repaint();
        //[/UserSliderCode_sustainLevel1]
    }
    else if (sliderThatWasMoved == releaseTime1)
    {
        //[UserSliderCode_releaseTime1] -- add your slider handling code here..
        envelopeCurve1->setRelease(static_cast<float>(releaseTime1->getValue()));
        envelopeCurve1->repaint();
        //[/UserSliderCode_releaseTime1]
    }
    else if (sliderThatWasMoved == attackShape1)
    {
        //[UserSliderCode_attackShape1] -- add your slider handling code here..
        envelopeCurve1->setAttackShape(static_cast<float>(attackShape1->getValue()));
        envelopeCurve1->repaint();
        //[/UserSliderCode_attackShape1]
    }
    else if (sliderThatWasMoved == decayShape1)
    {
        //[UserSliderCode_decayShape1] -- add your slider handling code here..
        envelopeCurve1->setDecayShape(static_cast<float>(decayShape1->getValue()));
        envelopeCurve1->repaint();
        //[/UserSliderCode_decayShape1]
    }
    else if (sliderThatWasMoved == releaseShape1)
    {
        //[UserSliderCode_releaseShape1] -- add your slider handling code here..
        envelopeCurve1->setReleaseShape(static_cast<float>(releaseShape1->getValue()));
        envelopeCurve1->repaint();
        //[/UserSliderCode_releaseShape1]
    }
    else if (sliderThatWasMoved == keyVelToEnv1)
    {
        //[UserSliderCode_keyVelToEnv1] -- add your slider handling code here..
        //[/UserSliderCode_keyVelToEnv1]
    }
    else if (sliderThatWasMoved == attackTime2)
    {
        //[UserSliderCode_attackTime2] -- add your slider handling code here..
        envelopeCurve2->setAttack(static_cast<float>(attackTime2->getValue()));
        envelopeCurve2->repaint();
        //[/UserSliderCode_attackTime2]
    }
    else if (sliderThatWasMoved == decayTime2)
    {
        //[UserSliderCode_decayTime2] -- add your slider handling code here..
        envelopeCurve2->setDecay(static_cast<float>(decayTime2->getValue()));
        envelopeCurve2->repaint();
        //[/UserSliderCode_decayTime2]
    }
    else if (sliderThatWasMoved == sustainLevel2)
    {
        //[UserSliderCode_sustainLevel2] -- add your slider handling code here..
        envelopeCurve2->setSustain(static_cast<float>(sustainLevel2->getValue()));
        envelopeCurve2->repaint();
        //[/UserSliderCode_sustainLevel2]
    }
    else if (sliderThatWasMoved == releaseTime2)
    {
        //[UserSliderCode_releaseTime2] -- add your slider handling code here..
        envelopeCurve2->setRelease(static_cast<float>(releaseTime2->getValue()));
        envelopeCurve2->repaint();
        //[/UserSliderCode_releaseTime2]
    }
    else if (sliderThatWasMoved == attackShape2)
    {
        //[UserSliderCode_attackShape2] -- add your slider handling code here..
        envelopeCurve2->setAttackShape(static_cast<float>(attackShape2->getValue()));
        envelopeCurve2->repaint();
        //[/UserSliderCode_attackShape2]
    }
    else if (sliderThatWasMoved == decayShape2)
    {
        //[UserSliderCode_decayShape2] -- add your slider handling code here..
        envelopeCurve2->setDecayShape(static_cast<float>(decayShape2->getValue()));
        envelopeCurve2->repaint();
        //[/UserSliderCode_decayShape2]
    }
    else if (sliderThatWasMoved == releaseShape2)
    {
        //[UserSliderCode_releaseShape2] -- add your slider handling code here..
        envelopeCurve2->setReleaseShape(static_cast<float>(releaseShape2->getValue()));
        envelopeCurve2->repaint();
        //[/UserSliderCode_releaseShape2]
    }
    else if (sliderThatWasMoved == keyVelToEnv2)
    {
        //[UserSliderCode_keyVelToEnv2] -- add your slider handling code here..
        //[/UserSliderCode_keyVelToEnv2]
    }
    else if (sliderThatWasMoved == attackTime3)
    {
        //[UserSliderCode_attackTime3] -- add your slider handling code here..
        envelopeCurve3->setAttack(static_cast<float>(attackTime3->getValue()));
        envelopeCurve3->repaint();
        //[/UserSliderCode_attackTime3]
    }
    else if (sliderThatWasMoved == decayTime3)
    {
        //[UserSliderCode_decayTime3] -- add your slider handling code here..
        envelopeCurve3->setDecay(static_cast<float>(decayTime3->getValue()));
        envelopeCurve3->repaint();
        //[/UserSliderCode_decayTime3]
    }
    else if (sliderThatWasMoved == sustainLevel3)
    {
        //[UserSliderCode_sustainLevel3] -- add your slider handling code here..
        envelopeCurve3->setSustain(static_cast<float>(sustainLevel3->getValue()));
        envelopeCurve3->repaint();
        //[/UserSliderCode_sustainLevel3]
    }
    else if (sliderThatWasMoved == releaseTime3)
    {
        //[UserSliderCode_releaseTime3] -- add your slider handling code here..
        envelopeCurve3->setRelease(static_cast<float>(releaseTime3->getValue()));
        envelopeCurve3->repaint();
        //[/UserSliderCode_releaseTime3]
    }
    else if (sliderThatWasMoved == attackShape3)
    {
        //[UserSliderCode_attackShape3] -- add your slider handling code here..
        envelopeCurve3->setAttackShape(static_cast<float>(attackShape3->getValue()));
        envelopeCurve3->repaint();
        //[/UserSliderCode_attackShape3]
    }
    else if (sliderThatWasMoved == decayShape3)
    {
        //[UserSliderCode_decayShape3] -- add your slider handling code here..
        envelopeCurve3->setDecayShape(static_cast<float>(decayShape3->getValue()));
        envelopeCurve3->repaint();
        //[/UserSliderCode_decayShape3]
    }
    else if (sliderThatWasMoved == releaseShape3)
    {
        //[UserSliderCode_releaseShape3] -- add your slider handling code here..
        envelopeCurve3->setReleaseShape(static_cast<float>(releaseShape3->getValue()));
        envelopeCurve3->repaint();
        //[/UserSliderCode_releaseShape3]
    }
    else if (sliderThatWasMoved == keyVelToEnv3)
    {
        //[UserSliderCode_keyVelToEnv3] -- add your slider handling code here..
        //[/UserSliderCode_keyVelToEnv3]
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

<JUCER_COMPONENT documentType="Component" className="EnvPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="800"
                 initialHeight="252">
  <BACKGROUND backgroundColour="ffcbca63"/>
  <SLIDER name="Attack Time" id="3c32cde7173ddbe6" memberName="attackTime1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.001" max="5" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Decay Time" id="84a4159bee0728d6" memberName="decayTime1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="69 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.001" max="5" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Sustain" id="4bc867c016d7595f" memberName="sustainLevel1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="130 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-96" max="0" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="3"/>
  <SLIDER name="Release Time" id="c8bc1120a33101cd" memberName="releaseTime1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="195 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.001" max="5" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Attack Shape" id="27ef7f1857e5d79b" memberName="attackShape1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="30 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.01" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="0.29999999999999999"/>
  <SLIDER name="Decay Shape" id="18adbff3650623b1" memberName="decayShape1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="91 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.01" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="0.29999999999999999"/>
  <SLIDER name="Release Shape" id="adb5f4f555fb76d1" memberName="releaseShape1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="216 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.01" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="0.29999999999999999"/>
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
  <SLIDER name="Attack Time" id="d82383e6dfac40a6" memberName="attackTime2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="274 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.001" max="5" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Decay Time" id="67dbc74fbb001d68" memberName="decayTime2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="335 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.001" max="5" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Sustain" id="88d6abc0d02d82ca" memberName="sustainLevel2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="396 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-96" max="0" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="3"/>
  <SLIDER name="Release Time" id="dbe18727523e8330" memberName="releaseTime2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="461 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.001" max="5" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Attack Shape" id="70e41380fa04f0f7" memberName="attackShape2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="296 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.01" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="0.29999999999999999"/>
  <SLIDER name="Decay Shape" id="4d9527d7e60da6b0" memberName="decayShape2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="357 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.01" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="0.29999999999999999"/>
  <SLIDER name="Release Shape" id="e7c0a50044b77170" memberName="releaseShape2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="482 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.01" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="0.29999999999999999"/>
  <SLIDER name="Vel to Env" id="da00a985059c1e0e" memberName="keyVelToEnv2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="274 146 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="0" textBoxWidth="56"
          textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="Envelope Curve" id="ad675fa3f267988f" memberName="envelopeCurve2"
                    virtualName="EnvelopeCurve" explicitFocusOrder="0" pos="383 146 128 64"
                    class="Component" params="params.envAttack2.get(), params.envDecay2.get(), params.envSustain2.get(), params.envRelease2.get(),  params.envAttackShape2.get(), params.envDecayShape2.get(), params.envReleaseShape2.get()&#10;"/>
  <LABEL name="new label" id="e5bc294f80e9c510" memberName="shapeLabel2"
         virtualName="" explicitFocusOrder="0" pos="403 108 51 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="shape" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Bauhaus 93"
         fontsize="20" bold="0" italic="0" justification="36"/>
  <SLIDER name="Attack Time" id="ea272f9f53fd8ee1" memberName="attackTime3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="543 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.001" max="5" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Decay Time" id="1681cfff464cf3ae" memberName="decayTime3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="604 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.001" max="5" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Sustain" id="dcb80fc468003013" memberName="sustainLevel3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="665 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-96" max="0" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="3"/>
  <SLIDER name="Release Time" id="3e58d33521665e55" memberName="releaseTime3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="730 38 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.001" max="5" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Attack Shape" id="b9292cbe5fc8e4e7" memberName="attackShape3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="565 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.01" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="0.29999999999999999"/>
  <SLIDER name="Decay Shape" id="6f4c19322855ba79" memberName="decayShape3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="626 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.01" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="0.29999999999999999"/>
  <SLIDER name="Release Shape" id="db7537581a79d7cc" memberName="releaseShape3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="751 111 20 20"
          rotarysliderfill="ffbfa65a" min="0.01" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="0.29999999999999999"/>
  <SLIDER name="Vel to Env" id="c44d940b08684afe" memberName="keyVelToEnv3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="543 146 64 64"
          rotarysliderfill="ffbfa65a" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="0" textBoxWidth="56"
          textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="Envelope Curve" id="8c10b97c649dec25" memberName="envelopeCurve3"
                    virtualName="EnvelopeCurve" explicitFocusOrder="0" pos="650 146 128 64"
                    class="Component" params="params.envAttack3.get(), params.envDecay3.get(), params.envSustain3.get(), params.envRelease3.get(),  params.envAttackShape3.get(), params.envDecayShape3.get(), params.envReleaseShape3.get()&#10;"/>
  <LABEL name="new label" id="14bc6752feb0b977" memberName="shapeLabel3"
         virtualName="" explicitFocusOrder="0" pos="672 108 51 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="shape" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Bauhaus 93"
         fontsize="20" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
