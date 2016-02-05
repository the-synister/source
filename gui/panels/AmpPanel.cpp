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

#include "AmpPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AmpPanel::AmpPanel (SynthParams &p)
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (amp = new MouseOverKnob ("amp"));
    amp->setRange (-96, 12, 0);
    amp->setSliderStyle (Slider::LinearBar);
    amp->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    amp->setColour (Slider::backgroundColourId, Colour (0x00ffffff));
    amp->setColour (Slider::thumbColourId, Colours::grey);
    amp->setColour (Slider::trackColourId, Colours::white);
    amp->setColour (Slider::rotarySliderFillColourId, Colours::blue);
    amp->setColour (Slider::textBoxTextColourId, Colours::white);
    amp->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    amp->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    amp->addListener (this);

    addAndMakeVisible (pan = new MouseOverKnob ("pan"));
    pan->setRange (-100, 100, 0);
    pan->setSliderStyle (Slider::LinearBar);
    pan->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    pan->setColour (Slider::thumbColourId, Colour (0xff6c788c));
    pan->setColour (Slider::trackColourId, Colours::white);
    pan->setColour (Slider::rotarySliderFillColourId, Colours::blue);
    pan->setColour (Slider::textBoxTextColourId, Colours::white);
    pan->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    pan->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    pan->addListener (this);

    addAndMakeVisible (label2 = new Label ("R label",
                                           TRANS("R")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("L label",
                                           TRANS("L")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (velocitySense = new MouseOverKnob ("Key Velocity"));
    velocitySense->setRange (0, 96, 0);
    velocitySense->setSliderStyle (Slider::RotaryVerticalDrag);
    velocitySense->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    velocitySense->setColour (Slider::rotarySliderFillColourId, Colour (0xff6c788c));
    velocitySense->addListener (this);


    //[UserPreSize]
    registerSlider(amp, &params.vol);
    registerSlider(pan, &params.panDir);
    registerSlider(velocitySense, &params.keyVelocityLevel);

    // TODO: vllt ohne textbox und stattdessen mit popup
    //amp->setPopupDisplayEnabled(true, this);
    //pan->setPopupDisplayEnabled(true, this);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

AmpPanel::~AmpPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    amp = nullptr;
    pan = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    velocitySense = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void AmpPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff6c788c));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void AmpPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    amp->setBounds (48, 152, 200, 60);
    pan->setBounds (296, 128, 125, 60);
    label2->setBounds (237, 96, 24, 24);
    label3->setBounds (166, 96, 24, 24);
    velocitySense->setBounds (66, 72, 112, 64);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void AmpPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == amp)
    {
        //[UserSliderCode_amp] -- add your slider handling code here..
        //[/UserSliderCode_amp]
    }
    else if (sliderThatWasMoved == pan)
    {
        //[UserSliderCode_pan] -- add your slider handling code here..
        //[/UserSliderCode_pan]
    }
    else if (sliderThatWasMoved == velocitySense)
    {
        //[UserSliderCode_velocitySense] -- add your slider handling code here..
        //[/UserSliderCode_velocitySense]
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

<JUCER_COMPONENT documentType="Component" className="AmpPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ff6c788c"/>
  <SLIDER name="amp" id="3279e0342166e50f" memberName="amp" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="48 152 200 60" bkgcol="ffffff" thumbcol="ff808080"
          trackcol="ffffffff" rotarysliderfill="ff0000ff" textboxtext="ffffffff"
          textboxbkgd="ffffff" textboxoutline="ffffff" min="-96" max="12"
          int="0" style="LinearBar" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="pan" id="d8f72bae093dfe35" memberName="pan" virtualName="MouseOverKnob"
          explicitFocusOrder="0" pos="296 128 125 60" thumbcol="ff6c788c"
          trackcol="ffffffff" rotarysliderfill="ff0000ff" textboxtext="ffffffff"
          textboxbkgd="ffffff" textboxoutline="ffffff" min="-100" max="100"
          int="0" style="LinearBar" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="R label" id="38f0a446950aca39" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="237 96 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="R" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="L label" id="fb5b8372200665a9" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="166 96 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="L" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="Key Velocity" id="e08e3c952cbb37a2" memberName="velocitySense"
          virtualName="MouseOverKnob" explicitFocusOrder="0" pos="66 72 112 64"
          rotarysliderfill="ff6c788c" min="0" max="96" int="0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
