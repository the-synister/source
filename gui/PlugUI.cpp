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
#include "panels/OscPanel.h"
#include "panels/LfoPanel.h"
#include "panels/AmpPanel.h"
#include "panels/EnvPanel.h"
#include "panels/LadderPanel.h"
#include "panels/FiltPanel.h"
#include "panels/FxPanel.h"
#include "panels/SeqPanel.h"
//[/Headers]

#include "PlugUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PlugUI::PlugUI (SynthParams &p)
    : params(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    startTimerHz (30);
    //[/Constructor_pre]

    addAndMakeVisible (freq = new MouseOverKnob ("frequency"));
    freq->setRange (220, 880, 0);
    freq->setSliderStyle (Slider::RotaryVerticalDrag);
    freq->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    freq->addListener (this);

    addAndMakeVisible (keyboard = new MidiKeyboardComponent (params.keyboardState,
                                                             MidiKeyboardComponent::horizontalKeyboard));
    keyboard->setName ("midi keyboard");

    addAndMakeVisible (tabs = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabs->setTabBarDepth (30);
    tabs->addTab (TRANS("OSC"), Colours::lightgrey, new OscPanel (params), true);
    tabs->addTab (TRANS("LFO"), Colours::lightgrey, new LfoPanel (params), true);
    tabs->addTab (TRANS("ENV"), Colours::lightgrey, new EnvPanel (params), true);
    tabs->addTab (TRANS("FILT"), Colours::lightgrey, new FiltPanel (params), true);
    tabs->addTab (TRANS("AMP"), Colours::lightgrey, new AmpPanel (params), true);
    tabs->addTab (TRANS("FX"), Colours::lightgrey, new FxPanel (params), true);
    tabs->addTab (TRANS("LADDER"), Colours::lightgrey, new LadderPanel (params), true);
    tabs->addTab (TRANS("SEQ"), Colours::lightgrey, new SeqPanel (params), true);
    tabs->setCurrentTabIndex (0);

    addAndMakeVisible (savePresetButton = new TextButton ("Save preset"));
    savePresetButton->addListener (this);

    addAndMakeVisible (loadPresetButton = new TextButton ("Load preset"));
    loadPresetButton->addListener (this);

    addAndMakeVisible (bpmLabel = new Label ("bpm label",
                                             TRANS("BPM:")));
    bpmLabel->setFont (Font (15.00f, Font::plain));
    bpmLabel->setJustificationType (Justification::centredLeft);
    bpmLabel->setEditable (false, false, false);
    bpmLabel->setColour (TextEditor::textColourId, Colours::black);
    bpmLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (bpmDisplay = new Label ("bpm display",
                                               String::empty));
    bpmDisplay->setFont (Font (15.00f, Font::plain));
    bpmDisplay->setJustificationType (Justification::centredLeft);
    bpmDisplay->setEditable (false, false, false);
    bpmDisplay->setColour (TextEditor::textColourId, Colours::black);
    bpmDisplay->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    freq->setValue(params.freq.getUI());
    freq->setTextValueSuffix(String(" ") + params.freq.unit());
    freq->setSkewFactorFromMidPoint(params.freq.getDefault());
    freq->initTextBox();
    //[/UserPreSize]

    setSize (800, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PlugUI::~PlugUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    freq = nullptr;
    keyboard = nullptr;
    tabs = nullptr;
    savePresetButton = nullptr;
    loadPresetButton = nullptr;
    bpmLabel = nullptr;
    bpmDisplay = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PlugUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PlugUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    freq->setBounds (728, 8, 64, 64);
    keyboard->setBounds (8, 552, 784, 40);
    tabs->setBounds (8, 128, 784, 416);
    savePresetButton->setBounds (8, 8, 88, 24);
    loadPresetButton->setBounds (8, 40, 88, 24);
    bpmLabel->setBounds (127, 7, 40, 24);
    bpmDisplay->setBounds (175, 7, 64, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PlugUI::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == freq)
    {
        //[UserSliderCode_freq] -- add your slider handling code here..
        params.freq.setUI(static_cast<float>(freq->getValue()));
        //[/UserSliderCode_freq]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PlugUI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == savePresetButton)
    {
        //[UserButtonCode_savePresetButton] -- add your button handler code here..
        params.writeXMLPatchStandalone();
        //[/UserButtonCode_savePresetButton]
    }
    else if (buttonThatWasClicked == loadPresetButton)
    {
        //[UserButtonCode_loadPresetButton] -- add your button handler code here..
        params.readXMLPatchStandalone();
        //[/UserButtonCode_loadPresetButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PlugUI::timerCallback()
{
    updateBpmDisplay (params.positionInfo[params.getGUIIndex()]);
}

void PlugUI::updateBpmDisplay(const AudioPlayHead::CurrentPositionInfo &currentPos)
{
    lastBpmInfo = static_cast<float>(currentPos.bpm);

    MemoryOutputStream bpmDisplayText;

    bpmDisplayText << String(currentPos.bpm, 2);
    bpmDisplay->setText(bpmDisplayText.toString(), dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PlugUI" componentName=""
                 parentClasses="public Component, private Timer" constructorParams="SynthParams &amp;p"
                 variableInitialisers="params(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="800"
                 initialHeight="600">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="frequency" id="b1ff18d26373a382" memberName="freq" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="728 8 64 64" min="220" max="880"
          int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="64" textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="midi keyboard" id="1a69e94e9d15e3be" memberName="keyboard"
                    virtualName="" explicitFocusOrder="0" pos="8 552 784 40" class="MidiKeyboardComponent"
                    params="params.keyboardState,&#10;MidiKeyboardComponent::horizontalKeyboard"/>
  <TABBEDCOMPONENT name="tabs" id="748541b462cb42f4" memberName="tabs" virtualName=""
                   explicitFocusOrder="0" pos="8 128 784 416" orientation="top"
                   tabBarDepth="30" initialTab="0">
    <TAB name="OSC" colour="ffd3d3d3" useJucerComp="0" contentClassName="OscPanel"
         constructorParams="params" jucerComponentFile=""/>
    <TAB name="LFO" colour="ffd3d3d3" useJucerComp="0" contentClassName="LfoPanel"
         constructorParams="params" jucerComponentFile=""/>
    <TAB name="ENV" colour="ffd3d3d3" useJucerComp="0" contentClassName="EnvPanel"
         constructorParams="params" jucerComponentFile=""/>
    <TAB name="FILT" colour="ffd3d3d3" useJucerComp="0" contentClassName="FiltPanel"
         constructorParams="params" jucerComponentFile=""/>
    <TAB name="AMP" colour="ffd3d3d3" useJucerComp="0" contentClassName="AmpPanel"
         constructorParams="params" jucerComponentFile=""/>
    <TAB name="FX" colour="ffd3d3d3" useJucerComp="0" contentClassName="FxPanel"
         constructorParams="params" jucerComponentFile=""/>
    <TAB name="FX" colour="ffd3d3d3" useJucerComp="0" contentClassName=""
         constructorParams="" jucerComponentFile=""/>
    <TAB name="LADDER" colour="ffd3d3d3" useJucerComp="0" contentClassName="LadderPanel"
         constructorParams="params" jucerComponentFile=""/>
    <TAB name="SEQ" colour="ffd3d3d3" useJucerComp="0" contentClassName="SeqPanel"
         constructorParams="params" jucerComponentFile=""/>
  </TABBEDCOMPONENT>
  <TEXTBUTTON name="Save preset" id="f92394121ad5ea71" memberName="savePresetButton"
              virtualName="" explicitFocusOrder="0" pos="8 8 88 24" buttonText="Save preset"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Load preset" id="75d257760189a81c" memberName="loadPresetButton"
              virtualName="" explicitFocusOrder="0" pos="8 40 88 24" buttonText="Load preset"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="bpm label" id="a8863f99ab598bc6" memberName="bpmLabel"
         virtualName="" explicitFocusOrder="0" pos="127 7 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="BPM:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="bpm display" id="68b77dd638977b94" memberName="bpmDisplay"
         virtualName="" explicitFocusOrder="0" pos="175 7 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
