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

#include "OscPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
OscPanel::OscPanel (SynthParams &p)
    : params(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (ftune1 = new Slider ("fine tune 1"));
    ftune1->setRange (-100, 100, 0);
    ftune1->setSliderStyle (Slider::RotaryVerticalDrag);
    ftune1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    ftune1->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("fine")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lfo1depth1 = new Slider ("LFO depth 1"));
    lfo1depth1->setRange (0, 12, 0);
    lfo1depth1->setSliderStyle (Slider::RotaryVerticalDrag);
    lfo1depth1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    lfo1depth1->addListener (this);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("LFO 1")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (pitchRange = new Slider ("pitch range"));
    pitchRange->setRange (0, 12, 0);
    pitchRange->setSliderStyle (Slider::RotaryVerticalDrag);
    pitchRange->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    pitchRange->addListener (this);

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Pitch Range")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (LFO_fade_in = new Slider ("LFO fade_in"));
    LFO_fade_in->setRange (0, 10, 0.01);
    LFO_fade_in->setSliderStyle (Slider::RotaryVerticalDrag);
    LFO_fade_in->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    LFO_fade_in->addListener (this);

    addAndMakeVisible (LFO_fadein_label = new Label ("LFO fade_in label",
                                                     TRANS("LFO fade in")));
    LFO_fadein_label->setFont (Font (15.00f, Font::plain));
    LFO_fadein_label->setJustificationType (Justification::centred);
    LFO_fadein_label->setEditable (false, false, false);
    LFO_fadein_label->setColour (TextEditor::textColourId, Colours::black);
    LFO_fadein_label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    ftune1->setValue(params.osc1fine.getUI());
    ftune1->setTextValueSuffix(String(" ") + params.osc1fine.unit());
	LFO_fade_in->setValue(params.lfo_fadein.getUI());
	LFO_fade_in->setTextValueSuffix(String(" ") + params.lfo_fadein.unit());
	LFO_fade_in->setSkewFactorFromMidPoint(1);  // Setting the slider logarithmic (value 1s in the middle of slider)
    lfo1depth1->setValue(params.osc1lfo1depth.getUI());
    lfo1depth1->setTextValueSuffix(String(" ") + params.osc1lfo1depth.unit());
    pitchRange->setValue(params.osc1PitchRange.getUI());
    pitchRange->setTextValueSuffix(String(" ") + params.osc1PitchRange.unit());
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

OscPanel::~OscPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    ftune1 = nullptr;
    label = nullptr;
    lfo1depth1 = nullptr;
    label3 = nullptr;
    pitchRange = nullptr;
    label4 = nullptr;
    LFO_fade_in = nullptr;
    LFO_fadein_label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void OscPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void OscPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    ftune1->setBounds (8, 32, 64, 64);
    label->setBounds (8, 8, 64, 16);
    lfo1depth1->setBounds (80, 32, 64, 64);
    label3->setBounds (80, 8, 64, 16);
    pitchRange->setBounds (156, 32, 64, 64);
    label4->setBounds (149, 4, 80, 24);
    LFO_fade_in->setBounds (240, 31, 64, 64);
    LFO_fadein_label->setBounds (240, 7, 64, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void OscPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == ftune1)
    {
        //[UserSliderCode_ftune1] -- add your slider handling code here..
        params.osc1fine.setUI(static_cast<float>(ftune1->getValue()));
        //[/UserSliderCode_ftune1]
    }
    else if (sliderThatWasMoved == lfo1depth1)
    {
        //[UserSliderCode_lfo1depth1] -- add your slider handling code here..
        params.osc1lfo1depth.setUI(static_cast<float>(lfo1depth1->getValue()));
        //[/UserSliderCode_lfo1depth1]
    }
    else if (sliderThatWasMoved == pitchRange)
    {
        //[UserSliderCode_pitchRange] -- add your slider handling code here..
        params.osc1PitchRange.setUI(static_cast<float>(pitchRange->getValue()));
        //[/UserSliderCode_pitchRange]
    }
    else if (sliderThatWasMoved == LFO_fade_in)
    {
        //[UserSliderCode_LFO_fade_in] -- add your slider handling code here..
		params.lfo_fadein.setUI(static_cast<float>(LFO_fade_in->getValue()));
        //[/UserSliderCode_LFO_fade_in]
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

<JUCER_COMPONENT documentType="Component" className="OscPanel" componentName=""
                 parentClasses="public Component" constructorParams="SynthParams &amp;p"
                 variableInitialisers="params(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="fine tune 1" id="3c32cde7173ddbe6" memberName="ftune1"
          virtualName="" explicitFocusOrder="0" pos="8 32 64 64" min="-100"
          max="100" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="9d171eeecf3cc269" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 8 64 16" edTextCol="ff000000" edBkgCol="0"
         labelText="fine" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="LFO depth 1" id="523b9024be39c1b" memberName="lfo1depth1"
          virtualName="" explicitFocusOrder="0" pos="80 32 64 64" min="0"
          max="12" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="d2ef03a114e2a714" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="80 8 64 16" edTextCol="ff000000"
         edBkgCol="0" labelText="LFO 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="pitch range" id="29275125e377aaa" memberName="pitchRange"
          virtualName="" explicitFocusOrder="0" pos="156 32 64 64" min="0"
          max="12" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="4067670d690acd0" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="149 4 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pitch Range" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="LFO fade_in" id="3c4d67b75173e0e3" memberName="LFO_fade_in"
          virtualName="" explicitFocusOrder="0" pos="240 31 64 64" min="0"
          max="10" int="0.010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="LFO fade_in label" id="8234bc16ffc2471e" memberName="LFO_fadein_label"
         virtualName="" explicitFocusOrder="0" pos="240 7 64 16" edTextCol="ff000000"
         edBkgCol="0" labelText="LFO fade in" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
