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
LfoPanel::LfoPanel (SynthParams &p)
    : params(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (freq = new Slider ("LFO freq"));
    freq->setRange (0.01, 50, 0);
    freq->setSliderStyle (Slider::RotaryVerticalDrag);
    freq->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    freq->addListener (this);

    addAndMakeVisible (label = new Label ("freq label",
                                          TRANS("freq")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    freq->setValue(params.lfo1freq.getUI());
    freq->setTextValueSuffix(String(" ") + params.lfo1freq.unit());
    freq->setSkewFactorFromMidPoint(params.lfo1freq.getDefault());
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

LfoPanel::~LfoPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    freq = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LfoPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void LfoPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    freq->setBounds (8, 32, 64, 64);
    label->setBounds (8, 8, 64, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void LfoPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == freq)
    {
        //[UserSliderCode_freq] -- add your slider handling code here..
        params.lfo1freq.setUI(static_cast<float>(freq->getValue()));
        //[/UserSliderCode_freq]
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

<JUCER_COMPONENT documentType="Component" className="LfoPanel" componentName=""
                 parentClasses="public Component" constructorParams="SynthParams &amp;p"
                 variableInitialisers="params(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="LFO freq" id="d136f7fae1b8db84" memberName="freq" virtualName=""
          explicitFocusOrder="0" pos="8 32 64 64" min="0.010000000000000000208"
          max="50" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="freq label" id="44d54eb754724ef0" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 8 64 16" edTextCol="ff000000" edBkgCol="0"
         labelText="freq" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
