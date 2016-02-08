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
                     bool shouldSectionInitiallyBeOpen = true,
                     int indexToInsertAt = -1);

    StringArray getSectionNames() const;

    bool isEmpty() const;
    bool isSectionOpen (const int sectionIndex) const;
    void setSectionOpen (int sectionIndex, bool shouldBeOpen);
    void setSectionEnabled (int sectionIndex, bool shouldBeEnabled);
    XmlElement* getOpennessState() const;
    void restoreOpennessState (const XmlElement& newState);
    void paint (Graphics&) override;
    void resized() override;

private:
    struct SectionComponent;
    struct PanelHolderComponent;
    PanelHolderComponent* panelHolderComponent;

    void updateLayout() const;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FoldablePanel)
};



#endif  // FOLDABLECOMPONENT_H_INCLUDED
