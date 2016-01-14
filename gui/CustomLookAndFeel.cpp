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
    // settings like colour
    this->setColour(16782097, Colour(0x00000000));

    // load assets
    rotarySliderImage = ImageCache::getFromMemory(BinaryData::knobstrip_png, BinaryData::knobstrip_pngSize);
    //rotarySliderImage.getClippedImage();
    //rotarySliderImage.moveImageSection(0, 0, 500, 500, 40, 40);
}

CustomLookAndFeel::~CustomLookAndFeel()
{
}
//==============================================================================

void CustomLookAndFeel::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &s)
{
    //LookAndFeel_V2::drawRotarySlider(g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, s);
    
    // calculate image frame for clipping
    double min = s.getMinimum();
    double max = s.getMaximum();
    double currValue = s.getValue();
    //double step = s.getInterval();
    double skewFactor = s.getSkewFactor();

    // skewFactor noch nicht perfekt
    int frame = 0;
    if (skewFactor <= 1)
    {
        frame = static_cast<int>(abs(currValue - min) / abs(max - min) * 50.0 / skewFactor);
    }
    else
    {
        frame = static_cast<int>(abs(currValue - min) / abs(max - min) * 50.0 * log(skewFactor));
    }
    //frame = static_cast<int>(abs(currValue - min) / abs(max - min) * 50.0);

    Rectangle<int> rect = { 0, jmax(0, jmin(frame, 49)) * 60, 60, 60 };
    g.drawImageWithin(rotarySliderImage.getClippedImage(rect), x, y, width, height, RectanglePlacement::centred);
}

void CustomLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s)
{
    LookAndFeel_V2::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
}
