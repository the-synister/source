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
    ftune1->addListener (this);

    addAndMakeVisible (lfo1depth1 = new MouseOverKnob ("LFO depth 1"));
    lfo1depth1->setRange (0, 12, 0);
    lfo1depth1->setSliderStyle (Slider::RotaryVerticalDrag);
    lfo1depth1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    lfo1depth1->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    lfo1depth1->addListener (this);

    addAndMakeVisible (osc1trngAmount = new MouseOverKnob ("Osc1 Triangle Amount"));
    osc1trngAmount->setRange (0, 1, 0);
    osc1trngAmount->setSliderStyle (Slider::RotaryVerticalDrag);
    osc1trngAmount->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    osc1trngAmount->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    osc1trngAmount->addListener (this);

    addAndMakeVisible (pulsewidth = new MouseOverKnob ("Pulse Width"));
    pulsewidth->setRange (0.01, 0.99, 0);
    pulsewidth->setSliderStyle (Slider::RotaryVerticalDrag);
    pulsewidth->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    pulsewidth->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pulsewidth->addListener (this);

    addAndMakeVisible (pitchRange = new MouseOverKnob ("pitch range"));
    pitchRange->setRange (0, 12, 0);
    pitchRange->setSliderStyle (Slider::RotaryVerticalDrag);
    pitchRange->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    pitchRange->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    pitchRange->addListener (this);

    addAndMakeVisible (ctune1 = new MouseOverKnob ("coarse tune 1"));
    ctune1->setRange (-11, 11, 1);
    ctune1->setSliderStyle (Slider::RotaryVerticalDrag);
    ctune1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    ctune1->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    ctune1->setColour (Slider::textBoxTextColourId, Colours::white);
    ctune1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    ctune1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    ctune1->addListener (this);

    addAndMakeVisible (lfoFadeIn = new MouseOverKnob ("LFO Fade In"));
    lfoFadeIn->setRange (0, 10, 0);
    lfoFadeIn->setSliderStyle (Slider::RotaryVerticalDrag);
    lfoFadeIn->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    lfoFadeIn->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    lfoFadeIn->addListener (this);

    addAndMakeVisible (waveformVisual = new WaveformVisual (params.osc1Waveform.getStep(), params.osc1pulsewidth.get(), params.osc1trngAmount.get()));
    waveformVisual->setName ("Waveform Visual");

    addAndMakeVisible (waveformSwitch = new MouseOverKnob ("Waveform Switch"));
    waveformSwitch->setRange (0, 2, 1);
    waveformSwitch->setSliderStyle (Slider::LinearHorizontal);
    waveformSwitch->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    waveformSwitch->setColour (Slider::thumbColourId, Colour (0xff6c788c));
    waveformSwitch->setColour (Slider::trackColourId, Colours::white);
    waveformSwitch->addListener (this);
 
    addAndMakeVisible (amountWidthMod = new MouseOverKnob ("Amount width mod"));
    amountWidthMod->setRange (0, 1, 0);
    amountWidthMod->setSliderStyle (Slider::RotaryVerticalDrag);
    amountWidthMod->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    amountWidthMod->addListener (this);


    //[UserPreSize]
    // NOTE: test wise
    registerSaturnSource(ctune1, lfoFadeIn, &params.lfoFadein, 2);
    registerSaturnSource(ctune1, pitchRange, &params.osc1PitchRange, 2);
    registerSaturnSource(ctune1, lfo1depth1, &params.osc1lfo1depth, 1);

    registerSaturnSource(lfo1depth1, pitchRange, &params.osc1PitchRange, 1);
    registerSaturnSource(lfo1depth1, lfoFadeIn, &params.lfoFadein, 2);

    registerSlider(ftune1, &params.osc1fine);
    registerSlider(lfo1depth1, &params.osc1lfo1depth);
    registerSlider(osc1trngAmount, &params.osc1trngAmount, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(pitchRange, &params.osc1PitchRange);
    registerSlider(pulsewidth, &params.osc1pulsewidth, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(amountWidthMod, &params.osc1AmountWidthMod);
    registerSlider(ctune1, &params.osc1coarse);
    registerSlider(waveformSwitch, &params.osc1Waveform, std::bind(&OscPanel::updateWFShapeControls, this));
    registerSlider(lfoFadeIn, &params.lfoFadein);
    registerSlider(waveformSwitch, &params.osc1Waveform);
    lfoFadeIn->setSkewFactorFromMidPoint(1); // Sets the LFOFadeIn slider to logarithmic scale with value 1 in the middle of the slider

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    osc1trngAmount->setVisible(false);
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
    lfoFadeIn = nullptr;
    waveformVisual = nullptr;
    waveformSwitch = nullptr;
    amountWidthMod = nullptr;


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
    //[/UserPaint]
}

void OscPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    ftune1->setBounds (80, 8, 64, 64);
    lfo1depth1->setBounds (224, 8, 64, 64);
    osc1trngAmount->setBounds (296, 8, 64, 64);
    pulsewidth->setBounds (296, 8, 64, 64);
    pitchRange->setBounds (152, 8, 64, 64);
    ctune1->setBounds (8, 8, 64, 64);
    lfoFadeIn->setBounds (440, 8, 64, 64);
    waveformVisual->setBounds (24, 112, 208, 96);
    waveformSwitch->setBounds (360, 128, 64, 64);
    amountWidthMod->setBounds (368, 8, 64, 64);
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
    else if (sliderThatWasMoved == lfoFadeIn)
    {
        //[UserSliderCode_lfoFadeIn] -- add your slider handling code here..
        //[/UserSliderCode_lfoFadeIn]
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
  <BACKGROUND backgroundColour="ff6c788c"/>
  <SLIDER name="fine tune 1" id="3c32cde7173ddbe6" memberName="ftune1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="80 8 64 64"
          rotarysliderfill="ff6c788c" min="-100" max="100" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="LFO depth 1" id="523b9024be39c1b" memberName="lfo1depth1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="224 8 64 64"
          rotarysliderfill="ff6c788c" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc1 Triangle Amount" id="d81a0f8c69078b3c" memberName="osc1trngAmount"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="296 8 64 64"
          rotarysliderfill="ff6c788c" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Pulse Width" id="96badb5ea7640431" memberName="pulsewidth"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="296 8 64 64"
          rotarysliderfill="ff6c788c" min="0.01" max="0.98999999999999999"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="pitch range" id="29275125e377aaa" memberName="pitchRange"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="152 8 64 64"
          rotarysliderfill="ff6c788c" min="0" max="12" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="coarse tune 1" id="52a6628a22cee304" memberName="ctune1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 8 64 64"
          rotarysliderfill="ff6c788c" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="-11" max="11" int="1" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="LFO Fade In" id="16de18984b3c12ef" memberName="lfoFadeIn"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="440 8 64 64"
          rotarysliderfill="ff6c788c" min="0" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="Waveform Visual" id="dc40e7918cb34428" memberName="waveformVisual"
                    virtualName="WaveformVisual" explicitFocusOrder="0" pos="24 112 208 96"
                    class="Component" params="params.osc1Waveform.getStep(), params.osc1pulsewidth.get(), params.osc1trngAmount.get()"/>
  <SLIDER name="Waveform Switch" id="df460155fcb1ed38" memberName="waveformSwitch"
          virtualName="" explicitFocusOrder="0" pos="360 128 64 64" thumbcol="ff6c788c"
          trackcol="ffffffff" min="0" max="2" int="1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Saw Label" id="ae7ee66ce3b9c1ef" memberName="sawlabel"
         virtualName="" explicitFocusOrder="0" pos="360 104 150 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Saw wave" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="Square Label" id="390c269ec611617c" memberName="squarelabel"
         virtualName="" explicitFocusOrder="0" pos="256 152 96 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Square wave&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="Noise label" id="b40cd065bdc2086c" memberName="noiselabel"
         virtualName="" explicitFocusOrder="0" pos="433 152 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="White noise" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="Amount width mod" id="ea500ea6791045c2" memberName="amountWidthMod"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="368 8 64 64"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
