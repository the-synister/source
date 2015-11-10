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
//[/Headers]

class MouseOverKnob : public Slider, 
					  public LabelListener
{
public:
	//==============================================================================
	MouseOverKnob(const String& name, String labelName);
	~MouseOverKnob();
	//==============================================================================

	void labelTextChanged(Label* labelTextChanged);
	void mouseEnter(const MouseEvent &e);
	void mouseExit(const MouseEvent &e);
	void mouseDoubleClick(const MouseEvent &e);

private:
	ScopedPointer<Label> knobLabel;
	String knobName;
};

#endif  // MOUSEOVERKNOB_H_INCLUDED
