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
CustomLookAndFeel::CustomLookAndFeel(SynthParams &p): LookAndFeel_V2(), params(p)
{
    // set various things like Font etc
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
    // TODO: if slider needs on saturn then smaller size for draw saturn
    // draw frame into given position
    //g.fillAll(Colours::grey); // debug background fill
    //g.drawImageWithin(glow, x, y, width, height, RectanglePlacement::centred);    

    //float radius = static_cast<float>(jmin(width, height));

    //ColourGradient gradient = ColourGradient(Colours::red, width / 2, height / 2, Colours::white, width / 2 + radius / 2, height / 2 + radius / 2, true);
    //g.setGradientFill(gradient);

    //g.fillEllipse(width/2 - radius/2, height/2 - radius/2, radius, radius);

    //int sizeSub = 12;
    //g.drawImageWithin(rotarySliderImage.getClippedImage(rect), x + sizeSub / 2, y + sizeSub / 2, width - sizeSub, height - sizeSub, RectanglePlacement::centred);
    //g.drawImageWithin(rotarySliderImage.getClippedImage(rect), x, y, width, height, RectanglePlacement::centred);

    //LookAndFeel_V2::drawRotarySlider(g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, s); // default knob
    
    /*===============================================================================================================================================================*/

    double min = slider.getMinimum();
    double max = slider.getMaximum();
    double currValue = slider.getValue();
    double skewFactor = slider.getSkewFactor();

    // calculate image frame for clipping and draw
    int frame = static_cast<int>(pow(((currValue - min) / (max - min)), skewFactor) * static_cast<double>(numberFramesRotary));

    // test modSource unipolar
    float mod1Val = params.osc1lfo1depth.get();
    int frameMod = static_cast<int>(pow(((jmin(currValue + mod1Val, max) - min) / (max - min)), skewFactor) * static_cast<double>(numberFramesRotary));
    float modAngle = degreesToRadians((frameMod / 50.0f) * 360.0f);

    Rectangle<int> rect = { 0, jmax(0, jmin(frame, numberFramesRotary - 1)) * heightRotary, widthRotary, heightRotary };

    // for now since testslider is full circle as well
    rotaryStartAngle = -float_Pi;
    rotaryEndAngle = float_Pi;

    //const float radius = jmin(widthRotary / 2, heightRotary / 2) - sizeSub; // originally [jmin(width / 2, height / 2) - 2.0f]
    const float radius = jmin(width / 2.0f, height / 2.0f); // whitout padding
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius; // upper left x coordinate
    const float ry = centreY - radius; // upper left y coordinate
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle); // current slider position angle
    const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

    //int sizeSub = 17 * (rw / heightRotary); // TODO: modular calculation, slider soll 70 oder 80% sein

    float scale = 0.6f;

    if (radius > 12.0f)
    {
        // TODO: add if saturn is enabled then show saturns
        if (slider.isEnabled())
            //g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 1.0f : 0.7f));
            g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(1.0f));
        else
            g.setColour(Colour(0x80808080));

        // fill arc with colour
        {
            // TODO: unipolar: from angle to min(endAngle, angle + amount)
            //       bipolar: from max(angle - amount/2, startAngle) to min(angle + amount/2, endAngle)

            ColourGradient gradient = ColourGradient(Colours::blue, centreX, centreY, Colours::transparentWhite, centreX + radius* (scale + (1.0f - scale) / 2.0f), centreY + radius * (scale + (1.0f - scale) / 2.0f), true);
            //gradient.multiplyOpacity(1.f);
            //gradient.addColour(1.0f, Colours::red);
            g.setGradientFill(gradient);
            Path outerSaturn;
            outerSaturn.addPieSegment(rx, ry, rw, rw, angle, angle + modAngle, scale + (1.0f - scale) / 2.0f); // TODO: fehler: moduliert sich selbst dazu
            g.fillPath(outerSaturn);

            //g.setColour(Colours::red);
            gradient = ColourGradient(Colours::red, centreX, centreY, Colours::transparentWhite, centreX + radius*scale, centreY + radius*scale, true);
            //gradient.multiplyOpacity(1.f);
            //gradient.addColour(1.0f, Colours::red);
            g.setGradientFill(gradient);
            Path innerSaturn;
            innerSaturn.addPieSegment(rx, ry, rw, rw, angle - rotaryEndAngle*0.2f, angle + rotaryEndAngle*0.2f, scale);
            g.fillPath(innerSaturn);
        }

        g.drawImageWithin(rotarySliderImage.getClippedImage(rect),
            x + (width - static_cast<int>(width * scale)) / 2,
            y + (height - static_cast<int>(height * scale)) / 2,
            static_cast<int>(width * scale), static_cast<int>(height * scale),
            RectanglePlacement::centred);

        // inner pointer on current value
        //{
        //    const float innerRadius = radius * 0.2f;
        //    Path p;
        //    p.addTriangle(-innerRadius, 0.0f,
        //        0.0f, -radius * thickness * 1.1f,
        //        innerRadius, 0.0f);

        //    p.addEllipse(-innerRadius, -innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);

        //    g.fillPath(p, AffineTransform::rotation(angle).translated(centreX, centreY));
        //}

        //if (slider.isEnabled())
        //    g.setColour(slider.findColour(Slider::rotarySliderOutlineColourId));
        //else
        //    g.setColour(Colour(0x80808080));

        // draw arc outlines
        //Path outlineArc;
        //outlineArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
        //outlineArc.closeSubPath();

        //g.strokePath(outlineArc, PathStrokeType(slider.isEnabled() ? (isMouseOver ? 2.0f : 1.2f) : 0.3f));
    }
    else
    {
        //if (slider.isEnabled())
        //    g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 1.0f : 0.7f));
        //else
        //    g.setColour(Colour(0x80808080));

        //Path p;
        //p.addEllipse(-0.4f * rw, -0.4f * rw, rw * 0.8f, rw * 0.8f);
        //PathStrokeType(rw * 0.1f).createStrokedPath(p, p);

        //p.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, -radius), rw * 0.2f);

        //g.fillPath(p, AffineTransform::rotation(angle).translated(centreX, centreY));
        g.drawImageWithin(rotarySliderImage.getClippedImage(rect), x, y, width, height, RectanglePlacement::centred);
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
        LookAndFeel_V2::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
}
