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

#include "FxPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
FxPanel::FxPanel (SynthParams &p)
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (feedbackSlider = new MouseOverKnob ("Feedback"));
    feedbackSlider->setRange (0, 1, 0);
    feedbackSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    feedbackSlider->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    feedbackSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xff2b3240));
    feedbackSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    feedbackSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    feedbackSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    feedbackSlider->addListener (this);

    addAndMakeVisible (dryWetSlider = new MouseOverKnob ("Wet"));
    dryWetSlider->setRange (0, 1, 0);
    dryWetSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    dryWetSlider->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    dryWetSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xff2b3240));
    dryWetSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    dryWetSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    dryWetSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    dryWetSlider->addListener (this);

    addAndMakeVisible (timeSlider = new MouseOverKnob ("Time"));
    timeSlider->setRange (1, 5000, 1);
    timeSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    timeSlider->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    timeSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xff2b3240));
    timeSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    timeSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    timeSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    timeSlider->addListener (this);
    timeSlider->setSkewFactor (0.33);

    addAndMakeVisible (syncToggle = new ToggleButton ("syncToggle1"));
    syncToggle->setButtonText (String::empty);
    syncToggle->addListener (this);
    syncToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (divisor = new IncDecDropDown ("delayDivisor"));
    divisor->setTooltip (TRANS("Divisor"));
    divisor->setEditableText (false);
    divisor->setJustificationType (Justification::centred);
    divisor->setTextWhenNothingSelected (TRANS("4"));
    divisor->setTextWhenNoChoicesAvailable (TRANS("4"));
    divisor->addItem (TRANS("1/1"), 1);
    divisor->addItem (TRANS("1/2"), 2);
    divisor->addItem (TRANS("1/4"), 3);
    divisor->addItem (TRANS("1/8"), 4);
    divisor->addItem (TRANS("1/16"), 5);
    divisor->addItem (TRANS("1/32"), 6);
    divisor->addItem (TRANS("1/64"), 7);
    divisor->addListener (this);

    addAndMakeVisible (cutoffSlider = new MouseOverKnob ("Cutoff"));
    cutoffSlider->setRange (1, 20000, 1);
    cutoffSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    cutoffSlider->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    cutoffSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xff2b3240));
    cutoffSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    cutoffSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    cutoffSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    cutoffSlider->addListener (this);
    cutoffSlider->setSkewFactor (0.33);

    addAndMakeVisible (tripTggl = new ToggleButton ("tripTggl1"));
    tripTggl->setButtonText (String::empty);
    tripTggl->addListener (this);
    tripTggl->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (filtTggl = new ToggleButton ("filtTggl1"));
    filtTggl->setButtonText (TRANS("rec cutoff"));
    filtTggl->addListener (this);
    filtTggl->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (revTggl = new ToggleButton ("revTggl"));
    revTggl->setButtonText (String::empty);
    revTggl->addListener (this);
    revTggl->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (onOffSwitch = new Slider ("delay switch"));
    onOffSwitch->setRange (0, 1, 1);
    onOffSwitch->setSliderStyle (Slider::LinearHorizontal);
    onOffSwitch->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    onOffSwitch->setColour (Slider::thumbColourId, Colour (0xffdadada));
    onOffSwitch->setColour (Slider::trackColourId, Colour (0xff666666));
    onOffSwitch->setColour (Slider::rotarySliderFillColourId, Colours::white);
    onOffSwitch->setColour (Slider::rotarySliderOutlineColourId, Colour (0xfff20000));
    onOffSwitch->setColour (Slider::textBoxBackgroundColourId, Colour (0xfffff4f4));
    onOffSwitch->addListener (this);

    addAndMakeVisible (dottedNotes = new ToggleButton ("dottedNotes"));
    dottedNotes->setButtonText (TRANS("dot"));
    dottedNotes->addListener (this);
    dottedNotes->setColour (ToggleButton::textColourId, Colours::white);


    //[UserPreSize]
    registerSlider(feedbackSlider, &params.delayFeedback);
    registerSlider(dryWetSlider, &params.delayDryWet);
    registerSlider(timeSlider, &params.delayTime);
	registerSlider(cutoffSlider, &params.delayCutoff);
	registerSlider(onOffSwitch, &params.delayActivation , std::bind(&FxPanel::onOffSwitchChanged, this));

    registerToggle(revTggl, &params.delayReverse);
    registerToggle(filtTggl, &params.delayRecordFilter);
    registerToggle(syncToggle, &params.delaySync, std::bind(&FxPanel::updateToggleState, this));
    registerToggle(tripTggl, &params.delayTriplet);
    registerToggle(dottedNotes, &params.delayDottedLength);

    registerNoteLength(divisor, &params.delayDivisor);

    onOffSwitchChanged();
    //[/UserPreSize]

    setSize (330, 200);


    //[Constructor] You can add your own custom stuff here..
    syncPic = ImageCache::getFromMemory(BinaryData::tempoSync_png, BinaryData::tempoSync_pngSize);
    tripletPic = ImageCache::getFromMemory(BinaryData::triplets_png, BinaryData::triplets_pngSize);
    reversePic = ImageCache::getFromMemory(BinaryData::delayReverse_png, BinaryData::delayReverse_pngSize);
    syncPicOff = ImageCache::getFromMemory(BinaryData::tempoSync_png, BinaryData::tempoSync_pngSize);
    tripletPicOff = ImageCache::getFromMemory(BinaryData::triplets_png, BinaryData::triplets_pngSize);
    reversePicOff = ImageCache::getFromMemory(BinaryData::delayReverse_png, BinaryData::delayReverse_pngSize);
    syncPicOff.duplicateIfShared();
    tripletPicOff.duplicateIfShared();
    reversePicOff.duplicateIfShared();
    syncPicOff.multiplyAllAlphas(0.5f);
    tripletPicOff.multiplyAllAlphas(0.5f);
    reversePicOff.multiplyAllAlphas(0.5f);
    //[/Constructor]
}

FxPanel::~FxPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    feedbackSlider = nullptr;
    dryWetSlider = nullptr;
    timeSlider = nullptr;
    syncToggle = nullptr;
    divisor = nullptr;
    cutoffSlider = nullptr;
    tripTggl = nullptr;
    filtTggl = nullptr;
    revTggl = nullptr;
    onOffSwitch = nullptr;
    dottedNotes = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FxPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff2b3240));

    //[UserPaint] Add your own custom painting code here..
    drawGroupBorder(g, "delay", 0, 0,
                    this->getWidth(), this->getHeight() - 22, 25.0f, 20.0f, 5.0f, 3.0f, SynthParams::fxColour);
    drawPics(g, syncToggle, tripTggl, revTggl);
    //[/UserPaint]
}

void FxPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    feedbackSlider->setBounds (173, 38, 64, 64);
    dryWetSlider->setBounds (17, 38, 64, 64);
    timeSlider->setBounds (95, 38, 64, 64);
    syncToggle->setBounds (39, 102, 65, 30);
    divisor->setBounds (26, 138, 85, 24);
    cutoffSlider->setBounds (251, 38, 64, 64);
    tripTggl->setBounds (122, 102, 65, 30);
    filtTggl->setBounds (214, 138, 100, 30);
    revTggl->setBounds (214, 102, 65, 30);
    onOffSwitch->setBounds (17, 2, 40, 30);
    dottedNotes->setBounds (122, 138, 64, 30);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void FxPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == feedbackSlider)
    {
        //[UserSliderCode_feedbackSlider] -- add your slider handling code here..
        //[/UserSliderCode_feedbackSlider]
    }
    else if (sliderThatWasMoved == dryWetSlider)
    {
        //[UserSliderCode_dryWetSlider] -- add your slider handling code here..
        //[/UserSliderCode_dryWetSlider]
    }
    else if (sliderThatWasMoved == timeSlider)
    {
        //[UserSliderCode_timeSlider] -- add your slider handling code here..
        //[/UserSliderCode_timeSlider]
    }
    else if (sliderThatWasMoved == cutoffSlider)
    {
        //[UserSliderCode_cutoffSlider] -- add your slider handling code here..
        //[/UserSliderCode_cutoffSlider]
    }
    else if (sliderThatWasMoved == onOffSwitch)
    {
        //[UserSliderCode_onOffSwitch] -- add your slider handling code here..
        //[/UserSliderCode_onOffSwitch]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void FxPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    handleToggle(buttonThatWasClicked);
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == syncToggle)
    {
        //[UserButtonCode_syncToggle] -- add your button handler code here..
        //[/UserButtonCode_syncToggle]
    }
    else if (buttonThatWasClicked == tripTggl)
    {
        //[UserButtonCode_tripTggl] -- add your button handler code here..
        //[/UserButtonCode_tripTggl]
    }
    else if (buttonThatWasClicked == filtTggl)
    {
        //[UserButtonCode_filtTggl] -- add your button handler code here..
        //[/UserButtonCode_filtTggl]
    }
    else if (buttonThatWasClicked == revTggl)
    {
        //[UserButtonCode_revTggl] -- add your button handler code here..
        //[/UserButtonCode_revTggl]
    }
    else if (buttonThatWasClicked == dottedNotes)
    {
        //[UserButtonCode_dottedNotes] -- add your button handler code here..
        //[/UserButtonCode_dottedNotes]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void FxPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    handleNoteLength(comboBoxThatHasChanged);
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == divisor)
    {
        //[UserComboBoxCode_divisor] -- add your combo box handling code here..
        //[/UserComboBoxCode_divisor]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void FxPanel::updateToggleState()
{
    timeSlider->setEnabled(!(params.delaySync.getStep() == eOnOffToggle::eOn) && (static_cast<int>(onOffSwitch->getValue()) == 1));
    tripTggl->setEnabled(params.delaySync.getStep() == eOnOffToggle::eOn && (static_cast<int>(onOffSwitch->getValue()) == 1));
    dottedNotes->setEnabled(params.delaySync.getStep() == eOnOffToggle::eOn && (static_cast<int>(onOffSwitch->getValue()) == 1));
    divisor->setEnabled(params.delaySync.getStep() == eOnOffToggle::eOn);

    if (divisor->isEnabled()) {
        params.delayTime.set(params.delayTime.get() + 0.0000001f); //dirty hack
        params.delayTime.set(params.delayTime.get() - 0.0000001f); //dirty hack
    }
    else {
        timeSlider->setValue(params.delayTime.get());
        params.delayTime.setUI(static_cast<float>(params.delayTime.get()));
    }
}

void FxPanel::onOffSwitchChanged()
{
	// Switches that don't depend on syncToggle
	feedbackSlider->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
	dryWetSlider->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
	cutoffSlider->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
	syncToggle->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
	revTggl->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
    filtTggl->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));

	// If delay is on, these sliders depend on syncToggle
	if (static_cast<int>(onOffSwitch->getValue()) == 1)
	{
		timeSlider->setEnabled(params.delaySync.getStep() == eOnOffToggle::eOff);
		divisor->setEnabled(params.delaySync.getStep() == eOnOffToggle::eOn);
        tripTggl->setEnabled(params.delaySync.getStep() == eOnOffToggle::eOn);
        dottedNotes->setEnabled(params.delaySync.getStep() == eOnOffToggle::eOn);
    }
	// If delay is off, all the sliders are disabled
	else
	{
		timeSlider->setEnabled(0);
		divisor->setEnabled(0);
		tripTggl->setEnabled(0);
        dottedNotes->setEnabled(0);
	}

	onOffSwitch->setColour(Slider::trackColourId, ((onOffSwitch->getValue() == 1) ? SynthParams::onOffSwitchEnabled : SynthParams::onOffSwitchDisabled));
}

void FxPanel::drawPics(Graphics& g, ScopedPointer<ToggleButton>& syncT, ScopedPointer<ToggleButton>& tripletT, ScopedPointer<ToggleButton>& reverseT)
{
    g.drawImageWithin(syncT->isEnabled()? syncPic : syncPicOff, syncT->getX() + 22, syncT->getY() + syncT->getHeight() / 2 - 12, 34, 23, Justification::centred); // 34x23
    g.drawImageWithin(tripletT->isEnabled()? tripletPic : tripletPicOff, tripletT->getX() + 22, tripletT->getY() + tripletT->getHeight() / 2 - 15, 39, 30, Justification::centred); // 39x30
    g.drawImageWithin(reverseT->isEnabled()? reversePic : reversePicOff, reverseT->getX() + 22, reverseT->getY() + reverseT->getHeight() / 2 - 14, 29, 26, Justification::centred); // 29x26
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="FxPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="330"
                 initialHeight="200">
  <BACKGROUND backgroundColour="ff2b3240"/>
  <SLIDER name="Feedback" id="9c0383d8383ea645" memberName="feedbackSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="173 38 64 64"
          rotarysliderfill="ff2b3240" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Wet" id="38a3801ec95e842b" memberName="dryWetSlider" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="17 38 64 64" rotarysliderfill="ff2b3240"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="ffffff"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Time" id="5ac27dc9db375d94" memberName="timeSlider" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="95 38 64 64" rotarysliderfill="ff2b3240"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="ffffff"
          min="1" max="5000" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="0.33000000000000002"/>
  <TOGGLEBUTTON name="syncToggle1" id="103062bcdc341811" memberName="syncToggle"
                virtualName="" explicitFocusOrder="0" pos="39 102 65 30" txtcol="ffffffff"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <COMBOBOX name="delayDivisor" id="182e27201e78c23e" memberName="divisor"
            virtualName="IncDecDropDown" explicitFocusOrder="0" pos="26 138 85 24"
            tooltip="Divisor" editable="0" layout="36" items="1/1&#10;1/2&#10;1/4&#10;1/8&#10;1/16&#10;1/32&#10;1/64"
            textWhenNonSelected="4" textWhenNoItems="4"/>
  <SLIDER name="Cutoff" id="4e89be5035a6b485" memberName="cutoffSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="251 38 64 64"
          rotarysliderfill="ff2b3240" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="1" max="20000" int="1" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="0.33000000000000002"/>
  <TOGGLEBUTTON name="tripTggl1" id="805f456c4a709e07" memberName="tripTggl"
                virtualName="" explicitFocusOrder="0" pos="122 102 65 30" txtcol="ffffffff"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="filtTggl1" id="14d5d3ba9ac30e1f" memberName="filtTggl"
                virtualName="" explicitFocusOrder="0" pos="214 138 100 30" txtcol="ffffffff"
                buttonText="rec cutoff" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="revTggl" id="abad5a425656f18e" memberName="revTggl" virtualName=""
                explicitFocusOrder="0" pos="214 102 65 30" txtcol="ffffffff"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <SLIDER name="delay switch" id="f46e9c55275d8f7b" memberName="onOffSwitch"
          virtualName="" explicitFocusOrder="0" pos="17 2 40 30" thumbcol="ffdadada"
          trackcol="ff666666" rotarysliderfill="ffffffff" rotaryslideroutline="fff20000"
          textboxbkgd="fffff4f4" min="0" max="1" int="1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="dottedNotes" id="ef5b938fe294c4b4" memberName="dottedNotes"
                virtualName="" explicitFocusOrder="0" pos="122 138 64 30" txtcol="ffffffff"
                buttonText="dot" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
