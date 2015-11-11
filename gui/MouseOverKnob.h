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
                      public ComponentListener,
                      public LabelListener
{
public:
    //==============================================================================
    MouseOverKnob(const String& name, String labelText, int width = 64, int height = 64);
    ~MouseOverKnob();
    //==============================================================================
    void resized();
    void componentMovedOrResized(Component &component, bool wasMoved, bool wasResized);

    void mouseEnter(const MouseEvent &e);
    void mouseExit(const MouseEvent &e);
    void mouseDoubleClick(const MouseEvent &e);
    void mouseDrag(const MouseEvent &e);

    void editorShown(Label* labelTextChanged);
    void labelTextChanged(Label* labelTextChanged);

private:
    ScopedPointer<Label> knobLabel;
    String labelText;
    int width = 64, height = 64;
};

#endif  // MOUSEOVERKNOB_H_INCLUDED
