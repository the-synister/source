#pragma once

#include <atomic>

#include "JuceHeader.h"

class Param {
public:
    Param(const String &name, const String &unit, float minval, float maxval, float defaultval)
    : val_(defaultval)
    , min_(minval)
    , max_(maxval)
    , default_(defaultval)
    , name_(name)
    , unit_(unit)
    {}

    const String& name() const { return name_; }
    const String& unit() const { return unit_; }

    void set(float f) { val_.store(f); }
    float get() const { return val_.load(); }

    //! \todo check min/max!
    void setUI(float f) { set(f); }
    float getUI() const { return get(); }

    float getMin() const { return min_; }
    float getMax() const { return max_; }
    float getDefault() const { return default_; }

    constexpr static float MIN_DB = -96.f;

    static float toDb(float linear) { return linear > 0.f ? 20.f * std::log10(linear) : MIN_DB; }
    static float fromDb(float db) { return db <= MIN_DB ? 0.f : std::pow(10.f, db / 20.f); }

    static float toCent(float factor) { return std::log(factor) / log(2.f)*1200.f; }
    static float fromCent(float ct) { return std::pow(2.f, ct / 1200.f); }

    static float toSemi(float factor) { return std::log(factor)/log(2.f)*12.f; }
    static float fromSemi(float st) { return std::pow(2.f, st / 12.f); }

protected:
    std::atomic<float> val_;
    float min_;
    float max_;
    float default_;
    String name_;
    String unit_;
};

class ParamDb : public Param {
public:
    using Param::Param;

    //! \todo check min/max!
    void setUI(float f) { set(fromDb(f)); }
    float getUI() const { return toDb(get()); }
};

