/*
  ==============================================================================

    MouseOverKnob.cpp
    Created: 4 Nov 2015 9:54:43pm
    Author:  Nhat

  ==============================================================================
*/

#include "MouseOverKnob.h"

//==============================================================================
MouseOverKnob::MouseOverKnob(const String& name, String labelName): Slider(name)
{
	knobName = labelName;

	addAndMakeVisible(knobLabel = new Label("new label", TRANS(knobName)));
	knobLabel->setFont(Font(15.00f, Font::plain));
	knobLabel->setJustificationType(Justification::centred);
	knobLabel->setEditable(false, false, false);
	knobLabel->setColour(TextEditor::textColourId, Colours::black);
	knobLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
	knobLabel->attachToComponent(this, false);

	knobLabel->addListener(this);
	knobLabel->addMouseListener(this, false);

	// default is NoTextBox
	this->setTextBoxStyle(MouseOverKnob::NoTextBox, false, 64, 20);
}

MouseOverKnob::~MouseOverKnob() {}
//==============================================================================

/**
*
*/
void MouseOverKnob::mouseEnter(const MouseEvent &e)
{
	if (e.eventComponent == this || e.eventComponent == knobLabel)
	{
		knobLabel->setVisible(false);
        this->setTextBoxStyle(MouseOverKnob::TextBoxBelow, false, 64, 20);
	}
}

/**
*
*/
void MouseOverKnob::mouseExit(const MouseEvent &e)
{
	if (e.eventComponent == this || e.eventComponent == knobLabel)
	{
		knobLabel->setVisible(true);
		this->setTextBoxStyle(MouseOverKnob::NoTextBox, false, 64, 20);
	}
}

/**
* If slider is clicked then values can be edited manually
*/
void MouseOverKnob::mouseDoubleClick(const MouseEvent &e) 
{
	if (e.eventComponent == this || e.eventComponent == knobLabel)
	{
		this->showTextBox();
	}
}

/**
* After editing the label, the values are checked.
* If they are in range then value is set else do nothing.
*/
void MouseOverKnob::labelTextChanged(Label* labelTextChanged) 
{
}