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
FiltPanel::FiltPanel (SynthParams &p, int filterNumber)
    : PanelBase(p),
      filter(p.filter[filterNumber])
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (cutoffSlider = new MouseOverKnob ("Cutoff"));
    cutoffSlider->setRange (10, 20000, 1);
    cutoffSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    cutoffSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    cutoffSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xff5b7a47));
    cutoffSlider->addListener (this);

    addAndMakeVisible (resonanceSlider = new MouseOverKnob ("Resonance"));
    resonanceSlider->setRange (0, 10, 0);
    resonanceSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    resonanceSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    resonanceSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xff5b7a47));
    resonanceSlider->addListener (this);

    addAndMakeVisible (cutoffSlider2 = new MouseOverKnob ("Cutoff2"));
    cutoffSlider2->setRange (10, 20000, 1);
    cutoffSlider2->setSliderStyle (Slider::RotaryVerticalDrag);
    cutoffSlider2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    cutoffSlider2->addListener (this);

    addAndMakeVisible (passtype = new MouseOverKnob ("passtype switch"));
    passtype->setRange (0, 3, 1);
    passtype->setSliderStyle (Slider::RotaryVerticalDrag);
    passtype->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    passtype->addListener (this);

    addAndMakeVisible (modSliderCut = new Slider ("Mod"));
    modSliderCut->setRange (0, 8, 0);
    modSliderCut->setSliderStyle (Slider::RotaryVerticalDrag);
    modSliderCut->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    modSliderCut->addListener (this);

    addAndMakeVisible (lp1ModSrc1 = new ComboBox ("lp1ModSrcBox1"));
    lp1ModSrc1->setEditableText (false);
    lp1ModSrc1->setJustificationType (Justification::centred);
    lp1ModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    lp1ModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    lp1ModSrc1->addListener (this);

    addAndMakeVisible (hp1ModSrc1 = new ComboBox ("hp1ModSrcBox1"));
    hp1ModSrc1->setEditableText (false);
    hp1ModSrc1->setJustificationType (Justification::centred);
    hp1ModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    hp1ModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    hp1ModSrc1->addListener (this);

    addAndMakeVisible (lp1ModSrc2 = new ComboBox ("lp1ModSrcBox2"));
    lp1ModSrc2->setEditableText (false);
    lp1ModSrc2->setJustificationType (Justification::centred);
    lp1ModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    lp1ModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    lp1ModSrc2->addListener (this);

    addAndMakeVisible (hp1ModSrc2 = new ComboBox ("hp1ModSrcBox2"));
    hp1ModSrc2->setEditableText (false);
    hp1ModSrc2->setJustificationType (Justification::centred);
    hp1ModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    hp1ModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    hp1ModSrc2->addListener (this);

    addAndMakeVisible (res1ModSrc1 = new ComboBox ("res1ModSrcBox1"));
    res1ModSrc1->setEditableText (false);
    res1ModSrc1->setJustificationType (Justification::centred);
    res1ModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    res1ModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    res1ModSrc1->addListener (this);

    addAndMakeVisible (res1ModSrc2 = new ComboBox ("res1ModSrcBox2"));
    res1ModSrc2->setEditableText (false);
    res1ModSrc2->setJustificationType (Justification::centred);
    res1ModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    res1ModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    res1ModSrc2->addListener (this);

    addAndMakeVisible (modSliderCut2 = new Slider ("Mod"));
    modSliderCut2->setRange (0, 8, 0);
    modSliderCut2->setSliderStyle (Slider::RotaryVerticalDrag);
    modSliderCut2->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    modSliderCut2->addListener (this);


    //[UserPreSize]
    registerSlider(cutoffSlider, &filter.lpCutoff);
    registerSlider(modSliderCut, &filter.lpModAmount1);
    registerSlider(modSliderCut2, &filter.lpModAmount2);
    cutoffSlider->setSkewFactorFromMidPoint(1000.0);

    registerSlider(cutoffSlider2, &filter.hpCutoff);
    cutoffSlider2->setSkewFactorFromMidPoint(1000.0);

    registerSlider(resonanceSlider, &filter.resonance);
    registerSlider(passtype, &filter.passtype);


    fillModsourceBox(lp1ModSrc1);
    fillModsourceBox(lp1ModSrc2);
    fillModsourceBox(hp1ModSrc1);
    fillModsourceBox(hp1ModSrc2);
    fillModsourceBox(res1ModSrc1);
    fillModsourceBox(res1ModSrc2);

    registerCombobox(lp1ModSrc1, &filter.lpCutModSrc1);
    registerCombobox(lp1ModSrc2, &filter.lpCutModSrc2);
    registerCombobox(hp1ModSrc1, &filter.hpCutModSrc1);
    registerCombobox(hp1ModSrc2, &filter.hpCutModSrc2);
    registerCombobox(res1ModSrc1, &filter.resonanceModSrc1);
    registerCombobox(res1ModSrc2, &filter.resonanceModSrc2);
    //[/UserPreSize]

    setSize (400, 180);


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
    modSliderCut = nullptr;
    lp1ModSrc1 = nullptr;
    hp1ModSrc1 = nullptr;
    lp1ModSrc2 = nullptr;
    hp1ModSrc2 = nullptr;
    res1ModSrc1 = nullptr;
    res1ModSrc2 = nullptr;
    modSliderCut2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FiltPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff40ae69));

    //[UserPaint] Add your own custom painting code here..
    drawGroupBorder(g, filter.name, 0, 0,
                    this->getWidth(), this->getHeight() - 22, 25.0f, 20.0f, 5.0f, 3.0f, SynthParams::filterColour);
    //[/UserPaint]
}

void FiltPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    cutoffSlider->setBounds (110, 34, 64, 64);
    resonanceSlider->setBounds (300, 36, 64, 64);
    cutoffSlider2->setBounds (204, 34, 64, 64);
    passtype->setBounds (8, 27, 64, 64);
    modSliderCut->setBounds (158, 98, 24, 24);
    lp1ModSrc1->setBounds (108, 101, 50, 16);
    hp1ModSrc1->setBounds (204, 104, 64, 16);
    lp1ModSrc2->setBounds (108, 125, 50, 16);
    hp1ModSrc2->setBounds (204, 128, 64, 16);
    res1ModSrc1->setBounds (299, 104, 64, 16);
    res1ModSrc2->setBounds (299, 127, 64, 16);
    modSliderCut2->setBounds (158, 122, 24, 24);
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
        filter.lpModAmount1.setUI(static_cast<float>(modSliderCut->getValue()));
        //[/UserSliderCode_modSliderCut]
    }
    else if (sliderThatWasMoved == modSliderCut2)
    {
        //[UserSliderCode_modSliderCut2] -- add your slider handling code here..
        //[/UserSliderCode_modSliderCut2]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void FiltPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    handleCombobox(comboBoxThatHasChanged);
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == lp1ModSrc1)
    {
        //[UserComboBoxCode_lp1ModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_lp1ModSrc1]
    }
    else if (comboBoxThatHasChanged == hp1ModSrc1)
    {
        //[UserComboBoxCode_hp1ModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_hp1ModSrc1]
    }
    else if (comboBoxThatHasChanged == lp1ModSrc2)
    {
        //[UserComboBoxCode_lp1ModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_lp1ModSrc2]
    }
    else if (comboBoxThatHasChanged == hp1ModSrc2)
    {
        //[UserComboBoxCode_hp1ModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_hp1ModSrc2]
    }
    else if (comboBoxThatHasChanged == res1ModSrc1)
    {
        //[UserComboBoxCode_res1ModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_res1ModSrc1]
    }
    else if (comboBoxThatHasChanged == res1ModSrc2)
    {
        //[UserComboBoxCode_res1ModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_res1ModSrc2]
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
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p, int filterNumber"
                 variableInitialisers="PanelBase(p),&#10;filter(p.filter[filterNumber])"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="400" initialHeight="180">
  <BACKGROUND backgroundColour="ff40ae69"/>
  <SLIDER name="Cutoff" id="f7fb929bf25ff4a4" memberName="cutoffSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="110 34 64 64"
          rotarysliderfill="ff5b7a47" min="10" max="20000" int="1" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Resonance" id="858a131fc3b886bf" memberName="resonanceSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="300 36 64 64"
          rotarysliderfill="ff5b7a47" min="0" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Cutoff2" id="113357b68931ad03" memberName="cutoffSlider2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="204 34 64 64"
          min="10" max="20000" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="passtype switch" id="163a0186fbf8b1b2" memberName="passtype"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 27 64 64"
          min="0" max="3" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Mod" id="2634056a966d88f4" memberName="modSliderCut" virtualName=""
          explicitFocusOrder="0" pos="158 98 24 24" min="0" max="8" int="0"
          style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="lp1ModSrcBox1" id="11f9848905955e67" memberName="lp1ModSrc1"
            virtualName="" explicitFocusOrder="0" pos="108 101 50 16" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="hp1ModSrcBox1" id="85c37cba161b4f29" memberName="hp1ModSrc1"
            virtualName="" explicitFocusOrder="0" pos="204 104 64 16" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="lp1ModSrcBox2" id="6dae6bde5fbe8153" memberName="lp1ModSrc2"
            virtualName="" explicitFocusOrder="0" pos="108 125 50 16" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="hp1ModSrcBox2" id="f1f85630e066837c" memberName="hp1ModSrc2"
            virtualName="" explicitFocusOrder="0" pos="204 128 64 16" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="res1ModSrcBox1" id="733eefe1cee8bab3" memberName="res1ModSrc1"
            virtualName="" explicitFocusOrder="0" pos="299 104 64 16" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="res1ModSrcBox2" id="cf210285cf2d4ef" memberName="res1ModSrc2"
            virtualName="" explicitFocusOrder="0" pos="299 127 64 16" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <SLIDER name="Mod" id="c0e4229cc3539fbe" memberName="modSliderCut2" virtualName=""
          explicitFocusOrder="0" pos="158 122 24 24" min="0" max="8" int="0"
          style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
