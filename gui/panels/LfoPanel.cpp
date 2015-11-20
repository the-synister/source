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

#include "LfoPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
LfoPanel::LfoPanel (SynthParams &p)
    : params(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (freq = new Slider ("LFO freq"));
    freq->setRange (0.01, 50, 0);
    freq->setSliderStyle (Slider::RotaryVerticalDrag);
    freq->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    freq->addListener (this);

    addAndMakeVisible (label = new Label ("freq label",
                                          TRANS("freq")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (wave = new Slider ("wave switch"));
    wave->setRange (0, 1, 1);
    wave->setSliderStyle (Slider::LinearHorizontal);
    wave->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    wave->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("sine wave")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("square wave")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (tempoSyncSwitch = new ToggleButton ("tempoSyncSwitch"));
    tempoSyncSwitch->setButtonText (TRANS("Tempo Sync"));
    tempoSyncSwitch->addListener (this);

    addAndMakeVisible (notelength = new Slider ("notelength"));
    notelength->setRange (1, 32, 1);
    notelength->setSliderStyle (Slider::IncDecButtons);
    notelength->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    notelength->addListener (this);

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Change note length 1/x")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    freq->setValue(params.lfo1freq.getUI());
    freq->setTextValueSuffix(String(" ") + params.lfo1freq.unit());
    freq->setSkewFactorFromMidPoint(params.lfo1freq.getDefault());
    wave->setValue(params.lfo1wave.getUI());
    tempoSyncSwitch->setValue(params.lfo1TempSync.getUI());
    notelength->setValue(params.noteLength.getUI());
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

LfoPanel::~LfoPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    freq = nullptr;
    label = nullptr;
    wave = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    tempoSyncSwitch = nullptr;
    notelength = nullptr;
    label4 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LfoPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void LfoPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    freq->setBounds (8, 32, 64, 64);
    label->setBounds (8, 8, 64, 16);
    wave->setBounds (166, 40, 41, 32);
    label2->setBounds (112, 72, 71, 24);
    label3->setBounds (189, 72, 83, 24);
    tempoSyncSwitch->setBounds (82, 113, 150, 24);
    notelength->setBounds (168, 152, 150, 24);
    label4->setBounds (8, 152, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void LfoPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == freq)
    {
        //[UserSliderCode_freq] -- add your slider handling code here..
        params.lfo1freq.setUI(static_cast<float>(freq->getValue()));
        //[/UserSliderCode_freq]
    }
    else if (sliderThatWasMoved == wave)
    {
        //[UserSliderCode_wave] -- add your slider handling code here..
        params.lfo1wave.setUI(std::round(static_cast<float>(wave->getValue())));
        //[/UserSliderCode_wave]
    }
    else if (sliderThatWasMoved == notelength)
    {
        //[UserSliderCode_notelength] -- add your slider handling code here..
        //[/UserSliderCode_notelength]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void LfoPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == tempoSyncSwitch)
    {
        //[UserButtonCode_tempoSyncSwitch] -- add your button handler code here..
        //[/UserButtonCode_tempoSyncSwitch]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="LfoPanel" componentName=""
                 parentClasses="public Component" constructorParams="SynthParams &amp;p"
                 variableInitialisers="params(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="LFO freq" id="d136f7fae1b8db84" memberName="freq" virtualName=""
          explicitFocusOrder="0" pos="8 32 64 64" min="0.01" max="50" int="0"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="freq label" id="44d54eb754724ef0" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 8 64 16" edTextCol="ff000000" edBkgCol="0"
         labelText="freq" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="wave switch" id="221421ebd522cd9a" memberName="wave" virtualName=""
          explicitFocusOrder="0" pos="166 40 41 32" min="0" max="1" int="1"
          style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="e7b5c6b105490306" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="112 72 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="sine wave" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a5e6136827f3a519" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="189 72 83 24" edTextCol="ff000000"
         edBkgCol="0" labelText="square wave" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="tempoSyncSwitch" id="79c4ab6638da99ef" memberName="tempoSyncSwitch"
                virtualName="" explicitFocusOrder="0" pos="82 113 150 24" buttonText="Tempo Sync"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="notelength" id="6fa8673edff62372" memberName="notelength"
          virtualName="" explicitFocusOrder="0" pos="168 152 150 24" min="1"
          max="32" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="22b737542921a599" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="8 152 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Change note length 1/x" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
