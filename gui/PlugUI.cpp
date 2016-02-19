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
#include "panels/EnvPanel.h"
#include "panels/Env1Panel.h"
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
    freq->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    freq->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    freq->setColour (Slider::textBoxTextColourId, Colours::white);
    freq->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    freq->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    freq->addListener (this);

    addAndMakeVisible (keyboard = new MidiKeyboardComponent (params.keyboardState,
                                                             MidiKeyboardComponent::horizontalKeyboard));
    keyboard->setName ("midi keyboard");

    addAndMakeVisible (savePresetButton = new TextButton ("Save preset"));
    savePresetButton->addListener (this);

    addAndMakeVisible (loadPresetButton = new TextButton ("Load preset"));
    loadPresetButton->addListener (this);

    addAndMakeVisible (foldableComponent = new FoldablePanel ("foldablePanels"));

    addAndMakeVisible (patchNameEditor = new TextEditor ("new text editor"));
    patchNameEditor->setMultiLine (false);
    patchNameEditor->setReturnKeyStartsNewLine (false);
    patchNameEditor->setReadOnly (false);
    patchNameEditor->setScrollbarsShown (true);
    patchNameEditor->setCaretVisible (true);
    patchNameEditor->setPopupMenuEnabled (true);
    patchNameEditor->setText (String::empty);


    //[UserPreSize]
    freq->setValue(params.freq.getUI());
    freq->setTextValueSuffix(String(" ") + params.freq.unit());
    freq->setSkewFactorFromMidPoint(params.freq.getDefault());
    freq->initTextBox();
    freq->setDefaultValue(params.freq.getDefault());
    //[/UserPreSize]

    setSize (800, 900);


    //[Constructor] You can add your own custom stuff here..
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
    foldableComponent->addSection (TRANS("SEQ"), new SeqPanel (params), SynthParams::stepSeqColour, 300, false, 5);

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
    foldableComponent = nullptr;
    patchNameEditor = nullptr;


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

    freq->setBounds (720, 0, 64, 64);
    keyboard->setBounds (0, 698, 800, 40);
    savePresetButton->setBounds (112, 40, 88, 24);
    loadPresetButton->setBounds (112, 8, 88, 24);
    foldableComponent->setBounds (0, 72, 800, 624);
    patchNameEditor->setBounds (8, 24, 96, 24);
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
        params.patchName = patchNameEditor->getText();
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
    if(params.patchNameDirty) updateDirtyPatchname(params.patchName);
}

void PlugUI::updateDirtyPatchname(const String patchName)
{
    patchNameEditor->setText(patchName);
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
          explicitFocusOrder="0" pos="720 0 64 64" rotarysliderfill="ff6c788c"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="ffffff"
          min="220" max="880" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="midi keyboard" id="1a69e94e9d15e3be" memberName="keyboard"
                    virtualName="" explicitFocusOrder="0" pos="0 698 800 40" class="MidiKeyboardComponent"
                    params="params.keyboardState,&#10;MidiKeyboardComponent::horizontalKeyboard"/>
  <TEXTBUTTON name="Save preset" id="f92394121ad5ea71" memberName="savePresetButton"
              virtualName="" explicitFocusOrder="0" pos="112 40 88 24" buttonText="Save preset"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Load preset" id="75d257760189a81c" memberName="loadPresetButton"
              virtualName="" explicitFocusOrder="0" pos="112 8 88 24" buttonText="Load preset"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="8fab73fbef5d680a" memberName="foldableComponent"
                    virtualName="FoldablePanel" explicitFocusOrder="0" pos="0 72 800 624"
                    class="FoldablePanel" params="&quot;foldablePanels&quot;"/>
  <TEXTEDITOR name="new text editor" id="3f8916006abe85bf" memberName="patchNameEditor"
              virtualName="" explicitFocusOrder="0" pos="8 24 96 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
