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
#include "SynthParams.h"

class MouseOverKnob : public Slider,
                      public ComponentListener
{
public:
    //==============================================================================
    MouseOverKnob(const String& name);
    ~MouseOverKnob();
    //==============================================================================

    void initTextBox();

    void setModSource(Param *p, int sourceNumber);
    std::array<Param*, 2> getModSources();

    virtual void setName(const String& newName) override;

    void resized() override;
    void setBounds(int x, int y, int width, int height);
    void enablementChanged() override;
    void componentMovedOrResized(Component &component, bool wasMoved, bool wasResized) override;

    void mouseEnter(const MouseEvent &e) override;
    void mouseExit(const MouseEvent &e) override;
    void mouseDown(const MouseEvent &e) override;
    void mouseDoubleClick(const MouseEvent &e) override;
    void mouseDrag(const MouseEvent &e) override;

private:
    ScopedPointer<Label> knobLabel;

    int knobWidth = 64;
    int knobHeight = 64;

    std::array<Param*, 2> modSources;
};

#endif  // MOUSEOVERKNOB_H_INCLUDED
