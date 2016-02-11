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

    /**
    *
    @param conversion if source unit is different from destination unit used for filter
           where source is in octave and destination is in freq
    */
    void setModSource(ParamStepped<eModSource> *source, Param *amount, bool convert, int sourceNumber);
    std::array<ParamStepped<eModSource>*, 2> getModSources();
    std::array<Param*, 2> getModAmounts();
    bool isModSourceValueConverted();

    void setDefaultValue(float val);

    virtual void setName(const String& newName) override;
    void setBounds(int x, int y, int width, int height);

    void resized() override;
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
    double defaultValue = 0.0;

    std::array<Param*, 2> modAmounts;
    std::array<ParamStepped<eModSource>*, 2> modSources;
    bool modSourceValueConverted;
};

#endif  // MOUSEOVERKNOB_H_INCLUDED
