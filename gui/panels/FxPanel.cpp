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

    addAndMakeVisible (lowFi_Active = new MouseOverKnob ("low fidelity active"));
    lowFi_Active->setRange (0, 1, 1);
    lowFi_Active->setSliderStyle (Slider::RotaryVerticalDrag);
    lowFi_Active->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    lowFi_Active->addListener (this);

    addAndMakeVisible (nBits_LowFi = new MouseOverKnob ("nBits Low Fi"));
    nBits_LowFi->setRange (1, 16, 1);
    nBits_LowFi->setSliderStyle (Slider::RotaryVerticalDrag);
    nBits_LowFi->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    nBits_LowFi->addListener (this);


    //[UserPreSize]
	registerSlider(lowFi_Active, &params.lowFiActivation);
	registerSlider(nBits_LowFi, &params.nBitsLowFi);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

FxPanel::~FxPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lowFi_Active = nullptr;
    nBits_LowFi = nullptr;


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

    lowFi_Active->setBounds (48, 24, 64, 64);
    nBits_LowFi->setBounds (144, 24, 64, 64);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void FxPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
	handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == lowFi_Active)
    {
        //[UserSliderCode_lowFi_Active] -- add your slider handling code here..
        //[/UserSliderCode_lowFi_Active]
    }
    else if (sliderThatWasMoved == nBits_LowFi)
    {
        //[UserSliderCode_nBits_LowFi] -- add your slider handling code here..
        //[/UserSliderCode_nBits_LowFi]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
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
  <SLIDER name="low fidelity active" id="221421ebd522cd9a" memberName="lowFi_Active"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="48 24 64 64"
          min="0" max="1" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="nBits Low Fi" id="c7728074cb4655d8" memberName="nBits_LowFi"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="144 24 64 64"
          min="1" max="16" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
