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
CustomLookAndFeel::CustomLookAndFeel()
    : LookAndFeel_V2()
    , modSource1(nullptr)
    , modSource2(nullptr)
{
    // set various things like Font and so on
    //this->setDefaultSansSerifTypefaceName("Arial");
    //this->setColour(ColourIds::rotarySliderFillColourId, Colour(0x00000000));

    // load assets
    rotarySliderImage = ImageCache::getFromMemory(BinaryData::knobstrip_png, BinaryData::knobstrip_pngSize);
    verticalSlider = ImageCache::getFromMemory(BinaryData::vertical_slider_png, BinaryData::vertical_slider_pngSize);
    verticalSliderThumb = ImageCache::getFromMemory(BinaryData::slider_thumb_png, BinaryData::slider_thumb_pngSize);
    glow = ImageCache::getFromMemory(BinaryData::glow_png, BinaryData::glow_pngSize);
}

CustomLookAndFeel::~CustomLookAndFeel()
{
    // TODO: release ressources
    //rotarySliderImage.~Image();
    //verticalSlider.~Image();
    //verticalSliderThumb.~Image();
    //glow.~Image();
}
//==============================================================================

void CustomLookAndFeel::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider)
{
    //g.fillAll(Colours::grey); // debug background fill
    //LookAndFeel_V2::drawRotarySlider(g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, s); // default knob
    /*===============================================================================================================================================================*/

    // calculate image frame for clipping image
    double min = slider.getMinimum();
    double max = slider.getMaximum();
    double currValue = slider.getValue();
    double skewFactor = slider.getSkewFactor();

    int frame = static_cast<int>(pow(((currValue - min) / (max - min)), skewFactor) * static_cast<double>(numberFramesRotary));
    Rectangle<int> clipRect = { 0, jmax(0, jmin(frame, numberFramesRotary - 1)) * heightRotary, widthRotary, heightRotary };

    //const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled(); // TODO: nutzen für irgendetwas?

    // if knob radius is bigger than 12, then downsize them for displaying possible modSource
    if (jmin(width, height) > 24)
    {
        // relative size of knob to it's bounds, still searching for ideal scale
        float scale = 0.6f;
        // for now since testslider is full circle as well
        rotaryStartAngle = -float_Pi;
        rotaryEndAngle = float_Pi;

        const float radius = jmin(width / 2.0f, height / 2.0f); // whitout padding; originally [jmin(width / 2, height / 2) - 2.0f]
        const float diameter = radius * 2.0f;
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius; // upper left x coordinate of saturn
        const float ry = centreY - radius; // upper left y coordinate of saturn
        const float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle); // current slider position angle

        // display modulation on slider
        {
            modSource1 = static_cast<MouseOverKnob&>(slider).getModSource1(); // TODO: wie siehts aus mit gewöhnlichem slider?
            modSource2 = static_cast<MouseOverKnob&>(slider).getModSource2(); //       macht source1 != NULL aber source2 == NULL, evtl. normale slider weg

            // TODO: SynthParams erweitern um...
            //       UNIPOLAR: from angle to min(endAngle, angle + amount)
            //       BIPOLAR: from max(angle - amount/2, startAngle) to min(angle + amount/2, endAngle)
            //       modSource ADDITIV oder MULTIPLIKATIV???
            // TODO: saturn größe und position noch mal besser berechnen, modularer an radius (und vllt. scale) angepasst
            // TODO: mod Amounts position berechnen

            ColourGradient gradient;
            Path saturn;

            // draw saturn 1 if modSource is in use
            if (modSource1 != nullptr)
            {
                // test modSource unipolar, changing amount
                float mod1Val = modSource1->get();
                int frameMod = static_cast<int>(pow(((jmin(currValue + mod1Val, max) - min) / (max - min)), skewFactor) * static_cast<double>(numberFramesRotary));
                float modAngle = degreesToRadians((frameMod / 50.0f) * 360.0f);

                // TODO: create better glow effect
                gradient = ColourGradient(Colours::blue, centreX, centreY, Colours::transparentWhite, centreX + radius* (scale + (1.0f - scale) / 2.0f), centreY + radius * (scale + (1.0f - scale) / 2.0f), true);
                g.setGradientFill(gradient);

                saturn.clear();
                saturn.addPieSegment(rx, ry, diameter, diameter, angle, modAngle, scale + (1.0f - scale) / 2.0f);
                g.fillPath(saturn);
            }

            // draw saturn 2 if modSource is in use
            if (modSource2 != nullptr)
            {
                // TODO: create better glow effect
                gradient = ColourGradient(Colours::red, centreX, centreY, Colours::transparentWhite, centreX + radius*scale, centreY + radius*scale, true);
                g.setGradientFill(gradient);

                saturn.clear();
                saturn.addPieSegment(rx, ry, diameter, diameter, angle - rotaryEndAngle*0.2f, angle + rotaryEndAngle*0.2f, scale); // test bipolar, fixed amount
                g.fillPath(saturn);
            }
        }

        // draw knob image
        if (slider.isEnabled()) // TODO: enabled nur für knob oder auch für saturns?
        {
            g.drawImageWithin(rotarySliderImage.getClippedImage(clipRect),
                x + (width - static_cast<int>(width * scale)) / 2,
                y + (height - static_cast<int>(height * scale)) / 2,
                static_cast<int>(width * scale), static_cast<int>(height * scale),
                RectanglePlacement::centred);
        }
        else
        {
            // TODO: grau zeichnen oder ANDERES BILD
            //g.drawImageWithin(rotarySliderImage.getClippedImage(clipRect),
            //    x + (width - static_cast<int>(width * scale)) / 2,
            //    y + (height - static_cast<int>(height * scale)) / 2,
            //    static_cast<int>(width * scale), static_cast<int>(height * scale),
            //    RectanglePlacement::centred);
        }
    }
    else
    {
        // if knob radius is smaller than 12, then draw without saturn using full width and full height
        if (slider.isEnabled())
        {
            g.drawImageWithin(rotarySliderImage.getClippedImage(clipRect), x, y, width, height, RectanglePlacement::centred);
        }
        else
        {
            g.drawImageWithin(rotarySliderImage.getClippedImage(clipRect), x, y, width, height, RectanglePlacement::centred); // TODO: grau zeichnen oder ANDERES BILD
        }
    }
}

void CustomLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider)
{
    if (style == Slider::SliderStyle::LinearVertical)
    {
        // draw vertical slider base
        g.drawImageWithin(verticalSlider, x, y, width, height, RectanglePlacement::centred);

        // draw thumb
        int offset = static_cast<int>(sliderPos - (static_cast<float>(thumbHeight) / 2.0) * (thumbSize / static_cast<float>(thumbHeight)));
        g.drawImageWithin(verticalSliderThumb, x, offset, width, static_cast<int>(thumbSize), RectanglePlacement::centred);
    }
    else
    {
        // TODO: für andere styles noch, je nach dem, was verwendet wird
        LookAndFeel_V2::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
}
