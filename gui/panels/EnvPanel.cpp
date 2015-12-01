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


    //[UserPreSize]
    registerSlider(attack, &params.envAttack);
    registerSlider(decay, &params.envDecay);
    registerSlider(sustain, &params.envSustain);
    registerSlider(release, &params.envRelease);
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

    attack->setBounds (8, 8, 64, 64);
    decay->setBounds (80, 8, 64, 64);
    sustain->setBounds (152, 8, 64, 64);
    release->setBounds (224, 8, 64, 64);
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
          explicitFocusOrder="0" pos="8 8 64 64" min="0.001" max="5" int="0"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Decay" id="84a4159bee0728d6" memberName="decay" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="80 8 64 64" min="0.001" max="5" int="0"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="Sustain" id="4bc867c016d7595f" memberName="sustain" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="152 8 64 64" min="-96" max="0" int="0"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="3"/>
  <SLIDER name="Release" id="c8bc1120a33101cd" memberName="release" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="224 8 64 64" min="0.001" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
