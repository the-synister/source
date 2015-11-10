
#pragma once

#include <map>

#include "JuceHeader.h"
#include "SynthParams.h"

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
        slider->setName(p->name());
        slider->setValue(p->getUI());
        slider->setTextValueSuffix(String(" ") + p->unit());
    }

    void updateDirtySliders() {
        for (auto s2p : sliderReg) {
            if (s2p.second->isUIDirty()) {
                s2p.first->setValue(s2p.second->getUI());
            }
        }
    }

    bool handleSlider(Slider* sliderThatWasMoved) {
        auto it = sliderReg.find(sliderThatWasMoved);
        if (it != sliderReg.end()) {
            it->second->setUI(static_cast<float>(it->first->getValue()));
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

