/*
  ==============================================================================

    FoldableComponent.h
    Created: 4 Feb 2016 12:51:20pm
    Author:  Juan Cabello

  ==============================================================================
*/

#ifndef FOLDABLECOMPONENT_H_INCLUDED
#define FOLDABLECOMPONENT_H_INCLUDED

#include "JuceHeader.h"
#include "SynthParams.h"

class FoldablePanel : public Component
{
public:
    FoldablePanel (const String& name);

    ~FoldablePanel();

    void clear();

    void addSection (const String& sectionTitle,
                     Component* const newPanel,
                     const Colour sectionColour,
                     const int sectionHeight,
                     ParamStepped<eSectionState>* sectionState,
                     int indexToInsertAt = -1);


    bool isEmpty() const;
    void addPanel(const int sectionIndex, Component* const newPanel);
    void getBackToPoint(const int y, int height);
    void paint (Graphics&) override;
    void resized() override;

private:
    Viewport viewport;
    int lastPosY;
    struct SectionComponent;
    struct PanelHolderComponent;
    ScopedPointer<PanelHolderComponent> panelHolderComponent;

    void updateLayout() const;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FoldablePanel)
};



#endif  // FOLDABLECOMPONENT_H_INCLUDED
