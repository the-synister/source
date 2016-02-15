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

#include "ClippingPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ClippingPanel::ClippingPanel (SynthParams &p)
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (clippingFactor = new MouseOverKnob ("Clipping Factor"));
    clippingFactor->setRange (0, 25, 0);
    clippingFactor->setSliderStyle (Slider::RotaryVerticalDrag);
    clippingFactor->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    clippingFactor->setColour (Slider::rotarySliderFillColourId, Colour (0xff2b3240));
    clippingFactor->addListener (this);

    addAndMakeVisible (onOffSwitch = new Slider ("clipping switch"));
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
	clippingFactor->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
	registerSlider(onOffSwitch, &params.clippingActivation, std::bind(&ClippingPanel::onOffSwitchChanged, this));
    registerSlider(clippingFactor, &params.clippingFactor);
    //[/UserPreSize]

    setSize (133, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ClippingPanel::~ClippingPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    clippingFactor = nullptr;
    onOffSwitch = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ClippingPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff2b3240));

    //[UserPaint] Add your own custom painting code here..
    drawGroupBorder(g, "clip", 0, 0,
                    this->getWidth(), this->getHeight() - 22, 25.0f, 20.0f, 5.0f, 3.0f, SynthParams::fxColour);
    //[/UserPaint]
}

void ClippingPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    clippingFactor->setBounds (32, 64, 64, 64);
    onOffSwitch->setBounds (9, 2, 47, 30);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ClippingPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == clippingFactor)
    {
        //[UserSliderCode_clippingFactor] -- add your slider handling code here..
        //[/UserSliderCode_clippingFactor]
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
void ClippingPanel::onOffSwitchChanged()
{
	clippingFactor->setEnabled((static_cast<int>(onOffSwitch->getValue()) == 1));
	onOffSwitch->setColour(Slider::trackColourId, ((onOffSwitch->getValue() == 1) ? SynthParams::onOffSwitchEnabled : SynthParams::onOffSwitchDisabled));
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ClippingPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="133"
                 initialHeight="200">
  <BACKGROUND backgroundColour="ff2b3240"/>
  <SLIDER name="Clipping Factor" id="3671e326d731f5ec" memberName="clippingFactor"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="32 64 64 64"
          rotarysliderfill="ff2b3240" min="0" max="25" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="clipping switch" id="f46e9c55275d8f7b" memberName="onOffSwitch"
          virtualName="" explicitFocusOrder="0" pos="9 2 47 30" thumbcol="ffdadada"
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
