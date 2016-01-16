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
                  public SliderListener
{
public:
    //==============================================================================
    OscPanel (SynthParams &p);
    ~OscPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<MouseOverKnob> ftune1;
    ScopedPointer<MouseOverKnob> lfo1depth1;
    ScopedPointer<MouseOverKnob> osc1trngAmount;
    ScopedPointer<MouseOverKnob> pulsewidth;
    ScopedPointer<MouseOverKnob> pitchRange;
    ScopedPointer<MouseOverKnob> ctune1;
    ScopedPointer<MouseOverKnob> lfoFadeIn;
    ScopedPointer<WaveformVisual> waveformVisual;
    ScopedPointer<Slider> waveformSwitch;
    ScopedPointer<Label> sawlabel;
    ScopedPointer<Label> squarelabel;
    ScopedPointer<MouseOverKnob> amountWidthMod;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_48919873852F91A2__
