#pragma once

#include <atomic>

#include "JuceHeader.h"

class Param {
public:
    Param(const String &name, const String &serializationTag, const String &unit, float minval, float maxval, float defaultval)
    : val_(defaultval)
    , min_(minval)
    , max_(maxval)
    , default_(defaultval)
    , name_(name)
    , serializationTag_(serializationTag)
    , unit_(unit)
    {
        jassert(minval < maxval);
        jassert(minval <= defaultval);
        jassert(defaultval <= maxval);
    }
    virtual ~Param() {}

    const String& name() const { return name_; }
    const String& serializationTag() const { return serializationTag_; }
    const String& unit() const { return unit_; }

    void set(float f) { val_.store(f); }
    float get() const { return val_.load(); }


    virtual void setUI(float f, bool notifyHost = true) {
        if (f >= min_ && f <= max_) set(f);
        else set(default_);
        if(notifyHost) listener.call(&Listener::paramUIChanged);
    }
    virtual float getUI() const { return get(); }

    float getMin() const { return min_; }
    float getMax() const { return max_; }
    float getDefault() const { return default_; }

    void setHost(float f) {
        setUI(f, false);
        uiDirty.exchange(true);
    }
    //! get and reset semantics -> this will break if one value is represented twice on the ui
    bool isUIDirty() {
        return uiDirty.exchange(false);
    }

    constexpr static float MIN_DB = -96.f;

    static float toDb(float linear) {return linear > 0.f ? 20.f * std::log10(linear) : MIN_DB; }
    static float fromDb(float db) { return db <= MIN_DB ? 0.f : std::pow(10.f, db / 20.f); }

    static float toCent(float factor) { return std::log(factor) / log(2.f)*1200.f; }
    static float fromCent(float ct) { return std::pow(2.f, ct / 1200.f); }

    static float toSemi(float factor) { return std::log(factor)/log(2.f)*12.f; }
    static float fromSemi(float st) { return std::pow(2.f, st / 12.f); }

    class Listener {
    public:
        virtual ~Listener(){}
        /// @brief only to be called it the param has been changed in the UI
        virtual void paramUIChanged() {}
    };

    void addListener(Listener *newListener) { listener.add(newListener); }
    void removeListener(Listener *aListener) { listener.remove(aListener); }

protected:
    std::atomic<float> val_;
    float min_;
    float max_;
    float default_;
    String name_;
    String serializationTag_;
    String unit_;

    ListenerList<Listener> listener;
    std::atomic<bool> uiDirty;
};

class ParamDb : public Param {
public:
    using Param::Param;

    virtual void setUI(float f, bool notifyHost = true) override {
        if (fromDb(f) >= min_ && fromDb(f) <= max_) set(fromDb(f));
        else set(default_);
        if (notifyHost) listener.call(&Listener::paramUIChanged);
    }
    virtual float getUI() const override { return toDb(get()); }
};
