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

#ifndef __JUCE_HEADER_17F31DC76882C8CC__
#define __JUCE_HEADER_17F31DC76882C8CC__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "SynthParams.h"
#include "MouseOverKnob.h"
#include "FoldablePanel.h"
#include "IncDecDropDown.h"
#include "panels/PanelBase.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PlugUI  : public PanelBase,
                public TextEditorListener,
                public SliderListener,
                public ButtonListener
{
public:
    //==============================================================================
    PlugUI (SynthParams &p);
    ~PlugUI();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SynthParams &params;

    void timerCallback() override;
    void updateDirtyPatchname(const String patchName);
    void textEditorFocusLost(TextEditor &editor);

    ScopedPointer<CustomLookAndFeel> lnf;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<MouseOverKnob> freq;
    ScopedPointer<MidiKeyboardComponent> keyboard;
    ScopedPointer<TextButton> savePresetButton;
    ScopedPointer<TextButton> loadPresetButton;
    ScopedPointer<FoldablePanel> foldableComponent;
    ScopedPointer<MouseOverKnob> masterAmp;
    ScopedPointer<MouseOverKnob> masterPan;
    ScopedPointer<TextEditor> patchNameEditor;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlugUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_17F31DC76882C8CC__
