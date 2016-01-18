/*
  ==============================================================================

    MouseOverKnob.h
    Created: 4 Nov 2015 9:54:43pm
    Author:  Nhat

  ==============================================================================
*/

#ifndef MOUSEOVERKNOB_H_INCLUDED
#define MOUSEOVERKNOB_H_INCLUDED

#include "JuceHeader.h"
#include "CustomLookAndFeel.h"
#include "../audio/inc/SynthParams.h"

class MouseOverKnob : public Slider,
                      public ComponentListener
{
public:
    //==============================================================================
    MouseOverKnob(const String& name);
    ~MouseOverKnob();
    //==============================================================================

    void initTextBox();
    void setModSource1(Param *p);

    Param *getModSource1();

    virtual void setName(const String& newName) override;

    void paint(Graphics &g) override;
    void resized() override;
    void setBounds(int x, int y, int width, int height);
    void componentMovedOrResized(Component &component, bool wasMoved, bool wasResized) override;

    void mouseEnter(const MouseEvent &e) override;
    void mouseExit(const MouseEvent &e) override;
    void mouseDoubleClick(const MouseEvent &e) override;
    void mouseDrag(const MouseEvent &e) override;

private:
    ScopedPointer<Label> knobLabel;
    int knobWidth = 64;
    int knobHeight = 64;
    
    Param *modSource1;
};

#endif  // MOUSEOVERKNOB_H_INCLUDED
