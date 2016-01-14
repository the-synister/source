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
//[/Headers]

class CustomLookAndFeel : public LookAndFeel_V2
{
public:
    //==============================================================================
    CustomLookAndFeel();
    virtual ~CustomLookAndFeel();
    //==============================================================================
    virtual void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &s);

    virtual void drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s);

private:
    // image assets to draw with g.draw(image, xPos, yPos)
    Image rotarySliderImage;
};

#endif  // CUSTOMLOOKANDFEEL_H_INCLUDED