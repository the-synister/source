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

    addAndMakeVisible (passtype = new MouseOverKnob ("passtype switch"));
    passtype->setRange (0, 2, 1);
    passtype->setSliderStyle (Slider::RotaryVerticalDrag);
    passtype->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    passtype->addListener (this);

    addAndMakeVisible (modSrc = new ComboBox ("modSrcBox"));
    modSrc->setEditableText (false);
    modSrc->setJustificationType (Justification::centred);
    modSrc->setTextWhenNothingSelected (TRANS("No Mod"));
    modSrc->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    modSrc->addItem (TRANS("No Mod"), 1);
    modSrc->addItem (TRANS("LFO 1"), 2);
    modSrc->addItem (TRANS("ENV 1"), 3);
    modSrc->addListener (this);

    addAndMakeVisible (modSliderCut = new Slider ("Mod"));
    modSliderCut->setRange (0, 100, 0);
    modSliderCut->setSliderStyle (Slider::RotaryVerticalDrag);
    modSliderCut->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    modSliderCut->addListener (this);
    modSliderCut->setSkewFactor (0.5);


    //[UserPreSize]
    registerSlider(cutoffSlider, &params.lpCutoff);
    registerSlider(modSliderCut, &params.lpModAmount);
    cutoffSlider->setSkewFactorFromMidPoint (1000.0);
    registerSlider(cutoffSlider2, &params.hpCutoff);
    cutoffSlider2->setSkewFactorFromMidPoint(1000.0);
    registerSlider(resonanceSlider, &params.biquadResonance);
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
    passtype = nullptr;
    modSrc = nullptr;
    modSliderCut = nullptr;


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

    cutoffSlider->setBounds (96, 8, 64, 64);
    resonanceSlider->setBounds (168, 8, 64, 64);
    cutoffSlider2->setBounds (96, 104, 64, 64);
    passtype->setBounds (8, 8, 64, 64);
    modSrc->setBounds (96, 80, 64, 16);
    modSliderCut->setBounds (160, 80, 24, 24);
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
    else if (sliderThatWasMoved == passtype)
    {
        //[UserSliderCode_passtype] -- add your slider handling code here..
        //[/UserSliderCode_passtype]
    }
    else if (sliderThatWasMoved == modSliderCut)
    {
        //[UserSliderCode_modSliderCut] -- add your slider handling code here..
        params.lpModAmount.setUI(static_cast<float>(modSliderCut->getValue()));
        //[/UserSliderCode_modSliderCut]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void FiltPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == modSrc)
    {
        //[UserComboBoxCode_modSrc] -- add your combo box handling code here..
        params.lpModSource.setStep(static_cast<eModSource>(modSrc->getSelectedItemIndex()));
        //[/UserComboBoxCode_modSrc]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
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
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="96 8 64 64"
          min="10" max="20000" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Resonance" id="858a131fc3b886bf" memberName="resonanceSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="168 8 64 64"
          min="-25" max="25" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Cutoff2" id="113357b68931ad03" memberName="cutoffSlider2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="96 104 64 64"
          min="10" max="20000" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="passtype switch" id="163a0186fbf8b1b2" memberName="passtype"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 8 64 64"
          min="0" max="2" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="modSrcBox" id="11f9848905955e67" memberName="modSrc" virtualName=""
            explicitFocusOrder="0" pos="96 80 64 16" editable="0" layout="36"
            items="No Mod&#10;LFO 1&#10;ENV 1" textWhenNonSelected="No Mod"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="Mod" id="2634056a966d88f4" memberName="modSliderCut" virtualName=""
          explicitFocusOrder="0" pos="160 80 24 24" min="0" max="100" int="0"
          style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
