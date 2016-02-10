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
#include "panels/Env1Panel.h"
#include "panels/LadderPanel.h"
#include "panels/FiltPanel.h"
#include "panels/FxPanel.h"
#include "panels/SeqPanel.h"
#include "panels/LoFiPanel.h"
#include "panels/ChorusPanel.h"
#include "panels/ClippingPanel.h"
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
    freq->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    freq->addListener (this);

    addAndMakeVisible (keyboard = new MidiKeyboardComponent (params.keyboardState,
                                                             MidiKeyboardComponent::horizontalKeyboard));
    keyboard->setName ("midi keyboard");

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

    addAndMakeVisible (foldableComponent = new FoldablePanel ("foldablePanels"));


    //[UserPreSize]
    freq->setValue(params.freq.getUI());
    freq->setTextValueSuffix(String(" ") + params.freq.unit());
    freq->setSkewFactorFromMidPoint(params.freq.getDefault());
    freq->initTextBox();
    //[/UserPreSize]

    setSize (800, 900);


    //[Constructor] You can add your own custom stuff here..

    // NOTE: preferred sectionHeight should be set (introjucer's panelHeight - 22) due to section header
    // see env panel. introjucer height is set to 252
    foldableComponent->addSection (TRANS("OSC"), new OscPanel (params, 0), SynthParams::oscColour, 250, true, 0);
    foldableComponent->addPanel(0, new OscPanel(params, 1));
    foldableComponent->addPanel(0, new OscPanel(params, 2));
    foldableComponent->addSection (TRANS("ENV"), new EnvPanel (params), SynthParams::envColour, 230, false, 1);
    foldableComponent->addPanel(1, new Env1Panel(params, 0));
    foldableComponent->addPanel(1, new Env1Panel(params, 1));
    foldableComponent->addSection (TRANS("LFO"), new LfoPanel (params, 0), SynthParams::lfoColour, 175, false, 2);
    foldableComponent->addPanel(2, new LfoPanel(params, 1));
    foldableComponent->addPanel(2, new LfoPanel(params, 2));
    foldableComponent->addSection (TRANS("FILT"), new FiltPanel (params, 0), SynthParams::filterColour, 158, false, 3);
    foldableComponent->addPanel(3, new FiltPanel (params, 1));
    foldableComponent->addSection (TRANS("FX"), new FxPanel (params), SynthParams::fxColour, 178, false, 4);
    foldableComponent->addPanel(4, new ChorusPanel(params));
    foldableComponent->addPanel(4, new LoFiPanel(params));
    foldableComponent->addPanel(4, new ClippingPanel(params));
    foldableComponent->addSection (TRANS("SEQ"), new SeqPanel (params), SynthParams::stepSeqColour, 323, false, 5);

    // set whole design from very parent GUI component
    lnf = new CustomLookAndFeel();
    LookAndFeel::setDefaultLookAndFeel(lnf);
    //[/Constructor]
}

PlugUI::~PlugUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    freq = nullptr;
    keyboard = nullptr;
    savePresetButton = nullptr;
    loadPresetButton = nullptr;
    bpmLabel = nullptr;
    bpmDisplay = nullptr;
    foldableComponent = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PlugUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff292929));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PlugUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    freq->setBounds (728, 0, 64, 64);
    keyboard->setBounds (0, 698, 800, 40);
    savePresetButton->setBounds (8, 8, 88, 24);
    loadPresetButton->setBounds (112, 8, 88, 24);
    bpmLabel->setBounds (222, 6, 40, 24);
    bpmDisplay->setBounds (270, 6, 64, 24);
    foldableComponent->setBounds (0, 72, 800, 624);
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
        params.writeXMLPatchStandalone(eSerializationParams::eAll);
        //[/UserButtonCode_savePresetButton]
    }
    else if (buttonThatWasClicked == loadPresetButton)
    {
        //[UserButtonCode_loadPresetButton] -- add your button handler code here..
        params.readXMLPatchStandalone(eSerializationParams::eAll);
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
                 initialHeight="900">
  <BACKGROUND backgroundColour="ff292929"/>
  <SLIDER name="frequency" id="b1ff18d26373a382" memberName="freq" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="728 0 64 64" rotarysliderfill="ff6c788c"
          min="220" max="880" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="64" textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="midi keyboard" id="1a69e94e9d15e3be" memberName="keyboard"
                    virtualName="" explicitFocusOrder="0" pos="0 698 800 40" class="MidiKeyboardComponent"
                    params="params.keyboardState,&#10;MidiKeyboardComponent::horizontalKeyboard"/>
  <TEXTBUTTON name="Save preset" id="f92394121ad5ea71" memberName="savePresetButton"
              virtualName="" explicitFocusOrder="0" pos="8 8 88 24" buttonText="Save preset"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Load preset" id="75d257760189a81c" memberName="loadPresetButton"
              virtualName="" explicitFocusOrder="0" pos="112 8 88 24" buttonText="Load preset"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="bpm label" id="a8863f99ab598bc6" memberName="bpmLabel"
         virtualName="" explicitFocusOrder="0" pos="222 6 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="BPM:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="bpm display" id="68b77dd638977b94" memberName="bpmDisplay"
         virtualName="" explicitFocusOrder="0" pos="270 6 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="" id="8fab73fbef5d680a" memberName="foldableComponent"
                    virtualName="FoldablePanel" explicitFocusOrder="0" pos="0 72 800 624"
                    class="FoldablePanel" params="&quot;foldablePanels&quot;"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
