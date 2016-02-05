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

struct PanelComponent : public Component
{
    PanelComponent() : preferredHeight(25)
    {};
    
    void refresh() { return; }
    
    int getPreferredHeight() const noexcept                 { return preferredHeight; }
    
    void setPreferredHeight (int newHeight) noexcept        { preferredHeight = newHeight; }
    
    int preferredHeight;
};

class FoldablePanel : public Component,
                      private Timer
{
public:
    //==============================================================================
    /** Creates an empty property panel. */
    FoldablePanel();
    
    /** Creates an empty property panel. */
    // TODO: Set constructor color
    FoldablePanel (const String& name);
    
    /** Destructor. */
    ~FoldablePanel();
    
    //==============================================================================
    /** Deletes all property components from the panel. */
    void clear();
    
    /** Adds a set of properties to the panel.
     
     The components in the list will be owned by this object and will be automatically
     deleted later on when no longer needed.
     
     These properties are added without them being inside a named section. If you
     want them to be kept together in a collapsible section, use addSection() instead.
     */
    void addPanel (const Component* newPanel);
    
    /** Adds a set of properties to the panel.
     
     These properties are added under a section heading with a plus/minus button that
     allows it to be opened and closed. If indexToInsertAt is < 0 then it will be added
     at the end of the list, or before the given index if the index is non-zero.
     
     The components in the list will be owned by this object and will be automatically
     deleted later on when no longer needed.
     
     To add properies without them being in a section, use addProperties().
     */
    void addSection (const String& sectionTitle,
                     Component* const newPanel,
                     const Colour sectionColour,
                     const int sectionHeight,
                     bool shouldSectionInitiallyBeOpen = true,
                     int indexToInsertAt = -1);
    
    /** Calls the refresh() method of all PropertyComponents in the panel */
    void refreshAll() const;
    
    /** Returns true if the panel contains no properties. */
    bool isEmpty() const;
    
    /** Returns the height that the panel needs in order to display all of its content
     without scrolling.
     */
    int getTotalContentHeight() const;
    
    //==============================================================================
    /** Returns a list of all the names of sections in the panel.
     These are the sections that have been added with addSection().
     */
    StringArray getSectionNames() const;
    
    /** Returns true if the section at this index is currently open.
     The index is from 0 up to the number of items returned by getSectionNames().
     */
    bool isSectionOpen (int sectionIndex) const;
    
    /** Opens or closes one of the sections.
     The index is from 0 up to the number of items returned by getSectionNames().
     */
    void setSectionOpen (int sectionIndex, bool shouldBeOpen);
    
    /** Enables or disables one of the sections.
     The index is from 0 up to the number of items returned by getSectionNames().
     */
    void setSectionEnabled (int sectionIndex, bool shouldBeEnabled);
    
    /** Remove one of the sections using the section index.
     The index is from 0 up to the number of items returned by getSectionNames().
     */
    void removeSection (int sectionIndex);
    
    //==============================================================================
    /** Saves the current state of open/closed sections so it can be restored later.
     
     The caller is responsible for deleting the object that is returned.
     To restore this state, use restoreOpennessState().
     
     @see restoreOpennessState
     */
    XmlElement* getOpennessState() const;
    
    /** Restores a previously saved arrangement of open/closed sections.
     
     This will try to restore a snapshot of the panel's state that was created by
     the getOpennessState() method. If any of the sections named in the original
     XML aren't present, they will be ignored.
     
     @see getOpennessState
     */
    void restoreOpennessState (const XmlElement& newState);
    
    //==============================================================================
    /** Sets a message to be displayed when there are no properties in the panel.
     The default message is "nothing selected".
     */
    void setMessageWhenEmpty (const String& newMessage);
    
    /** Returns the message that is displayed when there are no properties.
     @see setMessageWhenEmpty
     */
    const String& getMessageWhenEmpty() const noexcept;
    
    //==============================================================================
    /** @internal */
    void paint (Graphics&) override;
    /** @internal */
    void resized() override;
    
private:
    // set constructor color
    struct SectionComponent;
    struct PanelHolderComponent;
    PanelHolderComponent* panelHolderComponent;
    String messageWhenEmpty;
    Array<WeakReference<Component>> sections;
    
    void init();
    void timerCallback() override;
    void updatePropHolderLayout() const;
    void updatePropHolderLayout (int width) const;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FoldablePanel)
};



#endif  // FOLDABLECOMPONENT_H_INCLUDED
