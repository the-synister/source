
#pragma once

#include <map>
#include <functional>

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
    typedef std::function<void()> tHookFn;

    void registerSlider(Slider *slider, Param *p, const tHookFn hook = tHookFn()) {
        sliderReg[slider] = p;
        if (hook) {
            postUpdateHook[slider] = hook;
        }
        if (p->hasLabels()) {
            slider->setName(p->getUIString());
        }
        else {
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

    void updateDirtySliders() {
        for (auto s2p : sliderReg) {
            if (s2p.second->isUIDirty()) {
                s2p.first->setValue(s2p.second->getUI());
                if (s2p.second->hasLabels()) {
                    s2p.first->setName(s2p.second->getUIString());
                }

                auto itHook = postUpdateHook.find(s2p.first);
                if (itHook != postUpdateHook.end()) {
                    itHook->second();
                }
            }
        }
    }

    void updateDirtyBoxes() {
        for (auto c2p : comboboxReg) {
            if (c2p.second->isUIDirty()) {
                c2p.first->setSelectedId(static_cast<int>(c2p.second->getStep()) + 1);
                
                auto itHook = postUpdateHook.find(c2p.first);
                if (itHook != postUpdateHook.end()) {
                    itHook->second();
                }
            }
        }
    }

    bool handleSlider(Slider* sliderThatWasMoved) {
        auto it = sliderReg.find(sliderThatWasMoved);
        if (it != sliderReg.end()) {
            it->second->setUI(static_cast<float>(it->first->getValue()));
            if (it->second->hasLabels()) {
                it->first->setName(it->second->getUIString());
            }

            auto itHook = postUpdateHook.find(it->first);
            if (itHook != postUpdateHook.end()) {
                itHook->second();
            }
            return true;
        }
        else {
            return false;
        }
    }

    void registerCombobox(ComboBox* box, ParamStepped<eModSource> *p, const tHookFn hook = tHookFn()) {
        comboboxReg[box] = p;
        box->setSelectedId(static_cast<int>(p->getStep())+1);
        if (hook) {
            postUpdateHook[box] = hook;
        }
    }

    bool handleCombobox(ComboBox* comboboxThatWasChanged) {
        auto it = comboboxReg.find(comboboxThatWasChanged);
        if (it != comboboxReg.end()) {
            // we gotta subtract 2 from the item id since the combobox ids start at 1 and the sources enum starts at -1
            params.globalModMatrix.changeSource(comboboxThatWasChanged->getName(), static_cast<sources>(comboboxThatWasChanged->getSelectedId() - 2));
            // we gotta subtract 1 from the item id since the combobox ids start at 1 and the eModSources enum starts at 0
            it->second->setStep(static_cast<eModSource>(it->first->getSelectedId() - 1));
            return true;
        }
        else {
            return false;
        }
    }

    void fillModsourceBox(ComboBox* box) {
        for (int i = 0; i < 15; i++) {
            box->addItem(params.getModSrcName(i), i + 1);
        }
    }

    virtual void timerCallback() override {
        updateDirtySliders();
        updateDirtyBoxes();
    }

    std::map<Slider*, Param*> sliderReg;
    std::map<ComboBox*, ParamStepped<eModSource>*> comboboxReg;
    std::map<Component*, tHookFn> postUpdateHook;
    SynthParams &params;
};
