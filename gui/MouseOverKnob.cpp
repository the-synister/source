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
        setTextBoxStyle(MouseOverKnob::NoTextBox, false, textBoxWidth, textBoxHeight);
    } else {
        setTextBoxStyle(MouseOverKnob::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    }
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
        setTextBoxStyle(MouseOverKnob::TextBoxBelow, false, textBoxWidth, textBoxHeight);
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
        setTextBoxStyle(MouseOverKnob::NoTextBox, true, textBoxWidth, textBoxHeight);
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
        this->setSize(knobWidth, knobHeight - textBoxHeight);
    }
    else
    {
        this->setSize(knobWidth, knobHeight);
    }

    Slider::resized();
}

void MouseOverKnob::setTextBoxStyle(juce::Slider::TextEntryBoxPosition pos, bool readOnly, int boxWidth, int boxHeight)
{
    textBoxWidth = boxWidth;
    textBoxHeight = boxHeight;

    Slider::setTextBoxStyle(pos, readOnly, textBoxWidth, textBoxHeight);
}

void MouseOverKnob::setBounds(int x, int y, int width, int height)
{
    knobWidth = width;
    knobHeight = height;
    Slider::setBounds(x, y, knobWidth, knobHeight);
}

/**
* Always set label below slider.
*/
void MouseOverKnob::componentMovedOrResized(Component &component, bool wasMoved, bool wasResized)
{
    knobLabel->setSize(200, textBoxHeight);
    knobLabel->setTopLeftPosition(this->getX() + (knobWidth-200)/2, this->getY() + this->getHeight());

    ComponentListener::componentMovedOrResized(component, wasMoved, wasResized);
}
