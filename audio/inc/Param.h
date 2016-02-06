#pragma once

#include <atomic>

#include "JuceHeader.h"


class Param {
public:
    Param(const String &name, const String &serializationTag, const String &hostTag, const String &unit, float minval, float maxval, float defaultval, int numSteps=0)
    : val_(defaultval)
    , min_(minval)
    , max_(maxval)
    , default_(defaultval)
    , name_(name)
    , serializationTag_(serializationTag)
    , hostTag_(hostTag)
    , unit_(unit)
    , numSteps_(numSteps)
    {
        jassert(minval < maxval);
        jassert(minval <= defaultval);
        jassert(defaultval <= maxval);
    }
    virtual ~Param() {}

    const String& name() const { return name_; }
    const String& serializationTag() const { return serializationTag_; }
    const String& hostTag() const { return hostTag_; }
    const String& unit() const { return unit_; }
    int getNumSteps() const { return numSteps_; }

    void set(float f) { val_.store(f); }
    void set(float f, bool) {
        val_.store(f);
        uiDirty.exchange(true);
    }
    float get() const { return val_.load(); }

    virtual void setUI(float f, bool notifyHost = true) {
        if (f >= min_ && f <= max_) {
            set(f);
        } else {
            jassertfalse;
            //set(default_);
        }
        if(notifyHost) listener.call(&Listener::paramUIChanged);
    }
    virtual float getUI() const { return get(); }
    virtual String getUIString() const { return getUIString(get()); }
    virtual String getUIString(float v) const { return String::formatted("%f", v); }
    virtual bool hasLabels() const { return false; }

    float getMin() const { return min_; }
    float getMax() const { return max_; }
    float getDefault() const { return default_; }
    String getUnit() const { return unit_; }

    void setHost(float f) {
        setUI(f, false);
        uiDirty.exchange(true);
    }
    //! get and reset semantics -> this will break if one value is represented twice on the ui
    bool isUIDirty() {
        return uiDirty.exchange(false);
    }

    constexpr static float MIN_DB = -96.f;

    static inline float toDb(float linear) {return linear > 0.f ? 20.f * std::log10(linear) : MIN_DB; }
    static inline float fromDb(float db) { return db <= MIN_DB ? 0.f : std::pow(10.f, db / 20.f); }

    static inline float toCent(float factor) { return std::log(factor) / log(2.f)*1200.f; }
    static inline float fromCent(float ct) { return std::pow(2.f, ct / 1200.f); }

    static inline float toSemi(float factor) { return std::log(factor)/log(2.f)*12.f; }
    static inline float fromSemi(float st) { return std::pow(2.f, st / 12.f); }

    /**
    * @param modRange max modulation in octaves
    */
    static inline float bipolarToFreq(float modValue, float fInput, float modRange) {
        return fInput * std::pow(2.f, modValue * modRange);
    }

#if 0
    static bool isUnipolar(eModSource source) {
        switch (source) {
        case eModSource::eEnv:
            //todo: add all unipolar modulators
            return true;
        case eModSource::eLFO1:
            //todo: add all unipolar modulators
            return false;
        }
        return false;
    }
#endif

    class Listener {
    public:
        virtual ~Listener(){}
        /// @brief only to be called it the param has been changed in the UI
        virtual void paramUIChanged() {}
    };

    void addListener(Listener *newListener) { listener.add(newListener); }
    void removeListener(Listener *aListener) { listener.remove(aListener); }
    
protected:
    ScopedPointer<float> value;
    std::atomic<float> val_;
    float min_;
    float max_;
    float default_;
    String name_;
    String serializationTag_;
    String hostTag_;
    String unit_;
    int numSteps_;

    ListenerList<Listener> listener;
    std::atomic<bool> uiDirty;
};

class ParamDb : public Param {
public:
    ParamDb(const String &name, const String &serializationTag, const String &hostTag, const String &unit, float minval, float maxval, float defaultval)
        : Param(name, serializationTag, hostTag, unit, minval, maxval, fromDb(defaultval))
    {}

    virtual void setUI(float f, bool notifyHost = true) override {
        if (fromDb(f) >= min_ && fromDb(f) <= max_) set(fromDb(f));
        else set(default_);
        if (notifyHost) listener.call(&Listener::paramUIChanged);
    }
    virtual float getUI() const override { return toDb(get()); }
};

template<typename _enum>
class ParamStepped : public Param {
public:
    ParamStepped(const String &name, const String &serializationTag, const String &hostTag, _enum defaultval, const char **labels = nullptr)
    : Param(name, serializationTag, hostTag, "", 0.f, static_cast<float>(_enum::nSteps)-1.f,
            static_cast<float>(defaultval),
            static_cast<int>(_enum::nSteps))
    , step_(defaultval)
    , labelsSet(false)
    {
        const char **lbl = labels;
        for(size_t u = 0; u<labels_.size() && lbl != nullptr && *lbl != nullptr; ++u, ++lbl) {
            labels_[u] = *lbl;
            labelsSet = true;
        }
    }

    //! \todo what about the set method? Make sure that no inconsistent state is created!

    _enum getStep () const {
        return step_.load();
    }
    void setStep (_enum v) {
        step_.store(v);
        set(static_cast<float>(v));
    }

    virtual void setUI(float f, bool notifyHost = true) override {
        set(f);
        int ival = static_cast<int>(std::trunc(f + .5f));
        jassert(ival >= 0 && ival < static_cast<int>(_enum::nSteps));
        step_.store(static_cast<_enum>(ival));
        if (notifyHost) listener.call(&Listener::paramUIChanged);
    }
    virtual String getUIString() const override { return labels_[static_cast<size_t>(getStep())]; }
    virtual String getUIString(float v) const override {
        size_t u = static_cast<size_t>(std::trunc(v+.5f));
        if(u<labels_.size()) {
            return labels_[u];
        } else {
            jassert(false);
            return String::formatted("val%u",u);
        }
    }
    virtual bool hasLabels() const override { return labelsSet; }

protected:
    std::atomic<_enum> step_;
    std::array<String, static_cast<size_t>(_enum::nSteps)> labels_;
    bool labelsSet;
};
