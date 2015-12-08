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
    feedbackSlider->setRange (0, 100, 0);
    feedbackSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    feedbackSlider->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    feedbackSlider->addListener (this);

    addAndMakeVisible (dryWetSlider = new MouseOverKnob ("Wet"));
    dryWetSlider->setRange (0, 100, 0);
    dryWetSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    dryWetSlider->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    dryWetSlider->addListener (this);

    addAndMakeVisible (timeSlider = new MouseOverKnob ("Time"));
    timeSlider->setRange (1, 5000, 1);
    timeSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    timeSlider->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    timeSlider->addListener (this);
    timeSlider->setSkewFactor (0.33);

    addAndMakeVisible (syncToggle = new ToggleButton ("syncToggle1"));
    syncToggle->setButtonText (TRANS("Sync"));
    syncToggle->addListener (this);

    addAndMakeVisible (dividend = new ComboBox ("delayDividend"));
    dividend->setTooltip (TRANS("Dividend"));
    dividend->setEditableText (false);
    dividend->setJustificationType (Justification::centred);
    dividend->setTextWhenNothingSelected (TRANS("1"));
    dividend->setTextWhenNoChoicesAvailable (TRANS("1"));
    dividend->addItem (TRANS("1"), 1);
    dividend->addItem (TRANS("2"), 2);
    dividend->addItem (TRANS("3"), 3);
    dividend->addItem (TRANS("4"), 4);
    dividend->addListener (this);

    addAndMakeVisible (divisor = new ComboBox ("delayDivisor"));
    divisor->setTooltip (TRANS("Divisor"));
    divisor->setEditableText (false);
    divisor->setJustificationType (Justification::centred);
    divisor->setTextWhenNothingSelected (TRANS("1"));
    divisor->setTextWhenNoChoicesAvailable (TRANS("1"));
    divisor->addItem (TRANS("1"), 1);
    divisor->addItem (TRANS("2"), 2);
    divisor->addItem (TRANS("3"), 3);
    divisor->addItem (TRANS("4"), 4);
    divisor->addItem (TRANS("8"), 5);
    divisor->addItem (TRANS("16"), 6);
    divisor->addListener (this);

    addAndMakeVisible (cutoffSlider = new MouseOverKnob ("Cutoff"));
    cutoffSlider->setRange (1, 20000, 1);
    cutoffSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    cutoffSlider->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    cutoffSlider->addListener (this);
    cutoffSlider->setSkewFactor (0.33);

    addAndMakeVisible (resSlider = new MouseOverKnob ("Resonance"));
    resSlider->setRange (-25, 25, 1);
    resSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    resSlider->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    resSlider->addListener (this);
    resSlider->setSkewFactor (0.33);


    //[UserPreSize]
    registerSlider(feedbackSlider, &params.delayFeedback);
    registerSlider(dryWetSlider, &params.delayDryWet);
    registerSlider(timeSlider, &params.delayTime);
    registerSlider(resSlider, &params.delayResonance);
    registerSlider(cutoffSlider, &params.delayCutoff);
    divisor->setText(String("1"));
    dividend->setText(String("1"));
    dividend->setEnabled(false);
    divisor->setEnabled(false);

    //divisor->setTextWhenNothingSelected(String("1"));
    //divisor->setTextWhenNoChoicesAvailable(String("1"));
    //divisor->setTextWhenNothingSelected(String("1"));
    //divisor->setTextWhenNoChoicesAvailable(String("1"));

    dryWetSlider->setValue(params.delayDryWet.getUI());
    timeSlider->setValue(params.delayTime.getUI());
    feedbackSlider->setValue(params.delayFeedback.getUI());

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
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
    dividend = nullptr;
    divisor = nullptr;
    cutoffSlider = nullptr;
    resSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FxPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FxPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    feedbackSlider->setBounds (8, 8, 64, 64);
    dryWetSlider->setBounds (80, 8, 64, 64);
    timeSlider->setBounds (152, 8, 64, 64);
    syncToggle->setBounds (224, 8, 63, 24);
    dividend->setBounds (224, 32, 55, 16);
    divisor->setBounds (224, 56, 55, 16);
    cutoffSlider->setBounds (288, 8, 64, 64);
    resSlider->setBounds (360, 8, 64, 64);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void FxPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == feedbackSlider)
    {
        //[UserSliderCode_feedbackSlider] -- add your slider handling code here..
        params.delayFeedback.setUI(static_cast<float>(feedbackSlider->getValue()*0.01));
        //[/UserSliderCode_feedbackSlider]
    }
    else if (sliderThatWasMoved == dryWetSlider)
    {
        //[UserSliderCode_dryWetSlider] -- add your slider handling code here..
        params.delayDryWet.setUI(static_cast<float>(dryWetSlider->getValue()*0.01));
        //[/UserSliderCode_dryWetSlider]
    }
    else if (sliderThatWasMoved == timeSlider)
    {
        //[UserSliderCode_timeSlider] -- add your slider handling code here..
        params.delayTime.setUI(static_cast<float>(timeSlider->getValue()));
        //[/UserSliderCode_timeSlider]
    }
    else if (sliderThatWasMoved == cutoffSlider)
    {
        //[UserSliderCode_cutoffSlider] -- add your slider handling code here..
        params.delayCutoff.setUI(static_cast<float>(cutoffSlider->getValue()));
        //[/UserSliderCode_cutoffSlider]
    }
    else if (sliderThatWasMoved == resSlider)
    {
        //[UserSliderCode_resSlider] -- add your slider handling code here..
        params.delayResonance.setUI(static_cast<float>(resSlider->getValue()));
        //[/UserSliderCode_resSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void FxPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == syncToggle)
    {
        //[UserButtonCode_syncToggle] -- add your button handler code here..

        timeSlider->setEnabled(!timeSlider->isEnabled());
        dividend->setEnabled(!dividend->isEnabled());
        divisor->setEnabled(!divisor->isEnabled());

        if (divisor->isEnabled()) {
            params.delaySync.set(1.f);
            params.delayTime.set(params.delayTime.get() + 0.0000001f);
        }
        else {
            params.delaySync.set(0.f);
            timeSlider->setValue(params.delayTime.get());
            params.delayTime.setUI(static_cast<float>(params.delayTime.get()));
        }

        //[/UserButtonCode_syncToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void FxPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == dividend)
    {
        //[UserComboBoxCode_dividend] -- add your combo box handling code here..
        params.delayDividend.set(dividend->getText().getFloatValue());
        //[/UserComboBoxCode_dividend]
    }
    else if (comboBoxThatHasChanged == divisor)
    {
        //[UserComboBoxCode_divisor] -- add your combo box handling code here..
        params.delayDivisor.set(divisor->getText().getFloatValue());
        //[/UserComboBoxCode_divisor]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
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
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Feedback" id="9c0383d8383ea645" memberName="feedbackSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 8 64 64"
          min="0" max="100" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Wet" id="38a3801ec95e842b" memberName="dryWetSlider" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="80 8 64 64" min="0" max="100" int="0"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Time" id="5ac27dc9db375d94" memberName="timeSlider" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="152 8 64 64" min="1" max="5000" int="1"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.33000000000000002"/>
  <TOGGLEBUTTON name="syncToggle1" id="103062bcdc341811" memberName="syncToggle"
                virtualName="" explicitFocusOrder="0" pos="224 8 63 24" buttonText="Sync"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="delayDividend" id="f2c88d87f26bec88" memberName="dividend"
            virtualName="" explicitFocusOrder="0" pos="224 32 55 16" tooltip="Dividend"
            editable="0" layout="36" items="1&#10;2&#10;3&#10;4" textWhenNonSelected="1"
            textWhenNoItems="1"/>
  <COMBOBOX name="delayDivisor" id="182e27201e78c23e" memberName="divisor"
            virtualName="" explicitFocusOrder="0" pos="224 56 55 16" tooltip="Divisor"
            editable="0" layout="36" items="1&#10;2&#10;3&#10;4&#10;8&#10;16"
            textWhenNonSelected="1" textWhenNoItems="1"/>
  <SLIDER name="Cutoff" id="4e89be5035a6b485" memberName="cutoffSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="288 8 64 64"
          min="1" max="20000" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="0.33000000000000002"/>
  <SLIDER name="Resonance" id="b0842c8b86f33a2f" memberName="resSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="360 8 64 64"
          min="-25" max="25" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="0.33000000000000002"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
