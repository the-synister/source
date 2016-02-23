/*
  ==============================================================================

    modSourceBox.cpp
    Created: 21 Feb 2016 3:34:37pm
    Author:  Nutty

  ==============================================================================
*/

#include "modSourceBox.h"

//==============================================================================
// contructer & destructer
ModSourceBox::ModSourceBox(const String& name) : ComboBox(name)
{
}

ModSourceBox::~ModSourceBox()
{
}
//==============================================================================
void ModSourceBox::paint(Graphics &g)
{
    // do not show default text since it is too long
    this->setColour(ComboBox::ColourIds::textColourId, Colours::transparentWhite);
    ComboBox::paint(g);

    // draw short text with specific colour
    Rectangle<int> fittedArea = { 0, 0, this->getWidth() - this->getWidth() / 4, this->getHeight() };
    g.setColour(SynthParams::getModSourceColour(static_cast<eModSource>(this->getSelectedId() - COMBO_OFS)));
    g.drawFittedText(SynthParams::getShortModSrcName(this->getSelectedId() - COMBO_OFS), fittedArea, Justification::centred, 1);
}
