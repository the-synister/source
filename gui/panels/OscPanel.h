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

#ifndef __JUCE_HEADER_48919873852F91A2__
#define __JUCE_HEADER_48919873852F91A2__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PanelBase.h"
#include "WaveformVisual.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
An auto-generated component, created by the Introjucer.

Describe your class and how it works here!
                                                                    //[/Comments]
*/
class OscPanel  : public PanelBase,
                  public ComboBoxListener,
                  public SliderListener
{
public:
    //==============================================================================
    OscPanel (SynthParams &p, int oscillatorNumber);
    ~OscPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void updateWFShapeControls();
    void updateModAmountKnobs();
    void drawWaves(Graphics& g, ScopedPointer<Slider>& _waveformSwitch);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Image waveforms;
    Rectangle<int> sawFrame = { 0, 20, 30, 20 };
    Rectangle<int> squareFrame = { 69, 20, 30, 20 };
    Rectangle<int> noiseFrame = { 35, 0, 30, 20 };

    SynthParams::Osc &osc;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ModSourceBox> trngModSrc1;
    ScopedPointer<ModSourceBox> widthModSrc1;
    ScopedPointer<ModSourceBox> trngModSrc2;
    ScopedPointer<ModSourceBox> widthModSrc2;
    ScopedPointer<MouseOverKnob> ftune1;
    ScopedPointer<MouseOverKnob> pitchModAmount2;
    ScopedPointer<MouseOverKnob> trngAmount;
    ScopedPointer<MouseOverKnob> pulsewidth;
    ScopedPointer<MouseOverKnob> pitchModAmount1;
    ScopedPointer<MouseOverKnob> ctune1;
    ScopedPointer<WaveformVisual> waveformVisual;
    ScopedPointer<Slider> waveformSwitch;
    ScopedPointer<MouseOverKnob> widthModAmount1;
    ScopedPointer<ModSourceBox> pitchModSrc1;
    ScopedPointer<ModSourceBox> pitchModSrc2;
    ScopedPointer<MouseOverKnob> gain;
    ScopedPointer<MouseOverKnob> pan;
    ScopedPointer<MouseOverKnob> widthModAmount2;
    ScopedPointer<MouseOverKnob> gainModAmount2;
    ScopedPointer<MouseOverKnob> gainModAmount1;
    ScopedPointer<ModSourceBox> gainModSrc1;
    ScopedPointer<ModSourceBox> gainModSrc2;
    ScopedPointer<MouseOverKnob> panModAmount2;
    ScopedPointer<MouseOverKnob> panModAmount1;
    ScopedPointer<ModSourceBox> panModSrc1;
    ScopedPointer<ModSourceBox> panModSrc2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_48919873852F91A2__
