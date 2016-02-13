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
LfoPanel::LfoPanel (SynthParams &p, int lfoNumber)
    : PanelBase(p),
      lfo(p.lfo[lfoNumber])
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (freq = new MouseOverKnob ("LFO freq"));
    freq->setRange (0.01, 50, 0);
    freq->setSliderStyle (Slider::RotaryVerticalDrag);
    freq->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
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
    tempoSyncSwitch->setColour (ToggleButton::textColourId, Colours::white);

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
    lfoFadeIn->setTextBoxStyle (Slider::TextBoxBelow, false, 56, 20);
    lfoFadeIn->setColour (Slider::rotarySliderFillColourId, Colour (0xff855050));
    lfoFadeIn->setColour (Slider::textBoxTextColourId, Colours::white);
    lfoFadeIn->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    lfoFadeIn->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    lfoFadeIn->addListener (this);

    addAndMakeVisible (triplets = new ToggleButton ("triplets"));
    triplets->addListener (this);
    triplets->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (noteLength = new IncDecDropDown ("note length"));
    noteLength->setEditableText (false);
    noteLength->setJustificationType (Justification::centred);
    noteLength->setTextWhenNothingSelected (TRANS("Note Length"));
    noteLength->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    noteLength->addItem (TRANS("1/1"), 1);
    noteLength->addItem (TRANS("1/2"), 2);
    noteLength->addItem (TRANS("1/4"), 3);
    noteLength->addItem (TRANS("1/8"), 4);
    noteLength->addItem (TRANS("1/16"), 5);
    noteLength->addItem (TRANS("1/32"), 6);
    noteLength->addListener (this);

    addAndMakeVisible (freqModAmount1 = new MouseOverKnob ("freqModAmount1"));
    freqModAmount1->setRange (0, 1, 0);
    freqModAmount1->setSliderStyle (Slider::RotaryVerticalDrag);
    freqModAmount1->setTextBoxStyle (Slider::TextBoxBelow, false, 0, 0);
    freqModAmount1->setColour (Slider::rotarySliderFillColourId, Colours::white);
    freqModAmount1->setColour (Slider::textBoxTextColourId, Colours::white);
    freqModAmount1->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    freqModAmount1->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    freqModAmount1->addListener (this);

    addAndMakeVisible (freqModAmount2 = new MouseOverKnob ("freqModAmount2"));
    freqModAmount2->setRange (0, 1, 0);
    freqModAmount2->setSliderStyle (Slider::RotaryVerticalDrag);
    freqModAmount2->setTextBoxStyle (Slider::TextBoxBelow, false, 0, 0);
    freqModAmount2->setColour (Slider::rotarySliderFillColourId, Colours::white);
    freqModAmount2->setColour (Slider::textBoxTextColourId, Colours::white);
    freqModAmount2->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    freqModAmount2->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    freqModAmount2->addListener (this);

    addAndMakeVisible (freqModSrc1 = new ComboBox ("freqModSrc1"));
    freqModSrc1->setEditableText (false);
    freqModSrc1->setJustificationType (Justification::centred);
    freqModSrc1->setTextWhenNothingSelected (TRANS("No Mod"));
    freqModSrc1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    freqModSrc1->addListener (this);

    addAndMakeVisible (freqModSrc2 = new ComboBox ("freqModSrc2"));
    freqModSrc2->setEditableText (false);
    freqModSrc2->setJustificationType (Justification::centred);
    freqModSrc2->setTextWhenNothingSelected (TRANS("No Mod"));
    freqModSrc2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    freqModSrc2->addListener (this);

    addAndMakeVisible (lfoGain = new ComboBox ("lfoGain"));
    lfoGain->setEditableText (false);
    lfoGain->setJustificationType (Justification::centred);
    lfoGain->setTextWhenNothingSelected (TRANS("No Mod"));
    lfoGain->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    lfoGain->addListener (this);


    //[UserPreSize]
    registerSlider(freq, &lfo.freq);
    freq->setSkewFactorFromMidPoint(lfo.freq.getDefault());
    wave->setValue(lfo.wave.getUI());
    tempoSyncSwitch->setToggleState(0, dontSendNotification);
    noteLength->setText(getNoteLengthAsString(), dontSendNotification);
    registerDropdown(noteLength, &lfo.noteLength);
    registerSlider(wave, &lfo.wave);
    registerSlider(lfoFadeIn, &lfo.fadeIn);
    lfoFadeIn->setSkewFactorFromMidPoint(1); // Sets the LFOFadeIn slider to logarithmic scale with value 1 in the middle of the slider

    lfoGain->setColour(ComboBox::ColourIds::backgroundColourId, SynthParams::lfoColour);

    fillModsourceBox(freqModSrc1);
    fillModsourceBox(freqModSrc2);
    fillModsourceBox(lfoGain);
    //[/UserPreSize]

    setSize (267, 197);


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
    sineLabel = nullptr;
    squareLabel = nullptr;
    sampleHoldLabel2 = nullptr;
    lfoFadeIn = nullptr;
    triplets = nullptr;
    noteLength = nullptr;
    freqModAmount1 = nullptr;
    freqModAmount2 = nullptr;
    freqModSrc1 = nullptr;
    freqModSrc2 = nullptr;
    lfoGain = nullptr;


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
    drawGroupBorder(g, lfo.name, 0, 0,
                    this->getWidth(), this->getHeight() - 22, 25.0f, 20.0f, 5.0f, 3.0f, SynthParams::lfoColour);
    //[/UserPaint]
}

void LfoPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    freq->setBounds (10, 35, 64, 64);
    wave->setBounds (133, 81, 60, 24);
    tempoSyncSwitch->setBounds (83, 111, 150, 24);
    sineLabel->setBounds (78, 81, 64, 24);
    squareLabel->setBounds (133, 57, 64, 24);
    sampleHoldLabel2->setBounds (192, 81, 72, 24);
    lfoFadeIn->setBounds (10, 97, 64, 64);
    triplets->setBounds (192, 112, 120, 24);
    noteLength->setBounds (110, 135, 87, 24);
    freqModAmount1->setBounds (67, 35, 18, 18);
    freqModAmount2->setBounds (67, 59, 18, 18);
    freqModSrc1->setBounds (90, 35, 40, 18);
    freqModSrc2->setBounds (90, 59, 40, 18);
    lfoGain->setBounds (100, 6, 40, 18);
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
    else if (sliderThatWasMoved == lfoFadeIn)
    {
        //[UserSliderCode_lfoFadeIn] -- add your slider handling code here..
        //[/UserSliderCode_lfoFadeIn]
    }
    else if (sliderThatWasMoved == freqModAmount1)
    {
        //[UserSliderCode_freqModAmount1] -- add your slider handling code here..
        //[/UserSliderCode_freqModAmount1]
    }
    else if (sliderThatWasMoved == freqModAmount2)
    {
        //[UserSliderCode_freqModAmount2] -- add your slider handling code here..
        //[/UserSliderCode_freqModAmount2]
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
        lfo.tempSync.setUI(tempoSyncSwitch->getToggleState());
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
    handleDropdown(comboBoxThatHasChanged);
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == noteLength)
    {
        //[UserComboBoxCode_noteLength] -- add your combo box handling code here..
        //[/UserComboBoxCode_noteLength]
    }
    else if (comboBoxThatHasChanged == freqModSrc1)
    {
        //[UserComboBoxCode_freqModSrc1] -- add your combo box handling code here..
        //[/UserComboBoxCode_freqModSrc1]
    }
    else if (comboBoxThatHasChanged == freqModSrc2)
    {
        //[UserComboBoxCode_freqModSrc2] -- add your combo box handling code here..
        //[/UserComboBoxCode_freqModSrc2]
    }
    else if (comboBoxThatHasChanged == lfoGain)
    {
        //[UserComboBoxCode_lfoGain] -- add your combo box handling code here..
        //[/UserComboBoxCode_lfoGain]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
String LfoPanel::getNoteLengthAsString()
{
    return "1/" + String(lfo.noteLength.getUI());
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="LfoPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p, int lfoNumber"
                 variableInitialisers="PanelBase(p),&#10;lfo(p.lfo[lfoNumber])"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="267" initialHeight="197">
  <BACKGROUND backgroundColour="ffb16565"/>
  <SLIDER name="LFO freq" id="d136f7fae1b8db84" memberName="freq" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="10 35 64 64" rotarysliderfill="ff855050"
          min="0.01" max="50" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="56" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="wave switch" id="221421ebd522cd9a" memberName="wave" virtualName="Slider"
          explicitFocusOrder="0" pos="133 81 60 24" thumbcol="ff855050"
          trackcol="ffffffff" min="0" max="2" int="1" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="tempoSyncSwitch" id="79c4ab6638da99ef" memberName="tempoSyncSwitch"
                virtualName="" explicitFocusOrder="0" pos="83 111 150 24" txtcol="ffffffff"
                buttonText="Tempo Sync" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <LABEL name="sine label" id="b40cd065bdc2086c" memberName="sineLabel"
         virtualName="" explicitFocusOrder="0" pos="78 81 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Sine" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="square label" id="5adc08b39551a18d" memberName="squareLabel"
         virtualName="" explicitFocusOrder="0" pos="133 57 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Square" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="sample and hold label" id="f2be9ba7b41efda2" memberName="sampleHoldLabel2"
         virtualName="" explicitFocusOrder="0" pos="192 81 72 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Smp+Hold" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="LFO Fade In" id="16de18984b3c12ef" memberName="lfoFadeIn"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="10 97 64 64"
          rotarysliderfill="ff855050" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="10" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="56"
          textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="triplets" id="9c9e2393225a5b09" memberName="triplets" virtualName=""
                explicitFocusOrder="0" pos="192 112 120 24" txtcol="ffffffff"
                buttonText="triplets" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <COMBOBOX name="note length" id="9cc1e82a498c26a7" memberName="noteLength"
            virtualName="IncDecDropDown" explicitFocusOrder="0" pos="110 135 87 24"
            editable="0" layout="36" items="1/1&#10;1/2&#10;1/4&#10;1/8&#10;1/16&#10;1/32"
            textWhenNonSelected="Note Length" textWhenNoItems="(no choices)"/>
  <SLIDER name="freqModAmount1" id="ea500ea6791045c2" memberName="freqModAmount1"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="67 35 18 18"
          rotarysliderfill="ffffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="0"
          textBoxHeight="0" skewFactor="1"/>
  <SLIDER name="freqModAmount2" id="ae5c9ce50e2de7e1" memberName="freqModAmount2"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="67 59 18 18"
          rotarysliderfill="ffffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxoutline="ffffff" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="0"
          textBoxHeight="0" skewFactor="1"/>
  <COMBOBOX name="freqModSrc1" id="928cd04bb7b23ab9" memberName="freqModSrc1"
            virtualName="" explicitFocusOrder="0" pos="90 35 40 18" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="freqModSrc2" id="455e48a25414a454" memberName="freqModSrc2"
            virtualName="" explicitFocusOrder="0" pos="90 59 40 18" editable="0"
            layout="36" items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="lfoGain" id="3c7a245d6d4ecf90" memberName="lfoGain" virtualName=""
            explicitFocusOrder="0" pos="100 6 40 18" editable="0" layout="36"
            items="" textWhenNonSelected="No Mod" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
