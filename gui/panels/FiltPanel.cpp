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

#include "FiltPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
FiltPanel::FiltPanel (SynthParams &p)
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (cutoffSlider = new MouseOverKnob ("Cutoff"));
    cutoffSlider->setRange (10, 20000, 1);
    cutoffSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    cutoffSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    cutoffSlider->addListener (this);

    addAndMakeVisible (resonanceSlider = new MouseOverKnob ("Resonance"));
    resonanceSlider->setRange (-25, 25, 0);
    resonanceSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    resonanceSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    resonanceSlider->addListener (this);

    addAndMakeVisible (cutoffSlider2 = new MouseOverKnob ("Cutoff2"));
    cutoffSlider2->setRange (10, 20000, 1);
    cutoffSlider2->setSliderStyle (Slider::RotaryVerticalDrag);
    cutoffSlider2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    cutoffSlider2->addListener (this);

    addAndMakeVisible (resonanceSlider2 = new MouseOverKnob ("Resonance2"));
    resonanceSlider2->setRange (-25, 25, 0);
    resonanceSlider2->setSliderStyle (Slider::RotaryVerticalDrag);
    resonanceSlider2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    resonanceSlider2->addListener (this);

    addAndMakeVisible (passtype = new Slider ("passtype switch"));
    passtype->setRange (0, 2, 1);
    passtype->setSliderStyle (Slider::LinearHorizontal);
    passtype->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    passtype->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("lowpass")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("highpass")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("bandpass")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    registerSlider(cutoffSlider, &params.lpCutoff);
    cutoffSlider->setSkewFactorFromMidPoint (1000.0);
    registerSlider(cutoffSlider2, &params.hpCutoff);
    cutoffSlider2->setSkewFactorFromMidPoint(1000.0);
    registerSlider(resonanceSlider, &params.lpResonance);
    registerSlider(resonanceSlider2, &params.hpResonance);
    registerSlider(passtype, &params.passtype);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

FiltPanel::~FiltPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    cutoffSlider = nullptr;
    resonanceSlider = nullptr;
    cutoffSlider2 = nullptr;
    resonanceSlider2 = nullptr;
    passtype = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    label4 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FiltPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FiltPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    cutoffSlider->setBounds (8, 8, 64, 64);
    resonanceSlider->setBounds (80, 8, 64, 64);
    cutoffSlider2->setBounds (8, 85, 64, 64);
    resonanceSlider2->setBounds (80, 85, 64, 64);
    passtype->setBounds (205, 64, 128, 32);
    label2->setBounds (181, 88, 71, 24);
    label3->setBounds (236, 88, 71, 24);
    label4->setBounds (296, 88, 71, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void FiltPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == cutoffSlider)
    {
        //[UserSliderCode_cutoffSlider] -- add your slider handling code here..
        //[/UserSliderCode_cutoffSlider]
    }
    else if (sliderThatWasMoved == resonanceSlider)
    {
        //[UserSliderCode_resonanceSlider] -- add your slider handling code here..
        //[/UserSliderCode_resonanceSlider]
    }
    else if (sliderThatWasMoved == cutoffSlider2)
    {
        //[UserSliderCode_cutoffSlider2] -- add your slider handling code here..
        //[/UserSliderCode_cutoffSlider2]
    }
    else if (sliderThatWasMoved == resonanceSlider2)
    {
        //[UserSliderCode_resonanceSlider2] -- add your slider handling code here..
        //[/UserSliderCode_resonanceSlider2]
    }
    else if (sliderThatWasMoved == passtype)
    {
        //[UserSliderCode_passtype] -- add your slider handling code here..
        //[/UserSliderCode_passtype]
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

<JUCER_COMPONENT documentType="Component" className="FiltPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Cutoff" id="f7fb929bf25ff4a4" memberName="cutoffSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 8 64 64"
          min="10" max="20000" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Resonance" id="858a131fc3b886bf" memberName="resonanceSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="80 8 64 64"
          min="-25" max="25" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Cutoff2" id="113357b68931ad03" memberName="cutoffSlider2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 85 64 64"
          min="10" max="20000" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Resonance2" id="1de4c43c1bde07c2" memberName="resonanceSlider2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="80 85 64 64"
          min="-25" max="25" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="passtype switch" id="221421ebd522cd9a" memberName="passtype"
          virtualName="" explicitFocusOrder="0" pos="205 64 128 32" min="0"
          max="2" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="e7b5c6b105490306" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="181 88 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="lowpass" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="57513427bb0717d2" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="236 88 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="highpass" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="d1909f10e2139354" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="296 88 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="bandpass" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
