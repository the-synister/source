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
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (freq = new MouseOverKnob ("LFO freq"));
    freq->setRange (0.01, 50, 0);
    freq->setSliderStyle (Slider::RotaryVerticalDrag);
    freq->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    freq->addListener (this);

    addAndMakeVisible (wave = new MouseOverKnob ("wave switch"));
    wave->setRange (0, 2, 1);
    wave->setSliderStyle (Slider::RotaryVerticalDrag);
    wave->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    wave->addListener (this);

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
    registerSlider(freq, &params.lfo1freq);
    freq->setSkewFactorFromMidPoint(params.lfo1freq.getDefault());
    wave->setValue(params.lfo1wave.getUI());
    tempoSyncSwitch->setToggleState(0,0);
    notelength->setValue(params.noteLength.getUI());
    registerSlider(notelength, &params.noteLength);
    registerSlider(wave, &params.lfo1wave);
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
    wave = nullptr;
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

    freq->setBounds (8, 8, 64, 64);
    wave->setBounds (80, 8, 64, 64);
    tempoSyncSwitch->setBounds (82, 113, 150, 24);
    notelength->setBounds (168, 152, 150, 24);
    label4->setBounds (8, 152, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void LfoPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == freq)
    {
        //[UserSliderCode_freq] -- add your slider handling code here..
        //[/UserSliderCode_freq]
    }
    else if (sliderThatWasMoved == wave)
    {
        //[UserSliderCode_wave] -- add your slider handling code here..
        //[/UserSliderCode_wave]
    }
    else if (sliderThatWasMoved == notelength)
    {
        //[UserSliderCode_notelength] -- add your slider handling code here..
        //params.noteLength.setUI(notelength->getValue());
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
        params.lfo1TempSync.setUI(tempoSyncSwitch->getToggleState());
        if (tempoSyncSwitch->getToggleState()==1){
            freq->setEnabled(false);
        }else{
            freq->setEnabled(true);
        }
        //params.lfo1TempSync.setUI(std::round(static_cast<float>(tempoSyncSwitch->getToggleState())));
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
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="LFO freq" id="d136f7fae1b8db84" memberName="freq" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="8 8 64 64" min="0.01" max="50" int="0"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="wave switch" id="221421ebd522cd9a" memberName="wave" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="80 8 64 64" min="0" max="2" int="1"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
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
