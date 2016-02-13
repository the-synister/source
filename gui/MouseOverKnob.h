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
    virtual void setName(const String& newName) override;

    //==============================================================================

    /**
    * Init saturn parameters.
    @param source param of source kind
    @param amount modulation amount knob
    @param convert if source unit is different from destination unit then needs conversion while drawing saturn
           used for filter where source is in octave and destination is in freq
    @param sourceNumber 1 is inner saturn, 2 is outer saturn
    */
    void setModSource(ParamStepped<eModSource> *source, Param *amount, bool convert, int sourceNumber);
    void setDefaultValue(float val);

    std::array<ParamStepped<eModSource>*, 2> getModSources();
    std::array<Param*, 2> getModAmounts();
    bool isModSourceValueConverted();

    //==============================================================================

    /*
    * Needed to save bounds of slider.
    */
    void setBounds(int x, int y, int width, int height);

    /**
    * Overwrite resize(), so that slider size is independent of textbox visibility.
    */
    void resized() override;

    /**
    * Always set label below slider.
    */
    void componentMovedOrResized(Component &component, bool wasMoved, bool wasResized) override;

    /**
    * Adapt knob label depending on enablement state.
    */
    void enablementChanged() override;

    //==============================================================================

    /**
    * If mouse enters slider then replace label with textbox.
    */
    void mouseEnter(const MouseEvent &e) override;

    /**
    * If mouse exits slider then replace textbox with label.
    */
    void mouseExit(const MouseEvent &e) override;

    /**
    * Right click popup menu with some useful items.
    */
    void mouseDown(const MouseEvent &e) override;

    /**
    * If slider is double clicked then values can be edited manually.
    */
    void mouseDoubleClick(const MouseEvent &e) override;

    /**
    * Only drag on slider, not on label.
    */
    void mouseDrag(const MouseEvent &e) override;

//==============================================================================
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
