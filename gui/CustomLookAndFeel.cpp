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

void CustomLookAndFeel::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &s)
{
    //g.fillAll(Colours::grey); // debug background fill
    //LookAndFeel_V2::drawRotarySlider(g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, s); // default knob
    //===============================================================================================================================================================//

    // calculate image frame for clipping image
    double min = s.getMinimum();
    double max = s.getMaximum();
    double currValue = s.getValue();
    double skewFactor = s.getSkewFactor();

    int frame = static_cast<int>(pow(((currValue - min) / (max - min)), skewFactor) * static_cast<double>(numberFramesRotary));
    Rectangle<int> clipRect = { 0, jmax(0, jmin(frame, numberFramesRotary - 1)) * heightRotary, widthRotary, heightRotary };
    
    //const bool isMouseOver = s.isMouseOverOrDragging() && s.isEnabled(); // TODO: nutzen für irgendetwas?

    // if knob radius is bigger than 12, then downsize them for displaying possible modSource
    if (jmin(width, height) > 24)
    {
        // for now since testslider is full circle as well
        rotaryStartAngle = -float_Pi;
        rotaryEndAngle = float_Pi;

        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float currAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle); // current slider position angle in radians in range [-pi, pi]

        float radiusSource2 = jmin(width / 2.0f, height / 2.0f); // whole bounds
        float radiusKnob = radiusSource2 * 0.75f; // gute scale suchen (0.75 ganz gut für standard größe 64x64)
        float radiusSource1 = radiusKnob + (radiusSource2 - radiusKnob) / 2.0f;

        // display modulation on slider
        {
            Param* modSource1 = static_cast<MouseOverKnob&>(s).getModSource1(); // TODO: wie siehts aus mit gewöhnlichem slider?
            Param* modSource2 = static_cast<MouseOverKnob&>(s).getModSource2(); //       macht source1 != NULL aber source2 == NULL, evtl. alle normalen slider weg

            // TODO: SynthParams erweitern um...
            //       UNIPOLAR: from angle to min(endAngle, angle + amount)
            //       BIPOLAR: from max(angle - amount/2, startAngle) to min(angle + amount/2, endAngle)
            //       modSource ADDITIV oder MULTIPLIKATIV???
            // TODO: saturn größe und position noch mal besser berechnen, modularer an radius (und vllt. scale) angepasst
            // TODO: mod Amounts position berechnen

            ColourGradient gradient;
            Path saturn;
            float startAngle = rotaryStartAngle;
            float endAngle = rotaryEndAngle;

            // draw saturn 2 if modSource is in use
            if (true)
                if (modSource2 != nullptr)
            {
                // NOTE: testcase bipolar
                // if(unipolar)
                //{
                    // unipolar
                //}
                //else
                {
                    double afterModVal1 = currValue;
                    double afterModVal2 = currValue;
                    // if(additiv)
                    {
                        afterModVal1 = jmax(min, jmin(currValue + modSource1->get() / 2.0f, max));
                        afterModVal2 = jmax(min, jmin(currValue - modSource1->get() / 2.0f, max));
                    }
                    //else
                    //{
                    //// multiplicative
                    //afterModVal = jmax(min, jmin(currValue * modSource1->get(), max));
                    //}

                    float frameMod1 = static_cast<float>(pow((afterModVal1 - min) / (max - min), skewFactor));
                    float frameMod2 = static_cast<float>(pow((afterModVal2 - min) / (max - min), skewFactor));

                    float modAngle1 = degreesToRadians(frameMod1 * 360.0f) - float_Pi; // because angle in radians in range [-pi, pi]
                    float modAngle2 = degreesToRadians(frameMod2 * 360.0f) - float_Pi; // because angle in radians in range [-pi, pi]

                    startAngle = modAngle1;
                    endAngle = modAngle2;
                }

                //// TODO: create better glow effect
                //gradient = ColourGradient(Colours::red, centreX, centreY, Colours::transparentWhite, centreX + radiusSource2, centreY + radiusSource2, true);
                //g.setGradientFill(gradient);
                g.setColour(s.isEnabled()? Colours::red : Colours::slategrey);

                saturn.clear();
                saturn.addPieSegment(centreX - radiusSource2, centreY - radiusSource2, radiusSource2 * 2.0f, radiusSource2 * 2.0f, 
                    jmax(-float_Pi, jmin(startAngle, float_Pi)), jmax(-float_Pi, jmin(endAngle, float_Pi)), (radiusSource1 / radiusSource2));
                g.fillPath(saturn);
            }

            // draw saturn 1 if modSource is in use
            if (true)
                if (modSource1 != nullptr)
            {
                // NOTE: testcase unipolar
                // if(unipolar)
                {
                    double afterModVal = currValue;
                    // if(additiv)
                    {
                        afterModVal = jmax(min, jmin(currValue + modSource1->get(), max));
                    }
                    //else
                    //{
                        //// multiplicative
                        //afterModVal = jmax(min, jmin(currValue * modSource1->get(), max));
                    //}

                    float frameMod = static_cast<float>(pow((afterModVal - min) / (max - min), skewFactor));
                    
                    float modAngle = degreesToRadians(frameMod * 360.0f) - float_Pi; // because angle in radians in range [-pi, pi]

                    startAngle = currAngle;
                    endAngle = modAngle;
                }
                //else
                //{
                    // bipolar
                    
                //}

                //// TODO: create better glow effect
                //gradient = ColourGradient(Colours::blue, centreX, centreY, Colours::transparentWhite, centreX + radiusSource1, centreY + radiusSource1, true);
                //g.setGradientFill(gradient);
                g.setColour(s.isEnabled() ? Colours::blue : Colours::lightgrey);

                saturn.clear();
                saturn.addPieSegment(centreX - radiusSource1, centreY - radiusSource1, radiusSource1 * 2.0f, radiusSource1 * 2.0f, 
                    jmax(-float_Pi, jmin(startAngle, float_Pi)), jmax(-float_Pi, jmin(endAngle, float_Pi)), (radiusKnob / radiusSource1));
                g.fillPath(saturn);
            }
        }

        // draw knob image
        if (s.isEnabled()) // TODO: enabled nur für knob oder auch für saturns?
        {
            g.drawImageWithin(rotarySliderImage.getClippedImage(clipRect),
                static_cast<int>(centreX - radiusKnob), static_cast<int>(centreY - radiusKnob),
                static_cast<int>(radiusKnob * 2.0f), static_cast<int>(radiusKnob * 2.0f),
                RectanglePlacement::centred);
        }
        else
        {
            g.drawImageWithin(rotarySliderImage.getClippedImage(clipRect), // TODO: grau zeichnen oder ANDERES BILD
                static_cast<int>(centreX - radiusKnob), static_cast<int>(centreY - radiusKnob),
                static_cast<int>(radiusKnob * 2.0f), static_cast<int>(radiusKnob * 2.0f),
                RectanglePlacement::centred);
        }
    }
    else
    {
        // if knob radius is smaller than 12, then draw without saturn using full width and full height
        if (s.isEnabled())
        {
            g.drawImageWithin(rotarySliderImage.getClippedImage(clipRect), x, y, width, height, RectanglePlacement::centred);
        }
        else
        {
            g.drawImageWithin(rotarySliderImage.getClippedImage(clipRect), x, y, width, height, RectanglePlacement::centred); // TODO: grau zeichnen oder ANDERES BILD
        }
    }
}

void CustomLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s)
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
        LookAndFeel_V2::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
    }
}
