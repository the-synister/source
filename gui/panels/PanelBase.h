
#pragma once

#include <map>
#include <functional>

#include "JuceHeader.h"
#include "SynthParams.h"
#include "MouseOverKnob.h"
#include "IncDecDropDown.h"

class PanelBase : public Component, protected Timer
{
public:

    PanelBase(SynthParams &p)
        : params(p)
    {
        startTimerHz(60);
    }

    ~PanelBase() {
        stopTimer();
    }
    
protected:
    typedef std::function<void()> tHookFn;

    void registerSlider(Slider *slider, Param *p, const tHookFn hook = tHookFn()) {
        sliderReg[slider] = p;
        if (hook) {
            postUpdateHook[slider] = hook;
        }
        if(p->hasLabels()) {
            slider->setName(p->getUIString());
        } else {
            slider->setName(p->name());
            slider->setTextValueSuffix(String(" ") + p->unit());
        }
        slider->setValue(p->getUI());
    }

    void registerSlider(MouseOverKnob *slider, Param *p, const tHookFn hook = tHookFn()) {
        registerSlider(static_cast<Slider*>(slider), p);
        if (hook) {
            postUpdateHook[slider] = hook;
        }
        slider->initTextBox();
    }

    // NOTE: sourceNumber values 1 or 2
    // TODO: change it to an enum?
    void registerSaturnSource(MouseOverKnob *dest, Slider *source, Param *paramSource, int sourceNumber) {
        dest->setModSource(paramSource, sourceNumber);

        auto temp = saturnReg.find(dest);

        if (temp == saturnReg.end()) {
            std::array<Slider*, 2> newSource = {nullptr};
            newSource[sourceNumber-1] = source;
            saturnReg[dest] = newSource;
        } else {
            temp->second[sourceNumber-1] = source;
        }
    }

    void updateDirtySliders() {
        for (auto s2p : sliderReg) {
            if (s2p.second->isUIDirty()) {
                s2p.first->setValue(s2p.second->getUI());
                if(s2p.second->hasLabels()) {
                    s2p.first->setName(s2p.second->getUIString());
                }

                auto itHook = postUpdateHook.find(s2p.first);
                if (itHook != postUpdateHook.end()) {
                    itHook->second();
                }
            }

        }
    }

    // Callback function in case there are any dirty saturn glows
    void updateDirtySaturns() {
        // iterate over all the registered saturn glows
        for (auto dest2saturn : saturnReg) {
            // find the mod source from the slider register
            for (int i = 0; i < 2; ++i) {
                auto modSource = sliderReg.find(dest2saturn.second[i]);

                //if the mod source is Dirty repaint
                if (modSource != sliderReg.end() && modSource->second->isUIDirty()) {
                    dest2saturn.first->repaint();
                }

            }
        }
    }

    bool handleSlider(Slider* sliderThatWasMoved) {
        auto it = sliderReg.find(sliderThatWasMoved);
        if (it != sliderReg.end()) {
            it->second->setUI(static_cast<float>(it->first->getValue()));
            if(it->second->hasLabels()) {
                it->first->setName(it->second->getUIString());
            }

            for (auto saturn : saturnReg) {
                for (int i = 0; i < 2; ++i) {
                    if (saturn.second[i] == sliderThatWasMoved) {
                        saturn.first->repaint();
                    }
                }
            }

            auto itHook = postUpdateHook.find(it->first);
            if (itHook != postUpdateHook.end()) {
                itHook->second();
            }

            return true;
        } else {
            return false;
        }
    }

    virtual void timerCallback() override {
        updateDirtySaturns();
        updateDirtySliders();
    }

    /**
    * 
    */
    void drawGroupBorder(Graphics &g, const String &/*name*/, int x, int y, int width, int height, float headHeight, float cornerSize, float borderThickness, Colour &c)
    {

        // draw white groupborder
        Rectangle<float> rect = { static_cast<float>(x), static_cast<float>(y), 
                                  static_cast<float>(x + width), static_cast<float>(y + height) };
        g.setColour(Colours::white);
        g.fillRoundedRectangle(rect, cornerSize);

        //rect = { static_cast<float>(x) + borderThickness, static_cast<float>(y) + headHeight,
        //         static_cast<float>(x + width) - borderThickness * 2.0f, static_cast<float>(y + height) - headHeight * 2 - borderThickness };
        //g.setColour(c);
        //g.fillRoundedRectangle(rect, cornerSize);
    }

    std::map<Slider*, Param*> sliderReg;
    std::map<MouseOverKnob*, std::array<Slider*, 2>> saturnReg;
    std::map<Slider*, tHookFn> postUpdateHook;
    SynthParams &params;
};
