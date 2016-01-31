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
    this->setDefaultSansSerifTypefaceName("Bauhaus 93");

    // load assets
    //rotarySliderImage = ImageCache::getFromMemory(BinaryData::knobstrip_png, BinaryData::knobstrip_pngSize);
    //verticalSlider = ImageCache::getFromMemory(BinaryData::vertical_slider_png, BinaryData::vertical_slider_pngSize);
    //verticalSliderThumb = ImageCache::getFromMemory(BinaryData::slider_thumb_png, BinaryData::slider_thumb_pngSize);
    //glow = ImageCache::getFromMemory(BinaryData::glow_png, BinaryData::glow_pngSize);
}

CustomLookAndFeel::~CustomLookAndFeel()
{

}
//==============================================================================
/**
* Draw Rotary Slider with saturns if neccessary.
*/
void CustomLookAndFeel::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &s)
{
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const bool isMouseOver = s.isMouseOverOrDragging() && s.isEnabled();

    // custom start and end angle for knob and saturn
    rotaryStartAngle = -float_Pi + degreesToRadians(30.0f);
    rotaryEndAngle = float_Pi - degreesToRadians(30.0f);

    // current slider position angle in radians in range [rotaryStartAngle, rotaryEndAngle]
    const float currAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    const float knobMargin = 0.7f; // relative knobBorder to max radius
    const float radiusSource2 = jmin(width / 2.0f, height / 2.0f);
    const float radiusKnob = radiusSource2 * knobMargin;
    const float radiusSource1 = radiusKnob + (radiusSource2 - radiusKnob) / 2.0f;

    Path knob;
    Colour baseColour(s.findColour(Slider::rotarySliderFillColourId));
    float r;

    // if knob radius is bigger than 12, then downsize them for displaying possible modSource
    if (jmin(width, height) > 24)
    {
        // display modulation on slider if neccessary
        std::array<Param*, 2> modSources = static_cast<MouseOverKnob&>(s).getModSources();

        // draw saturn 1 if modSource is in use
        if (modSources[0] != nullptr)
        {
            drawModSource(g, s, modSources[0]->get(), true, centreX, centreY, radiusSource1, (radiusKnob / radiusSource1), currAngle, rotaryStartAngle, rotaryEndAngle);
        }

        // draw saturn 2 if modSource is in use
        if (modSources[1] != nullptr)
        {
            drawModSource(g, s, modSources[1]->get(), false, centreX, centreY, radiusSource2, (radiusSource1 / radiusSource2), currAngle, rotaryStartAngle, rotaryEndAngle);
        }

        // draw knob border
        g.setColour(s.isEnabled() ? Colours::white : Colours::grey);
        knob.addEllipse(centreX - radiusKnob, centreY - radiusKnob, radiusKnob * 2.0f, radiusKnob * 2.0f);
        g.fillPath(knob);

        g.setColour(s.isEnabled() ? (isMouseOver ? baseColour.brighter(0.1f) : baseColour) : baseColour.withAlpha(0.5f));
        knob.clear();
        r = radiusKnob * knobMargin;
    }
    else
    {
        g.setColour(s.isEnabled() ? Colours::white : Colours::grey);
        r = radiusSource2;
    }

    // draw first part of value pointer
    knob.addPieSegment(centreX - r, centreY - r, r * 2.0f, r * 2.0f, -float_Pi, currAngle - float_Pi / 18.0f, 0.0f);
    // draw second part of value pointer
    knob.addPieSegment(centreX - r, centreY - r, r * 2.0f, r * 2.0f, float_Pi, currAngle + float_Pi / 18.0f, 0.0f);
    g.fillPath(knob);
}

/**
* Draw modSource as Saturn.
* TODO: später statt sourceValue und unipolar, den ganzen param rein und dann check auf unipolar/bipolar und evtl. Colour
*/
void CustomLookAndFeel::drawModSource(Graphics &g, Slider &s, float sourceValue, bool unipolar,
    float centreX, float centreY, float radius, float innerCircleSize,
    float currAngle, float rotaryStartAngle, float rotaryEndAngle)
{
    const float val = static_cast<float>(s.getValue());
    const float min = static_cast<float>(s.getMinimum());
    const float max = static_cast<float>(s.getMaximum());
    const float skew = static_cast<float>(s.getSkewFactor());

    float modStartAngle, modEndAngle, modPosition1, modPosition2;
    float afterModVal1, afterModVal2;

    // TODO: SynthParams erweitern um...
    //       UNIPOLAR: from angle to min(endAngle, angle + amount)
    //       BIPOLAR: from max(angle - amount/2, startAngle) to min(angle + amount/2, endAngle)
    //       modSource ADDITIV oder MULTIPLIKATIV???
    // TODO: sourceValue generisch machen im bereich [0..1.f] als % mod amount

    if (unipolar)
    {
        afterModVal1 = jmax(min, jmin(val + sourceValue, max));
        modPosition1 = pow((afterModVal1 - min) / (max - min), skew);

        modStartAngle = currAngle;
        modEndAngle = rotaryStartAngle + modPosition1 * (rotaryEndAngle - rotaryStartAngle);
    }
    else
    {
        afterModVal1 = jmax(min, jmin(val + sourceValue / 2.0f, max));
        afterModVal2 = jmax(min, jmin(val - sourceValue / 2.0f, max));
        modPosition1 = pow((afterModVal1 - min) / (max - min), skew);
        modPosition2 = pow((afterModVal2 - min) / (max - min), skew);

        modStartAngle = rotaryStartAngle + modPosition1 * (rotaryEndAngle - rotaryStartAngle);
        modEndAngle = rotaryStartAngle + modPosition2 * (rotaryEndAngle - rotaryStartAngle);
    }

    Path saturn;
    g.setColour(s.isEnabled() ? Colours::yellow : Colours::lightgrey); // TODO: mod specific colour verwenden
    saturn.addPieSegment(centreX - radius, centreY - radius, radius * 2.0f, radius * 2.0f, modStartAngle, modEndAngle, innerCircleSize * 1.03f);
    g.fillPath(saturn);
}

/**
* Draw Custom linear Slider.
*/
void CustomLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s)
{
    // use bar slider to draw vol and pan instead
    if (style == Slider::LinearBar || style == Slider::LinearBarVertical)
    {
        const bool isMouseOver = s.isMouseOverOrDragging() && s.isEnabled();
        const float c = 0.0f; // instead of always using static cast

        Path path;
        Colour baseColour(s.findColour(Slider::trackColourId));
        g.setColour(s.isEnabled() ? (isMouseOver ? baseColour.brighter(0.1f) : baseColour) : baseColour.withAlpha(0.5f));

        // draw bipolar triangle bars for pan
        if (s.getMinimum() == -s.getMaximum())
        {
            const float thumbWidthHalf = 2.0f;

            // fill left side
            path.addTriangle(x + c, y + c, x + c, y + height + c, x + width / 2.0f, y + height + c);

            // fill right side
            path.addTriangle(x + +width / 2.0f, y + height + c, x + width + c, y + height + c, x + width + c, y + c);
            g.fillPath(path);

            // TODO: richtiges konzept für pan fragen
            path.clear();
            g.setColour(s.findColour(Slider::thumbColourId));

            path.addQuadrilateral(x + sliderPos - thumbWidthHalf, y + height + c,
                                  x + sliderPos + thumbWidthHalf, y + height + c,
                                  x + sliderPos + thumbWidthHalf, y + c,
                                  x + sliderPos - thumbWidthHalf, y + c);
            g.fillPath(path);
        }
        // draw unipolar triangle bar for vol
        else
        {
            float offSet = height - height * (x + sliderPos) / (x + width);

            // fill triangle
            path.addTriangle(x + c, y + height + c, x + sliderPos, y + height + c, x + sliderPos, y + offSet);
            g.fillPath(path);

            // draw outline
            path.clear();
            path.addTriangle(x + width + c, y + c, x + c, y + height + c, x + width + c, y + height + c);
            g.strokePath(path, PathStrokeType::PathStrokeType(isMouseOver ? 1.5f : 1.0f));
        }
    }
    else
    {
        // draw linear slider
        drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
        drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
    }
}

/**
* Draw linear slider background.
*/
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

/**
* Draw linear slider thumb.
*/
void CustomLookAndFeel::drawLinearSliderThumb(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s)
{
    const float sliderRadius = (float)(jmin(10, width / 2, height / 2) - 2);
    const float outlineThickness = s.isEnabled() ? 0.8f : 0.3f;
    float centreX, centreY;

    Colour baseColour(s.findColour(Slider::thumbColourId));

    // draw thumb at curretn position
    if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
    {
        g.setColour(s.isMouseOver() ? baseColour.brighter(0.1f) : baseColour);
        centreX = style == Slider::LinearVertical ? (x + width / 2.0f) : sliderPos;
        centreY = style == Slider::LinearVertical ? sliderPos : (y + height / 2.0f);

        g.fillEllipse(centreX - sliderRadius, centreY - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f);
    }
    else
    {
        // we only need TwoValueHorizontal as alternativ linear slider
        if (style == Slider::TwoValueHorizontal)
        {
            const float cornerSize = 10.0f;
            const float r = (float)(jmin(20, width / 2, height / 2) - cornerSize);
            const float yOffset = y + height * 0.5f - r * 0.5f;
            centreY = y + height / 2.0f;

            // fill inner track
            g.setColour(s.findColour(Slider::rotarySliderFillColourId));
            g.fillRect(minSliderPos - cornerSize / 2.0f, yOffset, maxSliderPos - minSliderPos + cornerSize, r);

            // draw min slider thumb
            g.setColour(s.isMouseOver() ? baseColour.brighter(0.1f) : baseColour);
            centreX = minSliderPos;
            g.fillEllipse(centreX - sliderRadius, centreY - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f);

            // draw max slider thumb
            centreX = maxSliderPos;
            g.fillEllipse(centreX - sliderRadius, centreY - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f);
        }
        else
        {
            LookAndFeel_V2::drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
        }
    }
}

/**
* Set Slider Layout. Needed for mouseOverKnob with barSlider to not set textBoxPosition into bar slider. TODO: oder vllt. doch?
*/
Slider::SliderLayout CustomLookAndFeel::getSliderLayout(Slider& s)
{
    // 1. compute the actually visible textBox size from the slider textBox size and some additional constraints
    int minXSpace = 0;
    int minYSpace = 0;

    Slider::TextEntryBoxPosition textBoxPos = s.getTextBoxPosition();

    if (textBoxPos == Slider::TextBoxLeft || textBoxPos == Slider::TextBoxRight)
        minXSpace = 30;
    else
        minYSpace = 15;

    Rectangle<int> localBounds = s.getLocalBounds();

    const int textBoxWidth = jmax(0, jmin(s.getTextBoxWidth(), localBounds.getWidth() - minXSpace));
    const int textBoxHeight = jmax(0, jmin(s.getTextBoxHeight(), localBounds.getHeight() - minYSpace));

    Slider::SliderLayout layout;

    // 2. set the textBox bounds
    if (textBoxPos != Slider::NoTextBox)
    {
        layout.textBoxBounds.setWidth(textBoxWidth);
        layout.textBoxBounds.setHeight(textBoxHeight);

        if (textBoxPos == Slider::TextBoxLeft)           layout.textBoxBounds.setX(0);
        else if (textBoxPos == Slider::TextBoxRight)     layout.textBoxBounds.setX(localBounds.getWidth() - textBoxWidth);
        else /* above or below -> centre horizontally */ layout.textBoxBounds.setX((localBounds.getWidth() - textBoxWidth) / 2);

        if (textBoxPos == Slider::TextBoxAbove)          layout.textBoxBounds.setY(0);
        else if (textBoxPos == Slider::TextBoxBelow)     layout.textBoxBounds.setY(localBounds.getHeight() - textBoxHeight);
        else /* left or right -> centre vertically */    layout.textBoxBounds.setY((localBounds.getHeight() - textBoxHeight) / 2);
    }

    // 3. set the slider bounds
    layout.sliderBounds = localBounds;

    if (s.isBar())
    {
        layout.sliderBounds.reduce(1, 1);   // bar border

        if (s.isMouseOverOrDragging())
        {
            layout.sliderBounds.setHeight(layout.sliderBounds.getHeight() - textBoxHeight);
        }
    }
    else
    {
        if (textBoxPos == Slider::TextBoxLeft)       layout.sliderBounds.removeFromLeft(textBoxWidth);
        else if (textBoxPos == Slider::TextBoxRight) layout.sliderBounds.removeFromRight(textBoxWidth);
        else if (textBoxPos == Slider::TextBoxAbove) layout.sliderBounds.removeFromTop(textBoxHeight);
        else if (textBoxPos == Slider::TextBoxBelow) layout.sliderBounds.removeFromBottom(textBoxHeight);

        const int thumbIndent = getSliderThumbRadius(s);

        if (s.isHorizontal())    layout.sliderBounds.reduce(thumbIndent, 0);
        else if (s.isVertical()) layout.sliderBounds.reduce(0, thumbIndent);
    }

    return layout;
}


/**
* Draw button background.
*/
void CustomLookAndFeel::drawButtonBackground(Graphics& g, Button& b, const Colour& c, bool isMouseOverButton, bool isButtonDown)
{
    const int width = b.getWidth();
    const int height = b.getHeight();
    const float cornerSize = 7.0f;
    const float outlineThickness = 2.2f;
    const float halfThickness = outlineThickness * 0.5f;

    // background colour
    g.setColour(b.isEnabled() ? (isMouseOverButton ? c.brighter(0.1f) : c) : Colours::grey);
    g.fillRoundedRectangle(halfThickness, halfThickness, width - halfThickness * 2.0f, height - halfThickness * 2.0f, cornerSize);

    // draw outline
    g.setColour(b.isEnabled() ? b.findColour(isButtonDown ? TextButton::textColourOnId : TextButton::textColourOffId) : c.withAlpha(0.5f));
    g.drawRoundedRectangle(halfThickness, halfThickness, width - halfThickness * 2.0f, height - halfThickness * 2.0f, cornerSize, outlineThickness);
}


/*
* Draw toggle button. Needed to delete the hasKeyboardFocus() rectangle sorrounding toggle.
*/
void CustomLookAndFeel::drawToggleButton(Graphics &g, ToggleButton &b, bool isMouseOverButton, bool isButtonDown)
{
    float fontSize = jmin(15.0f, b.getHeight() * 0.75f);
    const float tickWidth = fontSize * 1.1f;

    drawTickBox(g, b, 4.0f, (b.getHeight() - tickWidth) * 0.5f,
        tickWidth, tickWidth,
        b.getToggleState(),
        b.isEnabled(),
        isMouseOverButton,
        isButtonDown);

    g.setColour(b.findColour(ToggleButton::textColourId));
    g.setFont(fontSize);

    if (!b.isEnabled())
        g.setOpacity(0.5f);

    const int textX = (int)tickWidth + 5;

    g.drawFittedText(b.getButtonText(),
        textX, 0,
        b.getWidth() - textX - 2, b.getHeight(),
        Justification::centredLeft, 10);
}

/**
* Draw toggle tick box.
*/
void CustomLookAndFeel::drawTickBox(Graphics &g, Component &/*c*/, float x, float y, float width, float height, bool ticked, bool isEnabled, bool isMouseOverButton, bool /*isButtonDown*/)
{
    const float centreX = x + width * 0.85f / 2.0f;
    const float centreY = y + height / 2.0f;
    float boxSize = width;
    float gradientScale = 1.0f;
    Colour c1, c2;

    if (!ticked || !isEnabled)
    {
        boxSize *= 0.7f;
        c1 = isEnabled ? (isMouseOverButton ? Colours::grey.brighter(0.45f) : Colours::grey.brighter(0.35f)) : Colours::grey;
        c2 = Colours::black;
    }
    else
    {
        // if ticked, set colour as glow
        gradientScale = 0.75f;
        c1 = Colours::white;
        c2 = Colours::transparentWhite;
    }

    ColourGradient gradient(c1, centreX, centreY, c2, centreX + boxSize * gradientScale / 2.0f, centreX + boxSize * gradientScale / 2.0f, true);
    gradient.addColour(0.4f, c1);
    g.setGradientFill(gradient);

    g.fillEllipse(centreX - boxSize / 2.0f, centreY - boxSize / 2.0f, boxSize, boxSize);
}

/**
* Draw how combo box is displayed on GUI without selection box.
*/
void CustomLookAndFeel::drawComboBox(Graphics &g, int width, int height, bool /*isButtonDown*/, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &c)
{
    const float cornerSize = 5.0f;
    const float outlineThickness = c.isEnabled() ? (c.hasKeyboardFocus(true) ? 2.4f : 2.2f) : 1.7f;
    const float halfThickness = outlineThickness * 0.5f;
    Colour baseColour(c.isEnabled() ? Colours::white : Colours::grey);

    // set background colour as transparent
    g.fillAll(Colours::transparentWhite);

    // draw outline
    g.setColour(baseColour);
    g.drawRoundedRectangle(halfThickness, halfThickness, width - halfThickness * 2.0f, height - halfThickness * 2.0f, cornerSize, outlineThickness);

    // draw arrow background rectangle on right side
    g.fillRoundedRectangle(static_cast<float>(buttonX), static_cast<float>(buttonY), static_cast<float>(buttonW), static_cast<float>(buttonH), cornerSize);

    // draw arrow
    if (c.isEnabled())
    {
        const float arrowX = 0.1f;
        const float arrowH = 0.4f;

        Path p;
        p.addTriangle(buttonX + buttonW * 0.5f, buttonY + buttonH * (0.35f + arrowH),
            buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.35f,
            buttonX + buttonW * arrowX, buttonY + buttonH * 0.35f);

        g.setColour(Colours::darkgrey);
        g.fillPath(p);
    }
}

/**
* Get combo box font. Needed to change font properties.
*/
Font CustomLookAndFeel::getComboBoxFont(ComboBox& c)
{
    Font font(jmin(20.0f, c.getHeight() * 0.85f));
    return font;
}

/**
* Position combo box text. Needed to change label properties.
*/
void CustomLookAndFeel::positionComboBoxText(ComboBox& c, Label& l)
{
    l.setColour(Label::ColourIds::textColourId, Colours::white);
    l.setBounds(1, 1, c.getWidth() + 3 - c.getHeight(), c.getHeight() - 2);

    l.setFont(getComboBoxFont(c));
}
