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
MouseOverKnob::MouseOverKnob(const String& name)
    : Slider(name)
    , modSources({nullptr})
{
    addAndMakeVisible(knobLabel = new Label("new label", TRANS(name)));
    knobLabel->setFont(Font(18.00f, Font::plain));
    knobLabel->setJustificationType(Justification::centred);
    knobLabel->setEditable(false, false, false);
    knobLabel->setColour(Label::ColourIds::textColourId, Colours::white);

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

void MouseOverKnob::setModSource(Param *p, int sourceNumber)
{
    modSources[sourceNumber - 1] = p;
}

std::array<Param*, 2> MouseOverKnob::getModSources()
{
    return modSources;
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

void MouseOverKnob::enablementChanged()
{
    Slider::enablementChanged();

    if (this->isEnabled())
    {
        knobLabel->setColour(Label::ColourIds::textColourId, Colours::white);
    }
    else
    {
        knobLabel->setColour(Label::ColourIds::textColourId, Colours::white.withAlpha(0.5f));
    }
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
