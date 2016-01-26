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
    this->setDefaultSansSerifTypefaceName("Bauhaus 93");

    // load assets
    //rotarySliderImage = ImageCache::getFromMemory(BinaryData::knobstrip_png, BinaryData::knobstrip_pngSize);
    //verticalSlider = ImageCache::getFromMemory(BinaryData::vertical_slider_png, BinaryData::vertical_slider_pngSize);
    //verticalSliderThumb = ImageCache::getFromMemory(BinaryData::slider_thumb_png, BinaryData::slider_thumb_pngSize);
    //glow = ImageCache::getFromMemory(BinaryData::glow_png, BinaryData::glow_pngSize);
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
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    //const bool isMouseOver = s.isMouseOverOrDragging() && s.isEnabled(); // TODO: verwenden!

    // custom start and end angle for knob and saturn
    rotaryStartAngle = -float_Pi + degreesToRadians(45.0f);
    rotaryEndAngle = float_Pi - degreesToRadians(45.0f);

    // current slider position angle in radians in range [rotaryStartAngle, rotaryEndAngle]
    const float currAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    const float knobMargin = 0.70f; // relative knobBorder to max radius
    const float radiusSource2 = jmin(width / 2.0f, height / 2.0f);
    const float radiusKnob = radiusSource2 * knobMargin;
    const float radiusSource1 = radiusKnob + (radiusSource2 - radiusKnob) / 2.0f;

    Path knob, saturn;

    // if knob radius is bigger than 12, then downsize them for displaying possible modSource
    if (jmin(width, height) > 24)
    {
        // display modulation on slider if neccessary
        std::array<Param*, 2> modSources = static_cast<MouseOverKnob&>(s).getModSources();

        // TODO: SynthParams erweitern um...
        //       UNIPOLAR: from angle to min(endAngle, angle + amount)
        //       BIPOLAR: from max(angle - amount/2, startAngle) to min(angle + amount/2, endAngle)
        //       modSource ADDITIV oder MULTIPLIKATIV???
        // TODO: wie siehts aus mit gewöhnlichem slider? -> am besten alle normalen slider weg
        // TODO: wenn modSource vorhanden, dann draw arc outline?

        float modStartAngle, modEndAngle, modPosition1, modPosition2;
        double afterModVal1, afterModVal2;

        // draw saturn 1 if modSource is in use
        
            if (modSources[0] != nullptr)
            {
                // NOTE: testcase unipolar
                // if(unipolar)
                {
                    // if(additiv)
                    {
                        afterModVal1 = jmax(s.getMinimum(), jmin(s.getValue() + modSources[0]->get(), s.getMaximum()));
                    }
                    //else
                    //{
                    //// multiplicative
                    //afterModVal = jmax(s.getMinimum(), jmin(currValue * modSource1->get(), max));
                    //}
                    
                    modPosition1 = static_cast<float>(pow((afterModVal1 - s.getMinimum()) / (s.getMaximum() - s.getMinimum()), s.getSkewFactor()));
                    modStartAngle = currAngle;
                    modEndAngle = rotaryStartAngle + modPosition1 * (rotaryEndAngle - rotaryStartAngle);
                }
                //else
                //{
                // bipolar
                
                //}
                
                g.setColour(s.isEnabled() ? Colours::blue : Colours::lightgrey);
                saturn.addPieSegment(centreX - radiusSource1, centreY - radiusSource1, radiusSource1 * 2.0f, radiusSource1 * 2.0f,
                                     jmax(rotaryStartAngle, jmin(modStartAngle, rotaryEndAngle)), jmax(rotaryStartAngle, jmin(modEndAngle, rotaryEndAngle)), (radiusKnob / radiusSource1));
                g.fillPath(saturn);
            }

        // draw saturn 2 if modSource is in use
        if (modSources[1] != nullptr)
        {
            // NOTE: testcase bipolar
            // if(unipolar)
            //{
                // unipolar
            //}
            //else
            {
                // if(additiv)
                {
                    afterModVal1 = jmax(s.getMinimum(), jmin(s.getValue() + modSources[1]->get() / 2.0f, s.getMaximum()));
                    afterModVal2 = jmax(s.getMinimum(), jmin(s.getValue() - modSources[1]->get() / 2.0f, s.getMaximum()));
                }
                //else
                //{
                //// multiplicative
                //afterModVal = jmax(min, jmin(currValue * modSource1->get(), max));
                //}

                modPosition1 = static_cast<float>(pow((afterModVal1 - s.getMinimum()) / (s.getMaximum() - s.getMinimum()), s.getSkewFactor()));
                modPosition2 = static_cast<float>(pow((afterModVal2 - s.getMinimum()) / (s.getMaximum() - s.getMinimum()), s.getSkewFactor()));

                modStartAngle = rotaryStartAngle + modPosition1 * (rotaryEndAngle - rotaryStartAngle);
                modEndAngle = rotaryStartAngle + modPosition2 * (rotaryEndAngle - rotaryStartAngle);
            }

            g.setColour(s.isEnabled()? Colours::red : Colours::slategrey);
            saturn.clear();
            saturn.addPieSegment(centreX - radiusSource2, centreY - radiusSource2, radiusSource2 * 2.0f, radiusSource2 * 2.0f,
                jmax(-float_Pi, jmin(modStartAngle, float_Pi)), jmax(-float_Pi, jmin(modEndAngle, float_Pi)), (radiusSource1 / radiusSource2));
            g.fillPath(saturn);
        }

        // draw knob
        //int frame = static_cast<int>(sliderPosProportional * numberFramesRotary);
        //Rectangle<int> clipRect = { 0, jmax(0, jmin(frame, numberFramesRotary - 1)) * heightRotary, widthRotary, heightRotary };
        //g.drawImageWithin(rotarySliderImage.getClippedImage(clipRect),
        //    static_cast<int>(centreX - radiusKnob), static_cast<int>(centreY - radiusKnob),
        //    static_cast<int>(radiusKnob * 2.0f), static_cast<int>(radiusKnob * 2.0f),
        //    RectanglePlacement::centred);

        // draw knob border
        g.setColour(s.isEnabled() ? Colours::white : Colours::grey);
        knob.addEllipse(centreX - radiusKnob, centreY - radiusKnob, radiusKnob * 2.0f, radiusKnob * 2.0f);
        g.fillPath(knob);

        // draw knob pointer
        g.setColour(s.findColour(Slider::rotarySliderFillColourId).withAlpha(s.isEnabled()? 1.0f : 0.5f));
        knob.clear();
        knob.addPieSegment(centreX - radiusKnob * knobMargin, centreY - radiusKnob * knobMargin, radiusKnob * knobMargin * 2.0f, radiusKnob * knobMargin * 2.0f, // first part
            -float_Pi, jmax(-float_Pi, jmin(currAngle - float_Pi / 18.0f, float_Pi)), 0.0f);
        knob.addPieSegment(centreX - radiusKnob * knobMargin, centreY - radiusKnob * knobMargin, radiusKnob * knobMargin * 2.0f, radiusKnob * knobMargin * 2.0f, // second part
            float_Pi, jmax(-float_Pi, jmin(currAngle + float_Pi / 18.0f, float_Pi)), 0.0f);
        g.fillPath(knob);
    }
    else
    {
        // if knob radius is smaller than 12, then draw without saturn using full width and full height
        g.setColour(s.isEnabled()? Colours::white : Colours::grey);
        knob.addPieSegment(centreX - radiusSource2, centreY - radiusSource2, radiusSource2 * 2.0f, radiusSource2 * 2.0f, // first part
            -float_Pi, jmax(-float_Pi, jmin(currAngle - float_Pi / 18.0f, float_Pi)), 0.0f);
        knob.addPieSegment(centreX - radiusSource2, centreY - radiusSource2, radiusSource2 * 2.0f, radiusSource2 * 2.0f, // second part
            float_Pi, jmax(-float_Pi, jmin(currAngle + float_Pi / 18.0f, float_Pi)), 0.0f);
        g.fillPath(knob);
    }
}

void CustomLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s)
{
    if (style == Slider::LinearBar || style == Slider::LinearBarVertical)
    {
        // TODO: change bar into Vol and Pan
        LookAndFeel_V2::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
    }
    else
    {
        // draw linear slider
        drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
        drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
    }
}

void CustomLookAndFeel::drawLinearSliderBackground(Graphics &g, int x, int y, int width, int height, float /*sliderPos*/, float /*minSliderPos*/, float /*maxSliderPos*/, const Slider::SliderStyle /*style*/, Slider &s)
{
    const float sliderRadius = (float)(jmin(20, width / 2, height / 2) - 2);
    g.setColour(s.findColour(Slider::trackColourId));
    Path indent;

    if (s.isHorizontal())
    {
        const float iy = y + height * 0.5f - sliderRadius * 0.5f;
        const float ih = sliderRadius;

        indent.addRoundedRectangle(x - sliderRadius * 0.5f, iy,
            width + sliderRadius, ih,
            10.0f);
    }
    else
    {
        const float ix = x + width * 0.5f - sliderRadius * 0.5f;
        const float iw = sliderRadius;

        indent.addRoundedRectangle(ix, y - sliderRadius * 0.5f,
            iw, height + sliderRadius,
            10.0f);
    }

    g.fillPath(indent);
}

void CustomLookAndFeel::drawLinearSliderThumb(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s)
{
    const float sliderRadius = (float)(jmin(10, width / 2, height / 2) - 2);

    Colour knobColour(s.findColour(Slider::thumbColourId));

    const float outlineThickness = s.isEnabled() ? 0.8f : 0.3f;

    if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
    {
        float kx, ky;

        if (style == Slider::LinearVertical)
        {
            kx = x + width * 0.5f;
            ky = sliderPos;
        }
        else
        {
            kx = sliderPos;
            ky = y + height * 0.5f;
        }

        g.setColour(knobColour);
        g.fillEllipse(kx - sliderRadius, ky - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f);
    }
    else
    {
        // TODO: diese hier machen, falls verwendet werden, sonst egal
        if (style == Slider::ThreeValueVertical)
        {
            drawGlassSphere(g, x + width * 0.5f - sliderRadius,
                sliderPos - sliderRadius,
                sliderRadius * 2.0f,
                knobColour, outlineThickness);
        }
        else if (style == Slider::ThreeValueHorizontal)
        {
            drawGlassSphere(g, sliderPos - sliderRadius,
                y + height * 0.5f - sliderRadius,
                sliderRadius * 2.0f,
                knobColour, outlineThickness);
        }

        if (style == Slider::TwoValueVertical || style == Slider::ThreeValueVertical)
        {
            const float sr = jmin(sliderRadius, width * 0.4f);

            drawGlassPointer(g, jmax(0.0f, x + width * 0.5f - sliderRadius * 2.0f),
                minSliderPos - sliderRadius,
                sliderRadius * 2.0f, knobColour, outlineThickness, 1);

            drawGlassPointer(g, jmin(x + width - sliderRadius * 2.0f, x + width * 0.5f), maxSliderPos - sr,
                sliderRadius * 2.0f, knobColour, outlineThickness, 3);
        }
        else if (style == Slider::TwoValueHorizontal || style == Slider::ThreeValueHorizontal)
        {
            const float sr = jmin(sliderRadius, height * 0.4f);

            drawGlassPointer(g, minSliderPos - sr,
                jmax(0.0f, y + height * 0.5f - sliderRadius * 2.0f),
                sliderRadius * 2.0f, knobColour, outlineThickness, 2);

            drawGlassPointer(g, maxSliderPos - sliderRadius,
                jmin(y + height - sliderRadius * 2.0f, y + height * 0.5f),
                sliderRadius * 2.0f, knobColour, outlineThickness, 4);
        }
    }
}

void CustomLookAndFeel::drawToggleButton(Graphics &g, ToggleButton &t, bool isMouseOverButton, bool isButtonDown)
{
   // LookAndFeel_V2::drawToggleButton(g, t, isMouseOverButton, isButtonDown);

    if (t.hasKeyboardFocus(true))
    {
        g.setColour(t.findColour(TextEditor::focusedOutlineColourId));
        g.drawRect(0, 0, t.getWidth(), t.getHeight());
    }

    float fontSize = jmin(15.0f, t.getHeight() * 0.75f);
    const float tickWidth = fontSize * 1.1f;

    drawTickBox(g, t, 4.0f, (t.getHeight() - tickWidth) * 0.5f,
        tickWidth, tickWidth,
        t.getToggleState(),
        t.isEnabled(),
        isMouseOverButton,
        isButtonDown);

    g.setColour(t.findColour(ToggleButton::textColourId));
    g.setFont(fontSize);

    if (!t.isEnabled())
        g.setOpacity(0.5f);

    const int textX = (int)tickWidth + 5;

    g.drawFittedText(t.getButtonText(),
        textX, 0,
        t.getWidth() - textX - 2, t.getHeight(),
        Justification::centredLeft, 10);
}

void CustomLookAndFeel::drawTickBox(Graphics &g, Component &c, float x, float y, float width, float height, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
{
    float centreX = x + width * 0.85f / 2.0f;
    float centreY = y + height / 2.0f;
    Colour c1, c2;

    // TODO: colourgradient mit transparentwhite und transparentwhite verwenden wenn inactive
    // wenn active dann innere farbe zu white, s.d. glow
    // unterscheidung für mouseOver
    if (!ticked)
    {
        float boxSize = width * 0.7f;

        c1 = isMouseOverButton ? Colours::grey : Colours::lightgrey;
        c2 = Colours::black;

        ColourGradient gradient(c1, centreX, centreY, c2, centreX + boxSize / 2.0f, centreX + boxSize / 2.0f, true);
        gradient.addColour(0.1f, c1);
        g.setGradientFill(gradient);

        g.fillEllipse(centreX - boxSize / 2.0f, centreY - boxSize / 2.0f, boxSize, boxSize);
    }
    else
    {
        float glowSize = width * 0.9f;

        c1 = isMouseOverButton ? Colours::white : Colours::whitesmoke;
        c2 = Colours::transparentWhite;

        ColourGradient gradient(c1, centreX, centreY, c2, centreX + (glowSize * 0.75f) / 2.0f, centreX + (glowSize * 0.75f) / 2.0f, true);
        gradient.addColour(0.4f, c1);
        g.setGradientFill(gradient);

        g.fillEllipse(centreX - glowSize / 2.0f, centreY - glowSize / 2.0f, glowSize, glowSize);
    }
}
