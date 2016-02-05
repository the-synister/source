/*
  ==============================================================================

    FoldableComponent.cpp
    Created: 4 Feb 2016 12:51:20pm
    Author:  Juan Cabello

  ==============================================================================
*/

#include "FoldablePanel.h"
/**
 General thoughts to have:
   - is this the best approach
   - make from tabs component and property panel one
   - make the mvp (just one panel, fold and unfold must work) -> extend it to two panels and so on -> last step find a way to instantiate all the panels into one section (maybe create another class "panel" which has width or smthing like that)
   - define child numbers
 */
struct FoldablePanel::SectionComponent  : public Component
{
    // TODO: add color and height of component
    SectionComponent (const String& sectionTitle,
                      Component* const newPanel,
                      const Colour sectionColour,
                      const int sectionHeight,
                      const bool sectionIsOpen)
    : Component (sectionTitle),
    titleHeight (22),
    isOpen (sectionIsOpen),
    _sectionColour(sectionColour),
    _sectionHeight(sectionHeight + titleHeight)
    {
        jassert(sectionTitle.isNotEmpty());
        addAndMakeVisible (newPanel);
    }
    
    ~SectionComponent()
    {
        //panel->clear();
    }
    
    void paint (Graphics& g) override
    {
     //   g.fillAll(Colours::darkblue);
        
        if (titleHeight > 0)
            //implement
            getLookAndFeel().drawPropertyPanelSectionHeader (g, getName(), isOpen, getWidth(), titleHeight);
    }
    
    void resized() override
    {
        for (int i = 0; i < getNumChildComponents(); ++i ) {
            Component* c = getChildComponent(i);
            c->setBounds(c->getLocalBounds().withTop(titleHeight));
            c->resized();
        }
/*
        //y = 10; //TODO: Change //pec->getBottom();
         */
    }
    
    void setOpen (const bool open)
    {
        if (isOpen != open)
        {
            isOpen = open;
            
            for (int i = 0; i < getNumChildComponents(); ++i ) {
                Component* c = getChildComponent(i);
                c->setVisible(open);
            }
            
           if (FoldablePanel* const pp = findParentComponentOfClass<FoldablePanel>())
               pp->resized();
        }
    }
    
    void mouseUp (const MouseEvent& e) override
    {
        if (e.getMouseDownX() < titleHeight
            && e.x < titleHeight
            && e.getNumberOfClicks() != 2)
            mouseDoubleClick (e);
    }
    
    void mouseDoubleClick (const MouseEvent& e) override
    {
        if (e.y < titleHeight) {
            setOpen (! isOpen);
        }
        
    }
    
    Colour getSectionColour()
    {
        return _sectionColour;
    }
    
    bool getIsOpen()
    {
        return isOpen;
    }
    
    int getSectionHeight()
    {
        return (isOpen ? _sectionHeight : titleHeight);
    }
    
    const int titleHeight;
    bool isOpen;
    const int _sectionHeight;
    const Colour _sectionColour;
    
    JUCE_DECLARE_NON_COPYABLE (SectionComponent)
};

//==============================================================================
/* 
    TODO: Make it unfoldable
    - colors go crazy
    - move the bounds
    - create a instanciable class
    - be able to hold more than one control panel
    -
*/
struct FoldablePanel::PanelHolderComponent  : public Component
{
    PanelHolderComponent() {}
    
    void paint (Graphics& g) override
    {
        /*for (int i = 0; i < sections.size(); ++i)
        {
            SectionComponent* const section = sections.getUnchecked(i);
            
            Rectangle<int> content (section->getLocalBounds().withTop(22 /*make a getter helper*//*));
            g.reduceClipRegion (content);
            g.fillAll (section->getSectionColour()); // Colour getColour() //TODO: change for something more suitable
        }*/
    }
    
    // probably unneeded
    void updateLayout (int width)
    {
        int y = 0;
        
        for (int i = 0; i < sections.size(); ++i)
        {
            SectionComponent* const section = sections.getUnchecked(i);
            section->setBounds (0, y, width, section->getSectionHeight());
            y = section->getBottom();
        }
        
        repaint();
    }
    
    void insertSection (int indexToInsertAt, SectionComponent* newSection)
    {
        sections.insert (indexToInsertAt, newSection);
        addAndMakeVisible (newSection, 0);
    }
    
    SectionComponent* getSectionWithNonEmptyName (const int targetIndex) const noexcept
    {
        for (int index = 0, i = 0; i < sections.size(); ++i)
        {
            SectionComponent* const section = sections.getUnchecked (i);
            
            if (section->getName().isNotEmpty())
                if (index++ == targetIndex)
                    return section;
        }
        
        return nullptr;
    }
    
    OwnedArray<SectionComponent> sections;
    
    JUCE_DECLARE_NON_COPYABLE (PanelHolderComponent)
};


//==============================================================================
FoldablePanel::FoldablePanel()
{
    init();
}

FoldablePanel::FoldablePanel (const String& name)  : Component (name)
{
    init();
}

void FoldablePanel::init()
{
    messageWhenEmpty = TRANS("(nothing selected)");
    
    addAndMakeVisible (panelHolderComponent = new PanelHolderComponent());
}

FoldablePanel::~FoldablePanel()
{
    clear();
}

//==============================================================================
void FoldablePanel::paint (Graphics& g)
{
    if (isEmpty())
    {
        g.setColour (Colours::black.withAlpha (0.5f));
        g.setFont (14.0f);
        g.drawText (messageWhenEmpty, getLocalBounds().withHeight (30),
                    Justification::centred, true);
    }
}

// TODO: Have a closer look to the tabs.
void FoldablePanel::resized()
{
    Rectangle<int> content (getLocalBounds());
    
    panelHolderComponent->setBounds (content);
    panelHolderComponent->updateLayout (getWidth());
//    for (int i = sections.size(); --i >= 0;)
  //      if (Component* c = contentComponents.getReference(i))
    //        c->setBounds (content);

}

//==============================================================================
void FoldablePanel::clear()
{
    if (! isEmpty())
    {
        panelHolderComponent->sections.clear();
        //updatePropHolderLayout();
    }
}

bool FoldablePanel::isEmpty() const
{
    return panelHolderComponent->sections.size() == 0;
}

int FoldablePanel::getTotalContentHeight() const
{
    return panelHolderComponent->getHeight();
}

void FoldablePanel::addPanel(const Component* newPanel)
{
    if (isEmpty())
        repaint();
    
//    panelHolderComponent->insertSection (-1, new SectionComponent (String::empty, newPanel, true));
    //updatePropHolderLayout();
}

void FoldablePanel::addSection (const String& sectionTitle,
                                Component* const newPanel,
                                const Colour sectionColour,
                                const int sectionHeight,
                                const bool shouldBeOpen,
                                const int indexToInsertAt)
{
    jassert (sectionTitle.isNotEmpty());
    
    if (isEmpty())
        repaint();
    //sections.insert(indexToInsertAt, new SectionComponent(sectionTitle, newPanel, shouldBeOpen));
    panelHolderComponent->insertSection (indexToInsertAt, new SectionComponent (sectionTitle, newPanel, sectionColour, sectionHeight, shouldBeOpen));
    resized();
    updatePropHolderLayout();
}

void FoldablePanel::updatePropHolderLayout() const
{
    panelHolderComponent->updateLayout (getWidth());
}

//==============================================================================
StringArray FoldablePanel::getSectionNames() const
{
    StringArray s;
    
    for (int i = 0; i < panelHolderComponent->sections.size(); ++i)
    {
        SectionComponent* const section = panelHolderComponent->sections.getUnchecked(i);
        
        if (section->getName().isNotEmpty())
            s.add (section->getName());
    }
    
    return s;
}

bool FoldablePanel::isSectionOpen (const int sectionIndex) const
{
    if (SectionComponent* s = panelHolderComponent->getSectionWithNonEmptyName (sectionIndex))
        return s->isOpen;
    
    return false;
}

void FoldablePanel::setSectionOpen (const int sectionIndex, const bool shouldBeOpen)
{
    if (SectionComponent* s = panelHolderComponent->getSectionWithNonEmptyName (sectionIndex))
        s->setOpen (shouldBeOpen);
}

void FoldablePanel::setSectionEnabled (const int sectionIndex, const bool shouldBeEnabled)
{
    if (SectionComponent* s = panelHolderComponent->getSectionWithNonEmptyName (sectionIndex))
        s->setEnabled (shouldBeEnabled);
}

void FoldablePanel::removeSection (int sectionIndex)
{
    if (SectionComponent* s = panelHolderComponent->getSectionWithNonEmptyName (sectionIndex))
    {
        panelHolderComponent->sections.removeObject (s);
        updatePropHolderLayout();
    }
}

//==============================================================================
XmlElement* FoldablePanel::getOpennessState() const
{
    XmlElement* const xml = new XmlElement ("PROPERTYPANELSTATE");
    
    const StringArray sections (getSectionNames());
    
    for (int i = 0; i < sections.size(); ++i)
    {
        if (sections[i].isNotEmpty())
        {
            XmlElement* const e = xml->createNewChildElement ("SECTION");
            e->setAttribute ("name", sections[i]);
            e->setAttribute ("open", isSectionOpen (i) ? 1 : 0);
        }
    }
    
    return xml;
}

void FoldablePanel::restoreOpennessState (const XmlElement& xml)
{
    if (xml.hasTagName ("PROPERTYPANELSTATE"))
    {
        const StringArray sections (getSectionNames());
        
        forEachXmlChildElementWithTagName (xml, e, "SECTION")
        {
            setSectionOpen (sections.indexOf (e->getStringAttribute ("name")),
                            e->getBoolAttribute ("open"));
        }
        
    }
}

//==============================================================================
void FoldablePanel::setMessageWhenEmpty (const String& newMessage)
{
    if (messageWhenEmpty != newMessage)
    {
        messageWhenEmpty = newMessage;
        repaint();
    }
}

const String& FoldablePanel::getMessageWhenEmpty() const noexcept
{
    return messageWhenEmpty;
}
