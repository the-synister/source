#pragma once

#include <atomic>

#include "JuceHeader.h"
#include "Param.h"

template<typename _par>
class HostParam : public AudioProcessorParameter, public Param::Listener {
public:
    HostParam(_par &p) : param(p) {
        param.addListener(this);
    }

    ~HostParam() {
        /* Problem in the destruction sequence: 
         * The Param instances belong to SynthParams, a superclass of PluginAudioProcessor
         * The HostParam instances are held in a pointer array that is a private member of 
         * the Juce class AudioProcessor, which is also a superclass of PluginAudioProcessor.
         * 
         * This means that when the destructor of AudioProcessor is called, the Param instances
         * are already gone. We must therefore not access param at HostParam destruction time.
         *
         * A better solution would be clearing AudioProcessor::managedParameters within the 
         * PluginAudioProcessor destructor. This is currently not possible because 
         * managedParameters is private.
         */
        //param.removeListener(this);
    }

    float getValue() const override {
        return engineToHost(param.getUI());
    }

    void setValue(float newValue) override {
        jassert(newValue >= 0.f && newValue <= 1.f);
        param.setHost(hostToEngine(newValue));
    }

    virtual float getDefaultValue() const override {
        return engineToHost(param.getDefault());
    }

    virtual String getName(int maximumStringLength) const override {
        return param.hostTag().substring(0,maximumStringLength);
    }

    virtual String getLabel() const override {
        return param.unit();
    }

    virtual int getNumSteps() const override {
        return param.getNumSteps();
    }

    //! \todo implement this
    virtual float getValueForText(const String& text) const override {
        return text.getFloatValue();
    }

    virtual String getText (float value, int maximumStringLength) const override {
        return param.getUIString(hostToEngine(value)).substring(0, maximumStringLength);
    }

    virtual void paramUIChanged() override {
        // this will (unnecessarily) call setValue
        setValueNotifyingHost(engineToHost(param.getUI()));
    }

protected:
    virtual float engineToHost(float engineVal) const {
        jassert(engineVal >= param.getMin() && engineVal <= param.getMax());
        return (engineVal - param.getMin()) / (param.getMax() - param.getMin());
    }
    virtual float hostToEngine(float hostVal) const {
        jassert(hostVal >= 0.f && hostVal <= 1.f);
        if(param.getNumSteps()==0) {
            return (param.getMin() + hostVal*(param.getMax() - param.getMin()));
        } else {
            return trunc(hostVal*static_cast<float>(param.getNumSteps()-1) + .5f);
        }
    }

    _par &param;
};

template<typename _par>
class HostParamLog : public HostParam<_par> {
public:
    HostParamLog(_par &p, float midPoint) : HostParam<_par>(p) {
        skew = log(0.5f) / log((midPoint - p.getMin()) / (p.getMax() - p.getMin()));
        jassert(skew > 1.f || skew < 1.f);
        jassert(p.getNumSteps() == 0);
    }

protected:
    float skew;

    float engineToHost(float engineVal) const override {
        jassert(engineVal >= HostParam<_par>::param.getMin() && engineVal <= HostParam<_par>::param.getMax());
        float proportion = HostParam<_par>::engineToHost(engineVal);
        // copied from juce::Slider::valueToProportionOfLength
        return pow(proportion, skew);
    }
    float hostToEngine(float hostVal) const override {
        jassert(hostVal >= 0.f && hostVal <= 1.f);
        // copied from juce::Slider::proportionOfLengthToValue
        if (hostVal > 0.f) {
            hostVal = exp(log(hostVal) / skew);
        }
        return HostParam<_par>::hostToEngine(hostVal);
    }
};