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

void MouseOverKnob::setName(const String& newName) {
    knobLabel->setText(newName, NotificationType::dontSendNotification);
}

//==============================================================================

void MouseOverKnob::setModSource(ParamStepped<eModSource> *source, Param *amount, int sourceNumber, modAmountConversion conversion)
{
    modSources[sourceNumber - 1] = source;
    modAmounts[sourceNumber - 1] = amount;
    modSourceValueConverted = conversion;
}

void MouseOverKnob::showBipolarValues(bool showBipolar)
{
    displayBipolarValue = showBipolar;
}

void MouseOverKnob::setDefaultValue(float val)
{
    defaultValue = static_cast<double>(val);
}

String MouseOverKnob::getTextFromValue(double val)
{
    // calculate bipolar value, only makes sense if minimum is 0 since maximum is used for scaling
    if (displayBipolarValue)
    {
        float coeff = toBipolar(static_cast<float>(this->getMinimum()), static_cast<float>(this->getMaximum()), static_cast<float>(val));
        val = this->getMaximum() * coeff;
    }

    int decimal = getNumDecimalPlacesToDisplay();
    if (decimal > 0)
    {
        return String(val, decimal) + getTextValueSuffix();
    }
    return String(roundToInt(val)) + getTextValueSuffix();
}

std::array<ParamStepped<eModSource>*, 2> MouseOverKnob::getModSources()
{
    return modSources;
}

std::array<Param*, 2> MouseOverKnob::getModAmounts()
{
    return modAmounts;
}

MouseOverKnob::modAmountConversion MouseOverKnob::getConversionType()
{
    return modSourceValueConverted;
}

//==============================================================================

void MouseOverKnob::setBounds(int x, int y, int width, int height)
{
    knobWidth = width;
    knobHeight = height;

    // if no textbox then display popup on mouseDrag
    if (this->getTextBoxWidth() == 0 || this->getTextBoxHeight() == 0)
    {
        this->setPopupDisplayEnabled(true, this->getParentComponent());
    }

    Slider::setBounds(x, y, width, height);
}

void MouseOverKnob::resized()
{
    // is mouseOver then reduce height according to textbox height otherwise knobSize is reduced
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

void MouseOverKnob::componentMovedOrResized(Component &component, bool wasMoved, bool wasResized)
{
    knobLabel->setSize(knobWidth, this->getTextBoxHeight());
    knobLabel->setTopLeftPosition(this->getX(), this->getY() + this->getHeight() - 5);

    ComponentListener::componentMovedOrResized(component, wasMoved, wasResized);
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

//==============================================================================

void MouseOverKnob::mouseEnter(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        knobLabel->setVisible(false);
        setTextBoxStyle(MouseOverKnob::TextBoxBelow, false, this->getTextBoxWidth(), this->getTextBoxHeight());
    }
}

void MouseOverKnob::mouseExit(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        knobLabel->setVisible(true);
        setTextBoxStyle(MouseOverKnob::NoTextBox, true, this->getTextBoxWidth(), this->getTextBoxHeight());
    }
}

void MouseOverKnob::mouseDown(const MouseEvent &e)
{
    if (e.eventComponent == this && e.mods.isAltDown() && e.mods.isCtrlDown())
    {
        this->setValue(defaultValue, NotificationType::sendNotification);
    }

    Slider::mouseDown(e);

    // create popup menu and item handling
    if (e.eventComponent == this && e.mods == ModifierKeys::rightButtonModifier && this->isEnabled())
    {
        PopupMenu main;
        main.addSectionHeader("Current Value: " + String(getTextFromValue(this->getValue())));
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
            this->setValue(defaultValue, NotificationType::sendNotification);
        }
        else if (result == 2)
        {
            this->setValue(this->getMinimum(), NotificationType::sendNotification);
        }
        else if (result == 3)
        {
            this->setValue(this->getMaximum(), NotificationType::sendNotification);
        }
    }
}

void MouseOverKnob::mouseDoubleClick(const MouseEvent &e)
{
    if (e.eventComponent == this && this->isEnabled())
    {
        showTextBox();
    }
}

void MouseOverKnob::mouseDrag(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        Slider::mouseDrag(e);
    }
}
