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
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (freq = new MouseOverKnob ("LFO freq"));
    freq->setRange (0.01, 50, 0);
    freq->setSliderStyle (Slider::RotaryVerticalDrag);
    freq->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    freq->addListener (this);

    addAndMakeVisible (wave = new Slider ("wave switch"));
    wave->setRange (0, 2, 1);
    wave->setSliderStyle (Slider::LinearHorizontal);
    wave->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    wave->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Sine Wave |")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (squareWaveLabel = new Label ("new label",
                                                    TRANS("Square Wave")));
    squareWaveLabel->setFont (Font (15.00f, Font::plain));
    squareWaveLabel->setJustificationType (Justification::centredLeft);
    squareWaveLabel->setEditable (false, false, false);
    squareWaveLabel->setColour (TextEditor::textColourId, Colours::black);
    squareWaveLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sampleAndHoldLabel = new Label ("new label",
                                                       TRANS("Sample and Hold |")));
    sampleAndHoldLabel->setFont (Font (15.00f, Font::plain));
    sampleAndHoldLabel->setJustificationType (Justification::centredLeft);
    sampleAndHoldLabel->setEditable (false, false, false);
    sampleAndHoldLabel->setColour (TextEditor::textColourId, Colours::black);
    sampleAndHoldLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    registerSlider(freq, &params.lfo1freq);
    freq->setSkewFactorFromMidPoint(params.lfo1freq.getDefault());
    wave->setValue(params.lfo1wave.getUI());
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
    wave = nullptr;
    label2 = nullptr;
    squareWaveLabel = nullptr;
    sampleAndHoldLabel = nullptr;


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
    wave->setBounds (120, 40, 192, 32);
    label2->setBounds (88, 72, 80, 24);
    squareWaveLabel->setBounds (266, 72, 83, 24);
    sampleAndHoldLabel->setBounds (160, 72, 112, 24);

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
        params.lfo1wave.setUI(std::round(static_cast<float>(wave->getValue())));
        //[/UserSliderCode_wave]
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
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="LFO freq" id="d136f7fae1b8db84" memberName="freq" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="8 8 64 64" min="0.01" max="50" int="0"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="wave switch" id="221421ebd522cd9a" memberName="wave" virtualName=""
          explicitFocusOrder="0" pos="120 40 192 32" min="0" max="2" int="1"
          style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="e7b5c6b105490306" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="88 72 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sine Wave |" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a5e6136827f3a519" memberName="squareWaveLabel"
         virtualName="" explicitFocusOrder="0" pos="266 72 83 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Square Wave" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="cf2effe035a853f" memberName="sampleAndHoldLabel"
         virtualName="" explicitFocusOrder="0" pos="160 72 112 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sample and Hold |" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
