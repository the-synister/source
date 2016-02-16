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

#include "LfoPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
LfoPanel::LfoPanel (SynthParams &p, int lfoNumber)
    : PanelBase(p),
      lfo(p.lfo[lfoNumber])
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (freq = new MouseOverKnob ("LFO freq"));
    freq->setRange (0.01, 50, 0);
    freq->setSliderStyle (Slider::RotaryVerticalDrag);
    freq->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    freq->setColour (Slider::rotarySliderFillColourId, Colour (0xff855050));
    freq->setColour (Slider::textBoxTextColourId, Colours::white);
    freq->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    freq->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    freq->addListener (this);

    addAndMakeVisible (wave = new Slider ("wave switch"));
    wave->setRange (0, 2, 1);
    wave->setSliderStyle (Slider::LinearHorizontal);
    wave->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    wave->setColour (Slider::thumbColourId, Colour (0xff855050));
    wave->setColour (Slider::trackColourId, Colours::white);
    wave->addListener (this);

    addAndMakeVisible (tempoSyncSwitch = new ToggleButton ("tempoSyncSwitch"));
    tempoSyncSwitch->setButtonText (String::empty);
    tempoSyncSwitch->addListener (this);
    tempoSyncSwitch->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (lfoFadeIn = new MouseOverKnob ("LFO Fade In"));
    lfoFadeIn->setRange (0, 10, 0);
    lfoFadeIn->setSliderStyle (Slider::RotaryVerticalDrag);
    lfoFadeIn->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    lfoFadeIn->setColour (Slider::rotarySliderFillColourId, Colour (0xff855050));
    lfoFadeIn->setColour (Slider::textBoxTextColourId, Colours::white);
    lfoFadeIn->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    lfoFadeIn->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    lfoFadeIn->addListener (this);

    addAndMakeVisible (triplets = new ToggleButton ("triplets"));
    triplets->setButtonText (String::empty);
    triplets->addListener (this);
    triplets->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (noteLength = new IncDecDropDown ("note length"));
    noteLength->setEditableText (false);
    noteLength->setJustificationType (Justification::centred);
    noteLength->setTextWhenNothingSelected (TRANS("Note Length"));
    noteLength->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    noteLength->addItem (TRANS("1/1"), 1);
    noteLength->addItem (TRANS("1/2"), 2);
    noteLength->addItem (TRANS("1/4"), 3);
    noteLength->addItem (TRANS("1/8"), 4);
    noteLength->addItem (TRANS("1/16"), 5);
    noteLength->addItem (TRANS("1/32"), 6);
    noteLength->addListener (this);

    addAndMakeVisible (freqModAmount1 = new MouseOverKnob ("freqModAmount1"));
    freqModAmount1->setRange (0, 8, 0);
    freqModAmount1->setSliderStyle (Slider::RotaryVerticalDrag);
    freqModAmount1->setTextBoxStyle (Slider::TextBoxBelow, false, 0, 0);
    freqModAmount1->setColour (Slider::rotarySliderFillColourId, Colours::white);
    freqModAmount1->setColour (Slider::textBoxTextColourId, Colours::white);
    freqModAmount1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    freqModAmount1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    freqModAmount1->addListener (this);

    addAndMakeVisible (freqModAmount2 = new MouseOverKnob ("freqModAmount2"));
    freqModAmount2->setRange (0, 8, 0);
    freqModAmount2->setSliderStyle (Slider::RotaryVerticalDrag);
    freqModAmount2->setTextBoxStyle (Slider::TextBoxBelow, false, 0, 0);
    freqModAmount2->setColour (Slider::rotarySliderFillColourId, Colours::white);
    freqModAmount2->setColour (Slider::textBoxTextColourId, Colours::white);
    freqModAmount2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    freqModAmount2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    freqModAmount2->addListener (this);

    addAndMakeVisible (freqModSrc1 = new ComboBox ("freqModSrc1"));
    freqModSrc1->setEditableText (false);
    freqModSrc1->setJustificationType (Justification::centred);
    freqModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    freqModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    freqModSrc1->addListener (this);

    addAndMakeVisible (freqModSrc2 = new ComboBox ("freqModSrc2"));
    freqModSrc2->setEditableText (false);
    freqModSrc2->setJustificationType (Justification::centred);
    freqModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    freqModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    freqModSrc2->addListener (this);

    addAndMakeVisible (lfoGain = new ComboBox ("lfoGain"));
    lfoGain->setEditableText (false);
    lfoGain->setJustificationType (Justification::centred);
    lfoGain->setTextWhenNothingSelected (TRANS("No Mod"));
    lfoGain->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    lfoGain->addListener (this);


    //[UserPreSize]
    registerSaturnSource(freq, freqModAmount1, &lfo.freqModSrc1, &lfo.freqModAmount1, 1, MouseOverKnob::modAmountConversion::octToFreq);
    registerSaturnSource(freq, freqModAmount2, &lfo.freqModSrc2, &lfo.freqModAmount2, 2, MouseOverKnob::modAmountConversion::octToFreq);

    registerSlider(freq, &lfo.freq);
    registerSlider(wave, &lfo.wave);
    registerSlider(lfoFadeIn, &lfo.fadeIn);
    registerSlider(freqModAmount1, &lfo.freqModAmount1);
    registerSlider(freqModAmount2, &lfo.freqModAmount2);

    freq->setSkewFactorFromMidPoint(lfo.freq.getDefault());
    wave->setValue(lfo.wave.getUI());
    tempoSyncSwitch->setToggleState(0, dontSendNotification);
    noteLength->setText(getNoteLengthAsString(), dontSendNotification);
    registerDropdown(noteLength, &lfo.noteLength);

    lfoFadeIn->setSkewFactorFromMidPoint(1); // Sets the LFOFadeIn slider to logarithmic scale with value 1 in the middle of the slider

    lfoGain->setColour(ComboBox::ColourIds::backgroundColourId, SynthParams::lfoColour);

    fillModsourceBox(freqModSrc1);
    fillModsourceBox(freqModSrc2);
    registerCombobox(freqModSrc1, &lfo.freqModSrc1, {freq, nullptr, nullptr});
    registerCombobox(freqModSrc2, &lfo.freqModSrc2, {freq, nullptr, nullptr});
    fillModsourceBox(lfoGain);
    registerCombobox(lfoGain, &lfo.gainModSrc);

    noteLength->setEnabled(false);
    //[/UserPreSize]

    setSize (267, 197);


    //[Constructor] You can add your own custom stuff here..
    sineWave = ImageCache::getFromMemory(BinaryData::lfoSineWave_png, BinaryData::lfoSineWave_pngSize);
    squareWave = ImageCache::getFromMemory(BinaryData::lfoSquareWave_png, BinaryData::lfoSquareWave_pngSize);
    sampleHold = ImageCache::getFromMemory(BinaryData::lfoSampleHold_png, BinaryData::lfoSampleHold_pngSize);
    gainSign = ImageCache::getFromMemory(BinaryData::lfoGain_png, BinaryData::lfoGain_pngSize);
    syncPic = ImageCache::getFromMemory(BinaryData::tempoSync_png, BinaryData::tempoSync_pngSize);
    tripletPic = ImageCache::getFromMemory(BinaryData::triplets_png, BinaryData::triplets_pngSize);
    //[/Constructor]
}

LfoPanel::~LfoPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    freq = nullptr;
    wave = nullptr;
    tempoSyncSwitch = nullptr;
    lfoFadeIn = nullptr;
    triplets = nullptr;
    noteLength = nullptr;
    freqModAmount1 = nullptr;
    freqModAmount2 = nullptr;
    freqModSrc1 = nullptr;
    freqModSrc2 = nullptr;
    lfoGain = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LfoPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff855050));

    //[UserPaint] Add your own custom painting code here..
    drawGroupBorder(g, lfo.name, 0, 0,
                    this->getWidth(), this->getHeight() - 22, 25.0f, 20.0f, 5.0f, 3.0f, SynthParams::lfoColour);
    drawPics(g, wave, lfoGain, tempoSyncSwitch, triplets);
    //[/UserPaint]
}

void LfoPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    freq->setBounds (10, 35, 64, 64);
    wave->setBounds (168, 58, 60, 24);
    tempoSyncSwitch->setBounds (85, 100, 64, 30);
    lfoFadeIn->setBounds (10, 97, 64, 64);
    triplets->setBounds (175, 100, 64, 30);
    noteLength->setBounds (122, 135, 87, 24);
    freqModAmount1->setBounds (67, 35, 18, 18);
    freqModAmount2->setBounds (67, 59, 18, 18);
    freqModSrc1->setBounds (90, 35, 40, 18);
    freqModSrc2->setBounds (90, 59, 40, 18);
    lfoGain->setBounds (100, 6, 40, 18);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void LfoPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == freq)
    {
        //[UserSliderCode_freq] -- add your slider handling code here..
        //[/UserSliderCode_freq]
    }
    else if (sliderThatWasMoved == wave)
    {
        //[UserSliderCode_wave] -- add your slider handling code here..
        //[/UserSliderCode_wave]
    }
    else if (sliderThatWasMoved == lfoFadeIn)
    {
        //[UserSliderCode_lfoFadeIn] -- add your slider handling code here..
        //[/UserSliderCode_lfoFadeIn]
    }
    else if (sliderThatWasMoved == freqModAmount1)
    {
        //[UserSliderCode_freqModAmount1] -- add your slider handling code here..
        //[/UserSliderCode_freqModAmount1]
    }
    else if (sliderThatWasMoved == freqModAmount2)
    {
        //[UserSliderCode_freqModAmount2] -- add your slider handling code here..
        //[/UserSliderCode_freqModAmount2]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void LfoPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == tempoSyncSwitch)
    {
        //[UserButtonCode_tempoSyncSwitch] -- add your button handler code here..
        lfo.tempSync.setUI(tempoSyncSwitch->getToggleState());
        if (lfo.tempSync.getStep() == eOnOffToggle::eOn){
            freq->setEnabled(false);
            noteLength->setEnabled(true);
        }else{
            freq->setEnabled(true);
            noteLength->setEnabled(false);
        }
        //params.lfo1TempSync.setUI(std::round(static_cast<float>(tempoSyncSwitch->getToggleState())));
        //[/UserButtonCode_tempoSyncSwitch]
    }
    else if (buttonThatWasClicked == triplets)
    {
        //[UserButtonCode_triplets] -- add your button handler code here..
        //[/UserButtonCode_triplets]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void LfoPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    handleCombobox(comboBoxThatHasChanged);
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == noteLength)
    {
        //[UserComboBoxCode_noteLength] -- add your combo box handling code here..
        //[/UserComboBoxCode_noteLength]
    }
    else if (comboBoxThatHasChanged == freqModSrc1)
    {
        //[UserComboBoxCode_freqModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_freqModSrc1]
    }
    else if (comboBoxThatHasChanged == freqModSrc2)
    {
        //[UserComboBoxCode_freqModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_freqModSrc2]
    }
    else if (comboBoxThatHasChanged == lfoGain)
    {
        //[UserComboBoxCode_lfoGain] -- add your combo box handling code here..
        //[/UserComboBoxCode_lfoGain]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
String LfoPanel::getNoteLengthAsString()
{
    return "1/" + String(lfo.noteLength.getUI());
}

void LfoPanel::drawPics(Graphics& g, ScopedPointer<Slider>& _waveformSwitch, ScopedPointer<ComboBox>& _gainBox, ScopedPointer<ToggleButton>& syncT, ScopedPointer<ToggleButton>& tripletT)
{
    int centerX = _waveformSwitch->getX() + _waveformSwitch->getWidth() / 2;
    int centerY = _waveformSwitch->getY() + _waveformSwitch->getHeight() / 2;

    g.drawImageWithin(sineWave, _waveformSwitch->getX() - 20, centerY - 8, 19, 16, RectanglePlacement::centred); //19x16
    g.drawImageWithin(squareWave, centerX - 9, _waveformSwitch->getY() - 15, 17, 15, RectanglePlacement::centred); // 17x15
    g.drawImageWithin(sampleHold, _waveformSwitch->getX() + _waveformSwitch->getWidth() + 1, centerY - 5, 14, 11, RectanglePlacement::centred);// 14x11

    g.drawImageWithin(gainSign, _gainBox->getX() - 19, _gainBox->getY() + _gainBox->getHeight() / 2 - 8, 17, 17, RectanglePlacement::centred); // 17x17
    g.drawImageWithin(syncPic, syncT->getX() + 22, syncT->getY() + syncT->getHeight() / 2 - 12, 34, 23, Justification::centred); // 34x23
    g.drawImageWithin(tripletPic, tripletT->getX() + 22, tripletT->getY() + tripletT->getHeight() / 2 - 15, 39, 30, Justification::centred); // 39x30
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="LfoPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p, int lfoNumber"
                 variableInitialisers="PanelBase(p),&#10;lfo(p.lfo[lfoNumber])"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="267" initialHeight="197">
  <BACKGROUND backgroundColour="ff855050"/>
  <SLIDER name="LFO freq" id="d136f7fae1b8db84" memberName="freq" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="10 35 64 64" rotarysliderfill="ff855050"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="ffffff"
          min="0.01" max="50" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="wave switch" id="221421ebd522cd9a" memberName="wave" virtualName="Slider"
          explicitFocusOrder="0" pos="168 58 60 24" thumbcol="ff855050"
          trackcol="ffffffff" min="0" max="2" int="1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="tempoSyncSwitch" id="79c4ab6638da99ef" memberName="tempoSyncSwitch"
                virtualName="" explicitFocusOrder="0" pos="85 100 64 30" txtcol="ffffffff"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <SLIDER name="LFO Fade In" id="16de18984b3c12ef" memberName="lfoFadeIn"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="10 97 64 64"
          rotarysliderfill="ff855050" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="triplets" id="9c9e2393225a5b09" memberName="triplets" virtualName=""
                explicitFocusOrder="0" pos="175 100 64 30" txtcol="ffffffff"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <COMBOBOX name="note length" id="9cc1e82a498c26a7" memberName="noteLength"
            virtualName="IncDecDropDown" explicitFocusOrder="0" pos="122 135 87 24"
            editable="0" layout="36" items="1/1&#10;1/2&#10;1/4&#10;1/8&#10;1/16&#10;1/32"
            textWhenNonSelected="Note Length" textWhenNoItems="(no choices)"/>
  <SLIDER name="freqModAmount1" id="ea500ea6791045c2" memberName="freqModAmount1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="67 35 18 18"
          rotarysliderfill="ffffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="8" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="0"
          textBoxHeight="0" skewFactor="1"/>
  <SLIDER name="freqModAmount2" id="ae5c9ce50e2de7e1" memberName="freqModAmount2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="67 59 18 18"
          rotarysliderfill="ffffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="8" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="0"
          textBoxHeight="0" skewFactor="1"/>
  <COMBOBOX name="freqModSrc1" id="928cd04bb7b23ab9" memberName="freqModSrc1"
            virtualName="" explicitFocusOrder="0" pos="90 35 40 18" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="freqModSrc2" id="455e48a25414a454" memberName="freqModSrc2"
            virtualName="" explicitFocusOrder="0" pos="90 59 40 18" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="lfoGain" id="3c7a245d6d4ecf90" memberName="lfoGain" virtualName=""
            explicitFocusOrder="0" pos="100 6 40 18" editable="0" layout="36"
            items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
