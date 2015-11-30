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
FxPanel::FxPanel(SynthParams &p, FxDelay &d)
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    delay = &d;

    addAndMakeVisible(feedbackSlider = new MouseOverKnob("Feedback"));
    feedbackSlider->setRange(0, 100, 0);
    feedbackSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    feedbackSlider->setTextBoxStyle(Slider::TextBoxBelow, true, 80, 20);
    feedbackSlider->addListener(this);

    addAndMakeVisible(dryWetSlider = new MouseOverKnob("Wet"));
    dryWetSlider->setRange(0, 100, 0);
    dryWetSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    dryWetSlider->setTextBoxStyle(Slider::TextBoxBelow, true, 80, 20);
    dryWetSlider->addListener(this);

    addAndMakeVisible(timeSlider = new MouseOverKnob("Time"));
    timeSlider->setRange(1, 5000, 1);
    timeSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    timeSlider->setTextBoxStyle(Slider::TextBoxBelow, true, 80, 20);
    timeSlider->addListener(this);

    addAndMakeVisible(syncToggle = new ToggleButton("syncToggle1"));
    syncToggle->setButtonText(TRANS("Sync"));
    syncToggle->addListener(this);

    addAndMakeVisible(dividend = new ComboBox("new combo box"));
    dividend->setEditableText(false);
    dividend->setJustificationType(Justification::centred);
    dividend->setTextWhenNothingSelected(String("1"));
    dividend->setTextWhenNoChoicesAvailable(String("1"));
    dividend->addItem(TRANS("1"), 1);
    dividend->addItem(TRANS("2"), 2);
    dividend->addItem(TRANS("3"), 3);
    dividend->addItem(TRANS("4"), 4);
    dividend->addListener(this);

    addAndMakeVisible(divisor = new ComboBox("new combo box"));
    divisor->setEditableText(false);
    divisor->setJustificationType(Justification::centred);
    divisor->setTextWhenNothingSelected(String("1"));
    divisor->setTextWhenNoChoicesAvailable(String("1"));
    divisor->addItem(TRANS("1"), 1);
    divisor->addItem(TRANS("2"), 2);
    divisor->addItem(TRANS("3"), 3);
    divisor->addItem(TRANS("4"), 4);
    divisor->addItem(TRANS("8"), 5);
    divisor->addItem(TRANS("16"), 6);
    divisor->addListener(this);


    //[UserPreSize]
    registerSlider(feedbackSlider, &params.delayFeedback);
    registerSlider(dryWetSlider, &params.delayDryWet);
    registerSlider(timeSlider, &params.delayTime);
    divisor->setText(String("1"));
    dividend->setText(String("1"));
    dividend->setEnabled(false);
    divisor->setEnabled(false);

    dryWetSlider->setValue(params.delayDryWet.getUI());
    //dryWetSlider->setTextValueSuffix(String(" ") + params.delayDryWet.unit());
    timeSlider->setValue(params.delayTime.getUI());
    //timeSlider->setTextValueSuffix(String(" ") + params.delayTime.unit());
    feedbackSlider->setValue(params.delayFeedback.getUI());
    //feedbackSlider->setTextValueSuffix(String(" ") + params.delayFeedback.unit());

    //syncToggle

    //[/UserPreSize]

    setSize(600, 400);


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


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FxPanel::paint(Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll(Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FxPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    feedbackSlider->setBounds(8, 8, 64, 64);
    dryWetSlider->setBounds(80, 8, 64, 64);
    timeSlider->setBounds(152, 8, 64, 64);
    syncToggle->setBounds(224, 8, 63, 24);
    dividend->setBounds(224, 32, 55, 16);
    divisor->setBounds(224, 56, 55, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void FxPanel::sliderValueChanged(Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
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

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void FxPanel::buttonClicked(Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == syncToggle)
    {
        timeSlider->setEnabled(!timeSlider->isEnabled());
        dividend->setEnabled(!dividend->isEnabled());
        divisor->setEnabled(!divisor->isEnabled());

        if (!timeSlider->isEnabled()) {
            double newTimeValue = delay->calcDelayTime(dividend->getText().getDoubleValue(), divisor->getText().getDoubleValue(), params.bpm.get());

            if (newTimeValue > params.delayTime.getMax())
            {
                newTimeValue = params.delayTime.getMax();
                // ui feedback? blink?
            }
            else { params.delayTime.set(static_cast<float>(newTimeValue)); }
            timeSlider->setValue(params.delayTime.get());
        }
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void FxPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == dividend || comboBoxThatHasChanged == divisor)
    {
        double newTimeValue = delay->calcDelayTime(dividend->getText().getDoubleValue(), divisor->getText().getDoubleValue(), params.bpm.get());
        
        if (newTimeValue > params.delayTime.getMax())
        {
            newTimeValue = params.delayTime.getMax();
            // ui feedback? blink?
        }
        else{ params.delayTime.set(static_cast<float>(newTimeValue)); }
        timeSlider->setValue(params.delayTime.get());

        //if (syncToggle->getToggleState())
        //{
        //    double tmp = delay->calcDelayTime( dividend->getText().getDoubleValue(), );
        //    timeSlider->setValue(tmp);

        //    double newTimeValue;
        //    double bps = (params.positionInfo[0].bpm / 60.);
        //    double beatInMs = 1000 * (2. / bps) /* * (params.positionInfo[0].timeSigDenominator / params.positionInfo[0].timeSigNumerator)*/;

        //    double divTmp = dividend->getText().getDoubleValue();
        //    double divsorTmp = divisor->getText().getDoubleValue();

        //    newTimeValue = beatInMs * (divTmp / divsorTmp);

        //    if (newTimeValue > params.delayTime.getMax())
        //    {
        //        newTimeValue = params.delayTime.getMax();
        //        // ui feedback? blink?
        //    }
        //    params.delayTime.set(static_cast<float>(newTimeValue));
        //    timeSlider->setValue(params.delayTime.get());
        //}
    }
    else if (comboBoxThatHasChanged == divisor)
    {
        if (syncToggle->getToggleState())
        {

        }
    }
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
textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
<TOGGLEBUTTON name="syncToggle1" id="103062bcdc341811" memberName="syncToggle"
virtualName="" explicitFocusOrder="0" pos="224 8 63 24" buttonText="Sync"
connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
<COMBOBOX name="new combo box" id="f2c88d87f26bec88" memberName="dividend"
virtualName="" explicitFocusOrder="0" pos="224 32 55 16" editable="0"
layout="36" items="1&#10;2&#10;3&#10;4" textWhenNonSelected=""
textWhenNoItems=""/>
<COMBOBOX name="new combo box" id="182e27201e78c23e" memberName="divisor"
virtualName="" explicitFocusOrder="0" pos="224 56 55 16" editable="0"
layout="36" items="1&#10;2&#10;3&#10;4&#10;8&#10;16" textWhenNonSelected=""
textWhenNoItems=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
