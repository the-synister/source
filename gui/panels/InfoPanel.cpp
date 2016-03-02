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

    addAndMakeVisible (supervisorLabelWhite = new Label ("supervisor label white",
                                                         CharPointer_UTF8 ("SUPERVISORS {\n"
                                                         "    Marc Halbr\xc3\xbcgge,\n"
                                                         "\n"
                                                         "}\n")));
    supervisorLabelWhite->setFont (Font ("Berlin Sans FB", 20.00f, Font::plain));
    supervisorLabelWhite->setJustificationType (Justification::topLeft);
    supervisorLabelWhite->setEditable (false, false, false);
    supervisorLabelWhite->setColour (Label::textColourId, Colours::black);
    supervisorLabelWhite->setColour (TextEditor::textColourId, Colours::black);
    supervisorLabelWhite->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (supervisorLabelBlack = new Label ("supervisor label black",
                                                         TRANS("SUPERVISORS {\n"
                                                         "\n"
                                                         "    Gabriel Reimers\n"
                                                         "\n")));
    supervisorLabelBlack->setFont (Font ("Berlin Sans FB", 20.00f, Font::plain));
    supervisorLabelBlack->setJustificationType (Justification::topLeft);
    supervisorLabelBlack->setEditable (false, false, false);
    supervisorLabelBlack->setColour (Label::textColourId, Colour (0xffcccccc));
    supervisorLabelBlack->setColour (TextEditor::textColourId, Colours::black);
    supervisorLabelBlack->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (teamLabelBlack = new Label ("team label black",
                                                   CharPointer_UTF8 ("TEAM {\n"
                                                   "    Florian B\xc3\xbctow,\n"
                                                   "\n"
                                                   "    Luc Guy,\n"
                                                   "\n"
                                                   "    Martin Keil,\n"
                                                   "\n"
                                                   "    Xavier Presser,\n"
                                                   "\n"
                                                   "    Nhat D. Tran\n"
                                                   "}")));
    teamLabelBlack->setFont (Font ("Berlin Sans FB", 20.00f, Font::plain));
    teamLabelBlack->setJustificationType (Justification::topLeft);
    teamLabelBlack->setEditable (false, false, false);
    teamLabelBlack->setColour (Label::textColourId, Colour (0xffcccccc));
    teamLabelBlack->setColour (TextEditor::textColourId, Colours::black);
    teamLabelBlack->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (teamLabelWhite = new Label ("team label white",
                                                   CharPointer_UTF8 ("TEAM {\n"
                                                   "\n"
                                                   "    Juan Cabello,\n"
                                                   "\n"
                                                   "    Nils Jessen,\n"
                                                   "\n"
                                                   "    Christian Kn\xc3\xb6rzer,\n"
                                                   "\n"
                                                   "    Anton Schmied,\n"
                                                   "\n"
                                                   "}")));
    teamLabelWhite->setFont (Font ("Berlin Sans FB", 20.00f, Font::plain));
    teamLabelWhite->setJustificationType (Justification::topLeft);
    teamLabelWhite->setEditable (false, false, false);
    teamLabelWhite->setColour (Label::textColourId, Colours::black);
    teamLabelWhite->setColour (TextEditor::textColourId, Colours::black);
    teamLabelWhite->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (byStudentLabel = new Label ("by students label",
                                                   TRANS("...A SYNTH BY STUDENTS OF THE TU-BERLIN.")));
    byStudentLabel->setFont (Font ("Berlin Sans FB", 20.00f, Font::plain));
    byStudentLabel->setJustificationType (Justification::centredRight);
    byStudentLabel->setEditable (false, false, false);
    byStudentLabel->setColour (TextEditor::textColourId, Colours::black);
    byStudentLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (comingSoonLabel = new Label ("coming soon label",
                                                    TRANS("...COMING SOON!")));
    comingSoonLabel->setFont (Font ("Berlin Sans FB", 16.00f, Font::plain));
    comingSoonLabel->setJustificationType (Justification::centredRight);
    comingSoonLabel->setEditable (false, false, false);
    comingSoonLabel->setColour (TextEditor::textColourId, Colours::black);
    comingSoonLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (hyperlinkButton = new HyperlinkButton (TRANS("VISIT HTTPS://WWW.SYNISTER-THESYNTH.DE"),
                                                              URL ("http://www.synister-thesynth.de")));
    hyperlinkButton->setTooltip (TRANS("http://www.synister-thesynth.de"));
    hyperlinkButton->setButtonText (TRANS("VISIT HTTPS://WWW.SYNISTER-THESYNTH.DE"));
    hyperlinkButton->setColour (HyperlinkButton::textColourId, Colours::white);

    addAndMakeVisible (betaLabel = new Label ("beta label",
                                              TRANS("SPECIAL THANKS TO OUR BETA TESTERS!")));
    betaLabel->setFont (Font ("Berlin Sans FB", 20.00f, Font::plain));
    betaLabel->setJustificationType (Justification::centredRight);
    betaLabel->setEditable (false, false, false);
    betaLabel->setColour (Label::textColourId, Colour (0xffcccccc));
    betaLabel->setColour (TextEditor::textColourId, Colours::black);
    betaLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dateLabel = new Label ("date label",
                                              TRANS("MARCH 2016")));
    dateLabel->setFont (Font ("Berlin Sans FB", 18.00f, Font::plain));
    dateLabel->setJustificationType (Justification::centredRight);
    dateLabel->setEditable (false, false, false);
    dateLabel->setColour (Label::textColourId, Colours::black);
    dateLabel->setColour (TextEditor::textColourId, Colours::black);
    dateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (versionLabel = new Label ("version label",
                                                 TRANS("VERSION: ")));
    versionLabel->setFont (Font ("Berlin Sans FB", 26.00f, Font::plain));
    versionLabel->setJustificationType (Justification::centredRight);
    versionLabel->setEditable (false, false, false);
    versionLabel->setColour (Label::textColourId, Colour (0xffcccccc));
    versionLabel->setColour (TextEditor::textColourId, Colours::black);
    versionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    drawable1 = Drawable::createFromImageData (BinaryData::synisterLogo_png, BinaryData::synisterLogo_pngSize);
    drawable2 = Drawable::createFromImageData (BinaryData::QUL_Logo_png, BinaryData::QUL_Logo_pngSize);

    //[UserPreSize]
    versionLabel->setText(versionLabel->getText() + String(params.version), dontSendNotification);
    Time today = Time().getCompilationDate();
    const String& dateText = today.getMonthName(false).toUpperCase() + " " + String(today.getYear());
    dateLabel->setText(dateText, dontSendNotification);
    //[/UserPreSize]

    setSize (550, 460);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

InfoPanel::~InfoPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    supervisorLabelWhite = nullptr;
    supervisorLabelBlack = nullptr;
    teamLabelBlack = nullptr;
    teamLabelWhite = nullptr;
    byStudentLabel = nullptr;
    comingSoonLabel = nullptr;
    hyperlinkButton = nullptr;
    betaLabel = nullptr;
    dateLabel = nullptr;
    versionLabel = nullptr;
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

    g.setColour (Colour (0xe3ffffff));
    g.fillRect (311, 169, 220, 120);

    g.setColour (Colours::black);
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (0, 10, 550, 120),
                               RectanglePlacement::centred, 1.000f);

    g.setColour (Colours::black);
    jassert (drawable2 != 0);
    if (drawable2 != 0)
        drawable2->drawWithin (g, Rectangle<float> (321, 179, 200, 100),
                               RectanglePlacement::stretchToFit, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void InfoPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    supervisorLabelWhite->setBounds (14, 371, 177, 84);
    supervisorLabelBlack->setBounds (14, 371, 177, 84);
    teamLabelBlack->setBounds (14, 138, 177, 225);
    teamLabelWhite->setBounds (14, 138, 177, 225);
    byStudentLabel->setBounds (213, 135, 321, 24);
    comingSoonLabel->setBounds (331, 320, 200, 24);
    hyperlinkButton->setBounds (216, 291, 315, 27);
    betaLabel->setBounds (216, 424, 317, 24);
    dateLabel->setBounds (331, 380, 200, 24);
    versionLabel->setBounds (331, 356, 200, 24);
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
                 initialHeight="460">
  <BACKGROUND backgroundColour="ff6c788c">
    <RECT pos="311 169 220 120" fill="solid: e3ffffff" hasStroke="0"/>
    <IMAGE pos="0 10 550 120" resource="BinaryData::synisterLogo_png" opacity="1"
           mode="1"/>
    <IMAGE pos="321 179 200 100" resource="BinaryData::QUL_Logo_png" opacity="1"
           mode="0"/>
  </BACKGROUND>
  <LABEL name="supervisor label white" id="6134a59c4377e3f2" memberName="supervisorLabelWhite"
         virtualName="" explicitFocusOrder="0" pos="14 371 177 84" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="SUPERVISORS {&#10;    Marc Halbr&#252;gge,&#10;&#10;}&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Berlin Sans FB" fontsize="20" bold="0" italic="0" justification="9"/>
  <LABEL name="supervisor label black" id="c5fe9a3e3d382d57" memberName="supervisorLabelBlack"
         virtualName="" explicitFocusOrder="0" pos="14 371 177 84" textCol="ffcccccc"
         edTextCol="ff000000" edBkgCol="0" labelText="SUPERVISORS {&#10;&#10;    Gabriel Reimers&#10;&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Berlin Sans FB" fontsize="20" bold="0" italic="0" justification="9"/>
  <LABEL name="team label black" id="699e317fae603b03" memberName="teamLabelBlack"
         virtualName="" explicitFocusOrder="0" pos="14 138 177 225" textCol="ffcccccc"
         edTextCol="ff000000" edBkgCol="0" labelText="TEAM {&#10;    Florian B&#252;tow,&#10;&#10;    Luc Guy,&#10;&#10;    Martin Keil,&#10;&#10;    Xavier Presser,&#10;&#10;    Nhat D. Tran&#10;}"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Berlin Sans FB" fontsize="20" bold="0" italic="0" justification="9"/>
  <LABEL name="team label white" id="bfe0f06b1dd18385" memberName="teamLabelWhite"
         virtualName="" explicitFocusOrder="0" pos="14 138 177 225" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="TEAM {&#10;&#10;    Juan Cabello,&#10;&#10;    Nils Jessen,&#10;&#10;    Christian Kn&#246;rzer,&#10;&#10;    Anton Schmied,&#10;&#10;}"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Berlin Sans FB" fontsize="20" bold="0" italic="0" justification="9"/>
  <LABEL name="by students label" id="8f1673969ba85117" memberName="byStudentLabel"
         virtualName="" explicitFocusOrder="0" pos="213 135 321 24" edTextCol="ff000000"
         edBkgCol="0" labelText="...A SYNTH BY STUDENTS OF THE TU-BERLIN."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Berlin Sans FB" fontsize="20" bold="0" italic="0" justification="34"/>
  <LABEL name="coming soon label" id="e66f52edead82122" memberName="comingSoonLabel"
         virtualName="" explicitFocusOrder="0" pos="331 320 200 24" edTextCol="ff000000"
         edBkgCol="0" labelText="...COMING SOON!" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Berlin Sans FB"
         fontsize="16" bold="0" italic="0" justification="34"/>
  <HYPERLINKBUTTON name="new hyperlink" id="996ba2dd79b0f075" memberName="hyperlinkButton"
                   virtualName="" explicitFocusOrder="0" pos="216 291 315 27" tooltip="http://www.synister-thesynth.de"
                   textCol="ffffffff" buttonText="VISIT HTTPS://WWW.SYNISTER-THESYNTH.DE"
                   connectedEdges="0" needsCallback="0" radioGroupId="0" url="http://www.synister-thesynth.de"/>
  <LABEL name="beta label" id="67bd518906f00cc6" memberName="betaLabel"
         virtualName="" explicitFocusOrder="0" pos="216 424 317 24" textCol="ffcccccc"
         edTextCol="ff000000" edBkgCol="0" labelText="SPECIAL THANKS TO OUR BETA TESTERS!"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Berlin Sans FB" fontsize="20" bold="0" italic="0" justification="34"/>
  <LABEL name="date label" id="f9720aab4a14ffa7" memberName="dateLabel"
         virtualName="" explicitFocusOrder="0" pos="331 380 200 24" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="MARCH 2016" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Berlin Sans FB"
         fontsize="18" bold="0" italic="0" justification="34"/>
  <LABEL name="version label" id="81e1b9415143c8eb" memberName="versionLabel"
         virtualName="" explicitFocusOrder="0" pos="331 356 200 24" textCol="ffcccccc"
         edTextCol="ff000000" edBkgCol="0" labelText="VERSION: " editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Berlin Sans FB"
         fontsize="26" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
