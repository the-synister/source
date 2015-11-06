/*
  ==============================================================================

    MouseOverKnob.h
    Created: 4 Nov 2015 9:54:43pm
    Author:  Nhat

  ==============================================================================
*/

#ifndef MOUSEOVERKNOB_H_INCLUDED
#define MOUSEOVERKNOB_H_INCLUDED

//[Headers]
#include "JuceHeader.h"
#include "SynthParams.h"
//[/Headers]

class MouseOverKnob : public Slider, 
					  public LabelListener
{
public:
	//==============================================================================
	MouseOverKnob(const String& knobName, SynthParams &p, Label *label);
	~MouseOverKnob();
	//==============================================================================

	void paint(Graphics& g);
	void labelTextChanged(Label* labelTextChanged);
	void mouseDoubleClick(const MouseEvent &e);

private:
	SynthParams &params;
	Label* knobLabel;
	String knobName;
	bool drawLabelText = false;
};

#endif  // MOUSEOVERKNOB_H_INCLUDED
