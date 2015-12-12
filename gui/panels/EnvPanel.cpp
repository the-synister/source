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

#include "EnvPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
EnvPanel::EnvPanel (SynthParams &p)
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (attack = new MouseOverKnob ("Attack"));
    attack->setRange (0.001, 5, 0);
    attack->setSliderStyle (Slider::RotaryVerticalDrag);
    attack->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    attack->addListener (this);
    attack->setSkewFactor (0.5);

    addAndMakeVisible (decay = new MouseOverKnob ("Decay"));
    decay->setRange (0.001, 5, 0);
    decay->setSliderStyle (Slider::RotaryVerticalDrag);
    decay->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    decay->addListener (this);
    decay->setSkewFactor (0.5);

    addAndMakeVisible (sustain = new MouseOverKnob ("Sustain"));
    sustain->setRange (-96, 0, 0);
    sustain->setSliderStyle (Slider::RotaryVerticalDrag);
    sustain->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sustain->addListener (this);
    sustain->setSkewFactor (3);

    addAndMakeVisible (release = new MouseOverKnob ("Release"));
    release->setRange (0.001, 5, 0);
    release->setSliderStyle (Slider::RotaryVerticalDrag);
    release->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    release->addListener (this);
    release->setSkewFactor (0.5);

    addAndMakeVisible (freeEnv1Attack = new MouseOverKnob ("Attack"));
    freeEnv1Attack->setRange (0.001, 5, 0);
    freeEnv1Attack->setSliderStyle (Slider::RotaryVerticalDrag);
    freeEnv1Attack->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    freeEnv1Attack->addListener (this);
    freeEnv1Attack->setSkewFactor (0.5);

    addAndMakeVisible (freeEnv1Decay = new MouseOverKnob ("Decay"));
    freeEnv1Decay->setRange (0.001, 5, 0);
    freeEnv1Decay->setSliderStyle (Slider::RotaryVerticalDrag);
    freeEnv1Decay->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    freeEnv1Decay->addListener (this);
    freeEnv1Decay->setSkewFactor (0.5);

    addAndMakeVisible (freeEnv1Sustain = new MouseOverKnob ("Sustain"));
    freeEnv1Sustain->setExplicitFocusOrder (1);
    freeEnv1Sustain->setRange (0, 1, 0.001);
    freeEnv1Sustain->setSliderStyle (Slider::RotaryVerticalDrag);
    freeEnv1Sustain->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    freeEnv1Sustain->addListener (this);
    freeEnv1Sustain->setSkewFactor (0.5);

    addAndMakeVisible (freeEnv1Release = new MouseOverKnob ("Release"));
    freeEnv1Release->setRange (0.001, 5, 0);
    freeEnv1Release->setSliderStyle (Slider::RotaryVerticalDrag);
    freeEnv1Release->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    freeEnv1Release->addListener (this);
    freeEnv1Release->setSkewFactor (0.5);

    addAndMakeVisible (VolEnvLabel = new Label ("Volume Envelope",
                                                TRANS("Volume Envelope")));
    VolEnvLabel->setFont (Font (15.00f, Font::plain));
    VolEnvLabel->setJustificationType (Justification::centredLeft);
    VolEnvLabel->setEditable (false, false, false);
    VolEnvLabel->setColour (TextEditor::textColourId, Colours::black);
    VolEnvLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (Env1Label = new Label ("Envelope_1",
                                              TRANS("Envelope 1")));
    Env1Label->setFont (Font (15.00f, Font::plain));
    Env1Label->setJustificationType (Justification::centredLeft);
    Env1Label->setEditable (false, false, false);
    Env1Label->setColour (TextEditor::textColourId, Colours::black);
    Env1Label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    registerSlider(attack, &params.envAttack);
    registerSlider(decay, &params.envDecay);
    registerSlider(sustain, &params.envSustain);
    registerSlider(release, &params.envRelease);
    registerSlider(freeEnv1Attack, &params.freeEnv1Attack);
    registerSlider(freeEnv1Decay, &params.freeEnv1Decay);
    registerSlider(freeEnv1Release, &params.freeEnv1Release);
    registerSlider(freeEnv1Sustain, &params.freeEnv1Sustain);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

EnvPanel::~EnvPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    attack = nullptr;
    decay = nullptr;
    sustain = nullptr;
    release = nullptr;
    freeEnv1Attack = nullptr;
    freeEnv1Decay = nullptr;
    freeEnv1Sustain = nullptr;
    freeEnv1Release = nullptr;
    VolEnvLabel = nullptr;
    Env1Label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void EnvPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void EnvPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    attack->setBounds (8, 40, 64, 64);
    decay->setBounds (80, 40, 64, 64);
    sustain->setBounds (152, 40, 64, 64);
    release->setBounds (224, 40, 64, 64);
    freeEnv1Attack->setBounds (8, 200, 64, 64);
    freeEnv1Decay->setBounds (80, 200, 64, 64);
    freeEnv1Sustain->setBounds (152, 200, 64, 64);
    freeEnv1Release->setBounds (224, 200, 64, 64);
    VolEnvLabel->setBounds (8, 8, 150, 24);
    Env1Label->setBounds (8, 168, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void EnvPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == attack)
    {
        //[UserSliderCode_attack] -- add your slider handling code here..
        //[/UserSliderCode_attack]
    }
    else if (sliderThatWasMoved == decay)
    {
        //[UserSliderCode_decay] -- add your slider handling code here..
        //[/UserSliderCode_decay]
    }
    else if (sliderThatWasMoved == sustain)
    {
        //[UserSliderCode_sustain] -- add your slider handling code here..
        //[/UserSliderCode_sustain]
    }
    else if (sliderThatWasMoved == release)
    {
        //[UserSliderCode_release] -- add your slider handling code here..
        //[/UserSliderCode_release]
    }
    else if (sliderThatWasMoved == freeEnv1Attack)
    {
        //[UserSliderCode_freeEnv1Attack] -- add your slider handling code here..
        //[/UserSliderCode_freeEnv1Attack]
    }
    else if (sliderThatWasMoved == freeEnv1Decay)
    {
        //[UserSliderCode_freeEnv1Decay] -- add your slider handling code here..
        //[/UserSliderCode_freeEnv1Decay]
    }
    else if (sliderThatWasMoved == freeEnv1Sustain)
    {
        //[UserSliderCode_freeEnv1Sustain] -- add your slider handling code here..
        //[/UserSliderCode_freeEnv1Sustain]
    }
    else if (sliderThatWasMoved == freeEnv1Release)
    {
        //[UserSliderCode_freeEnv1Release] -- add your slider handling code here..
        //[/UserSliderCode_freeEnv1Release]
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

<JUCER_COMPONENT documentType="Component" className="EnvPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Attack" id="3c32cde7173ddbe6" memberName="attack" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="8 40 64 64" min="0.001" max="5" int="0"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Decay" id="84a4159bee0728d6" memberName="decay" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="80 40 64 64" min="0.001" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Sustain" id="4bc867c016d7595f" memberName="sustain" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="152 40 64 64" min="-96" max="0" int="0"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="3"/>
  <SLIDER name="Release" id="c8bc1120a33101cd" memberName="release" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="224 40 64 64" min="0.001" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Attack" id="57958b203784347" memberName="freeEnv1Attack"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 200 64 64"
          min="0.001" max="5" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Decay" id="85c1868e6bab119c" memberName="freeEnv1Decay"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="80 200 64 64"
          min="0.001" max="5" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Sustain" id="c7af19e02e26db3f" memberName="freeEnv1Sustain"
          virtualName="MouseOverKnob" explicitFocusOrder="1" pos="152 200 64 64"
          min="0" max="1" int="0.001" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Release" id="d51ee4839c4c233" memberName="freeEnv1Release"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="224 200 64 64"
          min="0.001" max="5" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <LABEL name="Volume Envelope" id="b3d84b49f651b0e" memberName="VolEnvLabel"
         virtualName="" explicitFocusOrder="0" pos="8 8 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Volume Envelope" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="Envelope_1" id="a3abaef13a231d86" memberName="Env1Label"
         virtualName="" explicitFocusOrder="0" pos="8 168 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Envelope 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
