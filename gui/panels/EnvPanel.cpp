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
    : params(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (attack = new Slider ("attack"));
    attack->setRange (0.001, 5, 0);
    attack->setSliderStyle (Slider::RotaryVerticalDrag);
    attack->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    attack->addListener (this);
    attack->setSkewFactor (0.5);

    addAndMakeVisible (label1 = new Label ("new label",
                                           TRANS("Attack")));
    label1->setFont (Font (15.00f, Font::plain));
    label1->setJustificationType (Justification::centred);
    label1->setEditable (false, false, false);
    label1->setColour (TextEditor::textColourId, Colours::black);
    label1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (decay = new Slider ("decay"));
    decay->setRange (0.001, 5, 0);
    decay->setSliderStyle (Slider::RotaryVerticalDrag);
    decay->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    decay->addListener (this);
    decay->setSkewFactor (0.5);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Decay")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centred);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sustain = new Slider ("sustain"));
    sustain->setRange (-96, 0, 0);
    sustain->setSliderStyle (Slider::RotaryVerticalDrag);
    sustain->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sustain->addListener (this);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Sustain")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (release = new Slider ("release"));
    release->setRange (0.001, 5, 0);
    release->setSliderStyle (Slider::RotaryVerticalDrag);
    release->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    release->addListener (this);
    release->setSkewFactor (0.5);

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Release")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centred);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    attack->setValue(params.envAttack.getUI());
    attack->setTextValueSuffix(String(" ") + params.envAttack.unit());
    decay->setValue(params.envDecay.getUI());
    decay->setTextValueSuffix(String(" ") + params.envDecay.unit());
    sustain->setValue(params.envSustain.getUI());
    sustain->setTextValueSuffix(String(" ") + params.envSustain.unit());
    release->setValue(params.envRelease.getUI());
    release->setTextValueSuffix(String(" ") + params.envRelease.unit());
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
    label1 = nullptr;
    decay = nullptr;
    label2 = nullptr;
    sustain = nullptr;
    label3 = nullptr;
    release = nullptr;
    label4 = nullptr;


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

    attack->setBounds (8, 32, 64, 64);
    label1->setBounds (8, 8, 64, 16);
    decay->setBounds (80, 32, 64, 64);
    label2->setBounds (80, 8, 64, 16);
    sustain->setBounds (152, 32, 64, 64);
    label3->setBounds (152, 8, 64, 16);
    release->setBounds (224, 32, 64, 64);
    label4->setBounds (224, 8, 64, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void EnvPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == attack)
    {
        //[UserSliderCode_attack] -- add your slider handling code here..
        params.envAttack.setUI(static_cast<float>(attack->getValue()));
        //[/UserSliderCode_attack]
    }
    else if (sliderThatWasMoved == decay)
    {
        //[UserSliderCode_decay] -- add your slider handling code here..
        params.envDecay.setUI(static_cast<float>(decay->getValue()));
        //[/UserSliderCode_decay]
    }
    else if (sliderThatWasMoved == sustain)
    {
        //[UserSliderCode_sustain] -- add your slider handling code here..
        params.envSustain.setUI(static_cast<float>(sustain->getValue()));
        //[/UserSliderCode_sustain]
    }
    else if (sliderThatWasMoved == release)
    {
        //[UserSliderCode_release] -- add your slider handling code here..
        params.envRelease.setUI(static_cast<float>(release->getValue()));
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
                 parentClasses="public Component" constructorParams="SynthParams &amp;p"
                 variableInitialisers="params(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="attack" id="3c32cde7173ddbe6" memberName="attack" virtualName=""
          explicitFocusOrder="0" pos="8 32 64 64" min="0.001" max="5" int="0"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <LABEL name="new label" id="9d171eeecf3cc269" memberName="label1" virtualName=""
         explicitFocusOrder="0" pos="8 8 64 16" edTextCol="ff000000" edBkgCol="0"
         labelText="Attack" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="decay" id="84a4159bee0728d6" memberName="decay" virtualName=""
          explicitFocusOrder="0" pos="80 32 64 64" min="0.001" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <LABEL name="new label" id="e17b991ffdabe7cd" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="80 8 64 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Decay" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="sustain" id="4bc867c016d7595f" memberName="sustain" virtualName=""
          explicitFocusOrder="0" pos="152 32 64 64" min="-96" max="0" int="0"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="139710301efdafa4" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="152 8 64 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Sustain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="release" id="c8bc1120a33101cd" memberName="release" virtualName=""
          explicitFocusOrder="0" pos="224 32 64 64" min="0.001" max="5"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <LABEL name="new label" id="935d071bb8ce6b2c" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="224 8 64 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Release" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
