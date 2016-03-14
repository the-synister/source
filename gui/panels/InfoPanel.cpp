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

    addAndMakeVisible (hyperlinkButton = new HyperlinkButton (TRANS("http://the-synister.github.io/"),
                                                              URL ("http://the-synister.github.io/")));
    hyperlinkButton->setTooltip (TRANS("http://the-synister.github.io/"));
    hyperlinkButton->setButtonText (TRANS("http://the-synister.github.io/"));
    hyperlinkButton->setColour (HyperlinkButton::textColourId, Colours::white);

    addAndMakeVisible (versionLabel = new Label ("version label",
                                                 TRANS("Version X.X")));
    versionLabel->setFont (Font (40.00f, Font::plain));
    versionLabel->setJustificationType (Justification::centredRight);
    versionLabel->setEditable (false, false, false);
    versionLabel->setColour (Label::textColourId, Colour (0xffcccccc));
    versionLabel->setColour (TextEditor::textColourId, Colours::black);
    versionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dateLabel = new Label ("date label",
                                              TRANS("Date")));
    dateLabel->setFont (Font (30.00f, Font::plain));
    dateLabel->setJustificationType (Justification::centredRight);
    dateLabel->setEditable (false, false, false);
    dateLabel->setColour (Label::textColourId, Colours::black);
    dateLabel->setColour (TextEditor::textColourId, Colours::black);
    dateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    drawable1 = Drawable::createFromImageData (BinaryData::infoScreen_png, BinaryData::infoScreen_pngSize);

    //[UserPreSize]
    today = Time().getCompilationDate();
    dateLabel->setText(today.getMonthName(false) + " " + String(today.getYear()), dontSendNotification);
    versionLabel->setText("Version: " + String(ProjectInfo::versionString), dontSendNotification);
    //[/UserPreSize]

    setSize (685, 555);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

InfoPanel::~InfoPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    hyperlinkButton = nullptr;
    versionLabel = nullptr;
    dateLabel = nullptr;
    drawable1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void InfoPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff6c788c));

    g.setColour (Colours::black);
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (0, 0, 685, 555),
                               RectanglePlacement::stretchToFit, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void InfoPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    today = Time().getCompilationDate();
    dateLabel->setText(today.getMonthName(false) + " " + String(today.getYear()), dontSendNotification);
    versionLabel->setText("Version: " + String(ProjectInfo::versionString), dontSendNotification);
    //[/UserPreResize]

    hyperlinkButton->setBounds (348, 219, 315, 39);
    versionLabel->setBounds (405, 270, 255, 30);
    dateLabel->setBounds (405, 305, 255, 20);
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
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="685"
                 initialHeight="555">
  <BACKGROUND backgroundColour="ff6c788c">
    <IMAGE pos="0 0 685 555" resource="BinaryData::infoScreen_png" opacity="1"
           mode="0"/>
  </BACKGROUND>
  <HYPERLINKBUTTON name="new hyperlink" id="da67067ab010118f" memberName="hyperlinkButton"
                   virtualName="" explicitFocusOrder="0" pos="348 219 315 39" tooltip="http://the-synister.github.io/"
                   textCol="ffffffff" buttonText="http://the-synister.github.io/"
                   connectedEdges="0" needsCallback="0" radioGroupId="0" url="http://the-synister.github.io/"/>
  <LABEL name="version label" id="4acef8b7a42ef7c5" memberName="versionLabel"
         virtualName="" explicitFocusOrder="0" pos="405 270 255 30" textCol="ffcccccc"
         edTextCol="ff000000" edBkgCol="0" labelText="Version X.X" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="40" bold="0" italic="0" justification="34"/>
  <LABEL name="date label" id="8bb2be6e3527c72a" memberName="dateLabel"
         virtualName="" explicitFocusOrder="0" pos="405 305 255 20" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="Date" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="30" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
