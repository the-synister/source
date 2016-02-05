/*
  ==============================================================================

    IncDecDropDown.h
    Created: 5 Feb 2016 1:08:53pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef INCDECDROPDOWN_H_INCLUDED
#define INCDECDROPDOWN_H_INCLUDED

#include "JuceHeader.h"
#include "SynthParams.h"
#include "CustomLookAndFeel.h"

/**
* Custom transparent Combobox with additional increment and decrement button for selecting item.
*/
class IncDecDropDown : public ComboBox,
                       public ComponentListener
{
public:
    //==============================================================================
    IncDecDropDown(const String &componentName = String::empty);
    ~IncDecDropDown();
    //==============================================================================
    void paint(Graphics &g) override;

    void mouseDown(const MouseEvent &e) override;
private:

};

#endif  // INCDECDROPDOWN_H_INCLUDED
