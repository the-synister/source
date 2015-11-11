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
MouseOverKnob::MouseOverKnob(const String& name, String labelText, int width, int height): Slider(name)
{
    this->setTextBoxStyle(MouseOverKnob::NoTextBox, false, width, 20);
    this->width = width;
    this->height = height;

	addAndMakeVisible(knobLabel = new Label("new label", TRANS(labelText)));
	knobLabel->setFont(Font(15.00f, Font::plain));
	knobLabel->setJustificationType(Justification::centred);
	knobLabel->setEditable(false, false, false);
	knobLabel->setColour(TextEditor::textColourId, Colours::black);
	knobLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	knobLabel->attachToComponent(this, false);
    knobLabel->addComponentListener(this);
}

MouseOverKnob::~MouseOverKnob() {
    knobLabel = nullptr;
}
//==============================================================================

/**
* If mouse enters slider then replace label with textbox.
*/
void MouseOverKnob::mouseEnter(const MouseEvent &e)
{
	if (e.eventComponent == this)
	{
		knobLabel->setVisible(false);
        this->setTextBoxStyle(MouseOverKnob::TextBoxBelow, false, width, 20);
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
		this->setTextBoxStyle(MouseOverKnob::NoTextBox, true, width, 20);
	}
}

/**
* If slider is double clicked then values can be edited manually.
*/
void MouseOverKnob::mouseDoubleClick(const MouseEvent &e) 
{
	if (e.eventComponent == this)
	{
		this->showTextBox();
	}
}

/**
* Only drag on slider, not on label.
*/
void MouseOverKnob::mouseDrag(const MouseEvent &e) {
    
    if (e.eventComponent == this) {
        Slider::mouseDrag(e);
    }
}

/**
* Overwrite resize(), so that slider size is independent of textbox visibility.
*/
void MouseOverKnob::resized()
{   
    if (!this->isMouseOver()) {
        this->setSize(width, height - 20);
    }
    else {
        this->setSize(width, height);
    }

    Slider::resized();
}

/**
* Always set label below slider.
*/
void MouseOverKnob::componentMovedOrResized(Component &component, bool wasMoved, bool wasResized) {
    ignoreUnused(component);
    ignoreUnused(wasMoved);
    ignoreUnused(wasResized);

    knobLabel->setSize(width, 20);
    knobLabel->setTopLeftPosition(this->getX(), this->getY() + this->getHeight());

    ComponentListener::componentMovedOrResized(component, wasMoved, wasResized);
}