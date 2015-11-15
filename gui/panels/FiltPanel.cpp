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
    : params(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (CutoffSlider = new Slider ("Cutoff"));
    CutoffSlider->setRange (10, 20000, 1);
    CutoffSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    CutoffSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    CutoffSlider->addListener (this);

    addAndMakeVisible (ResonanceSlider = new Slider ("Resonance"));
    ResonanceSlider->setRange (-25, 25, 0);
    ResonanceSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    ResonanceSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    ResonanceSlider->addListener (this);

    addAndMakeVisible (lpfLabel = new Label ("Lowpass Label",
                                             TRANS("Lowpass Filter")));
    lpfLabel->setFont (Font (15.00f, Font::plain));
    lpfLabel->setJustificationType (Justification::centredLeft);
    lpfLabel->setEditable (false, false, false);
    lpfLabel->setColour (TextEditor::textColourId, Colours::black);
    lpfLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Cutoff")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (reso_lbl = new Label ("Resonance",
                                             TRANS("Resonance")));
    reso_lbl->setFont (Font (15.00f, Font::plain));
    reso_lbl->setJustificationType (Justification::centredLeft);
    reso_lbl->setEditable (false, false, false);
    reso_lbl->setColour (TextEditor::textColourId, Colours::black);
    reso_lbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    CutoffSlider->setValue(params.lpCutoff.getUI());
    CutoffSlider->setTextValueSuffix(String(" ") + params.lpCutoff.unit());
    ResonanceSlider->setValue(params.lpResonance.getUI());
    ResonanceSlider->setTextValueSuffix(String(" ") + params.lpResonance.unit());
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

FiltPanel::~FiltPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    CutoffSlider = nullptr;
    ResonanceSlider = nullptr;
    lpfLabel = nullptr;
    label = nullptr;
    reso_lbl = nullptr;


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

    CutoffSlider->setBounds (56, 64, 80, 72);
    ResonanceSlider->setBounds (240, 64, 72, 72);
    lpfLabel->setBounds (40, 8, 150, 24);
    label->setBounds (72, 40, 48, 24);
    reso_lbl->setBounds (240, 40, 71, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void FiltPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == CutoffSlider)
    {
        //[UserSliderCode_CutoffSlider] -- add your slider handling code here..
        params.lpCutoff.setUI(static_cast<float>(CutoffSlider->getValue()));

        //[/UserSliderCode_CutoffSlider]
    }
    else if (sliderThatWasMoved == ResonanceSlider)
    {
        //[UserSliderCode_ResonanceSlider] -- add your slider handling code here..
        params.lpResonance.setUI(static_cast<float>(ResonanceSlider->getValue()));
        //[/UserSliderCode_ResonanceSlider]
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
                 parentClasses="public Component" constructorParams="SynthParams &amp;p"
                 variableInitialisers="params(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Cutoff" id="f7fb929bf25ff4a4" memberName="CutoffSlider"
          virtualName="" explicitFocusOrder="0" pos="56 64 80 72" min="10"
          max="20000" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Resonance" id="858a131fc3b886bf" memberName="ResonanceSlider"
          virtualName="" explicitFocusOrder="0" pos="240 64 72 72" min="-25"
          max="25" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Lowpass Label" id="a6bb552e4fa24670" memberName="lpfLabel"
         virtualName="" explicitFocusOrder="0" pos="40 8 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Lowpass Filter" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="11c4b0d3d48821ba" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="72 40 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Cutoff" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Resonance" id="3bfcec617ed028c5" memberName="reso_lbl"
         virtualName="" explicitFocusOrder="0" pos="240 40 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Resonance" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
