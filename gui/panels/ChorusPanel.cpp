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
    chorDryWetSlider->addListener (this);

    addAndMakeVisible (chorDepthSlider = new MouseOverKnob ("Chorus Depth"));
    chorDepthSlider->setRange (5, 20, 0);
    chorDepthSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    chorDepthSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    chorDepthSlider->addListener (this);

    addAndMakeVisible (chorDelayLengthSlider = new MouseOverKnob ("Chorus Width"));
    chorDelayLengthSlider->setRange (0.025, 0.08, 0);
    chorDelayLengthSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    chorDelayLengthSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    chorDelayLengthSlider->addListener (this);

    addAndMakeVisible (chorModRateSlider = new MouseOverKnob ("Chorus Rate"));
    chorModRateSlider->setRange (0.1, 1.5, 0);
    chorModRateSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    chorModRateSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    chorModRateSlider->addListener (this);


    //[UserPreSize]
    registerSlider(chorDryWetSlider, &params.chorDryWet);
    registerSlider(chorDepthSlider, &params.chorModDepth);
    registerSlider(chorDelayLengthSlider, &params.chorDelayLength);
    registerSlider(chorModRateSlider, &params.chorModRate);
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
    drawGroupBorder(g, "chorus", 0, 0,
                    this->getWidth(), this->getHeight() - 22, 25.0f, 20.0f, 5.0f, 3.0f, SynthParams::fxColour);
    //[/UserPaint]
}

void ChorusPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    chorDryWetSlider->setBounds (25, 31, 64, 64);
    chorDepthSlider->setBounds (111, 31, 64, 64);
    chorDelayLengthSlider->setBounds (25, 95, 64, 64);
    chorModRateSlider->setBounds (113, 95, 64, 64);
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

<JUCER_COMPONENT documentType="Component" className="ChorusPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="200"
                 initialHeight="200">
  <BACKGROUND backgroundColour="ff2b3240"/>
  <SLIDER name="Chorus Dry / Wet" id="d1b572a8e8671301" memberName="chorDryWetSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="25 31 64 64"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Chorus Depth" id="d8e8d503fe1af0f3" memberName="chorDepthSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="111 31 64 64"
          min="5" max="20" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Chorus Width" id="16cb41f7d7598aa9" memberName="chorDelayLengthSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="25 95 64 64"
          min="0.025000000000000001388" max="0.080000000000000001665" int="0"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Chorus Rate" id="ec42991e35f3fab6" memberName="chorModRateSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="113 95 64 64"
          min="0.10000000000000000555" max="1.5" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
