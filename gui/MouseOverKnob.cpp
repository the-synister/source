/*
  ==============================================================================

    MouseOverKnob.cpp
    Created: 4 Nov 2015 9:54:43pm
    Author:  Nhat

  ==============================================================================
*/

#include "MouseOverKnob.h"

MouseOverKnob::MouseOverKnob(const String& name, SynthParams &p, Label *label)
	: Slider(name), params(p), knobName(label->getText()){
	knobLabel = label;
	label->addListener(this);
	label->setFont(Font(15.00f, Font::plain));
	label->setJustificationType(Justification::centred);
	label->setEditable(false, true, false); // set label as editable on double click
	label->setColour(TextEditor::textColourId, Colours::black);
	label->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
}

MouseOverKnob::~MouseOverKnob() {
	knobLabel = nullptr;
}

void MouseOverKnob::paint(Graphics& g) {
	
	
	if (this->isMouseOverOrDragging()) 
	{
		knobLabel->setText((String)static_cast<float>(this->getValue()) + String(" ") + params.freq.unit(), NotificationType::sendNotification);
		//freq->setTextBoxStyle(MouseOverKnob::TextBoxAbove, false, 64, 20);
		//label2->setVisible(false);
		drawLabelText = true;
	}
	else
	{
		if (drawLabelText) {
			knobLabel->setText(knobName, NotificationType::sendNotification);
			drawLabelText = false;
		}
		//freq->setTextBoxStyle(MouseOverKnob::NoTextBox, false, 64, 20);
		//label2->setVisible(true);
	}
	__super::paint(g);
}

void MouseOverKnob::labelTextChanged(Label* labelTextChanged) {

	if (atof((labelTextChanged->getText().toUTF8())) >= this->getMinimum() && atof((labelTextChanged->getText().toUTF8())) <= this->getMaximum()) {
		this->setValue(atof((labelTextChanged->getText().toUTF8())));
	}
	else {
		knobLabel->setText(knobName, NotificationType::sendNotification);
	}
	drawLabelText = true;
}
