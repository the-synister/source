/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 13 Jan 2016 5:44:21pm
    Author:  Nutty

  ==============================================================================
*/

#include "CustomLookAndFeel.h"

//==============================================================================
// contructer & destructer
CustomLookAndFeel::CustomLookAndFeel(): LookAndFeel_V2()
{
    // set various things
    //this->setDefaultSansSerifTypefaceName("Arial");
    //this->setColour(ColourIds::rotarySliderFillColourId, Colour(0x00000000));

    // load assets
    rotarySliderImage = ImageCache::getFromMemory(BinaryData::knobstrip_png, BinaryData::knobstrip_pngSize);
}

CustomLookAndFeel::~CustomLookAndFeel()
{
}
//==============================================================================

void CustomLookAndFeel::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &s)
{
    ignoreUnused(sliderPosProportional);
    ignoreUnused(rotaryStartAngle);
    ignoreUnused(rotaryEndAngle);
    
    double min = s.getMinimum();
    double max = s.getMaximum();
    double currValue = s.getValue();
    double skewFactor = s.getSkewFactor();

    // calculate image frame for clipping and draw
    int frame = 0;
    frame = static_cast<int>(pow(((currValue - min) / (max - min)), skewFactor) * 50.0);
    Rectangle<int> rect = { 0, jmax(0, jmin(frame, 49)) * heightRotary, widthRotary, heightRotary };
    g.drawImageWithin(rotarySliderImage.getClippedImage(rect), x, y, width, height, RectanglePlacement::centred);

    //LookAndFeel_V2::drawRotarySlider(g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, s); // default knob
}

void CustomLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s)
{
    LookAndFeel_V2::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
}
