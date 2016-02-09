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
OscPanel::OscPanel (SynthParams &p, int oscillatorNumber, const String& panelTitle)
    : PanelBase(p)
      , osc(p.osc[oscillatorNumber])
      , _panelTitle(panelTitle)
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

    addAndMakeVisible (trngAmount = new MouseOverKnob ("Osc1 Triangle Amount"));
    trngAmount->setRange (0, 1, 0);
    trngAmount->setSliderStyle (Slider::RotaryVerticalDrag);
    trngAmount->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    trngAmount->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    trngAmount->setColour (Slider::textBoxTextColourId, Colours::white);
    trngAmount->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    trngAmount->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    trngAmount->addListener (this);

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

    addAndMakeVisible (waveformVisual = new WaveformVisual (osc.waveForm.getStep(), osc.pulseWidth.get(), osc.trngAmount.get()));
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

    addAndMakeVisible (osc1FreqModSrc1 = new ComboBox ("osc1FreqModSrcBox1"));
    osc1FreqModSrc1->setEditableText (false);
    osc1FreqModSrc1->setJustificationType (Justification::centred);
    osc1FreqModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    osc1FreqModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    osc1FreqModSrc1->addListener (this);

    addAndMakeVisible (osc1FreqModSrc2 = new ComboBox ("osc1FreqModSrcBox2"));
    osc1FreqModSrc2->setEditableText (false);
    osc1FreqModSrc2->setJustificationType (Justification::centred);
    osc1FreqModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    osc1FreqModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    osc1FreqModSrc2->addListener (this);


    //[UserPreSize]
    // NOTE: test wise
    registerSaturnSource(ctune1, pitchRange, &osc.pitchModAmount1, 2);
    registerSaturnSource(ctune1, lfo1depth1, &osc.pitchModAmount2, 1);

    registerSaturnSource(lfo1depth1, pitchRange, &osc.pitchModAmount1, 1);

    registerSlider(ftune1, &osc.fine);
    registerSlider(lfo1depth1, &osc.pitchModAmount2);
    registerSlider(trngAmount, &osc.trngAmount, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(pitchRange, &osc.pitchModAmount1);
    registerSlider(pulsewidth, &osc.pulseWidth, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(amountWidthMod, &osc.shapeModAmount);
    registerSlider(ctune1, &osc.coarse);
    registerSlider(waveformSwitch, &osc.waveForm, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(waveformSwitch, &osc.waveForm);

    fillModsourceBox(osc1FreqModSrc1);
    fillModsourceBox(osc1FreqModSrc2);

    registerCombobox(osc1FreqModSrc1, &osc.pitchModSrc1);
    registerCombobox(osc1FreqModSrc2, &osc.pitchModSrc2);
    //[/UserPreSize]

    setSize (267, 272);


    //[Constructor] You can add your own custom stuff here..
    trngAmount->setVisible(false);/*
    osc2trngAmount->setVisible(false);
    osc3trngAmount->setVisible(false);*/
    waveforms = ImageCache::getFromMemory(BinaryData::sineswitch_noise_png, BinaryData::sineswitch_noise_pngSize); // TODO: braucht destructor?
    //[/Constructor]
}

OscPanel::~OscPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    ftune1 = nullptr;
    lfo1depth1 = nullptr;
    trngAmount = nullptr;
    pulsewidth = nullptr;
    pitchRange = nullptr;
    ctune1 = nullptr;
    waveformVisual = nullptr;
    waveformSwitch = nullptr;
    amountWidthMod = nullptr;
    osc1FreqModSrc1 = nullptr;
    osc1FreqModSrc2 = nullptr;


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
    drawGroupBorder(g, _panelTitle, 0, 0,
                    this->getWidth(), this->getHeight() - 22, 25.0f, 20.0f, 5.0f, 3.0f, Colour(0xff6c788c));

    // draw waveform symbols
    drawWaves(g, waveformSwitch);
    //[/UserPaint]
}

void OscPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    ftune1->setBounds (8, 170, 64, 64);
    lfo1depth1->setBounds (84, 30, 64, 64);
    trngAmount->setBounds (80, 96, 64, 64);
    pulsewidth->setBounds (80, 96, 64, 64);
    pitchRange->setBounds (8, 31, 64, 64);
    ctune1->setBounds (8, 97, 64, 64);
    waveformVisual->setBounds (75, 160, 123, 72);
    waveformSwitch->setBounds (198, 169, 40, 54);
    amountWidthMod->setBounds (172, 30, 64, 64);
    osc1FreqModSrc1->setBounds (144, 96, 64, 16);
    osc1FreqModSrc2->setBounds (144, 120, 64, 16);
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

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void OscPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    handleCombobox(comboBoxThatHasChanged);
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == osc1FreqModSrc1)
    {
        //[UserComboBoxCode_osc1FreqModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_osc1FreqModSrc1]
    }
    else if (comboBoxThatHasChanged == osc1FreqModSrc2)
    {
        //[UserComboBoxCode_osc1FreqModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_osc1FreqModSrc2]
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
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p, int oscillatorNumber, const String&amp; panelTitle"
                 variableInitialisers="PanelBase(p)&#10;, osc(p.osc[oscillatorNumber])&#10;, _panelTitle(panelTitle)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="267" initialHeight="272">
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
  <SLIDER name="Osc1 Triangle Amount" id="d81a0f8c69078b3c" memberName="trngAmount"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="80 96 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Pulse Width" id="96badb5ea7640431" memberName="pulsewidth"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="80 96 64 64"
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
  <COMBOBOX name="osc1FreqModSrcBox1" id="4e9e1857f51fc7f4" memberName="osc1FreqModSrc1"
            virtualName="" explicitFocusOrder="0" pos="144 96 64 16" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="osc1FreqModSrcBox2" id="58dc64c4649ad205" memberName="osc1FreqModSrc2"
            virtualName="" explicitFocusOrder="0" pos="144 120 64 16" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
