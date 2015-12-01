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

#include "LadderPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
LadderPanel::LadderPanel (SynthParams &p)
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (cutoff = new Slider ("cutoff"));
    cutoff->setRange (10, 20000, 0);
    cutoff->setSliderStyle (Slider::RotaryVerticalDrag);
    cutoff->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    cutoff->addListener (this);

    addAndMakeVisible (resonance = new Slider ("resonance"));
    resonance->setRange (0, 10, 0);
    resonance->setSliderStyle (Slider::RotaryVerticalDrag);
    resonance->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    resonance->addListener (this);


    //[UserPreSize]
    cutoff->setValue(params.ladderCutoff.getUI());
    cutoff->setTextValueSuffix(String(" ") + params.ladderCutoff.unit());
    cutoff->setSkewFactor(0.5);
    resonance->setValue(params.ladderRes.getUI());
    resonance->setTextValueSuffix(String(" ") + params.ladderRes.unit());
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

LadderPanel::~LadderPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    cutoff = nullptr;
    resonance = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LadderPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void LadderPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    cutoff->setBounds (40, 56, 80, 64);
    resonance->setBounds (144, 56, 80, 64);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void LadderPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == cutoff)
    {
        //[UserSliderCode_cutoff] -- add your slider handling code here..
        params.ladderCutoff.setUI(static_cast<float>(cutoff->getValue()));
        //[/UserSliderCode_cutoff]
    }
    else if (sliderThatWasMoved == resonance)
    {
        //[UserSliderCode_resonance] -- add your slider handling code here..
        params.ladderRes.setUI(static_cast<float>(resonance->getValue()));
        //[/UserSliderCode_resonance]
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

<JUCER_COMPONENT documentType="Component" className="LadderPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="cutoff" id="9f0401962808ddd3" memberName="cutoff" virtualName=""
          explicitFocusOrder="0" pos="40 56 80 64" min="10" max="20000"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="resonance" id="5cc36d41af142d68" memberName="resonance"
          virtualName="" explicitFocusOrder="0" pos="144 56 80 64" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
