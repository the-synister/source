/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 13 Jan 2016 5:44:21pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef CUSTOMLOOKANDFEEL_H_INCLUDED
#define CUSTOMLOOKANDFEEL_H_INCLUDED

//[Headers]
#include "JuceHeader.h"
#include "../audio/inc/SynthParams.h"
#include "MouseOverKnob.h"
//[/Headers]

class CustomLookAndFeel : public LookAndFeel_V2 // our default design
{
public:
    //==============================================================================
    CustomLookAndFeel();
    virtual ~CustomLookAndFeel();
    //==============================================================================
    virtual void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &s);

    virtual void drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s);
    virtual void drawLinearSliderBackground(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s);
    virtual void drawLinearSliderThumb(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s);

    virtual Slider::SliderLayout getSliderLayout(Slider& s);

    virtual void drawButtonBackground(Graphics &g, Button &b, const Colour& c, bool isMouseOverButton, bool isButtonDown);

    virtual void drawToggleButton(Graphics &g, ToggleButton &b, bool isMouseOverButton, bool isButtonDown);
    virtual void drawTickBox(Graphics &g, Component &c, float x, float y, float width, float height, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown);

    virtual void drawComboBox(Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &c);
    virtual Font getComboBoxFont(ComboBox &c);
    virtual void positionComboBoxText(ComboBox &c, Label &l);

private:
    void drawModSource(Graphics &g, Slider &s, float sourceValue, bool unipolar, float centreX, float centreY, float radius, float innerCircleSize, float currAngle, float rotaryStartAngle, float rotaryEndAngle);
};

#endif  // CUSTOMLOOKANDFEEL_H_INCLUDED
