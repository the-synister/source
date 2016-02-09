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
    ftune1->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    ftune1->setColour (Slider::textBoxTextColourId, Colours::white);
    ftune1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    ftune1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    ftune1->addListener (this);

    addAndMakeVisible (lfo1depth1 = new MouseOverKnob ("LFO depth 1"));
    lfo1depth1->setRange (0, 12, 0);
    lfo1depth1->setSliderStyle (Slider::RotaryVerticalDrag);
    lfo1depth1->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    lfo1depth1->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    lfo1depth1->setColour (Slider::textBoxTextColourId, Colours::white);
    lfo1depth1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    lfo1depth1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    lfo1depth1->addListener (this);

    addAndMakeVisible (osc1trngAmount = new MouseOverKnob ("Osc1 Triangle Amount"));
    osc1trngAmount->setRange (0, 1, 0);
    osc1trngAmount->setSliderStyle (Slider::RotaryVerticalDrag);
    osc1trngAmount->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    osc1trngAmount->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    osc1trngAmount->setColour (Slider::textBoxTextColourId, Colours::white);
    osc1trngAmount->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    osc1trngAmount->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    osc1trngAmount->addListener (this);

    addAndMakeVisible (pulsewidth = new MouseOverKnob ("Pulse Width"));
    pulsewidth->setRange (0.01, 0.99, 0);
    pulsewidth->setSliderStyle (Slider::RotaryVerticalDrag);
    pulsewidth->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    pulsewidth->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pulsewidth->setColour (Slider::textBoxTextColourId, Colours::white);
    pulsewidth->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pulsewidth->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pulsewidth->addListener (this);

    addAndMakeVisible (pitchRange = new MouseOverKnob ("pitch range"));
    pitchRange->setRange (0, 12, 0);
    pitchRange->setSliderStyle (Slider::RotaryVerticalDrag);
    pitchRange->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    pitchRange->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pitchRange->setColour (Slider::textBoxTextColourId, Colours::white);
    pitchRange->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pitchRange->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pitchRange->addListener (this);

    addAndMakeVisible (ctune1 = new MouseOverKnob ("coarse tune 1"));
    ctune1->setRange (-11, 11, 1);
    ctune1->setSliderStyle (Slider::RotaryVerticalDrag);
    ctune1->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    ctune1->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    ctune1->setColour (Slider::textBoxTextColourId, Colours::white);
    ctune1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    ctune1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    ctune1->addListener (this);

    addAndMakeVisible (waveformVisual = new WaveformVisual (params.osc1Waveform.getStep(), params.osc1pulsewidth.get(), params.osc1trngAmount.get()));
    waveformVisual->setName ("Waveform Visual");

    addAndMakeVisible (waveformSwitch = new Slider ("Waveform Switch"));
    waveformSwitch->setRange (0, 2, 1);
    waveformSwitch->setSliderStyle (Slider::LinearVertical);
    waveformSwitch->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    waveformSwitch->setColour (Slider::thumbColourId, Colour (0xff6c788c));
    waveformSwitch->setColour (Slider::trackColourId, Colours::white);
    waveformSwitch->addListener (this);

    addAndMakeVisible (amountWidthMod = new MouseOverKnob ("Amount width mod"));
    amountWidthMod->setRange (0, 1, 0);
    amountWidthMod->setSliderStyle (Slider::RotaryVerticalDrag);
    amountWidthMod->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    amountWidthMod->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    amountWidthMod->setColour (Slider::textBoxTextColourId, Colours::white);
    amountWidthMod->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    amountWidthMod->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    amountWidthMod->addListener (this);

    addAndMakeVisible (ftune2 = new MouseOverKnob ("fine tune 2"));
    ftune2->setRange (-100, 100, 0);
    ftune2->setSliderStyle (Slider::RotaryVerticalDrag);
    ftune2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    ftune2->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    ftune2->setColour (Slider::textBoxTextColourId, Colours::white);
    ftune2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    ftune2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    ftune2->addListener (this);

    addAndMakeVisible (lfo1depth2 = new MouseOverKnob ("LFO depth 2"));
    lfo1depth2->setRange (0, 12, 0);
    lfo1depth2->setSliderStyle (Slider::RotaryVerticalDrag);
    lfo1depth2->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    lfo1depth2->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    lfo1depth2->setColour (Slider::textBoxTextColourId, Colours::white);
    lfo1depth2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    lfo1depth2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    lfo1depth2->addListener (this);

    addAndMakeVisible (osc2trngAmount = new MouseOverKnob ("Osc2 Triangle Amount"));
    osc2trngAmount->setRange (0, 1, 0);
    osc2trngAmount->setSliderStyle (Slider::RotaryVerticalDrag);
    osc2trngAmount->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    osc2trngAmount->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    osc2trngAmount->setColour (Slider::textBoxTextColourId, Colours::white);
    osc2trngAmount->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    osc2trngAmount->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    osc2trngAmount->addListener (this);

    addAndMakeVisible (pulsewidth2 = new MouseOverKnob ("Pulse Width 2"));
    pulsewidth2->setRange (0.01, 0.99, 0);
    pulsewidth2->setSliderStyle (Slider::RotaryVerticalDrag);
    pulsewidth2->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    pulsewidth2->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pulsewidth2->setColour (Slider::textBoxTextColourId, Colours::white);
    pulsewidth2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pulsewidth2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pulsewidth2->addListener (this);

    addAndMakeVisible (pitchRange2 = new MouseOverKnob ("pitch range 2"));
    pitchRange2->setRange (0, 12, 0);
    pitchRange2->setSliderStyle (Slider::RotaryVerticalDrag);
    pitchRange2->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    pitchRange2->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pitchRange2->setColour (Slider::textBoxTextColourId, Colours::white);
    pitchRange2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pitchRange2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pitchRange2->addListener (this);

    addAndMakeVisible (ctune2 = new MouseOverKnob ("coarse tune 2"));
    ctune2->setRange (-11, 11, 1);
    ctune2->setSliderStyle (Slider::RotaryVerticalDrag);
    ctune2->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    ctune2->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    ctune2->setColour (Slider::textBoxTextColourId, Colours::white);
    ctune2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    ctune2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    ctune2->addListener (this);

    addAndMakeVisible (waveformVisual2 = new WaveformVisual (params.osc1Waveform.getStep(), params.osc1pulsewidth.get(), params.osc1trngAmount.get()));
    waveformVisual2->setName ("Waveform Visual 2");

    addAndMakeVisible (waveformSwitch2 = new Slider ("Waveform Switch"));
    waveformSwitch2->setRange (0, 2, 1);
    waveformSwitch2->setSliderStyle (Slider::LinearVertical);
    waveformSwitch2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    waveformSwitch2->setColour (Slider::thumbColourId, Colour (0xff6c788c));
    waveformSwitch2->setColour (Slider::trackColourId, Colours::white);
    waveformSwitch2->addListener (this);

    addAndMakeVisible (amountWidthMod2 = new MouseOverKnob ("Amount width mod 2"));
    amountWidthMod2->setRange (0, 1, 0);
    amountWidthMod2->setSliderStyle (Slider::RotaryVerticalDrag);
    amountWidthMod2->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    amountWidthMod2->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    amountWidthMod2->setColour (Slider::textBoxTextColourId, Colours::white);
    amountWidthMod2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    amountWidthMod2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    amountWidthMod2->addListener (this);

    addAndMakeVisible (ftune3 = new MouseOverKnob ("fine tune 3"));
    ftune3->setRange (-100, 100, 0);
    ftune3->setSliderStyle (Slider::RotaryVerticalDrag);
    ftune3->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    ftune3->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    ftune3->setColour (Slider::textBoxTextColourId, Colours::white);
    ftune3->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    ftune3->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    ftune3->addListener (this);

    addAndMakeVisible (lfo1depth3 = new MouseOverKnob ("LFO depth 3"));
    lfo1depth3->setRange (0, 12, 0);
    lfo1depth3->setSliderStyle (Slider::RotaryVerticalDrag);
    lfo1depth3->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    lfo1depth3->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    lfo1depth3->setColour (Slider::textBoxTextColourId, Colours::white);
    lfo1depth3->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    lfo1depth3->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    lfo1depth3->addListener (this);

    addAndMakeVisible (osc3trngAmount = new MouseOverKnob ("Osc3 Triangle Amount"));
    osc3trngAmount->setRange (0, 1, 0);
    osc3trngAmount->setSliderStyle (Slider::RotaryVerticalDrag);
    osc3trngAmount->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    osc3trngAmount->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    osc3trngAmount->setColour (Slider::textBoxTextColourId, Colours::white);
    osc3trngAmount->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    osc3trngAmount->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    osc3trngAmount->addListener (this);

    addAndMakeVisible (pulsewidth3 = new MouseOverKnob ("Pulse Width 3"));
    pulsewidth3->setRange (0.01, 0.99, 0);
    pulsewidth3->setSliderStyle (Slider::RotaryVerticalDrag);
    pulsewidth3->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    pulsewidth3->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pulsewidth3->setColour (Slider::textBoxTextColourId, Colours::white);
    pulsewidth3->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pulsewidth3->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pulsewidth3->addListener (this);

    addAndMakeVisible (pitchRange3 = new MouseOverKnob ("pitch range 3"));
    pitchRange3->setRange (0, 12, 0);
    pitchRange3->setSliderStyle (Slider::RotaryVerticalDrag);
    pitchRange3->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    pitchRange3->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pitchRange3->setColour (Slider::textBoxTextColourId, Colours::white);
    pitchRange3->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pitchRange3->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pitchRange3->addListener (this);

    addAndMakeVisible (ctune3 = new MouseOverKnob ("coarse tune 3"));
    ctune3->setRange (-11, 11, 1);
    ctune3->setSliderStyle (Slider::RotaryVerticalDrag);
    ctune3->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    ctune3->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    ctune3->setColour (Slider::textBoxTextColourId, Colours::white);
    ctune3->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    ctune3->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    ctune3->addListener (this);

    addAndMakeVisible (waveformVisual3 = new WaveformVisual (params.osc1Waveform.getStep(), params.osc1pulsewidth.get(), params.osc1trngAmount.get()));
    waveformVisual3->setName ("Waveform Visual 3");

    addAndMakeVisible (waveformSwitch3 = new Slider ("Waveform Switch"));
    waveformSwitch3->setRange (0, 2, 1);
    waveformSwitch3->setSliderStyle (Slider::LinearVertical);
    waveformSwitch3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    waveformSwitch3->setColour (Slider::thumbColourId, Colour (0xff6c788c));
    waveformSwitch3->setColour (Slider::trackColourId, Colours::white);
    waveformSwitch3->addListener (this);

    addAndMakeVisible (amountWidthMod3 = new MouseOverKnob ("Amount width mod 3"));
    amountWidthMod3->setRange (0, 1, 0);
    amountWidthMod3->setSliderStyle (Slider::RotaryVerticalDrag);
    amountWidthMod3->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    amountWidthMod3->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    amountWidthMod3->setColour (Slider::textBoxTextColourId, Colours::white);
    amountWidthMod3->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    amountWidthMod3->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    amountWidthMod3->addListener (this);


    //[UserPreSize]
    // NOTE: test wise
    registerSaturnSource(ctune1, pitchRange, &params.osc1PitchRange, 2);
    registerSaturnSource(ctune1, lfo1depth1, &params.osc1lfo1depth, 1);
    registerSaturnSource(lfo1depth1, pitchRange, &params.osc1PitchRange, 1);

    registerSlider(ftune1, &params.osc1fine);
    registerSlider(lfo1depth1, &params.osc1lfo1depth);
    registerSlider(osc1trngAmount, &params.osc1trngAmount, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(pitchRange, &params.osc1PitchRange);
    registerSlider(pulsewidth, &params.osc1pulsewidth, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(amountWidthMod, &params.osc1AmountWidthMod);
    registerSlider(ctune1, &params.osc1coarse);
    registerSlider(waveformSwitch, &params.osc1Waveform, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(waveformSwitch, &params.osc1Waveform);

    registerSlider(ftune2, &params.osc2fine);
    registerSlider(lfo1depth2, &params.osc2lfo1depth);
    registerSlider(osc2trngAmount, &params.osc2trngAmount, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(pitchRange2, &params.osc2PitchRange);
    registerSlider(pulsewidth2, &params.osc2pulsewidth, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(amountWidthMod2, &params.osc2AmountWidthMod);
    registerSlider(ctune2, &params.osc2coarse);
    registerSlider(waveformSwitch, &params.osc2Waveform, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(waveformSwitch, &params.osc2Waveform);

    registerSlider(ftune3, &params.osc3fine);
    registerSlider(lfo1depth3, &params.osc3lfo1depth);
    registerSlider(osc3trngAmount, &params.osc3trngAmount, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(pitchRange3, &params.osc3PitchRange);
    registerSlider(pulsewidth3, &params.osc3pulsewidth, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(amountWidthMod3, &params.osc3AmountWidthMod);
    registerSlider(ctune3, &params.osc3coarse);
    registerSlider(waveformSwitch3, &params.osc3Waveform, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(waveformSwitch3, &params.osc3Waveform);
    //[/UserPreSize]

    setSize (800, 272);


    //[Constructor] You can add your own custom stuff here..
    osc1trngAmount->setVisible(false);
    osc2trngAmount->setVisible(false);
    osc3trngAmount->setVisible(false);
    waveforms = ImageCache::getFromMemory(BinaryData::sineswitch_noise_png, BinaryData::sineswitch_noise_pngSize); // TODO: braucht destructor?
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
    waveformVisual = nullptr;
    waveformSwitch = nullptr;
    amountWidthMod = nullptr;
    ftune2 = nullptr;
    lfo1depth2 = nullptr;
    osc2trngAmount = nullptr;
    pulsewidth2 = nullptr;
    pitchRange2 = nullptr;
    ctune2 = nullptr;
    waveformVisual2 = nullptr;
    waveformSwitch2 = nullptr;
    amountWidthMod2 = nullptr;
    ftune3 = nullptr;
    lfo1depth3 = nullptr;
    osc3trngAmount = nullptr;
    pulsewidth3 = nullptr;
    pitchRange3 = nullptr;
    ctune3 = nullptr;
    waveformVisual3 = nullptr;
    waveformSwitch3 = nullptr;
    amountWidthMod3 = nullptr;


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
    drawGroupBorder(g, "osc 1", 0, 0,
                    this->getWidth() / 3, this->getHeight(), 25.0f, 20.0f, 5.0f, 3.0f, Colour(0xff6c788c));
    drawGroupBorder(g, "osc 2",this->getWidth() / 3, 0,
                    this->getWidth() / 3, this->getHeight(), 25.0f, 20.0f, 5.0f, 3.0f, Colour(0xff6c788c));
    drawGroupBorder(g, "osc 3", this->getWidth() / 3 * 2, 0,
                    this->getWidth() / 3, this->getHeight(), 25.0f, 20.0f, 5.0f, 3.0f, Colour(0xff6c788c));

    // draw waveform symbols
    drawWaves(g, waveformSwitch);
    drawWaves(g, waveformSwitch2);
    drawWaves(g, waveformSwitch3);
    //[/UserPaint]
}

void OscPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    ftune1->setBounds (8, 170, 64, 64);
    lfo1depth1->setBounds (84, 30, 64, 64);
    osc1trngAmount->setBounds (84, 97, 64, 64);
    pulsewidth->setBounds (84, 97, 64, 64);
    pitchRange->setBounds (8, 31, 64, 64);
    ctune1->setBounds (8, 97, 64, 64);
    waveformVisual->setBounds (75, 160, 123, 72);
    waveformSwitch->setBounds (198, 169, 40, 54);
    amountWidthMod->setBounds (172, 30, 64, 64);
    ftune2->setBounds (275, 170, 64, 64);
    lfo1depth2->setBounds (351, 30, 64, 64);
    osc2trngAmount->setBounds (351, 97, 64, 64);
    pulsewidth2->setBounds (351, 97, 64, 64);
    pitchRange2->setBounds (275, 31, 64, 64);
    ctune2->setBounds (275, 97, 64, 64);
    waveformVisual2->setBounds (342, 160, 123, 72);
    waveformSwitch2->setBounds (465, 169, 40, 54);
    amountWidthMod2->setBounds (439, 30, 64, 64);
    ftune3->setBounds (544, 170, 64, 64);
    lfo1depth3->setBounds (620, 30, 64, 64);
    osc3trngAmount->setBounds (620, 97, 64, 64);
    pulsewidth3->setBounds (620, 97, 64, 64);
    pitchRange3->setBounds (544, 31, 64, 64);
    ctune3->setBounds (544, 97, 64, 64);
    waveformVisual3->setBounds (611, 160, 123, 72);
    waveformSwitch3->setBounds (734, 169, 40, 54);
    amountWidthMod3->setBounds (708, 30, 64, 64);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void OscPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //sliderThatWasMoved->repaint(); // TODO: only for now, not nice
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
    else if (sliderThatWasMoved == waveformSwitch)
    {
        //[UserSliderCode_waveformSwitch] -- add your slider handling code here..
        //[/UserSliderCode_waveformSwitch]
    }
    else if (sliderThatWasMoved == amountWidthMod)
    {
        //[UserSliderCode_amountWidthMod] -- add your slider handling code here..
        //[/UserSliderCode_amountWidthMod]
    }
    else if (sliderThatWasMoved == ftune2)
    {
        //[UserSliderCode_ftune2] -- add your slider handling code here..
        //[/UserSliderCode_ftune2]
    }
    else if (sliderThatWasMoved == lfo1depth2)
    {
        //[UserSliderCode_lfo1depth2] -- add your slider handling code here..
        //[/UserSliderCode_lfo1depth2]
    }
    else if (sliderThatWasMoved == osc2trngAmount)
    {
        //[UserSliderCode_osc2trngAmount] -- add your slider handling code here..
        //[/UserSliderCode_osc2trngAmount]
    }
    else if (sliderThatWasMoved == pulsewidth2)
    {
        //[UserSliderCode_pulsewidth2] -- add your slider handling code here..
        //[/UserSliderCode_pulsewidth2]
    }
    else if (sliderThatWasMoved == pitchRange2)
    {
        //[UserSliderCode_pitchRange2] -- add your slider handling code here..
        //[/UserSliderCode_pitchRange2]
    }
    else if (sliderThatWasMoved == ctune2)
    {
        //[UserSliderCode_ctune2] -- add your slider handling code here..
        //[/UserSliderCode_ctune2]
    }
    else if (sliderThatWasMoved == waveformSwitch2)
    {
        //[UserSliderCode_waveformSwitch2] -- add your slider handling code here..
        //[/UserSliderCode_waveformSwitch2]
    }
    else if (sliderThatWasMoved == amountWidthMod2)
    {
        //[UserSliderCode_amountWidthMod2] -- add your slider handling code here..
        //[/UserSliderCode_amountWidthMod2]
    }
    else if (sliderThatWasMoved == ftune3)
    {
        //[UserSliderCode_ftune3] -- add your slider handling code here..
        //[/UserSliderCode_ftune3]
    }
    else if (sliderThatWasMoved == lfo1depth3)
    {
        //[UserSliderCode_lfo1depth3] -- add your slider handling code here..
        //[/UserSliderCode_lfo1depth3]
    }
    else if (sliderThatWasMoved == osc3trngAmount)
    {
        //[UserSliderCode_osc3trngAmount] -- add your slider handling code here..
        //[/UserSliderCode_osc3trngAmount]
    }
    else if (sliderThatWasMoved == pulsewidth3)
    {
        //[UserSliderCode_pulsewidth3] -- add your slider handling code here..
        //[/UserSliderCode_pulsewidth3]
    }
    else if (sliderThatWasMoved == pitchRange3)
    {
        //[UserSliderCode_pitchRange3] -- add your slider handling code here..
        //[/UserSliderCode_pitchRange3]
    }
    else if (sliderThatWasMoved == ctune3)
    {
        //[UserSliderCode_ctune3] -- add your slider handling code here..
        //[/UserSliderCode_ctune3]
    }
    else if (sliderThatWasMoved == waveformSwitch3)
    {
        //[UserSliderCode_waveformSwitch3] -- add your slider handling code here..
        //[/UserSliderCode_waveformSwitch3]
    }
    else if (sliderThatWasMoved == amountWidthMod3)
    {
        //[UserSliderCode_amountWidthMod3] -- add your slider handling code here..
        //[/UserSliderCode_amountWidthMod3]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void OscPanel::updateWFShapeControls()
{
    int waveformKey = static_cast<int>(waveformSwitch->getValue());
    eOscWaves eWaveformKey = static_cast<eOscWaves>(waveformKey);
    params.osc1Waveform.setStep(eWaveformKey);
    pulsewidth->setVisible(eWaveformKey == eOscWaves::eOscSquare);
    osc1trngAmount->setVisible(eWaveformKey == eOscWaves::eOscSaw);
    waveformVisual->setWaveformKey(eWaveformKey);
    waveformVisual->setPulseWidth(static_cast<float>(pulsewidth->getValue()));
    waveformVisual->setTrngAmount(static_cast<float>(osc1trngAmount->getValue()));
}


void OscPanel::drawWaves(Graphics& g, ScopedPointer<Slider>& _waveformSwitch)
{
    int centerX = _waveformSwitch->getX() + _waveformSwitch->getWidth() / 2;
    int centerY = _waveformSwitch->getY() + _waveformSwitch->getHeight() / 2;

    g.drawImageWithin(waveforms.getClippedImage(noiseFrame), centerX - 15, _waveformSwitch->getY() - 20, 30, 20, RectanglePlacement::centred);
    g.drawImageWithin(waveforms.getClippedImage(sawFrame), _waveformSwitch->getX() + _waveformSwitch->getWidth() / 2 + 10, centerY - 10, 30, 20, RectanglePlacement::centred);
    g.drawImageWithin(waveforms.getClippedImage(squareFrame), centerX - 15, _waveformSwitch->getY() + _waveformSwitch->getHeight() - 2, 30, 20, RectanglePlacement::centred);
}
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
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="800"
                 initialHeight="272">
  <BACKGROUND backgroundColour="ff6c788c"/>
  <SLIDER name="fine tune 1" id="3c32cde7173ddbe6" memberName="ftune1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 170 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-100" max="100" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="LFO depth 1" id="523b9024be39c1b" memberName="lfo1depth1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="84 30 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc1 Triangle Amount" id="d81a0f8c69078b3c" memberName="osc1trngAmount"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="84 97 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Pulse Width" id="96badb5ea7640431" memberName="pulsewidth"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="84 97 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.010000000000000000208" max="0.98999999999999999112"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="64" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="pitch range" id="29275125e377aaa" memberName="pitchRange"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 31 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="coarse tune 1" id="52a6628a22cee304" memberName="ctune1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 97 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-11" max="11" int="1" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="Waveform Visual" id="dc40e7918cb34428" memberName="waveformVisual"
                    virtualName="WaveformVisual" explicitFocusOrder="0" pos="75 160 123 72"
                    class="Component" params="params.osc1Waveform.getStep(), params.osc1pulsewidth.get(), params.osc1trngAmount.get()"/>
  <SLIDER name="Waveform Switch" id="df460155fcb1ed38" memberName="waveformSwitch"
          virtualName="" explicitFocusOrder="0" pos="198 169 40 54" thumbcol="ff6c788c"
          trackcol="ffffffff" min="0" max="2" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Amount width mod" id="ea500ea6791045c2" memberName="amountWidthMod"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="172 30 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="fine tune 2" id="9c36cedeb4391374" memberName="ftune2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="275 170 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-100" max="100" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="LFO depth 2" id="b80fdf24bc6713e" memberName="lfo1depth2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="351 30 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc2 Triangle Amount" id="e81013cb2b079733" memberName="osc2trngAmount"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="351 97 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Pulse Width 2" id="83655640f6564c4f" memberName="pulsewidth2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="351 97 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.010000000000000000208" max="0.98999999999999999112"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="64" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="pitch range 2" id="2a387793c6e0d1e9" memberName="pitchRange2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="275 31 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="coarse tune 2" id="4c4f5887b60ce7e9" memberName="ctune2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="275 97 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-11" max="11" int="1" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="Waveform Visual 2" id="985d80b6241a36e7" memberName="waveformVisual2"
                    virtualName="WaveformVisual" explicitFocusOrder="0" pos="342 160 123 72"
                    class="Component" params="params.osc1Waveform.getStep(), params.osc1pulsewidth.get(), params.osc1trngAmount.get()"/>
  <SLIDER name="Waveform Switch" id="b70bb7e697214772" memberName="waveformSwitch2"
          virtualName="" explicitFocusOrder="0" pos="465 169 40 54" thumbcol="ff6c788c"
          trackcol="ffffffff" min="0" max="2" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Amount width mod 2" id="c49f5c6fd5eba5df" memberName="amountWidthMod2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="439 30 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="fine tune 3" id="75310905f918e8aa" memberName="ftune3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="544 170 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-100" max="100" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="LFO depth 3" id="330f1742cb28ab2f" memberName="lfo1depth3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="620 30 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc3 Triangle Amount" id="b8205160908ec945" memberName="osc3trngAmount"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="620 97 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Pulse Width 3" id="fbdb7af6c419abe3" memberName="pulsewidth3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="620 97 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.010000000000000000208" max="0.98999999999999999112"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="64" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="pitch range 3" id="73696dde9bad041c" memberName="pitchRange3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="544 31 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="coarse tune 3" id="65b439d50c799f0b" memberName="ctune3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="544 97 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-11" max="11" int="1" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="Waveform Visual 3" id="6f635e6741c69a8b" memberName="waveformVisual3"
                    virtualName="WaveformVisual" explicitFocusOrder="0" pos="611 160 123 72"
                    class="Component" params="params.osc1Waveform.getStep(), params.osc1pulsewidth.get(), params.osc1trngAmount.get()"/>
  <SLIDER name="Waveform Switch" id="f2fed0705e83265a" memberName="waveformSwitch3"
          virtualName="" explicitFocusOrder="0" pos="734 169 40 54" thumbcol="ff6c788c"
          trackcol="ffffffff" min="0" max="2" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Amount width mod 3" id="4cf51bedef649a1" memberName="amountWidthMod3"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="708 30 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
