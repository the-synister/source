
#pragma once

#include <map>
#include <functional>

#include "JuceHeader.h"
#include "SynthParams.h"
#include "MouseOverKnob.h"
#include "IncDecDropDown.h"
#include "ModSourceBox.h"

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

    static const int COMBO_OFS = 2;
protected:
    typedef std::function<void()> tHookFn;

    //=======================================================================================================================================
    void registerSlider(Slider *slider, Param *p, const tHookFn hook = tHookFn(), Param *min = nullptr, Param *max = nullptr) {
        slider->setScrollWheelEnabled(false);

        sliderReg[slider] = {p, min, max};
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

        if (min) {
            slider->setMinValue(min->getUI());
        }
        if (max) {
            slider->setMaxValue(max->getUI());
        }
        if (!min && !max) {
            slider->setValue(p->getUI());
        }
    }

    void registerSlider(MouseOverKnob *slider, Param *p, const tHookFn hook = tHookFn()) {
        slider->setDefaultValue(p->getDefaultUI());

        registerSlider(static_cast<Slider*>(slider), p);
        if (hook) {
            postUpdateHook[slider] = hook;
        }
        slider->initTextBox();
    }

    bool handleSlider(Slider* sliderThatWasMoved) {
        auto it = sliderReg.find(sliderThatWasMoved);
        if (it != sliderReg.end()) {
            if (it->second[1] == nullptr && it->second[2] == nullptr) {
                it->second[0]->setUI(static_cast<float>(it->first->getValue()));
                if (it->second[0]->hasLabels()) {
                    it->first->setName(it->second[0]->getUIString());
                }
            }

            if (it->second[1] && it->second[2]) {
                it->second[1]->setUI(static_cast<float>(it->first->getMinValue()));
                it->second[2]->setUI(static_cast<float>(it->first->getMaxValue()));
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
        }
        else {
            return false;
        }
    }

    void updateDirtySliders() {
        for (auto s2p : sliderReg) {
            if (s2p.second[0]->isUIDirty() && !s2p.second[1] && !s2p.second[2]) {
                s2p.first->setValue(s2p.second[0]->getUI());
                if (s2p.second[0]->hasLabels()) {
                    s2p.first->setName(s2p.second[0]->getUIString());
                }

                auto itHook = postUpdateHook.find(s2p.first);
                if (itHook != postUpdateHook.end()) {
                    itHook->second();
                }
            }

            // if min and max params are set
            if (s2p.second[1]) {
                if (s2p.second[1]->isUIDirty()) {
                    s2p.first->setMinValue(s2p.second[1]->getUI());
                }
            }
            if (s2p.second[2]) {
                if (s2p.second[2]->isUIDirty()) {
                    s2p.first->setMaxValue(s2p.second[2]->getUI());
                }
            }
        }
    }

    //=======================================================================================================================================

    // NOTE: sourceNumber values 1 or 2
    // TODO: change it to an enum?
    void registerSaturnSource(MouseOverKnob *dest, Slider *source, ParamStepped<eModSource> *modSource, Param *modAmount, int sourceNumber
        , MouseOverKnob::modAmountConversion convType = MouseOverKnob::modAmountConversion::noConversion) {
        dest->setModSource(modSource, modAmount, sourceNumber, convType);

        auto temp = saturnReg.find(dest);
        if (temp == saturnReg.end()) {
            std::array<Slider*, 2> newSource = {nullptr};
            newSource[sourceNumber-1] = source;
            saturnReg[dest] = newSource;
        } else {
            temp->second[sourceNumber-1] = source;
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
                if (modSource != sliderReg.end() && modSource->second[0]->isUIDirty()) {
                    dest2saturn.first->repaint();
                }
            }
        }
    }

    //=======================================================================================================================================

    void registerToggle(Button* toggle, ParamStepped<eOnOffToggle>* p, const tHookFn hook = tHookFn())
    {
        toggleReg[toggle] = p;

        if (hook) {
            postUpdateHook[toggle] = hook;
        }
    }

    bool handleToggle(Button* buttonThatWasClicked)
    {
        auto it = toggleReg.find(buttonThatWasClicked);

        if (it != toggleReg.end()) {
            it->second->setStep(it->second->getStep() == eOnOffToggle::eOn ? eOnOffToggle::eOff : eOnOffToggle::eOn);
            it->first->setToggleState(it->second->getStep() == eOnOffToggle::eOn, dontSendNotification);

            auto itHook = postUpdateHook.find(it->first);
            if (itHook != postUpdateHook.end()) {
                itHook->second();
            }

            return true;
        }

        return false;
    }

    void updateDirtyToggles()
    {
        for (auto t2p : toggleReg) {
            if (t2p.second->isUIDirty()) {
                t2p.first->setToggleState((t2p.second->getStep() == eOnOffToggle::eOn), dontSendNotification);

                auto itHook = postUpdateHook.find(t2p.first);
                if (itHook != postUpdateHook.end()) {
                    itHook->second();
                }
            }
        }
    }

    //=======================================================================================================================================

    void registerDropDowns(ComboBox* dropDown, Param* p, const tHookFn hook = tHookFn())
    {
        dropDownReg[dropDown] = p;

        if (hook) {
            postUpdateHook[dropDown] = hook;
        }
    }

    bool handleDropDowns(ComboBox* dropDownThatWasChanged)
    {
        auto it = dropDownReg.find(dropDownThatWasChanged);

        if (it != dropDownReg.end()) {
            it->second->setUI(dropDownThatWasChanged->getText().getFloatValue());

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

    void updateDirtyDropDowns()
    {
        for (auto d2p : dropDownReg) {
            if (d2p.second->isUIDirty()) {
                d2p.first->setText(String(d2p.second->getUI()));
            }

            auto itHook = postUpdateHook.find(d2p.first);
            if (itHook != postUpdateHook.end()) {
                itHook->second();
            }
        }
    }

    //=======================================================================================================================================

    // TODO: Change for ParamStepped? It might be just useful for the notelength, so maybe a general solution should be better.
    void registerNoteLength(ComboBox* noteLengthBox, Param* p, const tHookFn hook = tHookFn())
    {
        noteLengthReg[noteLengthBox] = p;

        if (hook) {
            postUpdateHook[noteLengthBox] = hook;
        }
    }

    // TODO: Change for ParamStepped?
    bool handleNoteLength(ComboBox* noteLengthThatWasChanged)
    {
        auto it = noteLengthReg.find(noteLengthThatWasChanged);

        if (it != noteLengthReg.end()) {
            it->second->setUI(noteLengthThatWasChanged->getText().substring(2).getFloatValue());

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

    // TODO: Change for ParamStepped? It might be just useful for the notelength, so maybe a general solution should be better.
    void updateDirtyNoteLength()
    {
        for (auto d2p : noteLengthReg) {
            if (d2p.second->isUIDirty()) {
                d2p.first->setText("1/" + String(d2p.second->getUI()));
            }

            auto itHook = postUpdateHook.find(d2p.first);
            if (itHook != postUpdateHook.end()) {
                itHook->second();
            }
        }
    }

    //=======================================================================================================================================

    // use only with ModSourceBox class
    void registerCombobox(ComboBox* box, ParamStepped<eModSource> *p, std::array<MouseOverKnob*, 3> modDest = {nullptr}, const tHookFn hook = tHookFn()) {
        comboboxReg[box] = p;

        // couple combobox with saturn knob
        if (!modDest.empty()) {
            saturnSourceReg[box] = modDest;
        }

        box->setSelectedId(static_cast<int>(p->getStep())+COMBO_OFS);

        if (hook) {
            postUpdateHook[box] = hook;
        }
    }

    bool handleCombobox(ComboBox* comboboxThatWasChanged) {
        auto it = comboboxReg.find(comboboxThatWasChanged);
        if (it != comboboxReg.end()) {
            // we gotta subtract 2 from the item id since the combobox ids start at 1 and the sources enum starts at -1
            params.globalModMatrix.changeSource(it->second->prefix()+" "+comboboxThatWasChanged->getName(), static_cast<eModSource>(comboboxThatWasChanged->getSelectedId() - COMBO_OFS));
            // we gotta subtract 1 from the item id since the combobox ids start at 1 and the eModSources enum starts at 0
            it->second->setStep(static_cast<eModSource>(it->first->getSelectedId() - COMBO_OFS));

            // set colour of textBox background with some transparency if no mod source is selected
            if (it->second->getStep() == eModSource::eNone) {
                it->first->setColour(ComboBox::ColourIds::backgroundColourId, it->first->findColour(ComboBox::ColourIds::backgroundColourId).withAlpha(0.5f));
            }
            else {
                it->first->setColour(ComboBox::ColourIds::backgroundColourId, it->first->findColour(ComboBox::ColourIds::backgroundColourId).withAlpha(1.0f));
            }

            // update saturn
            auto temp = saturnSourceReg.find(comboboxThatWasChanged);
            if (temp != saturnSourceReg.end()) {
                for (int i = 0; i < 3; ++i ) {
                    if (temp->second[i]) {
                        temp->second[i]->repaint();
                    }
                }
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

    void updateDirtyBoxes() {
        for (auto c2p : comboboxReg) {
            if (c2p.second->isUIDirty()) {
                c2p.first->setSelectedId(static_cast<int>(c2p.second->getStep()) + COMBO_OFS);

                auto c2s = saturnSourceReg.find(c2p.first);
                if (c2s != saturnSourceReg.end()) {
                    for (int i = 0; i < 3; ++i) {
                        if (c2s->second[i]) {
                            c2s->second[i]->repaint();
                        }
                    }
                }

                auto itHook = postUpdateHook.find(c2p.first);
                if (itHook != postUpdateHook.end()) {
                    itHook->second();
                }
            }
        }
    }

    //=======================================================================================================================================

    virtual void timerCallback() override {
        updateDirtySaturns();
        updateDirtySliders();
        updateDirtyBoxes();
        updateDirtyNoteLength();
        updateDirtyDropDowns();
        updateDirtyToggles();
    }

    /**
    * Draw white group border with group name alligned right.
    */
    void drawGroupBorder(Graphics &g, const String &name, int x, int y, int width, int height, float headHeight, float cornerSize, float borderThickness, float padding, Colour c)
    {
        float posX = static_cast<float>(x) + padding;
        float posY = static_cast<float>(y) + padding;
        float boxWidth = static_cast<float>(width) - 2.0f * padding;
        float boxHeight = static_cast<float>(height) - 2.0f * padding;

        // draw white groupborder
        Rectangle<float> rect = { posX, posY, boxWidth, boxHeight };
        g.setColour(Colours::white);
        g.fillRoundedRectangle(rect, cornerSize);

        rect = { posX + borderThickness, posY + headHeight, boxWidth - borderThickness * 2.0f, boxHeight - headHeight - borderThickness };
        g.setColour(c);
        g.fillRoundedRectangle(rect, cornerSize);

        // draw group name text
        int offset = 2 * static_cast<int>(cornerSize);
        g.setFont(headHeight * 0.85f);
        g.drawText(name, static_cast<int>(posX) + offset, static_cast<int>(posY),
            width - 2 * offset, static_cast<int>(posY) + static_cast<int>(headHeight - (headHeight - headHeight * 0.85f) * 0.5f), Justification::centredRight);
    }

    std::map<Slider*, std::array<Param*, 3>> sliderReg;
    std::map<Button*, ParamStepped<eOnOffToggle>*> toggleReg;
    std::map<ComboBox*, ParamStepped<eModSource>*> comboboxReg;
    std::map<Component*, tHookFn> postUpdateHook;
    std::map<ComboBox*, Param*> noteLengthReg;
    std::map<ComboBox*, Param*> dropDownReg;
    std::map<MouseOverKnob*, std::array<Slider*, 2>> saturnReg; // 2 for each mod amount
    std::map<ComboBox*, std::array<MouseOverKnob*, 3>> saturnSourceReg; // there are up to 3, because of the ADR
    SynthParams &params;
};
