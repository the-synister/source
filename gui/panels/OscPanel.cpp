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
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (ftune1 = new Slider ("fine tune 1"));
    ftune1->setRange (-100, 100, 0);
    ftune1->setSliderStyle (Slider::RotaryVerticalDrag);
    ftune1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    ftune1->addListener (this);

    addAndMakeVisible (fineLabel = new Label ("new label",
                                              TRANS("fine")));
    fineLabel->setFont (Font (15.00f, Font::plain));
    fineLabel->setJustificationType (Justification::centred);
    fineLabel->setEditable (false, false, false);
    fineLabel->setColour (TextEditor::textColourId, Colours::black);
    fineLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lfo1depth1 = new Slider ("LFO depth 1"));
    lfo1depth1->setRange (0, 12, 0);
    lfo1depth1->setSliderStyle (Slider::RotaryVerticalDrag);
    lfo1depth1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    lfo1depth1->addListener (this);

    addAndMakeVisible (lfoOscLabel = new Label ("new label",
                                                TRANS("LFO 1")));
    lfoOscLabel->setFont (Font (15.00f, Font::plain));
    lfoOscLabel->setJustificationType (Justification::centred);
    lfoOscLabel->setEditable (false, false, false);
    lfoOscLabel->setColour (TextEditor::textColourId, Colours::black);
    lfoOscLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (osc1trngAmount = new Slider ("Osc1 Triangle Amount"));
    osc1trngAmount->setRange (0, 1, 0);
    osc1trngAmount->setSliderStyle (Slider::RotaryVerticalDrag);
    osc1trngAmount->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    osc1trngAmount->addListener (this);

    addAndMakeVisible (triangleMorphLabel = new Label ("new label",
                                                       TRANS("Triangle Morph\n")));
    triangleMorphLabel->setFont (Font (15.00f, Font::plain));
    triangleMorphLabel->setJustificationType (Justification::centred);
    triangleMorphLabel->setEditable (false, false, false);
    triangleMorphLabel->setColour (TextEditor::textColourId, Colours::black);
    triangleMorphLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (pulsewidth = new Slider ("Pulse Width"));
    pulsewidth->setRange (0.01, 0.99, 0);
    pulsewidth->setSliderStyle (Slider::RotaryVerticalDrag);
    pulsewidth->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    pulsewidth->addListener (this);

    addAndMakeVisible (pulseWidthLabel = new Label ("new label",
                                                    TRANS("Pulse Width\n")));
    pulseWidthLabel->setFont (Font (15.00f, Font::plain));
    pulseWidthLabel->setJustificationType (Justification::centred);
    pulseWidthLabel->setEditable (false, false, false);
    pulseWidthLabel->setColour (TextEditor::textColourId, Colours::black);
    pulseWidthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (pitchRange = new Slider ("pitch range"));
    pitchRange->setRange (0, 12, 0);
    pitchRange->setSliderStyle (Slider::RotaryVerticalDrag);
    pitchRange->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    pitchRange->addListener (this);

    addAndMakeVisible (pitchRangeLabel = new Label ("new label",
                                                    TRANS("Pitch\n"
                                                    "Range")));
    pitchRangeLabel->setFont (Font (15.00f, Font::plain));
    pitchRangeLabel->setJustificationType (Justification::centred);
    pitchRangeLabel->setEditable (false, false, false);
    pitchRangeLabel->setColour (TextEditor::textColourId, Colours::black);
    pitchRangeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (ctune1 = new Slider ("coarse tune 1"));
    ctune1->setRange (-11, 11, 1);
    ctune1->setSliderStyle (Slider::RotaryVerticalDrag);
    ctune1->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    ctune1->addListener (this);

    addAndMakeVisible (coarseTuneLabel = new Label ("new label",
                                                    TRANS("Coarse Tune")));
    coarseTuneLabel->setFont (Font (15.00f, Font::plain));
    coarseTuneLabel->setJustificationType (Justification::centred);
    coarseTuneLabel->setEditable (false, false, false);
    coarseTuneLabel->setColour (TextEditor::textColourId, Colours::black);
    coarseTuneLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    registerSlider(ftune1, &params.osc1fine);
    registerSlider(lfo1depth1, &params.osc1lfo1depth);
    registerSlider(osc1trngAmount, &params.osc1trngAmount);
    registerSlider(pitchRange, &params.osc1PitchRange);
    registerSlider(pulsewidth, &params.osc1pulsewidth);
    registerSlider(ctune1, &params.osc1coarse);
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
    fineLabel = nullptr;
    lfo1depth1 = nullptr;
    lfoOscLabel = nullptr;
    osc1trngAmount = nullptr;
    triangleMorphLabel = nullptr;
    pulsewidth = nullptr;
    pulseWidthLabel = nullptr;
    pitchRange = nullptr;
    pitchRangeLabel = nullptr;
    ctune1 = nullptr;
    coarseTuneLabel = nullptr;


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
    fineLabel->setBounds (8, 8, 64, 16);
    lfo1depth1->setBounds (80, 32, 64, 64);
    lfoOscLabel->setBounds (80, 8, 64, 16);
    osc1trngAmount->setBounds (152, 32, 64, 64);
    triangleMorphLabel->setBounds (138, 3, 93, 31);
    pulsewidth->setBounds (224, 32, 64, 64);
    pulseWidthLabel->setBounds (218, 7, 80, 24);
    pitchRange->setBounds (296, 32, 64, 64);
    pitchRangeLabel->setBounds (292, 2, 72, 32);
    ctune1->setBounds (368, 32, 64, 64);
    coarseTuneLabel->setBounds (360, 8, 80, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void OscPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == ftune1)
    {
        //[UserSliderCode_ftune1] -- add your slider handling code here..
        //[/UserSliderCode_ftune1]
    }
    else if (sliderThatWasMoved == lfo1depth1)
    {
        //[UserSliderCode_lfo1depth1] -- add your slider handling code here..
        //[/UserSliderCode_lfo1depth1]
    }
    else if (sliderThatWasMoved == osc1trngAmount)
    {
        //[UserSliderCode_osc1trngAmount] -- add your slider handling code here..
        //[/UserSliderCode_osc1trngAmount]
    }
    else if (sliderThatWasMoved == pulsewidth)
    {
        //[UserSliderCode_pulsewidth] -- add your slider handling code here..
        //[/UserSliderCode_pulsewidth]
    }
    else if (sliderThatWasMoved == pitchRange)
    {
        //[UserSliderCode_pitchRange] -- add your slider handling code here..
        //[/UserSliderCode_pitchRange]
    }
    else if (sliderThatWasMoved == ctune1)
    {
        //[UserSliderCode_ctune1] -- add your slider handling code here..
        //[/UserSliderCode_ctune1]
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
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="fine tune 1" id="3c32cde7173ddbe6" memberName="ftune1"
          virtualName="" explicitFocusOrder="0" pos="8 32 64 64" min="-100"
          max="100" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="9d171eeecf3cc269" memberName="fineLabel"
         virtualName="" explicitFocusOrder="0" pos="8 8 64 16" edTextCol="ff000000"
         edBkgCol="0" labelText="fine" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="LFO depth 1" id="523b9024be39c1b" memberName="lfo1depth1"
          virtualName="" explicitFocusOrder="0" pos="80 32 64 64" min="0"
          max="12" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="d2ef03a114e2a714" memberName="lfoOscLabel"
         virtualName="" explicitFocusOrder="0" pos="80 8 64 16" edTextCol="ff000000"
         edBkgCol="0" labelText="LFO 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="Osc1 Triangle Amount" id="d81a0f8c69078b3c" memberName="osc1trngAmount"
          virtualName="" explicitFocusOrder="0" pos="152 32 64 64" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="fffbfc69001f744b" memberName="triangleMorphLabel"
         virtualName="" explicitFocusOrder="0" pos="138 3 93 31" edTextCol="ff000000"
         edBkgCol="0" labelText="Triangle Morph&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Pulse Width" id="96badb5ea7640431" memberName="pulsewidth"
          virtualName="" explicitFocusOrder="0" pos="224 32 64 64" min="0.010000000000000000208"
          max="0.98999999999999999112" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="6c4a0c81a4fa9676" memberName="pulseWidthLabel"
         virtualName="" explicitFocusOrder="0" pos="218 7 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pulse Width&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="pitch range" id="29275125e377aaa" memberName="pitchRange"
          virtualName="" explicitFocusOrder="0" pos="296 32 64 64" min="0"
          max="12" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="4067670d690acd0" memberName="pitchRangeLabel"
         virtualName="" explicitFocusOrder="0" pos="292 2 72 32" edTextCol="ff000000"
         edBkgCol="0" labelText="Pitch&#10;Range" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="coarse tune 1" id="52a6628a22cee304" memberName="ctune1"
          virtualName="" explicitFocusOrder="0" pos="368 32 64 64" min="-11"
          max="11" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="18844143981102bf" memberName="coarseTuneLabel"
         virtualName="" explicitFocusOrder="0" pos="360 8 80 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Coarse Tune" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
