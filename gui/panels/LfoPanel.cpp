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
    freq->setColour (Slider::rotarySliderFillColourId, Colour (0xff855050));
    freq->addListener (this);

    addAndMakeVisible (wave = new Slider ("wave switch"));
    wave->setRange (0, 2, 1);
    wave->setSliderStyle (Slider::LinearHorizontal);
    wave->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    wave->setColour (Slider::thumbColourId, Colour (0xff855050));
    wave->setColour (Slider::trackColourId, Colours::white);
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

    addAndMakeVisible (sineLabel = new Label ("sine label",
                                              TRANS("Sine")));
    sineLabel->setFont (Font (15.00f, Font::plain));
    sineLabel->setJustificationType (Justification::centred);
    sineLabel->setEditable (false, false, false);
    sineLabel->setColour (Label::textColourId, Colours::white);
    sineLabel->setColour (TextEditor::textColourId, Colours::black);
    sineLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (squareLabel = new Label ("square label",
                                                TRANS("Square")));
    squareLabel->setFont (Font (15.00f, Font::plain));
    squareLabel->setJustificationType (Justification::centred);
    squareLabel->setEditable (false, false, false);
    squareLabel->setColour (Label::textColourId, Colours::white);
    squareLabel->setColour (TextEditor::textColourId, Colours::black);
    squareLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sampleHoldLabel2 = new Label ("sample and hold label",
                                                     TRANS("Smp+Hold")));
    sampleHoldLabel2->setFont (Font (15.00f, Font::plain));
    sampleHoldLabel2->setJustificationType (Justification::centred);
    sampleHoldLabel2->setEditable (false, false, false);
    sampleHoldLabel2->setColour (Label::textColourId, Colours::white);
    sampleHoldLabel2->setColour (TextEditor::textColourId, Colours::black);
    sampleHoldLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lfoFadeIn = new MouseOverKnob ("LFO Fade In"));
    lfoFadeIn->setRange (0, 10, 0);
    lfoFadeIn->setSliderStyle (Slider::RotaryVerticalDrag);
    lfoFadeIn->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    lfoFadeIn->setColour (Slider::rotarySliderFillColourId, Colour (0xff855050));
    lfoFadeIn->setColour (Slider::textBoxTextColourId, Colours::white);
    lfoFadeIn->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    lfoFadeIn->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    lfoFadeIn->addListener (this);

    addAndMakeVisible (triplets = new ToggleButton ("triplets"));
    triplets->addListener (this);

    addAndMakeVisible (noteLength = new IncDecDropDown ("note length"));
    noteLength->setEditableText (false);
    noteLength->setJustificationType (Justification::centred);
    noteLength->setTextWhenNothingSelected (TRANS("Step Length"));
    noteLength->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    noteLength->addItem (TRANS("1/32"), 1);
    noteLength->addItem (TRANS("1/16"), 2);
    noteLength->addItem (TRANS("1/8"), 3);
    noteLength->addItem (TRANS("1/4"), 4);
    noteLength->addItem (TRANS("1/2"), 5);
    noteLength->addItem (TRANS("1/1"), 6);
    noteLength->addListener (this);


    //[UserPreSize]
    registerSlider(freq, &params.lfo1freq);
    freq->setSkewFactorFromMidPoint(params.lfo1freq.getDefault());
    wave->setValue(params.lfo1wave.getUI());
    tempoSyncSwitch->setToggleState(0, dontSendNotification);
    notelength->setValue(params.noteLength.getUI());
    registerSlider(notelength, &params.noteLength);
    registerSlider(wave, &params.lfo1wave);
    registerSlider(lfoFadeIn, &params.lfoFadein);
    lfoFadeIn->setSkewFactorFromMidPoint(1); // Sets the LFOFadeIn slider to logarithmic scale with value 1 in the middle of the slider
    //[/UserPreSize]

    setSize (266, 400);


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
    sineLabel = nullptr;
    squareLabel = nullptr;
    sampleHoldLabel2 = nullptr;
    lfoFadeIn = nullptr;
    triplets = nullptr;
    noteLength = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LfoPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffb16565));

    //[UserPaint] Add your own custom painting code here..
    drawGroupBorder(g, "lfo1", 0, 0,
                    this->getWidth(), this->getHeight() - 22, 25.0f, 20.0f, 5.0f, 3.0f, Colour(0xffcbca63));
    //[/UserPaint]
}

void LfoPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    freq->setBounds (8, 8, 64, 64);
    wave->setBounds (216, 40, 64, 24);
    tempoSyncSwitch->setBounds (96, 78, 150, 24);
    notelength->setBounds (136, 144, 152, 24);
    label4->setBounds (280, 112, 150, 24);
    sineLabel->setBounds (144, 40, 64, 24);
    squareLabel->setBounds (216, 8, 64, 24);
    sampleHoldLabel2->setBounds (288, 40, 80, 24);
    lfoFadeIn->setBounds (8, 80, 64, 64);
    triplets->setBounds (205, 79, 120, 24);
    noteLength->setBounds (152, 104, 87, 24);
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
    else if (sliderThatWasMoved == lfoFadeIn)
    {
        //[UserSliderCode_lfoFadeIn] -- add your slider handling code here..
        //[/UserSliderCode_lfoFadeIn]
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
    else if (buttonThatWasClicked == triplets)
    {
        //[UserButtonCode_triplets] -- add your button handler code here..
        //[/UserButtonCode_triplets]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void LfoPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == noteLength)
    {
        //[UserComboBoxCode_noteLength] -- add your combo box handling code here..
        //[/UserComboBoxCode_noteLength]
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

<JUCER_COMPONENT documentType="Component" className="LfoPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="266"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffb16565"/>
  <SLIDER name="LFO freq" id="d136f7fae1b8db84" memberName="freq" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="8 8 64 64" rotarysliderfill="ff855050"
          min="0.010000000000000000208" max="50" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="wave switch" id="221421ebd522cd9a" memberName="wave" virtualName="Slider"
          explicitFocusOrder="0" pos="216 40 64 24" thumbcol="ff855050"
          trackcol="ffffffff" min="0" max="2" int="1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="tempoSyncSwitch" id="79c4ab6638da99ef" memberName="tempoSyncSwitch"
                virtualName="" explicitFocusOrder="0" pos="96 78 150 24" buttonText="Tempo Sync"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="notelength" id="6fa8673edff62372" memberName="notelength"
          virtualName="" explicitFocusOrder="0" pos="136 144 152 24" min="1"
          max="32" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="22b737542921a599" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="280 112 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Change note length 1/x" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="sine label" id="b40cd065bdc2086c" memberName="sineLabel"
         virtualName="" explicitFocusOrder="0" pos="144 40 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Sine" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="square label" id="5adc08b39551a18d" memberName="squareLabel"
         virtualName="" explicitFocusOrder="0" pos="216 8 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Square" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="sample and hold label" id="f2be9ba7b41efda2" memberName="sampleHoldLabel2"
         virtualName="" explicitFocusOrder="0" pos="288 40 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Smp+Hold" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="LFO Fade In" id="16de18984b3c12ef" memberName="lfoFadeIn"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="8 80 64 64"
          rotarysliderfill="ff855050" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="triplets" id="9c9e2393225a5b09" memberName="triplets" virtualName=""
                explicitFocusOrder="0" pos="205 79 120 24" buttonText="triplets"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="note length" id="9cc1e82a498c26a7" memberName="noteLength"
            virtualName="IncDecDropDown" explicitFocusOrder="0" pos="152 104 87 24"
            editable="0" layout="36" items="1/32&#10;1/16&#10;1/8&#10;1/4&#10;1/2&#10;1/1"
            textWhenNonSelected="Step Length" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
