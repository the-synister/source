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

#include "ChorusPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ChorusPanel::ChorusPanel (SynthParams &p)
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (chorDryWetSlider = new MouseOverKnob ("Chorus Dry / Wet"));
    chorDryWetSlider->setRange (0, 1, 0);
    chorDryWetSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    chorDryWetSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    chorDryWetSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xff2b3240));
    chorDryWetSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    chorDryWetSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    chorDryWetSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    chorDryWetSlider->addListener (this);

    addAndMakeVisible (chorDepthSlider = new MouseOverKnob ("Chorus Depth"));
    chorDepthSlider->setRange (5, 20, 0);
    chorDepthSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    chorDepthSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    chorDepthSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xff2b3240));
    chorDepthSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    chorDepthSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    chorDepthSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    chorDepthSlider->addListener (this);

    addAndMakeVisible (chorDelayLengthSlider = new MouseOverKnob ("Chorus Width"));
    chorDelayLengthSlider->setRange (0.025, 0.08, 0);
    chorDelayLengthSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    chorDelayLengthSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    chorDelayLengthSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xff2b3240));
    chorDelayLengthSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    chorDelayLengthSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    chorDelayLengthSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    chorDelayLengthSlider->addListener (this);

    addAndMakeVisible (chorModRateSlider = new MouseOverKnob ("Chorus Rate"));
    chorModRateSlider->setRange (0.1, 1.5, 0);
    chorModRateSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    chorModRateSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    chorModRateSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xff2b3240));
    chorModRateSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    chorModRateSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    chorModRateSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    chorModRateSlider->addListener (this);

    addAndMakeVisible (onOffSwitch = new Slider ("chorus switch"));
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
    registerSlider(chorDryWetSlider, &params.chorDryWet);
    registerSlider(chorDepthSlider, &params.chorModDepth);
    registerSlider(chorDelayLengthSlider, &params.chorDelayLength);
    registerSlider(chorModRateSlider, &params.chorModRate);
  	onOffSwitchChanged();
	registerSlider(onOffSwitch, &params.chorActivation, std::bind(&ChorusPanel::onOffSwitchChanged, this));
    //[/UserPreSize]

    setSize (200, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ChorusPanel::~ChorusPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    chorDryWetSlider = nullptr;
    chorDepthSlider = nullptr;
    chorDelayLengthSlider = nullptr;
    chorModRateSlider = nullptr;
    onOffSwitch = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ChorusPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff2b3240));

    //[UserPaint] Add your own custom painting code here..
    drawGroupBorder(g, "chor./flang.", 0, 0,
                    this->getWidth(), this->getHeight() - 22, 25.0f, 24.0f, 4.0f, 3.0f, 30, SynthParams::fxColour);
    //[/UserPaint]
}

void ChorusPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    chorDryWetSlider->setBounds (26, 35, 64, 64);
    chorDepthSlider->setBounds (112, 35, 64, 64);
    chorDelayLengthSlider->setBounds (26, 99, 64, 64);
    chorModRateSlider->setBounds (114, 99, 64, 64);
    onOffSwitch->setBounds (30, 1, 40, 30);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ChorusPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == chorDryWetSlider)
    {
        //[UserSliderCode_chorDryWetSlider] -- add your slider handling code here..
        //[/UserSliderCode_chorDryWetSlider]
    }
    else if (sliderThatWasMoved == chorDepthSlider)
    {
        //[UserSliderCode_chorDepthSlider] -- add your slider handling code here..
        //[/UserSliderCode_chorDepthSlider]
    }
    else if (sliderThatWasMoved == chorDelayLengthSlider)
    {
        //[UserSliderCode_chorDelayLengthSlider] -- add your slider handling code here..
        //[/UserSliderCode_chorDelayLengthSlider]
    }
    else if (sliderThatWasMoved == chorModRateSlider)
    {
        //[UserSliderCode_chorModRateSlider] -- add your slider handling code here..
        //[/UserSliderCode_chorModRateSlider]
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
void ChorusPanel::onOffSwitchChanged()
{
	chorDelayLengthSlider->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
	chorDepthSlider->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
	chorDryWetSlider->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
	chorModRateSlider->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
	onOffSwitch->setColour(Slider::trackColourId, ((onOffSwitch->getValue() == 1) ? SynthParams::onOffSwitchEnabled : SynthParams::onOffSwitchDisabled));
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ChorusPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="200"
                 initialHeight="200">
  <BACKGROUND backgroundColour="ff2b3240"/>
  <SLIDER name="Chorus Dry / Wet" id="d1b572a8e8671301" memberName="chorDryWetSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="26 35 64 64"
          rotarysliderfill="ff2b3240" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Chorus Depth" id="d8e8d503fe1af0f3" memberName="chorDepthSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="112 35 64 64"
          rotarysliderfill="ff2b3240" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="5" max="20" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Chorus Width" id="16cb41f7d7598aa9" memberName="chorDelayLengthSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="26 99 64 64"
          rotarysliderfill="ff2b3240" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.025000000000000001" max="0.080000000000000002"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Chorus Rate" id="ec42991e35f3fab6" memberName="chorModRateSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="114 99 64 64"
          rotarysliderfill="ff2b3240" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0.10000000000000001" max="1.5" int="0"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="chorus switch" id="f46e9c55275d8f7b" memberName="onOffSwitch"
          virtualName="" explicitFocusOrder="0" pos="30 1 40 30" thumbcol="ffdadada"
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
