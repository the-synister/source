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

#include "FxPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
FxPanel::FxPanel (SynthParams &p)
    : params(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (feedbackSlider = new Slider ("feedbackSlider1"));
    feedbackSlider->setRange (0, 100, 0);
    feedbackSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    feedbackSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    feedbackSlider->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Feedback")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredTop);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dryWetSlider = new Slider ("dryWetSlider1"));
    dryWetSlider->setRange (0, 100, 0);
    dryWetSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    dryWetSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    dryWetSlider->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Dry / Wet")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredTop);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (timeSlider = new Slider ("timeSlider1"));
    timeSlider->setRange (1, 2000, 1);
    timeSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    timeSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    timeSlider->addListener (this);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Time")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredTop);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (syncToggle = new ToggleButton ("syncToggle1"));
    syncToggle->setButtonText (TRANS("Sync"));
    syncToggle->addListener (this);


    //[UserPreSize]
    dryWetSlider->setValue(params.delayDryWet.getUI());
    dryWetSlider->setTextValueSuffix(String(" ") + params.delayDryWet.unit());
    timeSlider->setValue(params.delayTime.getUI());
    timeSlider->setTextValueSuffix(String(" ") + params.delayTime.unit());
    feedbackSlider->setValue(params.delayFeedback.getUI());
    feedbackSlider->setTextValueSuffix(String(" ") + params.delayFeedback.unit());

    //syncToggle
    syncToggle->setEnabled(false);

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

FxPanel::~FxPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    feedbackSlider = nullptr;
    label = nullptr;
    dryWetSlider = nullptr;
    label2 = nullptr;
    timeSlider = nullptr;
    label3 = nullptr;
    syncToggle = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FxPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FxPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    feedbackSlider->setBounds (32, 56, 87, 72);
    label->setBounds (40, 32, 72, 16);
    dryWetSlider->setBounds (136, 56, 87, 72);
    label2->setBounds (144, 32, 72, 16);
    timeSlider->setBounds (240, 56, 87, 72);
    label3->setBounds (248, 32, 72, 16);
    syncToggle->setBounds (336, 104, 63, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void FxPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == feedbackSlider)
    {
        //[UserSliderCode_feedbackSlider] -- add your slider handling code here..
        params.delayFeedback.setUI(static_cast<float>(feedbackSlider->getValue()*0.01));
        //[/UserSliderCode_feedbackSlider]
    }
    else if (sliderThatWasMoved == dryWetSlider)
    {
        //[UserSliderCode_dryWetSlider] -- add your slider handling code here..
        params.delayDryWet.setUI(static_cast<float>(dryWetSlider->getValue()*0.01));
        //[/UserSliderCode_dryWetSlider]
    }
    else if (sliderThatWasMoved == timeSlider)
    {
        //[UserSliderCode_timeSlider] -- add your slider handling code here..
        params.delayTime.setUI(static_cast<float>(timeSlider->getValue()));
        //[/UserSliderCode_timeSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void FxPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == syncToggle)
    {
        //[UserButtonCode_syncToggle] -- add your button handler code here..
        //[/UserButtonCode_syncToggle]
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

<JUCER_COMPONENT documentType="Component" className="FxPanel" componentName=""
                 parentClasses="public Component" constructorParams="SynthParams &amp;p"
                 variableInitialisers="params(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="feedbackSlider1" id="9c0383d8383ea645" memberName="feedbackSlider"
          virtualName="" explicitFocusOrder="0" pos="32 56 87 72" min="0"
          max="100" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="2a06a11c8bdb9f27" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="40 32 72 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Feedback" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="12"/>
  <SLIDER name="dryWetSlider1" id="38a3801ec95e842b" memberName="dryWetSlider"
          virtualName="" explicitFocusOrder="0" pos="136 56 87 72" min="0"
          max="100" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="e9970f1693202a99" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="144 32 72 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Dry / Wet" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="12"/>
  <SLIDER name="timeSlider1" id="5ac27dc9db375d94" memberName="timeSlider"
          virtualName="" explicitFocusOrder="0" pos="240 56 87 72" min="1"
          max="2000" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="acae269e78c925a5" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="248 32 72 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Time" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="12"/>
  <TOGGLEBUTTON name="syncToggle1" id="103062bcdc341811" memberName="syncToggle"
                virtualName="" explicitFocusOrder="0" pos="336 104 63 24" buttonText="Sync"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
