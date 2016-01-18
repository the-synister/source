/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 13 Jan 2016 5:44:21pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef CUSTOMLOOKANDFEEL_H_INCLUDED
#define CUSTOMLOOKANDFEEL_H_INCLUDED

//[Headers]
#include "JuceHeader.h"
#include "../audio/inc/SynthParams.h"
//[/Headers]

class CustomLookAndFeel : public LookAndFeel_V2 // our default design
{
public:
    //==============================================================================
    CustomLookAndFeel(SynthParams &p);
    virtual ~CustomLookAndFeel();
    //==============================================================================
    virtual void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider);

    virtual void drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider);

private:
    SynthParams &params;

    // image assets
    Image rotarySliderImage;
    Image verticalSlider;
    Image verticalSliderThumb;
    Image glow;

    // properties of our temporary assets
    int numberFramesRotary = 50;
    int widthRotary = 60;
    int heightRotary = 60;

    int widthVertical = 50;
    int heigthVertical = 290;

    int thumbWidth = 45;
    int thumbHeight = 45;

    // size of thumb to be displayed
    float thumbSize = 15.0;
};

#endif  // CUSTOMLOOKANDFEEL_H_INCLUDED
