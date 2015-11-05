/*
  ==============================================================================

    MouseOverKnob.h
    Created: 4 Nov 2015 9:54:43pm
    Author:  Nhat

  ==============================================================================
*/

#ifndef MOUSEOVERKNOB_H_INCLUDED
#define MOUSEOVERKNOB_H_INCLUDED

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "SynthParams.h"
//[/Headers]

class MouseOverKnob : public Slider, public LabelListener
{
public:
	//==============================================================================
	MouseOverKnob(const String& knobName, SynthParams &p, Label *label);
	~MouseOverKnob();
	//==============================================================================
	//[UserMethods]     -- You can add your own custom methods in this section.
	void paint(Graphics& g);

	void labelTextChanged(Label* labelTextChanged);
	//[/UserMethods]

private:
	//[UserVariables]   -- You can add your own custom variables in this section.
	SynthParams &params;
	Label* knobLabel;
	String knobName;
	bool drawLabelText = false;
	//[/UserVariables]
};

#endif  // MOUSEOVERKNOB_H_INCLUDED
