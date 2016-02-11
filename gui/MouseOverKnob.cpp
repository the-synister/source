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
    , modSources({ nullptr })
    , modAmounts({ nullptr })
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

//==============================================================================

/**
* Init saturn parameters by saving amount knob and modSource parameter.
*/
void MouseOverKnob::setModSource(ParamStepped<eModSource> *source, Param *amount, int sourceNumber)
{
    modSources[sourceNumber - 1] = source;
    modAmounts[sourceNumber - 1] = amount;
}

std::array<ParamStepped<eModSource>*, 2> MouseOverKnob::getModSources()
{
    return modSources;
}

std::array<Param*, 2> MouseOverKnob::getModAmounts()
{
    return modAmounts;
}

//==============================================================================

void MouseOverKnob::setDefaultValue(float val)
{
    defaultValue = static_cast<double>(val);
}

void MouseOverKnob::setName(const String& newName) {
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
* Right click popup menu with some useful items.
*/
void MouseOverKnob::mouseDown(const MouseEvent &e)
{
    Slider::mouseDown(e);

    if (e.eventComponent == this && e.mods == ModifierKeys::rightButtonModifier)
    {
        PopupMenu main;
        main.addSectionHeader("Current Value: " + String(this->getValue()) + this->getTextValueSuffix());
        main.addItem(1, "reset value");
        main.addItem(2, "set min");
        main.addItem(3, "set max");

        const int result = main.show();
        if (result == 0)
        {
            // user dismissed the menu without picking anything
        }
        else if (result == 1)
        {
            this->setValue(defaultValue);
        }
        else if (result == 2)
        {
            this->setValue(this->getMinimum());
        }
        else if (result == 3)
        {
            this->setValue(this->getMaximum());
        }
    }
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
