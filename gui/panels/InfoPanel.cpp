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

#include "InfoPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
InfoPanel::InfoPanel (SynthParams &p)
    : PanelBase(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (hyperlinkButton = new HyperlinkButton (TRANS("VISIT HTTPS://WWW.SYNISTER-THESYNTH.DE"),
                                                              URL ("http://www.synister-thesynth.de")));
    hyperlinkButton->setTooltip (TRANS("http://www.synister-thesynth.de"));
    hyperlinkButton->setButtonText (TRANS("VISIT HTTPS://WWW.SYNISTER-THESYNTH.DE"));
    hyperlinkButton->setColour (HyperlinkButton::textColourId, Colours::white);

    addAndMakeVisible (label1 = new Label ("label1",
                                           TRANS("...A SYNTH BY STUDENTS OF THE TU-BERLIN.")));
    label1->setFont (Font (20.00f, Font::plain));
    label1->setJustificationType (Justification::centredRight);
    label1->setEditable (false, false, false);
    label1->setColour (TextEditor::textColourId, Colours::black);
    label1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    drawable1 = Drawable::createFromImageData (BinaryData::synisterLogo_png, BinaryData::synisterLogo_pngSize);
    drawable2 = Drawable::createFromImageData (BinaryData::QUL_Logo_png, BinaryData::QUL_Logo_pngSize);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (550, 450);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

InfoPanel::~InfoPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    hyperlinkButton = nullptr;
    label1 = nullptr;
    drawable1 = nullptr;
    drawable2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void InfoPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff6c788c));

    g.setColour (Colour (0xc0ffffff));
    g.fillRect (268, 298, 250, 130);

    g.setColour (Colours::black);
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (60, 28, 428, 100),
                               RectanglePlacement::centred, 1.000f);

    g.setColour (Colours::black);
    jassert (drawable2 != 0);
    if (drawable2 != 0)
        drawable2->drawWithin (g, Rectangle<float> (278, 308, 230, 110),
                               RectanglePlacement::stretchToFit, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void InfoPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    hyperlinkButton->setBounds (209, 183, 335, 24);
    label1->setBounds (185, 153, 335, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="InfoPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="550"
                 initialHeight="450">
  <BACKGROUND backgroundColour="ff6c788c">
    <RECT pos="268 298 250 130" fill="solid: c0ffffff" hasStroke="0"/>
    <IMAGE pos="60 28 428 100" resource="BinaryData::synisterLogo_png" opacity="1"
           mode="1"/>
    <IMAGE pos="278 308 230 110" resource="BinaryData::QUL_Logo_png" opacity="1"
           mode="0"/>
  </BACKGROUND>
  <HYPERLINKBUTTON name="new hyperlink" id="996ba2dd79b0f075" memberName="hyperlinkButton"
                   virtualName="" explicitFocusOrder="0" pos="209 183 335 24" tooltip="http://www.synister-thesynth.de"
                   textCol="ffffffff" buttonText="VISIT HTTPS://WWW.SYNISTER-THESYNTH.DE"
                   connectedEdges="0" needsCallback="0" radioGroupId="0" url="http://www.synister-thesynth.de"/>
  <LABEL name="label1" id="8f1673969ba85117" memberName="label1" virtualName=""
         explicitFocusOrder="0" pos="185 153 335 24" edTextCol="ff000000"
         edBkgCol="0" labelText="...A SYNTH BY STUDENTS OF THE TU-BERLIN."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="20" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
