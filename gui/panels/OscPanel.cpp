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
OscPanel::OscPanel (SynthParams &p, int oscillatorNumber)
    : PanelBase(p), osc(p.osc[oscillatorNumber])
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (trngModSrc1 = new ModSourceBox ("TrngModSrc1"));
    trngModSrc1->setEditableText (false);
    trngModSrc1->setJustificationType (Justification::centred);
    trngModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    trngModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    trngModSrc1->addListener (this);

    addAndMakeVisible (widthModSrc1 = new ModSourceBox ("WidthModSrc1"));
    widthModSrc1->setEditableText (false);
    widthModSrc1->setJustificationType (Justification::centred);
    widthModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    widthModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    widthModSrc1->addListener (this);

    addAndMakeVisible (trngModSrc2 = new ModSourceBox ("TrngModSrc2"));
    trngModSrc2->setEditableText (false);
    trngModSrc2->setJustificationType (Justification::centred);
    trngModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    trngModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    trngModSrc2->addListener (this);

    addAndMakeVisible (widthModSrc2 = new ModSourceBox ("WidthModSrc2"));
    widthModSrc2->setEditableText (false);
    widthModSrc2->setJustificationType (Justification::centred);
    widthModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    widthModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    widthModSrc2->addListener (this);

    addAndMakeVisible (ftune1 = new MouseOverKnob ("fine tune 1"));
    ftune1->setRange (-100, 100, 0);
    ftune1->setSliderStyle (Slider::RotaryVerticalDrag);
    ftune1->setTextBoxStyle (Slider::TextBoxBelow, false, 58, 20);
    ftune1->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    ftune1->setColour (Slider::textBoxTextColourId, Colours::white);
    ftune1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    ftune1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    ftune1->addListener (this);

    addAndMakeVisible (pitchModAmount2 = new MouseOverKnob ("PitchModAmount2"));
    pitchModAmount2->setRange (0, 48, 0);
    pitchModAmount2->setSliderStyle (Slider::RotaryVerticalDrag);
    pitchModAmount2->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    pitchModAmount2->setColour (Slider::rotarySliderFillColourId, Colours::white);
    pitchModAmount2->setColour (Slider::textBoxTextColourId, Colours::white);
    pitchModAmount2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pitchModAmount2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pitchModAmount2->addListener (this);

    addAndMakeVisible (trngAmount = new MouseOverKnob ("Triangle Amount"));
    trngAmount->setRange (0, 1, 0);
    trngAmount->setSliderStyle (Slider::RotaryVerticalDrag);
    trngAmount->setTextBoxStyle (Slider::TextBoxBelow, false, 58, 20);
    trngAmount->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    trngAmount->setColour (Slider::textBoxTextColourId, Colours::white);
    trngAmount->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    trngAmount->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    trngAmount->addListener (this);

    addAndMakeVisible (pulsewidth = new MouseOverKnob ("Pulse Width"));
    pulsewidth->setRange (0.01, 0.99, 0);
    pulsewidth->setSliderStyle (Slider::RotaryVerticalDrag);
    pulsewidth->setTextBoxStyle (Slider::TextBoxBelow, false, 58, 20);
    pulsewidth->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pulsewidth->setColour (Slider::textBoxTextColourId, Colours::white);
    pulsewidth->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pulsewidth->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pulsewidth->addListener (this);

    addAndMakeVisible (pitchModAmount1 = new MouseOverKnob ("PitchModAmount1"));
    pitchModAmount1->setRange (0, 48, 0);
    pitchModAmount1->setSliderStyle (Slider::RotaryVerticalDrag);
    pitchModAmount1->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    pitchModAmount1->setColour (Slider::rotarySliderFillColourId, Colours::white);
    pitchModAmount1->setColour (Slider::textBoxTextColourId, Colours::white);
    pitchModAmount1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pitchModAmount1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pitchModAmount1->addListener (this);

    addAndMakeVisible (ctune1 = new MouseOverKnob ("coarse tune 1"));
    ctune1->setRange (-36, 36, 1);
    ctune1->setSliderStyle (Slider::RotaryVerticalDrag);
    ctune1->setTextBoxStyle (Slider::TextBoxBelow, false, 58, 20);
    ctune1->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    ctune1->setColour (Slider::textBoxTextColourId, Colours::white);
    ctune1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    ctune1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    ctune1->addListener (this);

    addAndMakeVisible (waveformVisual = new WaveformVisual (osc.waveForm.getStep(), osc.pulseWidth.get(), osc.trngAmount.get()));
    waveformVisual->setName ("Waveform Visual");

    addAndMakeVisible (waveformSwitch = new Slider ("Waveform Switch"));
    waveformSwitch->setRange (0, 2, 1);
    waveformSwitch->setSliderStyle (Slider::LinearVertical);
    waveformSwitch->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    waveformSwitch->setColour (Slider::thumbColourId, Colour (0xff6c788c));
    waveformSwitch->setColour (Slider::trackColourId, Colours::white);
    waveformSwitch->addListener (this);

    addAndMakeVisible (widthModAmount1 = new MouseOverKnob ("WidthModAmount1"));
    widthModAmount1->setRange (0, 1, 0);
    widthModAmount1->setSliderStyle (Slider::RotaryVerticalDrag);
    widthModAmount1->setTextBoxStyle (Slider::TextBoxBelow, false, 0, 0);
    widthModAmount1->setColour (Slider::rotarySliderFillColourId, Colours::white);
    widthModAmount1->setColour (Slider::textBoxTextColourId, Colours::white);
    widthModAmount1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    widthModAmount1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    widthModAmount1->addListener (this);

    addAndMakeVisible (pitchModSrc1 = new ModSourceBox ("oscPitchModSrc1"));
    pitchModSrc1->setEditableText (false);
    pitchModSrc1->setJustificationType (Justification::centred);
    pitchModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    pitchModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    pitchModSrc1->addListener (this);

    addAndMakeVisible (pitchModSrc2 = new ModSourceBox ("oscPitchModSrc2"));
    pitchModSrc2->setEditableText (false);
    pitchModSrc2->setJustificationType (Justification::centred);
    pitchModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    pitchModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    pitchModSrc2->addListener (this);

    addAndMakeVisible (gain = new MouseOverKnob ("gain knob"));
    gain->setRange (-96, 12, 0);
    gain->setSliderStyle (Slider::RotaryVerticalDrag);
    gain->setTextBoxStyle (Slider::TextBoxBelow, false, 58, 20);
    gain->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    gain->setColour (Slider::textBoxTextColourId, Colours::white);
    gain->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    gain->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    gain->addListener (this);

    addAndMakeVisible (pan = new MouseOverKnob ("pan knob"));
    pan->setRange (-100, 100, 0);
    pan->setSliderStyle (Slider::RotaryVerticalDrag);
    pan->setTextBoxStyle (Slider::TextBoxBelow, false, 58, 20);
    pan->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pan->setColour (Slider::textBoxTextColourId, Colours::white);
    pan->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pan->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pan->addListener (this);

    addAndMakeVisible (widthModAmount2 = new MouseOverKnob ("WidthModAmount2"));
    widthModAmount2->setRange (0, 1, 0);
    widthModAmount2->setSliderStyle (Slider::RotaryVerticalDrag);
    widthModAmount2->setTextBoxStyle (Slider::TextBoxBelow, false, 0, 0);
    widthModAmount2->setColour (Slider::rotarySliderFillColourId, Colours::white);
    widthModAmount2->setColour (Slider::textBoxTextColourId, Colours::white);
    widthModAmount2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    widthModAmount2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    widthModAmount2->addListener (this);

    addAndMakeVisible (gainModAmount2 = new MouseOverKnob ("GainModAmount2"));
    gainModAmount2->setRange (0, 96, 0);
    gainModAmount2->setSliderStyle (Slider::RotaryVerticalDrag);
    gainModAmount2->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    gainModAmount2->setColour (Slider::rotarySliderFillColourId, Colours::white);
    gainModAmount2->setColour (Slider::textBoxTextColourId, Colours::white);
    gainModAmount2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    gainModAmount2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    gainModAmount2->addListener (this);

    addAndMakeVisible (gainModAmount1 = new MouseOverKnob ("GainModAmount1"));
    gainModAmount1->setRange (0, 96, 0);
    gainModAmount1->setSliderStyle (Slider::RotaryVerticalDrag);
    gainModAmount1->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    gainModAmount1->setColour (Slider::rotarySliderFillColourId, Colours::white);
    gainModAmount1->setColour (Slider::textBoxTextColourId, Colours::white);
    gainModAmount1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    gainModAmount1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    gainModAmount1->addListener (this);

    addAndMakeVisible (gainModSrc1 = new ModSourceBox ("GainModSrc1"));
    gainModSrc1->setEditableText (false);
    gainModSrc1->setJustificationType (Justification::centred);
    gainModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    gainModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    gainModSrc1->addListener (this);

    addAndMakeVisible (gainModSrc2 = new ModSourceBox ("GainModSrc2"));
    gainModSrc2->setEditableText (false);
    gainModSrc2->setJustificationType (Justification::centred);
    gainModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    gainModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    gainModSrc2->addListener (this);

    addAndMakeVisible (panModAmount2 = new MouseOverKnob ("PanModAmount2"));
    panModAmount2->setRange (0, 200, 0);
    panModAmount2->setSliderStyle (Slider::RotaryVerticalDrag);
    panModAmount2->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    panModAmount2->setColour (Slider::rotarySliderFillColourId, Colours::white);
    panModAmount2->setColour (Slider::textBoxTextColourId, Colours::white);
    panModAmount2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    panModAmount2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    panModAmount2->addListener (this);

    addAndMakeVisible (panModAmount1 = new MouseOverKnob ("PanModAmount1"));
    panModAmount1->setRange (0, 200, 0);
    panModAmount1->setSliderStyle (Slider::RotaryVerticalDrag);
    panModAmount1->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    panModAmount1->setColour (Slider::rotarySliderFillColourId, Colours::white);
    panModAmount1->setColour (Slider::textBoxTextColourId, Colours::white);
    panModAmount1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    panModAmount1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    panModAmount1->addListener (this);

    addAndMakeVisible (panModSrc1 = new ModSourceBox ("PanModSrc1"));
    panModSrc1->setEditableText (false);
    panModSrc1->setJustificationType (Justification::centred);
    panModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    panModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    panModSrc1->addListener (this);

    addAndMakeVisible (panModSrc2 = new ModSourceBox ("PanModSrc2"));
    panModSrc2->setEditableText (false);
    panModSrc2->setJustificationType (Justification::centred);
    panModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    panModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    panModSrc2->addListener (this);

    addAndMakeVisible (onOffSwitch = new Slider ("switch"));
    onOffSwitch->setRange (0, 1, 1);
    onOffSwitch->setSliderStyle (Slider::LinearHorizontal);
    onOffSwitch->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    onOffSwitch->setColour (Slider::thumbColourId, Colour (0xffdadada));
    onOffSwitch->setColour (Slider::trackColourId, Colour (0xff666666));
    onOffSwitch->setColour (Slider::rotarySliderFillColourId, Colours::white);
    onOffSwitch->setColour (Slider::rotarySliderOutlineColourId, Colour (0xfff20000));
    onOffSwitch->setColour (Slider::textBoxBackgroundColourId, Colour (0xfffff4f4));
    onOffSwitch->addListener (this);


    //[UserPreSize]
    registerSlider(gain, &osc.vol);
    registerSlider(pan, &osc.panDir);
    registerSlider(ftune1, &osc.fine);
    registerSlider(ctune1, &osc.coarse);
    registerSlider(waveformSwitch, &osc.waveForm, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(trngAmount, &osc.trngAmount, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(pulsewidth, &osc.pulseWidth, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(pitchModAmount1, &osc.pitchModAmount1);
    registerSlider(pitchModAmount2, &osc.pitchModAmount2);
    registerSlider(widthModAmount1, &osc.shapeModAmount1);
    registerSlider(widthModAmount2, &osc.shapeModAmount2);
    registerSlider(panModAmount1, &osc.panModAmount1);
    registerSlider(panModAmount2, &osc.panModAmount2);
    registerSlider(gainModAmount1, &osc.gainModAmount1);
    registerSlider(gainModAmount2, &osc.gainModAmount2);

    registerSlider(onOffSwitch, &osc.oscActivation, std::bind(&OscPanel::onOffSwitchChanged, this));
    
    // fill and register mod selection boxes
    fillModsourceBox(pitchModSrc1, false);
    fillModsourceBox(pitchModSrc2, false);
    registerCombobox(pitchModSrc1, &osc.pitchModSrc1, {ctune1, nullptr, nullptr}, std::bind(&OscPanel::updateModAmountKnobs, this));
    registerCombobox(pitchModSrc2, &osc.pitchModSrc2, {ctune1, nullptr, nullptr}, std::bind(&OscPanel::updateModAmountKnobs, this));

    fillModsourceBox(widthModSrc1, false);
    fillModsourceBox(widthModSrc2, false);
    fillModsourceBox(trngModSrc1, false);
    fillModsourceBox(trngModSrc2, false);
    registerCombobox(widthModSrc1, &osc.shapeModSrc1, {pulsewidth, trngAmount, nullptr}, std::bind(&OscPanel::updateModAmountKnobs, this));
    registerCombobox(widthModSrc2, &osc.shapeModSrc2, {pulsewidth, trngAmount, nullptr}, std::bind(&OscPanel::updateModAmountKnobs, this));
    registerCombobox(trngModSrc1, &osc.shapeModSrc1, {trngAmount, pulsewidth, nullptr}, std::bind(&OscPanel::updateModAmountKnobs, this));
    registerCombobox(trngModSrc2, &osc.shapeModSrc2, {trngAmount, pulsewidth, nullptr}, std::bind(&OscPanel::updateModAmountKnobs, this));

    fillModsourceBox(panModSrc1, false);
    fillModsourceBox(panModSrc2, false);
    registerCombobox(panModSrc1, &osc.panModSrc1, {pan, nullptr, nullptr}, std::bind(&OscPanel::updateModAmountKnobs, this));
    registerCombobox(panModSrc2, &osc.panModSrc2, {pan, nullptr, nullptr}, std::bind(&OscPanel::updateModAmountKnobs, this));

    fillModsourceBox(gainModSrc1, false);
    fillModsourceBox(gainModSrc2, false);
    registerCombobox(gainModSrc1, &osc.gainModSrc1, {gain, nullptr, nullptr}, std::bind(&OscPanel::updateModAmountKnobs, this));
    registerCombobox(gainModSrc2, &osc.gainModSrc2, {gain, nullptr, nullptr}, std::bind(&OscPanel::updateModAmountKnobs, this));

    registerSaturnSource(ctune1, pitchModAmount1, &osc.pitchModSrc1, &osc.pitchModAmount1, 1);
    registerSaturnSource(ctune1, pitchModAmount2, &osc.pitchModSrc2, &osc.pitchModAmount2, 2);
    registerSaturnSource(gain, gainModAmount1, &osc.gainModSrc1, &osc.gainModAmount1, 1);
    registerSaturnSource(gain, gainModAmount2, &osc.gainModSrc2, &osc.gainModAmount2, 2);
    registerSaturnSource(pan, panModAmount1, &osc.panModSrc1, &osc.panModAmount1, 1);
    registerSaturnSource(pan, panModAmount2, &osc.panModSrc2, &osc.panModAmount2, 2);
    registerSaturnSource(pulsewidth, widthModAmount1, &osc.shapeModSrc1, &osc.shapeModAmount1, 1);
    registerSaturnSource(pulsewidth, widthModAmount2, &osc.shapeModSrc2, &osc.shapeModAmount2, 2);
    registerSaturnSource(trngAmount, widthModAmount1, &osc.shapeModSrc1, &osc.shapeModAmount1, 1);
    registerSaturnSource(trngAmount, widthModAmount2, &osc.shapeModSrc2, &osc.shapeModAmount2, 2);
    
    onOffSwitchChanged();
    //[/UserPreSize]

    setSize (267, 272);


    //[Constructor] You can add your own custom stuff here..
    waveforms = ImageCache::getFromMemory(BinaryData::oscWaveForms_png, BinaryData::oscWaveForms_pngSize);
    gain->setSkewFactorFromMidPoint(-6.0);

    pitchModAmount1->setAlwaysOnTop(true);
    pitchModAmount2->setAlwaysOnTop(true);
    gainModAmount1->setAlwaysOnTop(true);
    gainModAmount2->setAlwaysOnTop(true);
    widthModAmount1->setAlwaysOnTop(true);
    widthModAmount2->setAlwaysOnTop(true);
    panModAmount1->setAlwaysOnTop(true);
    panModAmount2->setAlwaysOnTop(true);
    //[/Constructor]
}

OscPanel::~OscPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    trngModSrc1 = nullptr;
    widthModSrc1 = nullptr;
    trngModSrc2 = nullptr;
    widthModSrc2 = nullptr;
    ftune1 = nullptr;
    pitchModAmount2 = nullptr;
    trngAmount = nullptr;
    pulsewidth = nullptr;
    pitchModAmount1 = nullptr;
    ctune1 = nullptr;
    waveformVisual = nullptr;
    waveformSwitch = nullptr;
    widthModAmount1 = nullptr;
    pitchModSrc1 = nullptr;
    pitchModSrc2 = nullptr;
    gain = nullptr;
    pan = nullptr;
    widthModAmount2 = nullptr;
    gainModAmount2 = nullptr;
    gainModAmount1 = nullptr;
    gainModSrc1 = nullptr;
    gainModSrc2 = nullptr;
    panModAmount2 = nullptr;
    panModAmount1 = nullptr;
    panModSrc1 = nullptr;
    panModSrc2 = nullptr;
    onOffSwitch = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void OscPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff6c788c));

    //[UserPaint] Add your own custom painting code here..
    drawGroupBorder(g, osc.name, 0, 0,
                    this->getWidth(), this->getHeight() - 22, 25.0f, 24.0f, 4.0f, 3.0f, 40,SynthParams::oscColour);

    // draw waveform symbols
    drawWaves(g, waveformSwitch);
    //[/UserPaint]
}

void OscPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    int cID = ComboBox::ColourIds::backgroundColourId;
    pitchModSrc1->setColour(cID, pitchModSrc1->findColour(cID).withAlpha(osc.pitchModSrc1.getStep() == eModSource::eNone ? 0.5f : 1.0f));
    pitchModSrc2->setColour(cID, pitchModSrc2->findColour(cID).withAlpha(osc.pitchModSrc2.getStep() == eModSource::eNone ? 0.5f : 1.0f));

    widthModSrc1->setColour(cID, widthModSrc1->findColour(cID).withAlpha(osc.shapeModSrc1.getStep() == eModSource::eNone ? 0.5f : 1.0f));
    widthModSrc2->setColour(cID, widthModSrc2->findColour(cID).withAlpha(osc.shapeModSrc2.getStep() == eModSource::eNone ? 0.5f : 1.0f));
    trngModSrc1->setColour(cID, trngModSrc1->findColour(cID).withAlpha(osc.shapeModSrc1.getStep() == eModSource::eNone ? 0.5f : 1.0f));
    trngModSrc2->setColour(cID, trngModSrc2->findColour(cID).withAlpha(osc.shapeModSrc2.getStep() == eModSource::eNone ? 0.5f : 1.0f));

    panModSrc1->setColour(cID, panModSrc1->findColour(cID).withAlpha(osc.panModSrc1.getStep() == eModSource::eNone ? 0.5f : 1.0f));
    panModSrc2->setColour(cID, panModSrc2->findColour(cID).withAlpha(osc.panModSrc2.getStep() == eModSource::eNone ? 0.5f : 1.0f));

    gainModSrc1->setColour(cID, gainModSrc1->findColour(cID).withAlpha(osc.gainModSrc1.getStep() == eModSource::eNone ? 0.5f : 1.0f));
    gainModSrc2->setColour(cID, gainModSrc2->findColour(cID).withAlpha(osc.gainModSrc2.getStep() == eModSource::eNone ? 0.5f : 1.0f));
    //[/UserPreResize]

    trngModSrc1->setBounds (207, 103, 40, 18);
    widthModSrc1->setBounds (207, 103, 40, 18);
    trngModSrc2->setBounds (207, 127, 40, 18);
    widthModSrc2->setBounds (207, 127, 40, 18);
    ftune1->setBounds (8, 170, 64, 64);
    pitchModAmount2->setBounds (65, 127, 18, 18);
    trngAmount->setBounds (127, 101, 64, 64);
    pulsewidth->setBounds (127, 101, 64, 64);
    pitchModAmount1->setBounds (65, 103, 18, 18);
    ctune1->setBounds (8, 101, 64, 64);
    waveformVisual->setBounds (69, 163, 123, 72);
    waveformSwitch->setBounds (195, 175, 40, 44);
    widthModAmount1->setBounds (184, 103, 18, 18);
    pitchModSrc1->setBounds (88, 103, 40, 18);
    pitchModSrc2->setBounds (88, 127, 40, 18);
    gain->setBounds (8, 36, 64, 64);
    pan->setBounds (127, 36, 64, 64);
    widthModAmount2->setBounds (184, 127, 18, 18);
    gainModAmount2->setBounds (65, 64, 18, 18);
    gainModAmount1->setBounds (65, 40, 18, 18);
    gainModSrc1->setBounds (88, 40, 40, 18);
    gainModSrc2->setBounds (88, 64, 40, 18);
    panModAmount2->setBounds (184, 64, 18, 18);
    panModAmount1->setBounds (184, 40, 18, 18);
    panModSrc1->setBounds (207, 40, 40, 18);
    panModSrc2->setBounds (207, 64, 40, 18);
    onOffSwitch->setBounds (14, 2, 40, 30);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void OscPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    handleCombobox(comboBoxThatHasChanged);
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == trngModSrc1)
    {
        //[UserComboBoxCode_trngModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_trngModSrc1]
    }
    else if (comboBoxThatHasChanged == widthModSrc1)
    {
        //[UserComboBoxCode_widthModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_widthModSrc1]
    }
    else if (comboBoxThatHasChanged == trngModSrc2)
    {
        //[UserComboBoxCode_trngModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_trngModSrc2]
    }
    else if (comboBoxThatHasChanged == widthModSrc2)
    {
        //[UserComboBoxCode_widthModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_widthModSrc2]
    }
    else if (comboBoxThatHasChanged == pitchModSrc1)
    {
        //[UserComboBoxCode_pitchModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_pitchModSrc1]
    }
    else if (comboBoxThatHasChanged == pitchModSrc2)
    {
        //[UserComboBoxCode_pitchModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_pitchModSrc2]
    }
    else if (comboBoxThatHasChanged == gainModSrc1)
    {
        //[UserComboBoxCode_gainModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_gainModSrc1]
    }
    else if (comboBoxThatHasChanged == gainModSrc2)
    {
        //[UserComboBoxCode_gainModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_gainModSrc2]
    }
    else if (comboBoxThatHasChanged == panModSrc1)
    {
        //[UserComboBoxCode_panModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_panModSrc1]
    }
    else if (comboBoxThatHasChanged == panModSrc2)
    {
        //[UserComboBoxCode_panModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_panModSrc2]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
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
    else if (sliderThatWasMoved == pitchModAmount2)
    {
        //[UserSliderCode_pitchModAmount2] -- add your slider handling code here..
        //[/UserSliderCode_pitchModAmount2]
    }
    else if (sliderThatWasMoved == trngAmount)
    {
        //[UserSliderCode_trngAmount] -- add your slider handling code here..
        //[/UserSliderCode_trngAmount]
    }
    else if (sliderThatWasMoved == pulsewidth)
    {
        //[UserSliderCode_pulsewidth] -- add your slider handling code here..
        //[/UserSliderCode_pulsewidth]
    }
    else if (sliderThatWasMoved == pitchModAmount1)
    {
        //[UserSliderCode_pitchModAmount1] -- add your slider handling code here..
        //[/UserSliderCode_pitchModAmount1]
    }
    else if (sliderThatWasMoved == ctune1)
    {
        //[UserSliderCode_ctune1] -- add your slider handling code here..
        //[/UserSliderCode_ctune1]
    }
    else if (sliderThatWasMoved == waveformSwitch)
    {
        //[UserSliderCode_waveformSwitch] -- add your slider handling code here..
        //[/UserSliderCode_waveformSwitch]
    }
    else if (sliderThatWasMoved == widthModAmount1)
    {
        //[UserSliderCode_widthModAmount1] -- add your slider handling code here..
        //[/UserSliderCode_widthModAmount1]
    }
    else if (sliderThatWasMoved == gain)
    {
        //[UserSliderCode_gain] -- add your slider handling code here..
        //[/UserSliderCode_gain]
    }
    else if (sliderThatWasMoved == pan)
    {
        //[UserSliderCode_pan] -- add your slider handling code here..
        //[/UserSliderCode_pan]
    }
    else if (sliderThatWasMoved == widthModAmount2)
    {
        //[UserSliderCode_widthModAmount2] -- add your slider handling code here..
        //[/UserSliderCode_widthModAmount2]
    }
    else if (sliderThatWasMoved == gainModAmount2)
    {
        //[UserSliderCode_gainModAmount2] -- add your slider handling code here..
        //[/UserSliderCode_gainModAmount2]
    }
    else if (sliderThatWasMoved == gainModAmount1)
    {
        //[UserSliderCode_gainModAmount1] -- add your slider handling code here..
        //[/UserSliderCode_gainModAmount1]
    }
    else if (sliderThatWasMoved == panModAmount2)
    {
        //[UserSliderCode_panModAmount2] -- add your slider handling code here..
        //[/UserSliderCode_panModAmount2]
    }
    else if (sliderThatWasMoved == panModAmount1)
    {
        //[UserSliderCode_panModAmount1] -- add your slider handling code here..
        //[/UserSliderCode_panModAmount1]
    }
    else if (sliderThatWasMoved == onOffSwitch)
    {
        //[UserSliderCode_onOffSwitch] -- add your slider handling code here..
        //[/UserSliderCode_onOffSwitch]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void OscPanel::onOffSwitchChanged()
{

    ftune1->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
    trngAmount->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.waveForm.getStep() == eOscWaves::eOscSaw);
    pulsewidth->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.waveForm.getStep() == eOscWaves::eOscSquare);
    ctune1->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
    waveformVisual->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
    waveformSwitch->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
    gain->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
    pan->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
    
    pitchModAmount1->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.pitchModSrc1.getStep() != eModSource::eNone);
    pitchModAmount2->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.pitchModSrc2.getStep() != eModSource::eNone);
    widthModAmount1->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.shapeModSrc1.getStep() != eModSource::eNone);
    widthModAmount2->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.shapeModSrc2.getStep() != eModSource::eNone);
    gainModAmount1->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.gainModSrc1.getStep() != eModSource::eNone);
    gainModAmount2->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.gainModSrc2.getStep() != eModSource::eNone);
    panModAmount1->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.panModSrc1.getStep() != eModSource::eNone);
    panModAmount2->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.panModSrc2.getStep() != eModSource::eNone);
    
    panModSrc1->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
    panModSrc2->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
    widthModSrc1->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.waveForm.getStep() == eOscWaves::eOscSquare);
    widthModSrc2->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.waveForm.getStep() == eOscWaves::eOscSquare);
    trngModSrc1->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.waveForm.getStep() == eOscWaves::eOscSaw);
    trngModSrc2->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1) && osc.waveForm.getStep() == eOscWaves::eOscSaw);
    gainModSrc1->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
    gainModSrc2->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
    pitchModSrc1->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
    pitchModSrc2->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
    
    onOffSwitch->setColour(Slider::trackColourId, ((onOffSwitch->getValue() == 1) ? SynthParams::oscColour : SynthParams::onOffSwitchDisabled));

}

void OscPanel::updateWFShapeControls()
{
    eOscWaves eWaveformKey = osc.waveForm.getStep();
    
    pulsewidth->setVisible(eWaveformKey == eOscWaves::eOscSquare);
    pulsewidth->setEnabled(eWaveformKey == eOscWaves::eOscSquare);
    widthModSrc1->setVisible(eWaveformKey == eOscWaves::eOscSquare);
    widthModSrc2->setVisible(eWaveformKey == eOscWaves::eOscSquare);
    
    trngAmount->setVisible(eWaveformKey != eOscWaves::eOscSquare);
    trngAmount->setEnabled(eWaveformKey == eOscWaves::eOscSaw);
    
    trngModSrc1->setVisible(eWaveformKey != eOscWaves::eOscSquare);
    trngModSrc1->setEnabled(eWaveformKey == eOscWaves::eOscSaw);
    trngModSrc2->setVisible(eWaveformKey != eOscWaves::eOscSquare);
    trngModSrc2->setEnabled(eWaveformKey == eOscWaves::eOscSaw);

    widthModAmount1->setEnabled(osc.shapeModSrc1.getStep() != eModSource::eNone && eWaveformKey != eOscWaves::eOscNoise);
    widthModAmount2->setEnabled(osc.shapeModSrc2.getStep() != eModSource::eNone && eWaveformKey != eOscWaves::eOscNoise);

    // sync boxes of shapeModSrc
    trngModSrc1->setSelectedId(static_cast<int>(osc.shapeModSrc1.getStep()) + COMBO_OFS);
    trngModSrc2->setSelectedId(static_cast<int>(osc.shapeModSrc2.getStep()) + COMBO_OFS);
    widthModSrc1->setSelectedId(static_cast<int>(osc.shapeModSrc1.getStep()) + COMBO_OFS);
    widthModSrc2->setSelectedId(static_cast<int>(osc.shapeModSrc2.getStep()) + COMBO_OFS);

    // update and repaint waveform
    waveformVisual->setWaveformKey(eWaveformKey);
    waveformVisual->setPulseWidth(static_cast<float>(pulsewidth->getValue()));
    waveformVisual->setTrngAmount(static_cast<float>(trngAmount->getValue()));
}

void OscPanel::updateModAmountKnobs()
{
    gainModAmount1->setEnabled(osc.gainModSrc1.getStep() != eModSource::eNone);
    gainModAmount1->showBipolarValues(isUnipolar(osc.gainModSrc1.getStep()));
    gainModAmount2->setEnabled(osc.gainModSrc2.getStep() != eModSource::eNone);
    gainModAmount2->showBipolarValues(isUnipolar(osc.gainModSrc2.getStep()));

    panModAmount1->setEnabled(osc.panModSrc1.getStep() != eModSource::eNone);
    panModAmount1->showBipolarValues(isUnipolar(osc.panModSrc1.getStep()));
    panModAmount2->setEnabled(osc.panModSrc2.getStep() != eModSource::eNone);
    panModAmount2->showBipolarValues(isUnipolar(osc.panModSrc2.getStep()));

    pitchModAmount1->setEnabled(osc.pitchModSrc1.getStep() != eModSource::eNone);
    pitchModAmount1->showBipolarValues(isUnipolar(osc.pitchModSrc1.getStep()));
    pitchModAmount2->setEnabled(osc.pitchModSrc2.getStep() != eModSource::eNone);
    pitchModAmount2->showBipolarValues(isUnipolar(osc.pitchModSrc2.getStep()));

    widthModAmount1->setEnabled(osc.shapeModSrc1.getStep() != eModSource::eNone && osc.waveForm.getStep() != eOscWaves::eOscNoise);
    widthModAmount1->showBipolarValues(isUnipolar(osc.shapeModSrc1.getStep()));
    widthModAmount2->setEnabled(osc.shapeModSrc2.getStep() != eModSource::eNone && osc.waveForm.getStep() != eOscWaves::eOscNoise);
    widthModAmount2->showBipolarValues(isUnipolar(osc.shapeModSrc2.getStep()));
}

void OscPanel::drawWaves(Graphics& g, ScopedPointer<Slider>& _waveformSwitch)
{
    int centerX = _waveformSwitch->getX() + _waveformSwitch->getWidth() / 2;
    int centerY = _waveformSwitch->getY() + _waveformSwitch->getHeight() / 2;

    g.drawImageWithin(waveforms.getClippedImage(noiseFrame), centerX - 15, _waveformSwitch->getY() - 22, 30, 20, RectanglePlacement::centred);
    g.drawImageWithin(waveforms.getClippedImage(sawFrame), _waveformSwitch->getX() + _waveformSwitch->getWidth() / 2 + 12, centerY - 10, 30, 20, RectanglePlacement::centred);
    g.drawImageWithin(waveforms.getClippedImage(squareFrame), centerX - 15, _waveformSwitch->getY() + _waveformSwitch->getHeight() - 1, 30, 20, RectanglePlacement::centred);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="OscPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p, int oscillatorNumber"
                 variableInitialisers="PanelBase(p), osc(p.osc[oscillatorNumber])"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="267" initialHeight="272">
  <BACKGROUND backgroundColour="ff6c788c"/>
  <COMBOBOX name="TrngModSrc1" id="45d3fe360f9a8e44" memberName="trngModSrc1"
            virtualName="ModSourceBox" explicitFocusOrder="0" pos="207 103 40 18"
            editable="0" layout="36" items="" textWhenNonSelected="No Mod"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="WidthModSrc1" id="928cd04bb7b23ab9" memberName="widthModSrc1"
            virtualName="ModSourceBox" explicitFocusOrder="0" pos="207 103 40 18"
            editable="0" layout="36" items="" textWhenNonSelected="No Mod"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="TrngModSrc2" id="7e124307f2c9f46b" memberName="trngModSrc2"
            virtualName="ModSourceBox" explicitFocusOrder="0" pos="207 127 40 18"
            editable="0" layout="36" items="" textWhenNonSelected="No Mod"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="WidthModSrc2" id="455e48a25414a454" memberName="widthModSrc2"
            virtualName="ModSourceBox" explicitFocusOrder="0" pos="207 127 40 18"
            editable="0" layout="36" items="" textWhenNonSelected="No Mod"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="fine tune 1" id="3c32cde7173ddbe6" memberName="ftune1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 170 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-100" max="100" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="58"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="PitchModAmount2" id="523b9024be39c1b" memberName="pitchModAmount2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="65 127 18 18"
          rotarysliderfill="ffffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="48" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="1"/>
  <SLIDER name="Triangle Amount" id="d81a0f8c69078b3c" memberName="trngAmount"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="127 101 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="58"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Pulse Width" id="96badb5ea7640431" memberName="pulsewidth"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="127 101 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.01" max="0.98999999999999999"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="58" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="PitchModAmount1" id="29275125e377aaa" memberName="pitchModAmount1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="65 103 18 18"
          rotarysliderfill="ffffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="48" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="1"/>
  <SLIDER name="coarse tune 1" id="52a6628a22cee304" memberName="ctune1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 101 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-36" max="36" int="1" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="58"
          textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="Waveform Visual" id="dc40e7918cb34428" memberName="waveformVisual"
                    virtualName="WaveformVisual" explicitFocusOrder="0" pos="69 163 123 72"
                    class="Component" params="osc.waveForm.getStep(), osc.pulseWidth.get(), osc.trngAmount.get()"/>
  <SLIDER name="Waveform Switch" id="df460155fcb1ed38" memberName="waveformSwitch"
          virtualName="" explicitFocusOrder="0" pos="195 175 40 44" thumbcol="ff6c788c"
          trackcol="ffffffff" min="0" max="2" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="WidthModAmount1" id="ea500ea6791045c2" memberName="widthModAmount1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="184 103 18 18"
          rotarysliderfill="ffffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="0"
          textBoxHeight="0" skewFactor="1"/>
  <COMBOBOX name="oscPitchModSrc1" id="4e9e1857f51fc7f4" memberName="pitchModSrc1"
            virtualName="ModSourceBox" explicitFocusOrder="0" pos="88 103 40 18"
            editable="0" layout="36" items="" textWhenNonSelected="No Mod"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="oscPitchModSrc2" id="58dc64c4649ad205" memberName="pitchModSrc2"
            virtualName="ModSourceBox" explicitFocusOrder="0" pos="88 127 40 18"
            editable="0" layout="36" items="" textWhenNonSelected="No Mod"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="gain knob" id="da94529625060498" memberName="gain" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="8 36 64 64" rotarysliderfill="ff6c788c"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="ffffff"
          min="-96" max="12" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="58" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="pan knob" id="dd33a09584f4c2ff" memberName="pan" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="127 36 64 64" rotarysliderfill="ff6c788c"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="ffffff"
          min="-100" max="100" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="58" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="WidthModAmount2" id="ae5c9ce50e2de7e1" memberName="widthModAmount2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="184 127 18 18"
          rotarysliderfill="ffffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="0"
          textBoxHeight="0" skewFactor="1"/>
  <SLIDER name="GainModAmount2" id="93ff4adc6f243ee3" memberName="gainModAmount2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="65 64 18 18"
          rotarysliderfill="ffffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="96" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="1"/>
  <SLIDER name="GainModAmount1" id="6604fe537dac0d1e" memberName="gainModAmount1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="65 40 18 18"
          rotarysliderfill="ffffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="96" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="1"/>
  <COMBOBOX name="GainModSrc1" id="66da971c3fe90ee6" memberName="gainModSrc1"
            virtualName="ModSourceBox" explicitFocusOrder="0" pos="88 40 40 18"
            editable="0" layout="36" items="" textWhenNonSelected="No Mod"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="GainModSrc2" id="7fad32464e7c032" memberName="gainModSrc2"
            virtualName="ModSourceBox" explicitFocusOrder="0" pos="88 64 40 18"
            editable="0" layout="36" items="" textWhenNonSelected="No Mod"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="PanModAmount2" id="373f8321765bf923" memberName="panModAmount2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="184 64 18 18"
          rotarysliderfill="ffffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="200" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="1"/>
  <SLIDER name="PanModAmount1" id="3d939a1eb44dbbb0" memberName="panModAmount1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="184 40 18 18"
          rotarysliderfill="ffffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="200" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="1"/>
  <COMBOBOX name="PanModSrc1" id="9c99fb5c7e8aa9ca" memberName="panModSrc1"
            virtualName="ModSourceBox" explicitFocusOrder="0" pos="207 40 40 18"
            editable="0" layout="36" items="" textWhenNonSelected="No Mod"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="PanModSrc2" id="48da71ae7732f1b" memberName="panModSrc2"
            virtualName="ModSourceBox" explicitFocusOrder="0" pos="207 64 40 18"
            editable="0" layout="36" items="" textWhenNonSelected="No Mod"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="switch" id="f46e9c55275d8f7b" memberName="onOffSwitch"
          virtualName="" explicitFocusOrder="0" pos="14 2 40 30" thumbcol="ffdadada"
          trackcol="ff666666" rotarysliderfill="ffffffff" rotaryslideroutline="fff20000"
          textboxbkgd="fffff4f4" min="0" max="1" int="1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
