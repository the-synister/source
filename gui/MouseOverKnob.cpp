/*
  ==============================================================================

    MouseOverKnob.cpp
    Created: 4 Nov 2015 9:54:43pm
    Author:  Nhat

  ==============================================================================
*/

#include "MouseOverKnob.h"

//==============================================================================
// contructer & destructer
MouseOverKnob::MouseOverKnob(const String& name): Slider(name)
{
    addAndMakeVisible(knobLabel = new Label("new label", TRANS(name)));
    knobLabel->setFont(Font(15.00f, Font::plain));
    knobLabel->setJustificationType(Justification::centred);
    knobLabel->setEditable(false, false, false);
    knobLabel->setColour(TextEditor::textColourId, Colours::black);
    knobLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    knobLabel->attachToComponent(this, false);
    knobLabel->addComponentListener(this);

    initTextBox();
}

MouseOverKnob::~MouseOverKnob()
{
    knobLabel = nullptr;
}
//==============================================================================

void MouseOverKnob::initTextBox()
{
    if (knobLabel->isVisible()) {
        setTextBoxStyle(MouseOverKnob::NoTextBox, false, this->getTextBoxWidth(), this->getTextBoxHeight());
    } else {
        setTextBoxStyle(MouseOverKnob::TextBoxBelow, false, this->getTextBoxWidth(), this->getTextBoxHeight());
    }
}

void MouseOverKnob::setModSource1(Param *p)
{
    modSource1 = p;
}

Param* MouseOverKnob::getModSource1()
{
    return modSource1;
}


void MouseOverKnob::setName  (const String& newName) {
    knobLabel->setText(newName, NotificationType::dontSendNotification);
}


/**
* If mouse enters slider then replace label with textbox.
*/
void MouseOverKnob::mouseEnter(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        knobLabel->setVisible(false);
        setTextBoxStyle(MouseOverKnob::TextBoxBelow, false, this->getTextBoxWidth(), this->getTextBoxHeight());
    }
}

/**
* If mouse exits slider then replace textbox with label.
*/
void MouseOverKnob::mouseExit(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        knobLabel->setVisible(true);
        setTextBoxStyle(MouseOverKnob::NoTextBox, true, this->getTextBoxWidth(), this->getTextBoxHeight());
    }
}

/**
* If slider is double clicked then values can be edited manually.
*/
void MouseOverKnob::mouseDoubleClick(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        showTextBox();
    }
}

/**
* Only drag on slider, not on label.
*/
void MouseOverKnob::mouseDrag(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        Slider::mouseDrag(e);
    }
}

void MouseOverKnob::paint(Graphics &g) 
{
    //int sizeSub = 10;
    //float radius = static_cast<float>(jmin(knobWidth, knobHeight));

    //ColourGradient gradient = ColourGradient(Colours::red, knobWidth / 2, knobHeight / 2, Colours::white, knobWidth / 2 + radius / 2, knobHeight / 2 + radius / 2, true);
    //g.setGradientFill(gradient);

    //g.fillEllipse(knobWidth / 2 - radius / 2, knobHeight / 2 - radius / 2, radius, radius);

    Slider::paint(g);

    //const float radius = jmin(width / 2, height / 2) - 2.0f;
    //const float centreX = x + width * 0.5f;
    //const float centreY = y + height * 0.5f;
    //const float rx = centreX - radius;
    //const float ry = centreY - radius;
    //const float rw = radius * 2.0f;
    //const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    //const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

    //if (radius > 12.0f)
    //{
    //    if (slider.isEnabled())
    //        g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 1.0f : 0.7f));
    //    else
    //        g.setColour(Colour(0x80808080));

    //    const float thickness = 0.7f;

    //    {
    //        Path filledArc;
    //        filledArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
    //        g.fillPath(filledArc);
    //    }

    //    {
    //        const float innerRadius = radius * 0.2f;
    //        Path p;
    //        p.addTriangle(-innerRadius, 0.0f,
    //            0.0f, -radius * thickness * 1.1f,
    //            innerRadius, 0.0f);

    //        p.addEllipse(-innerRadius, -innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);

    //        g.fillPath(p, AffineTransform::rotation(angle).translated(centreX, centreY));
    //    }

    //    if (slider.isEnabled())
    //        g.setColour(slider.findColour(Slider::rotarySliderOutlineColourId));
    //    else
    //        g.setColour(Colour(0x80808080));

    //    Path outlineArc;
    //    outlineArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
    //    outlineArc.closeSubPath();

    //    g.strokePath(outlineArc, PathStrokeType(slider.isEnabled() ? (isMouseOver ? 2.0f : 1.2f) : 0.3f));
    //}
    //else
    //{
    //    if (slider.isEnabled())
    //        g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 1.0f : 0.7f));
    //    else
    //        g.setColour(Colour(0x80808080));

    //    Path p;
    //    p.addEllipse(-0.4f * rw, -0.4f * rw, rw * 0.8f, rw * 0.8f);
    //    PathStrokeType(rw * 0.1f).createStrokedPath(p, p);

    //    p.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, -radius), rw * 0.2f);

    //    g.fillPath(p, AffineTransform::rotation(angle).translated(centreX, centreY));
    //}
}

/**
* Overwrite resize(), so that slider size is independent of textbox visibility.
*/
void MouseOverKnob::resized()
{
    if (!this->isMouseOver())
    {
        this->setSize(knobWidth, knobHeight - this->getTextBoxHeight());
    }
    else
    {
        this->setSize(knobWidth, knobHeight);
    }

    Slider::resized();
}

/*
* Needed to save bounds of slider.
*/
void MouseOverKnob::setBounds(int x, int y, int width, int height)
{
    knobWidth = width;
    knobHeight = height;
    Slider::setBounds(x, y, width, height);
}

/**
* Always set label below slider.
*/
void MouseOverKnob::componentMovedOrResized(Component &component, bool wasMoved, bool wasResized)
{
    knobLabel->setSize(knobWidth, this->getTextBoxHeight());
    knobLabel->setTopLeftPosition(this->getX(), this->getY() + this->getHeight());

    ComponentListener::componentMovedOrResized(component, wasMoved, wasResized);
}