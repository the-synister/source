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

    addAndMakeVisible (hyperlinkButton = new HyperlinkButton (String::empty,
                                                              URL ("http://www.synister-thesynth.de")));
    hyperlinkButton->setTooltip (TRANS("http://www.synister-thesynth.de"));
    hyperlinkButton->setButtonText (String::empty);
    hyperlinkButton->setColour (HyperlinkButton::textColourId, Colours::white);

    drawable1 = Drawable::createFromImageData (BinaryData::infoScreen_png, BinaryData::infoScreen_pngSize);

    //[UserPreSize]
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
    //[/UserPreResize]

    hyperlinkButton->setBounds (298, 304, 361, 20);
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
  <HYPERLINKBUTTON name="new hyperlink" id="996ba2dd79b0f075" memberName="hyperlinkButton"
                   virtualName="" explicitFocusOrder="0" pos="298 304 361 20" tooltip="http://www.synister-thesynth.de"
                   textCol="ffffffff" buttonText="" connectedEdges="0" needsCallback="0"
                   radioGroupId="0" url="http://www.synister-thesynth.de"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
