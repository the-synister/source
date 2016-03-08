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
#include "panels/InfoPanel.h"
//[/Headers]

#include "PlugUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PlugUI::PlugUI (SynthParams &p)
    : PanelBase(p), params(p)
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
    savePresetButton->setButtonText (TRANS("save"));
    savePresetButton->addListener (this);
    savePresetButton->setColour (TextButton::buttonColourId, Colours::white);
    savePresetButton->setColour (TextButton::textColourOnId, Colour (0xff6c788c));
    savePresetButton->setColour (TextButton::textColourOffId, Colour (0xff6c788c));

    addAndMakeVisible (loadPresetButton = new TextButton ("Load preset"));
    loadPresetButton->setButtonText (TRANS("load"));
    loadPresetButton->addListener (this);
    loadPresetButton->setColour (TextButton::buttonColourId, Colours::white);
    loadPresetButton->setColour (TextButton::textColourOnId, Colour (0xff6c788c));
    loadPresetButton->setColour (TextButton::textColourOffId, Colour (0xff6c788c));

    addAndMakeVisible (foldableComponent = new FoldablePanel ("foldablePanels"));

    addAndMakeVisible (masterAmp = new MouseOverKnob ("amp"));
    masterAmp->setRange (-96, 12, 0);
    masterAmp->setSliderStyle (Slider::LinearBar);
    masterAmp->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    masterAmp->setColour (Slider::backgroundColourId, Colour (0x00ffffff));
    masterAmp->setColour (Slider::thumbColourId, Colours::grey);
    masterAmp->setColour (Slider::trackColourId, Colours::white);
    masterAmp->setColour (Slider::rotarySliderFillColourId, Colours::blue);
    masterAmp->setColour (Slider::textBoxTextColourId, Colours::white);
    masterAmp->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    masterAmp->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    masterAmp->addListener (this);

    addAndMakeVisible (masterPan = new MouseOverKnob ("pan"));
    masterPan->setRange (-100, 100, 0);
    masterPan->setSliderStyle (Slider::LinearBar);
    masterPan->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    masterPan->setColour (Slider::thumbColourId, Colour (0xff292929));
    masterPan->setColour (Slider::trackColourId, Colours::white);
    masterPan->setColour (Slider::rotarySliderFillColourId, Colours::blue);
    masterPan->setColour (Slider::textBoxTextColourId, Colours::white);
    masterPan->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    masterPan->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    masterPan->addListener (this);

    addAndMakeVisible (patchNameEditor = new TextEditor ("new text editor"));
    patchNameEditor->setMultiLine (false);
    patchNameEditor->setReturnKeyStartsNewLine (false);
    patchNameEditor->setReadOnly (false);
    patchNameEditor->setScrollbarsShown (true);
    patchNameEditor->setCaretVisible (true);
    patchNameEditor->setPopupMenuEnabled (true);
    patchNameEditor->setText (String::empty);

    addAndMakeVisible (logoInfoButton = new ImageButton ("logo info button"));
    logoInfoButton->setButtonText (String::empty);
    logoInfoButton->addListener (this);

    logoInfoButton->setImages (false, true, true,
                               ImageCache::getFromMemory (BinaryData::synisterLogoSmall_png, BinaryData::synisterLogoSmall_pngSize), 1.000f, Colour (0x00ffffff),
                               ImageCache::getFromMemory (BinaryData::synisterLogoSmall_png, BinaryData::synisterLogoSmall_pngSize), 1.000f, Colours::white,
                               ImageCache::getFromMemory (BinaryData::synisterLogoSmall_png, BinaryData::synisterLogoSmall_pngSize), 1.000f, Colours::white);

    //[UserPreSize]
    registerSlider(freq, &params.freq);
    registerSlider(masterAmp, &params.masterAmp);
    registerSlider(masterPan, &params.masterPan);

    freq->setSkewFactorFromMidPoint(params.freq.getDefault());
    freq->initTextBox();
    freq->setDefaultValue(params.freq.getDefault());

    //patchNameEditor->addListener (this);
    //[/UserPreSize]

    setSize (812, 693);


    //[Constructor] You can add your own custom stuff here..
    foldableComponent->addSection (TRANS("oscillators"), new OscPanel (params, 0), SynthParams::oscColour, 250, true, 0);
    foldableComponent->addPanel(0, new OscPanel(params, 1));
    foldableComponent->addPanel(0, new OscPanel(params, 2));
    foldableComponent->addSection (TRANS("envelopes"), new EnvPanel (params), SynthParams::envColour, 230, false, 1);
    foldableComponent->addPanel(1, new Env1Panel(params, 0));
    foldableComponent->addPanel(1, new Env1Panel(params, 1));
    foldableComponent->addSection (TRANS("LFOs"), new LfoPanel (params, 0), SynthParams::lfoColour, 175, false, 2);
    foldableComponent->addPanel(2, new LfoPanel(params, 1));
    foldableComponent->addPanel(2, new LfoPanel(params, 2));
    foldableComponent->addSection (TRANS("filters"), new FiltPanel (params, 0), SynthParams::filterColour, 158, false, 3);
    foldableComponent->addPanel(3, new FiltPanel (params, 1));
    foldableComponent->addSection (TRANS("FX"), new FxPanel (params), SynthParams::fxColour, 178, false, 4);
    foldableComponent->addPanel(4, new ChorusPanel(params));
    foldableComponent->addPanel(4, new LoFiPanel(params));
    foldableComponent->addPanel(4, new ClippingPanel(params));
    foldableComponent->addSection (TRANS("step sequencer"), new SeqPanel (params), SynthParams::stepSeqColour, 300, false, 5);

    // set whole design from very parent GUI component
    lnf = new CustomLookAndFeel();
    LookAndFeel::setDefaultLookAndFeel(lnf);

    // sub window as info panel screen
    addAndMakeVisible(infoScreen = new InfoWindow("Info Screen", Colours::black, InfoWindow::TitleBarButtons::closeButton));
    infoScreen->setAlwaysOnTop(true);
    //infoScreen->setDraggable(false);

    // create infoscreen gui component and set as content of sub window
    infoScreen->setContentOwned(new InfoPanel(params), true);
    infoScreen->centreWithSize(infoScreen->getWidth(), infoScreen->getHeight());
    infoScreen->setVisible(false);
    //[/Constructor]
}

PlugUI::~PlugUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    infoScreen = nullptr;
    //[/Destructor_pre]

    freq = nullptr;
    keyboard = nullptr;
    savePresetButton = nullptr;
    loadPresetButton = nullptr;
    foldableComponent = nullptr;
    masterAmp = nullptr;
    masterPan = nullptr;
    patchNameEditor = nullptr;
    logoInfoButton = nullptr;


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

    freq->setBounds (712, 8, 80, 64);
    keyboard->setBounds (-1, 651, 812, 40);
    savePresetButton->setBounds (60, 14, 50, 20);
    loadPresetButton->setBounds (8, 14, 50, 20);
    foldableComponent->setBounds (0, 72, 812, 576);
    masterAmp->setBounds (199, 24, 100, 32);
    masterPan->setBounds (498, 24, 80, 32);
    patchNameEditor->setBounds (8, 37, 102, 24);
    logoInfoButton->setBounds (322, 16, 153, 40);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PlugUI::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == freq)
    {
        //[UserSliderCode_freq] -- add your slider handling code here..
        //[/UserSliderCode_freq]
    }
    else if (sliderThatWasMoved == masterAmp)
    {
        //[UserSliderCode_masterAmp] -- add your slider handling code here..
        //[/UserSliderCode_masterAmp]
    }
    else if (sliderThatWasMoved == masterPan)
    {
        //[UserSliderCode_masterPan] -- add your slider handling code here..
        //[/UserSliderCode_masterPan]
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
    else if (buttonThatWasClicked == logoInfoButton)
    {
        //[UserButtonCode_logoInfoButton] -- add your button handler code here..
        infoScreen->centreWithSize(infoScreen->getWidth(), infoScreen->getHeight());
        infoScreen->setVisible(true);
        infoScreen->grabKeyboardFocus();
        //[/UserButtonCode_logoInfoButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PlugUI::timerCallback()
{
    if (params.patchNameDirty) {
        updateDirtyPatchname(params.patchName);
        params.patchNameDirty = 0;
    }
}

void PlugUI::updateDirtyPatchname(const String patchName)
{
    patchNameEditor->setText(patchName);
}

void PlugUI::textEditorFocusLost(TextEditor &editor)
{
    params.patchName = editor.getText();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PlugUI" componentName=""
                 parentClasses="public PanelBase, public TextEditorListener" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p), params(p)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="812" initialHeight="693">
  <BACKGROUND backgroundColour="ff292929"/>
  <SLIDER name="frequency" id="b1ff18d26373a382" memberName="freq" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="712 8 80 64" rotarysliderfill="ff6c788c"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="ffffff"
          min="220" max="880" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="midi keyboard" id="1a69e94e9d15e3be" memberName="keyboard"
                    virtualName="" explicitFocusOrder="0" pos="-1 651 812 40" class="MidiKeyboardComponent"
                    params="params.keyboardState,&#10;MidiKeyboardComponent::horizontalKeyboard"/>
  <TEXTBUTTON name="Save preset" id="f92394121ad5ea71" memberName="savePresetButton"
              virtualName="" explicitFocusOrder="0" pos="60 14 50 20" bgColOff="ffffffff"
              textCol="ff6c788c" textColOn="ff6c788c" buttonText="save" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Load preset" id="75d257760189a81c" memberName="loadPresetButton"
              virtualName="" explicitFocusOrder="0" pos="8 14 50 20" bgColOff="ffffffff"
              textCol="ff6c788c" textColOn="ff6c788c" buttonText="load" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="8fab73fbef5d680a" memberName="foldableComponent"
                    virtualName="FoldablePanel" explicitFocusOrder="0" pos="0 72 812 576"
                    class="FoldablePanel" params="&quot;foldablePanels&quot;"/>
  <SLIDER name="amp" id="3279e0342166e50f" memberName="masterAmp" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="199 24 100 32" bkgcol="ffffff" thumbcol="ff808080"
          trackcol="ffffffff" rotarysliderfill="ff0000ff" textboxtext="ffffffff"
          textboxbkgd="ffffff" textboxoutline="ffffff" min="-96" max="12"
          int="0" style="LinearBar" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="0" textBoxHeight="0" skewFactor="1"/>
  <SLIDER name="pan" id="d8f72bae093dfe35" memberName="masterPan" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="498 24 80 32" thumbcol="ff292929"
          trackcol="ffffffff" rotarysliderfill="ff0000ff" textboxtext="ffffffff"
          textboxbkgd="ffffff" textboxoutline="ffffff" min="-100" max="100"
          int="0" style="LinearBar" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="0" textBoxHeight="0" skewFactor="1"/>
  <TEXTEDITOR name="new text editor" id="3f8916006abe85bf" memberName="patchNameEditor"
              virtualName="" explicitFocusOrder="0" pos="8 37 102 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <IMAGEBUTTON name="logo info button" id="a24de2ae6a78130c" memberName="logoInfoButton"
               virtualName="" explicitFocusOrder="0" pos="322 16 153 40" buttonText=""
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::synisterLogoSmall_png" opacityNormal="1"
               colourNormal="ffffff" resourceOver="BinaryData::synisterLogoSmall_png"
               opacityOver="1" colourOver="ffffffff" resourceDown="BinaryData::synisterLogoSmall_png"
               opacityDown="1" colourDown="ffffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
