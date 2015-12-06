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

    addAndMakeVisible (FilterAttack = new MouseOverKnob ("Attack"));
    FilterAttack->setRange (0.001, 5, 0);
    FilterAttack->setSliderStyle (Slider::RotaryVerticalDrag);
    FilterAttack->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    FilterAttack->addListener (this);
    FilterAttack->setSkewFactor (0.5);

    addAndMakeVisible (FilterDecay = new MouseOverKnob ("Decay"));
    FilterDecay->setRange (0.001, 5, 0);
    FilterDecay->setSliderStyle (Slider::RotaryVerticalDrag);
    FilterDecay->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    FilterDecay->addListener (this);
    FilterDecay->setSkewFactor (0.5);

    addAndMakeVisible (FilterSustain = new MouseOverKnob ("Sustain"));
    FilterSustain->setRange (10, 20000, 1);
    FilterSustain->setSliderStyle (Slider::RotaryVerticalDrag);
    FilterSustain->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    FilterSustain->addListener (this);
    FilterSustain->setSkewFactor (3);

    addAndMakeVisible (FilterRelease = new MouseOverKnob ("Release"));
    FilterRelease->setRange (0.001, 5, 0);
    FilterRelease->setSliderStyle (Slider::RotaryVerticalDrag);
    FilterRelease->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    FilterRelease->addListener (this);
    FilterRelease->setSkewFactor (0.5);

    addAndMakeVisible (modSrc = new ComboBox ("modSrcBox"));
    modSrc->setEditableText (false);
    modSrc->setJustificationType (Justification::centred);
    modSrc->setTextWhenNothingSelected (TRANS("No Mod"));
    modSrc->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    modSrc->addItem (TRANS("No Mod"), 1);
    modSrc->addItem (TRANS("LFO1"), 2);
    modSrc->addItem (TRANS("Envelope1"), 3);
    modSrc->addListener (this);

    addAndMakeVisible (modSliderCut = new MouseOverKnob ("modSliderCut1"));
    modSliderCut->setRange (0, 100, 0);
    modSliderCut->setSliderStyle (Slider::RotaryVerticalDrag);
    modSliderCut->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    modSliderCut->addListener (this);
    modSliderCut->setSkewFactor (0.33);


    //[UserPreSize]
    registerSlider(cutoffSlider, &params.lpCutoff);
    registerSlider(modSliderCut, &params.lpModAmout);
    cutoffSlider->setSkewFactorFromMidPoint (1000.0);
    registerSlider(resonanceSlider, &params.lpResonance);
    registerSlider(FilterAttack, &params.filterEnvAttack);
    registerSlider(FilterDecay, &params.filterEnvDecay);
    registerSlider(FilterRelease, &params.filterEnvRelease);
    registerSlider(FilterSustain, &params.filterEnvSustain);
    FilterSustain->setSkewFactorFromMidPoint(1000.0);
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
    FilterAttack = nullptr;
    FilterDecay = nullptr;
    FilterSustain = nullptr;
    FilterRelease = nullptr;
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

    cutoffSlider->setBounds (8, 8, 64, 64);
    resonanceSlider->setBounds (152, 8, 64, 64);
    FilterAttack->setBounds (9, 104, 64, 64);
    FilterDecay->setBounds (81, 104, 64, 64);
    FilterSustain->setBounds (153, 104, 64, 64);
    FilterRelease->setBounds (225, 104, 64, 64);
    modSrc->setBounds (8, 80, 64, 16);
    modSliderCut->setBounds (80, 8, 64, 64);
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
    else if (sliderThatWasMoved == FilterAttack)
    {
        //[UserSliderCode_FilterAttack] -- add your slider handling code here..
        //[/UserSliderCode_FilterAttack]
    }
    else if (sliderThatWasMoved == FilterDecay)
    {
        //[UserSliderCode_FilterDecay] -- add your slider handling code here..
        //[/UserSliderCode_FilterDecay]
    }
    else if (sliderThatWasMoved == FilterSustain)
    {
        //[UserSliderCode_FilterSustain] -- add your slider handling code here..
        //[/UserSliderCode_FilterSustain]
    }
    else if (sliderThatWasMoved == FilterRelease)
    {
        //[UserSliderCode_FilterRelease] -- add your slider handling code here..
        //[/UserSliderCode_FilterRelease]
    }
    else if (sliderThatWasMoved == modSliderCut)
    {
        //[UserSliderCode_modSliderCut] -- add your slider handling code here..
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
        params.lpModSource.set(static_cast<float>(modSrc->getSelectedItemIndex()));
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
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 8 64 64"
          min="10" max="20000" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Resonance" id="858a131fc3b886bf" memberName="resonanceSlider"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="152 8 64 64"
          min="-25" max="25" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Attack" id="3c32cde7173ddbe6" memberName="FilterAttack"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="9 104 64 64"
          min="0.001" max="5" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Decay" id="84a4159bee0728d6" memberName="FilterDecay" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="81 104 64 64" min="0.001" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Sustain" id="4bc867c016d7595f" memberName="FilterSustain"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="153 104 64 64"
          min="10" max="20000" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="3"/>
  <SLIDER name="Release" id="c8bc1120a33101cd" memberName="FilterRelease"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="225 104 64 64"
          min="0.001" max="5" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <COMBOBOX name="modSrcBox" id="11f9848905955e67" memberName="modSrc" virtualName=""
            explicitFocusOrder="0" pos="8 80 64 16" editable="0" layout="36"
            items="No Mod&#10;LFO1&#10;Envelope1" textWhenNonSelected="No Mod"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="modSliderCut1" id="2596fb730a93410" memberName="modSliderCut"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="80 8 64 64"
          min="0" max="100" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.33000000000000002"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
