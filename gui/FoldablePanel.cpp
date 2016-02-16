
/*
  ==============================================================================

    FoldableComponent.cpp
    Created: 4 Feb 2016 12:51:20pm
    Author:  Juan Cabello

  ==============================================================================
*/

#include "FoldablePanel.h"

struct FoldablePanel::SectionComponent  : public Component
{
    // TODO: add color and height of component
    SectionComponent (const String& sectionTitle,
                      Component* const newPanel,
                      const Colour sectionColour,
                      const int sectionHeight,
                      const bool sectionIsOpen)
    : Component (sectionTitle),
    positionIndex(0),
    titleHeight (27),
    isOpen (sectionIsOpen),
    _sectionHeight(sectionHeight + titleHeight),
    _sectionColour(sectionColour)
    {
        jassert(sectionTitle.isNotEmpty());
        addPanel (newPanel);
    }

    ~SectionComponent()
    {
        panels.clear();
        positionIndex = 0;
    }

    void paint(Graphics& g) override
    {
        if (titleHeight > 0)
        {
            getLookAndFeel().drawPropertyPanelSectionHeader(g, getName(), isOpen, getWidth(), titleHeight);

            const float buttonSize = titleHeight * 0.65f;
            const float buttonIndent = (titleHeight - buttonSize) * 0.5f;

            // draw section header text
            const int textX = (int)(buttonIndent * 4.0f + buttonSize);
            g.setColour(getSectionColour().withSaturation(.6f).brighter());
            g.setFont(Font(titleHeight * 0.75f, Font::plain));
            g.drawText(getName(), textX, 0, getWidth() - textX - 4, titleHeight, Justification::centredLeft, true);
        }
    }

    void addPanel(Component* const newPanel)
    {
        panels.insert(positionIndex++, newPanel);
        addAndMakeVisible (newPanel, 0);
        resized();
    }

    void resized() override
    {
        int x = 0;
        for (int i = 0; i < panels.size(); ++i ) {
            Component* const panel = panels.getUnchecked(i);
            panel->setBounds(x, titleHeight, panel->getWidth(), panel->getHeight());
            x += panel->getWidth();
        }
    }

    void setOpen (const bool open)
    {
        if (isOpen != open)
        {
            isOpen = open;
            for (int i = 0; i < panels.size(); ++i ) {
                Component* const panel = panels.getUnchecked(i);
                panel->setVisible(open);
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

    int getSectionHeight()
    {
        return (isOpen ? _sectionHeight : titleHeight);
    }

    int positionIndex;
    OwnedArray<Component> panels;
    const int titleHeight;
    bool isOpen;
    const int _sectionHeight;
    const Colour _sectionColour;

    JUCE_DECLARE_NON_COPYABLE (SectionComponent)
};

//==============================================================================
struct FoldablePanel::PanelHolderComponent  : public Component
{
    PanelHolderComponent() {}

    void paint (Graphics& g) override
    {
        const int titleHeight = 22;
        int y = 0;

        // TODO: at each panel some space is cutoff at bottom of original panel
        // see NOTE in PlugUI.cpp
        for (int i = 0; i < sections.size(); ++i)
        {
            SectionComponent* const section = sections.getUnchecked(i);

            Rectangle<int> content (0, y + 22, getWidth(), section->getSectionHeight() - titleHeight);
            y = section->getBottom();

            g.setColour(section->getSectionColour());
            g.fillRect (content);
        }
    }

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

    SectionComponent* getSection (const int targetIndex) const noexcept
    {
        return sections.getUnchecked (targetIndex);
    }

    OwnedArray<SectionComponent> sections;

    JUCE_DECLARE_NON_COPYABLE (PanelHolderComponent)
};

FoldablePanel::FoldablePanel (const String& name)  : Component (name)
{
    addAndMakeVisible (panelHolderComponent = new PanelHolderComponent());
}

FoldablePanel::~FoldablePanel()
{
    clear();
}

void FoldablePanel::paint (Graphics& /*g*/)
{
}

void FoldablePanel::resized()
{
    Rectangle<int> content (getLocalBounds());

    panelHolderComponent->setBounds (content);
    panelHolderComponent->updateLayout (getWidth());
}

bool FoldablePanel::isEmpty() const
{
    return (panelHolderComponent->sections.size() == 0);
}

void FoldablePanel::clear()
{
    if (! isEmpty())
    {
        panelHolderComponent->sections.clear();
        updateLayout();
    }
}

void FoldablePanel::addSection (const String& sectionTitle,
                                Component* const newPanel,
                                const Colour sectionColour,
                                const int sectionHeight,
                                const bool shouldBeOpen,
                                const int indexToInsertAt)
{
    jassert (sectionTitle.isNotEmpty());

    if (isEmpty()) {
        repaint();
    }

    panelHolderComponent->insertSection (indexToInsertAt, new SectionComponent (sectionTitle, newPanel, sectionColour, sectionHeight, shouldBeOpen));
    resized();
    updateLayout();
}

void FoldablePanel::addPanel(const int sectionIndex, Component* const newPanel)
{
    if (SectionComponent* s = panelHolderComponent->getSection (sectionIndex)) {
        s->addPanel(newPanel);
    }
}

void FoldablePanel::updateLayout() const
{
    panelHolderComponent->updateLayout (getWidth());
}
