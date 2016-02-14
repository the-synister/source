/*
  ==============================================================================

    IncDecDropDown.cpp
    Created: 5 Feb 2016 1:08:53pm
    Author:  Nutty

  ==============================================================================
*/

#include "IncDecDropDown.h"

//==============================================================================
// contructer & destructer
IncDecDropDown::IncDecDropDown(const String& name): ComboBox(name)
{
}

IncDecDropDown::~IncDecDropDown()
{
}
//==============================================================================

void IncDecDropDown::paint(Graphics &g)
{
    // do not show default text, since it is not centered
    this->setColour(ComboBox::ColourIds::textColourId, Colours::transparentWhite);

    // set background colour as transparent
    g.fillAll(Colours::transparentWhite);

    const float width = static_cast<float>(this->getWidth());
    const float height = static_cast<float>(this->getHeight());
    const float buttonWidth = width / 4.0f;

    const float cornerSize = 5.0f;
    const float outlineThickness = this->isEnabled() ? (this->isMouseOver() ? 2.5f : 2.0f) : 1.7f;
    const float halfThickness = outlineThickness * 0.5f;
    Colour baseColour(this->isEnabled() ? Colours::white : Colours::grey);

    // draw outline
    g.setColour(baseColour);
    g.drawRoundedRectangle(halfThickness, halfThickness, width - halfThickness * 2.0f, height - halfThickness * 2.0f, cornerSize, outlineThickness);

    // draw text box
    Rectangle<float> rect = { buttonWidth, 0.0f, this->getWidth() - buttonWidth * 2.0f, height };
    g.drawRect(rect, outlineThickness);

    // set font size and style
    g.setFont(Font(jmin(20.0f, this->getHeight() * 0.85f), Font::plain));

    // draw inc and dec text
    int cornerSizeHalf = static_cast<int>(cornerSize / 2.f);
    Rectangle<int> fittedArea = { cornerSizeHalf, 0, static_cast<int>(buttonWidth) - cornerSizeHalf, this->getHeight() };
    g.drawFittedText("-", fittedArea, Justification::centred, 1);
    fittedArea = { this->getWidth() - static_cast<int>(buttonWidth), 0, static_cast<int>(buttonWidth) - cornerSizeHalf, this->getHeight() };
    g.drawFittedText("+", fittedArea, Justification::centred, 1);

    // draw value text
    fittedArea = { static_cast<int>(buttonWidth), 0, this->getWidth() - 2 * static_cast<int>(buttonWidth), this->getHeight() };
    g.drawFittedText(this->getText(), fittedArea, Justification::centred, 1);
}

void IncDecDropDown::mouseDown(const MouseEvent &e)
{
    if (this->isEnabled())
    {
        const float width = static_cast<float>(this->getWidth());
        const float buttonWidth = width / 4.0f;
        const int numItems = this->getNumItems();
        int index = this->getSelectedItemIndex();

        if (e.position.getX() <= buttonWidth)
        {
            // if dec button
            if (index == 0)
            {
                index = numItems;
            }
            this->setSelectedItemIndex((index - 1) % numItems);
        }
        else if (e.position.getX() >= width - buttonWidth)
        {
            // if inc button
            this->setSelectedItemIndex((index + 1) % numItems);
        }
        else
        {
            ComboBox::mouseDown(e);
        }
    }
}
