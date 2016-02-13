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

    addAndMakeVisible (ftune1 = new MouseOverKnob ("fine tune 1"));
    ftune1->setRange (-100, 100, 0);
    ftune1->setSliderStyle (Slider::RotaryVerticalDrag);
    ftune1->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    ftune1->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    ftune1->setColour (Slider::textBoxTextColourId, Colours::white);
    ftune1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    ftune1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    ftune1->addListener (this);

    addAndMakeVisible (pitchModAmount2 = new MouseOverKnob ("PitchModAmount2"));
    pitchModAmount2->setRange (0, 12, 0);
    pitchModAmount2->setSliderStyle (Slider::RotaryVerticalDrag);
    pitchModAmount2->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    pitchModAmount2->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pitchModAmount2->setColour (Slider::textBoxTextColourId, Colours::white);
    pitchModAmount2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pitchModAmount2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pitchModAmount2->addListener (this);

    addAndMakeVisible (trngAmount = new MouseOverKnob ("Osc1 Triangle Amount"));
    trngAmount->setRange (0, 1, 0);
    trngAmount->setSliderStyle (Slider::RotaryVerticalDrag);
    trngAmount->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    trngAmount->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    trngAmount->setColour (Slider::textBoxTextColourId, Colours::white);
    trngAmount->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    trngAmount->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    trngAmount->addListener (this);

    addAndMakeVisible (pulsewidth = new MouseOverKnob ("Pulse Width"));
    pulsewidth->setRange (0.01, 0.99, 0);
    pulsewidth->setSliderStyle (Slider::RotaryVerticalDrag);
    pulsewidth->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    pulsewidth->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pulsewidth->setColour (Slider::textBoxTextColourId, Colours::white);
    pulsewidth->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pulsewidth->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pulsewidth->addListener (this);

    addAndMakeVisible (pitchModAmount1 = new MouseOverKnob ("PitchModAmount1"));
    pitchModAmount1->setRange (0, 12, 0);
    pitchModAmount1->setSliderStyle (Slider::RotaryVerticalDrag);
    pitchModAmount1->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    pitchModAmount1->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pitchModAmount1->setColour (Slider::textBoxTextColourId, Colours::white);
    pitchModAmount1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pitchModAmount1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pitchModAmount1->addListener (this);

    addAndMakeVisible (ctune1 = new MouseOverKnob ("coarse tune 1"));
    ctune1->setRange (-11, 11, 1);
    ctune1->setSliderStyle (Slider::RotaryVerticalDrag);
    ctune1->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
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
    widthModAmount1->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    widthModAmount1->setColour (Slider::textBoxTextColourId, Colours::white);
    widthModAmount1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    widthModAmount1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    widthModAmount1->addListener (this);

    addAndMakeVisible (pitchModSrc1 = new ComboBox ("oscPitchModSrc1"));
    pitchModSrc1->setEditableText (false);
    pitchModSrc1->setJustificationType (Justification::centred);
    pitchModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    pitchModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    pitchModSrc1->addListener (this);

    addAndMakeVisible (pitchModSrc2 = new ComboBox ("oscPitchModSrc2"));
    pitchModSrc2->setEditableText (false);
    pitchModSrc2->setJustificationType (Justification::centred);
    pitchModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    pitchModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    pitchModSrc2->addListener (this);

    addAndMakeVisible (gain = new MouseOverKnob ("gain knob"));
    gain->setRange (-96, 12, 0);
    gain->setSliderStyle (Slider::RotaryVerticalDrag);
    gain->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    gain->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    gain->setColour (Slider::textBoxTextColourId, Colours::white);
    gain->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    gain->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    gain->addListener (this);

    addAndMakeVisible (pan = new MouseOverKnob ("pan knob"));
    pan->setRange (-100, 100, 0);
    pan->setSliderStyle (Slider::RotaryVerticalDrag);
    pan->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    pan->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pan->setColour (Slider::textBoxTextColourId, Colours::white);
    pan->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pan->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pan->addListener (this);

    addAndMakeVisible (widthModAmount2 = new MouseOverKnob ("WidthModAmount2"));
    widthModAmount2->setRange (0, 1, 0);
    widthModAmount2->setSliderStyle (Slider::RotaryVerticalDrag);
    widthModAmount2->setTextBoxStyle (Slider::TextBoxBelow, false, 0, 0);
    widthModAmount2->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    widthModAmount2->setColour (Slider::textBoxTextColourId, Colours::white);
    widthModAmount2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    widthModAmount2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    widthModAmount2->addListener (this);

    addAndMakeVisible (widthModSrc1 = new ComboBox ("WidthModSrc1"));
    widthModSrc1->setEditableText (false);
    widthModSrc1->setJustificationType (Justification::centred);
    widthModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    widthModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    widthModSrc1->addListener (this);

    addAndMakeVisible (widthModSrc2 = new ComboBox ("WidthModSrc2"));
    widthModSrc2->setEditableText (false);
    widthModSrc2->setJustificationType (Justification::centred);
    widthModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    widthModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    widthModSrc2->addListener (this);

    addAndMakeVisible (gainModAmount2 = new MouseOverKnob ("GainModAmount2"));
    gainModAmount2->setRange (0, 12, 0);
    gainModAmount2->setSliderStyle (Slider::RotaryVerticalDrag);
    gainModAmount2->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    gainModAmount2->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    gainModAmount2->setColour (Slider::textBoxTextColourId, Colours::white);
    gainModAmount2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    gainModAmount2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    gainModAmount2->addListener (this);

    addAndMakeVisible (gainModAmount1 = new MouseOverKnob ("GainModAmount1"));
    gainModAmount1->setRange (0, 12, 0);
    gainModAmount1->setSliderStyle (Slider::RotaryVerticalDrag);
    gainModAmount1->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    gainModAmount1->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    gainModAmount1->setColour (Slider::textBoxTextColourId, Colours::white);
    gainModAmount1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    gainModAmount1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    gainModAmount1->addListener (this);

    addAndMakeVisible (gainModSrc1 = new ComboBox ("GainModSrc1"));
    gainModSrc1->setEditableText (false);
    gainModSrc1->setJustificationType (Justification::centred);
    gainModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    gainModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    gainModSrc1->addListener (this);

    addAndMakeVisible (gainModSrc2 = new ComboBox ("GainModSrc2"));
    gainModSrc2->setEditableText (false);
    gainModSrc2->setJustificationType (Justification::centred);
    gainModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    gainModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    gainModSrc2->addListener (this);

    addAndMakeVisible (panModAmount2 = new MouseOverKnob ("PanModAmount2"));
    panModAmount2->setRange (0, 12, 0);
    panModAmount2->setSliderStyle (Slider::RotaryVerticalDrag);
    panModAmount2->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    panModAmount2->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    panModAmount2->setColour (Slider::textBoxTextColourId, Colours::white);
    panModAmount2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    panModAmount2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    panModAmount2->addListener (this);

    addAndMakeVisible (panModAmount1 = new MouseOverKnob ("PanModAmount1"));
    panModAmount1->setRange (0, 12, 0);
    panModAmount1->setSliderStyle (Slider::RotaryVerticalDrag);
    panModAmount1->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    panModAmount1->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    panModAmount1->setColour (Slider::textBoxTextColourId, Colours::white);
    panModAmount1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    panModAmount1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    panModAmount1->addListener (this);

    addAndMakeVisible (panModSrc1 = new ComboBox ("PanModSrc1"));
    panModSrc1->setEditableText (false);
    panModSrc1->setJustificationType (Justification::centred);
    panModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    panModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    panModSrc1->addListener (this);

    addAndMakeVisible (panModSrc2 = new ComboBox ("PanModSrc2"));
    panModSrc2->setEditableText (false);
    panModSrc2->setJustificationType (Justification::centred);
    panModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    panModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    panModSrc2->addListener (this);


    //[UserPreSize]
    // NOTE: test wise
    registerSaturnSource(ctune1, pitchModAmount1, &osc.pitchModSrc1, &osc.pitchModAmount1, false, 1);
    registerSaturnSource(ctune1, pitchModAmount2, &osc.pitchModSrc2, &osc.pitchModAmount2, false, 2);

    registerSlider(gain, &osc.vol);
    registerSlider(pan, &osc.panDir);
    registerSlider(ftune1, &osc.fine);
    registerSlider(ctune1, &osc.coarse);
    registerSlider(pitchModAmount1, &osc.pitchModAmount1);
    registerSlider(pitchModAmount2, &osc.pitchModAmount2);
    registerSlider(waveformSwitch, &osc.waveForm, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(trngAmount, &osc.trngAmount, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(pulsewidth, &osc.pulseWidth, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(widthModAmount1, &osc.shapeModAmount);
    //registerSlider(widthModAmount2, &osc.shapeModAmount2);

    // TODO: register other boxes
    fillModsourceBox(pitchModSrc1);
    fillModsourceBox(pitchModSrc2);
    registerCombobox(pitchModSrc1, &osc.pitchModSrc1, ctune1);
    registerCombobox(pitchModSrc2, &osc.pitchModSrc2, ctune1);

    fillModsourceBox(widthModSrc1);
    fillModsourceBox(widthModSrc2);
    registerCombobox(widthModSrc1, &osc.shapeModSrc1, trngAmount);
    registerCombobox(widthModSrc2, &osc.shapeModSrc2, trngAmount);
    registerCombobox(widthModSrc1, &osc.shapeModSrc1, pulsewidth);
    registerCombobox(widthModSrc2, &osc.shapeModSrc2, pulsewidth);

    fillModsourceBox(panModSrc1);
    fillModsourceBox(panModSrc2);

    fillModsourceBox(gainModSrc1);
    fillModsourceBox(gainModSrc2);
    //[/UserPreSize]

    setSize (267, 272);


    //[Constructor] You can add your own custom stuff here..
    trngAmount->setVisible(false);
    gain->setSkewFactorFromMidPoint(-6.0);

    pitchModAmount1->setAlwaysOnTop(true);
    pitchModAmount2->setAlwaysOnTop(true);
    gainModAmount1->setAlwaysOnTop(true);
    gainModAmount2->setAlwaysOnTop(true);
    widthModAmount1->setAlwaysOnTop(true);
    widthModAmount2->setAlwaysOnTop(true);
    panModAmount1->setAlwaysOnTop(true);
    panModAmount2->setAlwaysOnTop(true);

    waveforms = ImageCache::getFromMemory(BinaryData::sineswitch_noise_png, BinaryData::sineswitch_noise_pngSize);
    //[/Constructor]
}

OscPanel::~OscPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

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
    widthModSrc1 = nullptr;
    widthModSrc2 = nullptr;
    gainModAmount2 = nullptr;
    gainModAmount1 = nullptr;
    gainModSrc1 = nullptr;
    gainModSrc2 = nullptr;
    panModAmount2 = nullptr;
    panModAmount1 = nullptr;
    panModSrc1 = nullptr;
    panModSrc2 = nullptr;


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
                    this->getWidth(), this->getHeight() - 22, 25.0f, 20.0f, 5.0f, 3.0f, SynthParams::oscColour);

    // draw waveform symbols
    drawWaves(g, waveformSwitch);
    //[/UserPaint]
}

void OscPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    ftune1->setBounds (8, 170, 64, 64);
    pitchModAmount2->setBounds (65, 124, 18, 18);
    trngAmount->setBounds (127, 100, 64, 64);
    pulsewidth->setBounds (127, 100, 64, 64);
    pitchModAmount1->setBounds (65, 100, 18, 18);
    ctune1->setBounds (8, 100, 64, 64);
    waveformVisual->setBounds (75, 160, 123, 72);
    waveformSwitch->setBounds (198, 169, 40, 54);
    widthModAmount1->setBounds (184, 100, 18, 18);
    pitchModSrc1->setBounds (88, 100, 40, 18);
    pitchModSrc2->setBounds (88, 124, 40, 18);
    gain->setBounds (8, 34, 64, 64);
    pan->setBounds (127, 34, 64, 64);
    widthModAmount2->setBounds (184, 124, 18, 18);
    widthModSrc1->setBounds (207, 100, 40, 18);
    widthModSrc2->setBounds (207, 124, 40, 18);
    gainModAmount2->setBounds (65, 58, 18, 18);
    gainModAmount1->setBounds (65, 34, 18, 18);
    gainModSrc1->setBounds (88, 34, 40, 18);
    gainModSrc2->setBounds (88, 58, 40, 18);
    panModAmount2->setBounds (184, 58, 18, 18);
    panModAmount1->setBounds (184, 34, 18, 18);
    panModSrc1->setBounds (207, 34, 40, 18);
    panModSrc2->setBounds (207, 58, 40, 18);
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

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void OscPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    handleCombobox(comboBoxThatHasChanged);
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == pitchModSrc1)
    {
        //[UserComboBoxCode_pitchModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_pitchModSrc1]
    }
    else if (comboBoxThatHasChanged == pitchModSrc2)
    {
        //[UserComboBoxCode_pitchModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_pitchModSrc2]
    }
    else if (comboBoxThatHasChanged == widthModSrc1)
    {
        //[UserComboBoxCode_widthModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_widthModSrc1]
    }
    else if (comboBoxThatHasChanged == widthModSrc2)
    {
        //[UserComboBoxCode_widthModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_widthModSrc2]
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



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void OscPanel::updateWFShapeControls()
{
    int waveformKey = static_cast<int>(waveformSwitch->getValue());
    eOscWaves eWaveformKey = static_cast<eOscWaves>(waveformKey);
    osc.waveForm.setStep(eWaveformKey);
    pulsewidth->setVisible(eWaveformKey == eOscWaves::eOscSquare);
    trngAmount->setVisible(eWaveformKey == eOscWaves::eOscSaw);
    waveformVisual->setWaveformKey(eWaveformKey);
    waveformVisual->setPulseWidth(static_cast<float>(pulsewidth->getValue()));
    waveformVisual->setTrngAmount(static_cast<float>(trngAmount->getValue()));
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
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p, int oscillatorNumber"
                 variableInitialisers="PanelBase(p), osc(p.osc[oscillatorNumber])"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="267" initialHeight="272">
  <BACKGROUND backgroundColour="ff6c788c"/>
  <SLIDER name="fine tune 1" id="3c32cde7173ddbe6" memberName="ftune1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 170 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-100" max="100" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="PitchModAmount2" id="523b9024be39c1b" memberName="pitchModAmount2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="65 124 18 18"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="1"/>
  <SLIDER name="Osc1 Triangle Amount" id="d81a0f8c69078b3c" memberName="trngAmount"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="127 100 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Pulse Width" id="96badb5ea7640431" memberName="pulsewidth"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="127 100 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.01" max="0.98999999999999999"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="PitchModAmount1" id="29275125e377aaa" memberName="pitchModAmount1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="65 100 18 18"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="1"/>
  <SLIDER name="coarse tune 1" id="52a6628a22cee304" memberName="ctune1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 100 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-11" max="11" int="1" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="Waveform Visual" id="dc40e7918cb34428" memberName="waveformVisual"
                    virtualName="WaveformVisual" explicitFocusOrder="0" pos="75 160 123 72"
                    class="Component" params="osc.waveForm.getStep(), osc.pulseWidth.get(), osc.trngAmount.get()"/>
  <SLIDER name="Waveform Switch" id="df460155fcb1ed38" memberName="waveformSwitch"
          virtualName="" explicitFocusOrder="0" pos="198 169 40 54" thumbcol="ff6c788c"
          trackcol="ffffffff" min="0" max="2" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="WidthModAmount1" id="ea500ea6791045c2" memberName="widthModAmount1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="184 100 18 18"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="0"
          textBoxHeight="0" skewFactor="1"/>
  <COMBOBOX name="oscPitchModSrc1" id="4e9e1857f51fc7f4" memberName="pitchModSrc1"
            virtualName="" explicitFocusOrder="0" pos="88 100 40 18" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="oscPitchModSrc2" id="58dc64c4649ad205" memberName="pitchModSrc2"
            virtualName="" explicitFocusOrder="0" pos="88 124 40 18" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <SLIDER name="gain knob" id="da94529625060498" memberName="gain" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="8 34 64 64" rotarysliderfill="ff6c788c"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="ffffff"
          min="-96" max="12" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="pan knob" id="dd33a09584f4c2ff" memberName="pan" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="127 34 64 64" rotarysliderfill="ff6c788c"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="ffffff"
          min="-100" max="100" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="WidthModAmount2" id="ae5c9ce50e2de7e1" memberName="widthModAmount2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="184 124 18 18"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="0"
          textBoxHeight="0" skewFactor="1"/>
  <COMBOBOX name="WidthModSrc1" id="928cd04bb7b23ab9" memberName="widthModSrc1"
            virtualName="" explicitFocusOrder="0" pos="207 100 40 18" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="WidthModSrc2" id="455e48a25414a454" memberName="widthModSrc2"
            virtualName="" explicitFocusOrder="0" pos="207 124 40 18" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <SLIDER name="GainModAmount2" id="93ff4adc6f243ee3" memberName="gainModAmount2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="65 58 18 18"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="1"/>
  <SLIDER name="GainModAmount1" id="6604fe537dac0d1e" memberName="gainModAmount1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="65 34 18 18"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="1"/>
  <COMBOBOX name="GainModSrc1" id="66da971c3fe90ee6" memberName="gainModSrc1"
            virtualName="" explicitFocusOrder="0" pos="88 34 40 18" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="GainModSrc2" id="7fad32464e7c032" memberName="gainModSrc2"
            virtualName="" explicitFocusOrder="0" pos="88 58 40 18" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <SLIDER name="PanModAmount2" id="373f8321765bf923" memberName="panModAmount2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="184 58 18 18"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="1"/>
  <SLIDER name="PanModAmount1" id="3d939a1eb44dbbb0" memberName="panModAmount1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="184 34 18 18"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="0" textBoxHeight="0"
          skewFactor="1"/>
  <COMBOBOX name="PanModSrc1" id="9c99fb5c7e8aa9ca" memberName="panModSrc1"
            virtualName="" explicitFocusOrder="0" pos="207 34 40 18" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="PanModSrc2" id="48da71ae7732f1b" memberName="panModSrc2"
            virtualName="" explicitFocusOrder="0" pos="207 58 40 18" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
