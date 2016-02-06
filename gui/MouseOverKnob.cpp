/*
  ==============================================================================

    MouseOverKnob.cpp
    Created: 4 Nov 2015 9:54:43pm
    Author:  Nhat

  ==============================================================================
*/

#include "MouseOverKnob.h"

//==============================================================================
// contructer & destructer
MouseOverKnob::MouseOverKnob(const String& name)
    : Slider(name)
    , modSources({nullptr})
{
    addAndMakeVisible(knobLabel = new Label("new label", TRANS(name)));
    knobLabel->setFont(Font(18.00f, Font::plain));
    knobLabel->setJustificationType(Justification::centred);
    knobLabel->setEditable(false, false, false);
    knobLabel->setColour(Label::ColourIds::textColourId, Colours::white);

    knobLabel->attachToComponent(this, false);
    knobLabel->addComponentListener(this);

    initTextBox();
}

MouseOverKnob::~MouseOverKnob()
{
    knobLabel = nullptr;
    modSources = {nullptr};
}
//==============================================================================

void MouseOverKnob::initTextBox()
{
    if (knobLabel->isVisible()) {
        setTextBoxStyle(MouseOverKnob::NoTextBox, false, this->getTextBoxWidth(), this->getTextBoxHeight());
    } else {
        setTextBoxStyle(MouseOverKnob::TextBoxBelow, false, this->getTextBoxWidth(), this->getTextBoxHeight());
    }
}

void MouseOverKnob::setModSource(Param *p, int sourceNumber)
{
    modSources[sourceNumber - 1] = p;
}

std::array<Param*, 2> MouseOverKnob::getModSources()
{
    return modSources;
}

void MouseOverKnob::setName  (const String& newName) {
    knobLabel->setText(newName, NotificationType::dontSendNotification);
}

/**
* If mouse enters slider then replace label with textbox.
*/
void MouseOverKnob::mouseEnter(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        knobLabel->setVisible(false);
        setTextBoxStyle(MouseOverKnob::TextBoxBelow, false, this->getTextBoxWidth(), this->getTextBoxHeight());
    }
}

/**
* If mouse exits slider then replace textbox with label.
*/
void MouseOverKnob::mouseExit(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        knobLabel->setVisible(true);
        setTextBoxStyle(MouseOverKnob::NoTextBox, true, this->getTextBoxWidth(), this->getTextBoxHeight());
    }
}

/**
* Right click popup menu.
*/
void MouseOverKnob::mouseDown(const MouseEvent &e)
{
    // TODO: erben von synthparams und dann hier setzen
    // mouseOverKnob mit dem amount verbinden über registerSaturn, danach hierüber nur noch params ändern
    if (e.eventComponent == this && e.mods == ModifierKeys::rightButtonModifier)
    {
        PopupMenu main, sub;
        sub.addItem(3, "set min");
        sub.addItem(4, "set max");

        main.addSectionHeader("Test Popup Menu");
        main.addItem(1, "set 0.0");
        main.addItem(2, "change colour to red");
        main.addSubMenu("sub item", sub);
        const int result = main.show();
        if (result == 0)
        {
            // user dismissed the menu without picking anything
        }
        else if (result == 1)
        {
            this->setValue(0.0);
        }
        else if (result == 2)
        {
            this->setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::red);
        }
        else if (result == 3)
        {
            this->setValue(this->getMinimum());
        }
        else if (result == 4)
        {
            this->setValue(this->getMaximum());
        }
    }

    Slider::mouseDown(e);
}

/**
* If slider is double clicked then values can be edited manually.
*/
void MouseOverKnob::mouseDoubleClick(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        showTextBox();
    }
}

/**
* Only drag on slider, not on label.
*/
void MouseOverKnob::mouseDrag(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        Slider::mouseDrag(e);
    }
}

/**
* Overwrite resize(), so that slider size is independent of textbox visibility.
*/
void MouseOverKnob::resized()
{
    if (!this->isMouseOver())
    {
        this->setSize(knobWidth, knobHeight - this->getTextBoxHeight());
    }
    else
    {
        this->setSize(knobWidth, knobHeight);
    }

    Slider::resized();
}

/*
* Needed to save bounds of slider.
*/
void MouseOverKnob::setBounds(int x, int y, int width, int height)
{
    knobWidth = width;
    knobHeight = height;
    Slider::setBounds(x, y, width, height);
}

void MouseOverKnob::enablementChanged()
{
    Slider::enablementChanged();

    if (this->isEnabled())
    {
        knobLabel->setColour(Label::ColourIds::textColourId, Colours::white);
    }
    else
    {
        knobLabel->setColour(Label::ColourIds::textColourId, Colours::white.withAlpha(0.5f));
    }
}

/**
* Always set label below slider.
*/
void MouseOverKnob::componentMovedOrResized(Component &component, bool wasMoved, bool wasResized)
{
    knobLabel->setSize(knobWidth, this->getTextBoxHeight());
    knobLabel->setTopLeftPosition(this->getX(), this->getY() + this->getHeight() - 5);

    ComponentListener::componentMovedOrResized(component, wasMoved, wasResized);
}
