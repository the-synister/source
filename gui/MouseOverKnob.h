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
                      public ComponentListener
{
public:
    //==============================================================================
    MouseOverKnob(const String& name);
    ~MouseOverKnob();
    //==============================================================================

    void initTextBox();

    void resized();
    void componentMovedOrResized(Component &component, bool wasMoved, bool wasResized);

    void mouseEnter(const MouseEvent &e);
    void mouseExit(const MouseEvent &e);
    void mouseDoubleClick(const MouseEvent &e);
    void mouseDrag(const MouseEvent &e);

private:
    ScopedPointer<Label> knobLabel;
    int width = 64, height = 64;
};

#endif  // MOUSEOVERKNOB_H_INCLUDED
