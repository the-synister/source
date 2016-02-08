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
    // set custom default font typeface
    this->setDefaultSansSerifTypefaceName("Bauhaus 93");
}

CustomLookAndFeel::~CustomLookAndFeel()
{
    // release ressources
}
//==============================================================================
void CustomLookAndFeel::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &s)
{
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const bool isMouseOver = s.isMouseOverOrDragging() && s.isEnabled();

    // custom start and end angle for knob and saturn
    rotaryStartAngle = -float_Pi + degreesToRadians(45.0f);
    rotaryEndAngle = float_Pi - degreesToRadians(45.0f);

    // current slider position angle in radians in range [rotaryStartAngle, rotaryEndAngle]
    const float currAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    const float knobMargin = 0.7f; // relative knobBorder to max radius

    const float radiusSource2 = jmin(width / 2.0f, height / 2.0f);
    const float radiusKnob = radiusSource2 * knobMargin;
    const float radiusSource1 = radiusKnob + (radiusSource2 - radiusKnob) / 2.0f;

    Path knob;
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

        Colour baseColour(s.findColour(Slider::rotarySliderFillColourId));
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

//TODO: vorzeitige version später statt sourceValue und unipolar, den ganzen param rein und dann check auf unipolar / bipolar und evtl.Colour
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

    // TODO: unipolar/bipolar aus param oder source slider entnehmen
    //       zugriff auf modSourceSlider, dann werte umrechnen und addieren usw.
    // calculate positions for saturns
    if (unipolar)
    {
        afterModVal1 = jmax(min, jmin(val + sourceValue, max));
        modPosition1 = pow((afterModVal1 - min) / (max - min), skew);

        modStartAngle = currAngle;
        modEndAngle = rotaryStartAngle + modPosition1 * (rotaryEndAngle - rotaryStartAngle);
    }
    else
    {
        afterModVal1 = jmax(min, jmin(val + sourceValue /*/ 2.0f*/, max));
        afterModVal2 = jmax(min, jmin(val - sourceValue /*/ 2.0f*/, max));
        modPosition1 = pow((afterModVal1 - min) / (max - min), skew);
        modPosition2 = pow((afterModVal2 - min) / (max - min), skew);

        modStartAngle = rotaryStartAngle + modPosition1 * (rotaryEndAngle - rotaryStartAngle);
        modEndAngle = rotaryStartAngle + modPosition2 * (rotaryEndAngle - rotaryStartAngle);
    }

    // draw saturns
    Path saturn;
    g.setColour(s.isEnabled() ? Colours::yellow : Colours::lightgrey); // TODO: mod specific colour verwenden
    saturn.addPieSegment(centreX - radius, centreY - radius, radius * 2.0f, radius * 2.0f, modStartAngle, modEndAngle, innerCircleSize * 1.03f);
    g.fillPath(saturn);
}

void CustomLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s)
{
    // use bar slider to draw vol and pan instead
    if (style == Slider::LinearBar)
    {
        const bool isMouseOver = s.isMouseOverOrDragging() && s.isEnabled();
        const float posX = static_cast<float>(x);
        const float posY = static_cast<float>(y);
        const float boxWidth = static_cast<float>(width);
        const float boxHeight = static_cast<float>(height);
        float offset1, offset2;

        Path path;
        Colour baseColour(s.findColour(Slider::trackColourId));
        g.setColour(s.isEnabled() ? (isMouseOver ? baseColour.brighter(0.1f) : baseColour) : baseColour.withAlpha(0.5f));

        if (s.getMinimum() == -s.getMaximum())
        {
            // TODO: wenn überhaupt am ende noch relevant ist, ansonsten löschen
            const float middleHeight = boxHeight * 0.65f;
            // create left and right part of pan
            path.addQuadrilateral(posX, posY,
                                  posX, posY + boxHeight,
                                  posX + boxWidth / 2.0f, posY + boxHeight,
                                  posX + boxWidth / 2.0f, posY + middleHeight);
            path.addQuadrilateral(posX + boxWidth, posY,
                                  posX + boxWidth, posY + boxHeight,
                                  posX + boxWidth / 2.0f, posY + boxHeight,
                                  posX + boxWidth / 2.0f, posY + middleHeight);
            g.fillPath(path);

            // create and fill pan pointer
            path.clear();

            g.setColour(s.findColour(Slider::thumbColourId));
            const float thumbWidthHalf = boxWidth / 15.0f;

            // create left and right part of pan thumb
            offset1 = -abs(sliderPos - thumbWidthHalf - posX - boxWidth / 2.0f) * middleHeight / (boxWidth / 2.0f) + middleHeight;
            offset2 = -abs(sliderPos - posX - boxWidth / 2.0f) * middleHeight / (boxWidth / 2.0f) + middleHeight;
            path.addQuadrilateral(sliderPos - thumbWidthHalf, posY + boxHeight,
                                  sliderPos - thumbWidthHalf, posY + offset1 - 1.f,
                                  sliderPos, posY + offset2 - 1.f,
                                  sliderPos, posY + boxHeight);

            offset1 = -abs(sliderPos + thumbWidthHalf - posX - boxWidth / 2.0f) * middleHeight / (boxWidth / 2.0f) + middleHeight;
            offset2 = -abs(sliderPos - posX - boxWidth / 2.0f) * middleHeight / (boxWidth / 2.0f) + middleHeight;
            path.addQuadrilateral(sliderPos + thumbWidthHalf, posY + boxHeight,
                                  sliderPos + thumbWidthHalf, posY + offset1 - 1.f,
                                  sliderPos, posY + offset2 - 1.f,
                                  sliderPos, posY + boxHeight);
            g.fillPath(path);
        }
        else
        {
            // fill vol triangle
            offset1 = boxHeight - boxHeight * (sliderPos / (posX + boxWidth));
            path.addTriangle(posX, posY + boxHeight, sliderPos, posY + boxHeight, sliderPos, posY + offset1);
            g.fillPath(path);

            // draw outline
            path.clear();
            path.addTriangle(posX + boxWidth, posY, posX, posY + boxHeight, posX + boxWidth, posY + boxHeight);
            g.strokePath(path, PathStrokeType::PathStrokeType(isMouseOver ? 1.4f : 0.7f));
        }
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

    // set bounds and  draw slider background
    if (s.isHorizontal())
    {
        const float iy = y + height * 0.5f - sliderRadius * 0.5f;
        const float ih = sliderRadius;

        indent.addRoundedRectangle(x - sliderRadius * 0.5f, iy,
            width + sliderRadius, ih,
            sliderRadius * 0.5f);
    }
    else
    {
        const float ix = x + width * 0.5f - sliderRadius * 0.5f;
        const float iw = sliderRadius;

        indent.addRoundedRectangle(ix, y - sliderRadius * 0.5f,
            iw, height + sliderRadius,
            sliderRadius * 0.5f);
    }

    g.fillPath(indent);
}

void CustomLookAndFeel::drawLinearSliderThumb(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s)
{
    const float sliderRadius = (float)(jmin(10, width / 4, height / 4) - 2);
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

// TODO: wenn nicht benötigt, dann weg
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
        else if (textBoxPos == Slider::TextBoxBelow)     layout.textBoxBounds.setY(localBounds.getHeight() - textBoxHeight - 5);
        else /* left or right -> centre vertically */    layout.textBoxBounds.setY((localBounds.getHeight() - textBoxHeight) / 2);
    }

    // 3. set the slider bounds
    layout.sliderBounds = localBounds;

    if (s.isBar())
    {
        layout.sliderBounds.reduce(1, 1);   // bar border

        // adapt bounds to avoid flickering with mouseOverKnob
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

//==============================================================================

void CustomLookAndFeel::drawButtonBackground(Graphics& g, Button& b, const Colour& c, bool isMouseOverButton, bool isButtonDown)
{
    const int width = b.getWidth();
    const int height = b.getHeight();
    const float cornerSize = 7.0f;
    const float outlineThickness = 2.2f;
    const float halfThickness = outlineThickness * 0.5f;

    // background colour
    g.setColour(b.isEnabled() ? (isMouseOverButton ? c.brighter(0.1f) : c) : c.withAlpha(0.5f));
    g.fillRoundedRectangle(halfThickness, halfThickness, width - halfThickness * 2.0f, height - halfThickness * 2.0f, cornerSize);

    // draw outline
    g.setColour(b.isEnabled() ? b.findColour(isButtonDown ? TextButton::textColourOnId : TextButton::textColourOffId) : c.withAlpha(0.5f));
    g.drawRoundedRectangle(halfThickness, halfThickness, width - halfThickness * 2.0f, height - halfThickness * 2.0f, cornerSize, outlineThickness);
}

void CustomLookAndFeel::drawToggleButton(Graphics &g, ToggleButton &b, bool isMouseOverButton, bool isButtonDown)
{
    float fontSize = jmin(15.0f, b.getHeight() * 0.75f);
    const float tickWidth = fontSize * 1.1f;

    // draw tickbox
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

    // draw text
    const int textX = (int)tickWidth + 5;
    g.drawFittedText(b.getButtonText(),
        textX, 0,
        b.getWidth() - textX - 2, b.getHeight(),
        Justification::centredLeft, 10);
}

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
        c1 = isEnabled ? (isMouseOverButton ? Colours::darkgrey.brighter(0.4f) : Colours::darkgrey.brighter(0.2f)) : Colours::darkgrey;
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

Font CustomLookAndFeel::getTextButtonFont(TextButton& /*t*/, int buttonHeight)
{
    return Font(jmin(20.0f, buttonHeight * 0.85f));
}

//==============================================================================

void CustomLookAndFeel::drawComboBox(Graphics &g, int width, int height, bool /*isButtonDown*/, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &c)
{
    const float outlineThickness = c.isEnabled() ? (c.isMouseOver()? 2.4f : 2.1f) : 1.7f;
    const float halfThickness = outlineThickness * 0.5f;

    // draw and fill white background rect
    Colour baseColour(c.findColour(ComboBox::ColourIds::backgroundColourId));
    g.setColour(c.isEnabled() ? baseColour : baseColour.withAlpha(0.5f));
    Rectangle<float> rect = { halfThickness, halfThickness, width - halfThickness * 2.0f, height - halfThickness * 2.0f };
    g.fillRect(rect);

    // draw arrow background rectangle on right side
    g.drawRect(0.f, 0.f, width+ 0.f, height+ 0.f, outlineThickness);

    // draw arrow
    if (c.isEnabled())
    {
        const float arrowOffset = 0.2f;

        Path p;
        p.addTriangle(buttonX + buttonW * (1.0f - arrowOffset), buttonY + buttonH * 0.5f,
                      buttonX + buttonW * arrowOffset, buttonY + buttonH * arrowOffset,
                      buttonX + buttonW * arrowOffset, buttonY + buttonH * (1.0f - arrowOffset));

        g.setColour(c.findColour(ComboBox::ColourIds::arrowColourId));
        g.fillPath(p);
    }
}

Font CustomLookAndFeel::getComboBoxFont(ComboBox& c)
{
    Font font(jmin(20.0f, c.getHeight() * 0.85f));
    return font;
}

void CustomLookAndFeel::positionComboBoxText(ComboBox& c, Label& l)
{
    l.setBounds(1, 1, c.getWidth() + 3 - c.getHeight(), c.getHeight() - 2);

    l.setFont(getComboBoxFont(c));
}

//==============================================================================

// TODO: alle popup sachen je nach dem ob benötigt werden später, ansonsten löschen
Font CustomLookAndFeel::getPopupMenuFont()
{
    return LookAndFeel_V2::getPopupMenuFont();
}

void CustomLookAndFeel::drawPopupMenuBackground(Graphics &g, int width, int height)
{
    LookAndFeel_V2::drawPopupMenuBackground(g, width, height);
}

void CustomLookAndFeel::drawPopupMenuItem(Graphics &g, const Rectangle< int > &area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
    const String &text, const String &shortcutKeyText, const Drawable *icon, const Colour *textColour)
{
    LookAndFeel_V2::drawPopupMenuItem(g, area, isSeparator, isActive, isHighlighted, isTicked, hasSubMenu, text, shortcutKeyText, icon, textColour);
}

void CustomLookAndFeel::drawBubble(Graphics& g, BubbleComponent& comp, const Point<float>& tip, const Rectangle<float>& body)
{
    Path p;
    p.addBubble(body.reduced(0.5f), body.getUnion(Rectangle<float>(tip.x, tip.y, 1.0f, 1.0f)),
        tip, 5.0f, jmin(15.0f, body.getWidth() * 0.2f, body.getHeight() * 0.2f));

    g.setColour(Colours::white);
    g.fillPath(p);

    g.setColour(comp.findColour(BubbleComponent::outlineColourId));
    g.strokePath(p, PathStrokeType(2.5f));
}

Font CustomLookAndFeel::getSliderPopupFont(Slider &/*s*/)
{
    return Font(15.0f, Font::plain);
}

int CustomLookAndFeel::getSliderPopupPlacement(Slider &/*s*/)
{
    return BubbleComponent::above
        | BubbleComponent::below
        | BubbleComponent::left
        | BubbleComponent::right;
}

//==============================================================================

void CustomLookAndFeel::drawPropertyPanelSectionHeader(Graphics& g, const String& /*name*/, bool isOpen, int width, int height)
{
    // background colour
    ColourGradient gradient(Colour (77, 77, 79), 0.0f, 0.0f, Colour (45, 43, 44), 0.0f, static_cast<float>(height), false);
    g.setGradientFill(gradient);
    g.fillRect(0, 0, width, height);

    // draw arrow
    const float buttonSize = height * 0.65f;
    const float buttonIndent = (height - buttonSize) * 0.5f;
    const float x = buttonIndent * 2.0f;
    const float y = (height - buttonSize) * 0.5f;
    const float arrowThickness = buttonIndent * 2.0f;

    Path arrow;
    if (isOpen)
    {
        arrow.addQuadrilateral(x, y,
                               x + buttonSize * 0.5f, y + buttonSize - arrowThickness,
                               x + buttonSize, y,
                               x + buttonSize * 0.5f, y + buttonSize);
    }
    else
    {
        arrow.addQuadrilateral(x, y,
                               x + buttonSize - arrowThickness, y + buttonSize * 0.5f,
                               x, y + buttonSize,
                               x + buttonSize, y + buttonSize * 0.5f);
    }

    g.setColour(Colours::grey);
    g.fillPath(arrow);

    // draw text is done in FoldablePanel::SectionComponent::paint() due to text colour
}
