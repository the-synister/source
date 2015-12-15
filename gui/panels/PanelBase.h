
#pragma once

#include <map>

#include "JuceHeader.h"
#include "SynthParams.h"
#include "MouseOverKnob.h"

class PanelBase : public Component, protected Timer
{
public:
    PanelBase(SynthParams &p)
        : params(p) {
        startTimerHz(60);
    }

    ~PanelBase() {
        stopTimer();
    }

protected:
    void registerSlider(Slider *slider, Param *p) {
        sliderReg[slider] = p;
        if(p->hasLabels()) {
            slider->setName(p->getUIString());
        } else {
            slider->setName(p->name());
            slider->setTextValueSuffix(String(" ") + p->unit());
        }
        slider->setValue(p->getUI());
    }

    void registerSlider(MouseOverKnob *slider, Param *p) {
        registerSlider(static_cast<Slider*>(slider), p);
        slider->initTextBox();
    }

    void updateDirtySliders() {
        for (auto s2p : sliderReg) {
            if (s2p.second->isUIDirty()) {
                s2p.first->setValue(s2p.second->getUI());
                if(s2p.second->hasLabels()) {
                    s2p.first->setName(s2p.second->getUIString());
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
            return true;
        } else {
            return false;
        }
    }

    virtual void timerCallback() override {
        updateDirtySliders();
    }

    std::map<Slider*, Param*> sliderReg;
    SynthParams &params;
};
