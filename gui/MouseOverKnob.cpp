/*
  ==============================================================================

    MouseOverKnob.cpp
    Created: 4 Nov 2015 9:54:43pm
    Author:  Nhat

  ==============================================================================
*/

#include "MouseOverKnob.h"

//==============================================================================
MouseOverKnob::MouseOverKnob(const String& name, SynthParams &p, Label *label)
	: Slider(name), params(p), knobName(label->getText()){

	knobLabel = label;

	// add listener to label
	label->addListener(this);
	label->addMouseListener(this, true);

	// default is NoTextBox
	this->setTextBoxStyle(MouseOverKnob::NoTextBox, false, 64, 20);
}

MouseOverKnob::~MouseOverKnob() {}
//==============================================================================

void MouseOverKnob::paint(Graphics& g) {

	// only if mouse is over or dragging the slider then show current value
	if (this->isMouseOverOrDragging()) 
	{
		if (!knobLabel->isBeingEdited()) {
			knobLabel->setText((String)static_cast<float>(this->getValue()) + String(" ") + params.freq.unit(), NotificationType::sendNotification);
		}
	}
	else
	{
		if (drawLabelText) {
			knobLabel->setText(knobName, NotificationType::sendNotification);
			drawLabelText = false;
		}
	}

	// if not superClass paint() is called then slider image is not drawn
	__super::paint(g);
}

/**
* If slider is clicked then values can be edited manually
*/
void MouseOverKnob::mouseDoubleClick(const MouseEvent &e) {

	if (e.eventComponent == this) {
		knobLabel->setText((String)static_cast<float>(this->getValue()) + String(" ") + params.freq.unit(), NotificationType::sendNotification);
		knobLabel->showEditor();
	}
}

/**
* After editing the label, the values are checked.
* If they are in range then value is set else do nothing.
*/
void MouseOverKnob::labelTextChanged(Label* labelTextChanged) {

	if (atof((labelTextChanged->getText().toUTF8())) >= this->getMinimum() && atof((labelTextChanged->getText().toUTF8())) <= this->getMaximum()) {
		this->setValue(atof((labelTextChanged->getText().toUTF8())));
	}
	else {
		knobLabel->setText(knobName, NotificationType::sendNotification);
	}
	drawLabelText = true;
}
