/*
  ==============================================================================

    Oscillator.h
    Created: 9 Jan 2016 8:48:22pm
    Author:  Florian (& Anton)

  ==============================================================================
*/

#ifndef OSCILLATOR_H_INCLUDED
#define OSCILLATOR_H_INCLUDED

#include "SynthParams.h"
#include "Param.h"


template<float(*_waveform)(float, float, float)>
class Oscillator {
public:
    float phase;
    float phaseDelta;
    float trngAmount;
    float width;

    Oscillator() : phase(0.f)
        , phaseDelta(0.f)
    {}

    void reset() {
        phase = 0.f;
        phaseDelta = 0.f;
        width = .5f;
        trngAmount = .0f;
    }

    bool isActive() const {
        return phaseDelta > 0.f;
    }

    float next() {
        const float result = _waveform(phase, trngAmount, width);
        phase = std::fmod(phase + phaseDelta, float_Pi * 2.0f);
        return result;
    }

    float next(float pitchMod) {
        const float result = _waveform(phase, trngAmount, width);
        phase = std::fmod(phase + phaseDelta*pitchMod, float_Pi * 2.0f);
        return result;
    }

    float next(float pitchMod, float widthOrTrDelta) {
        const float result = _waveform(phase, trngAmount + widthOrTrDelta, width + widthOrTrDelta);
        phase = std::fmod(phase + phaseDelta*pitchMod, float_Pi * 2.0f);
        return result;
    }
};


struct Waveforms {
    static float sinus(float phs, float trngAmount, float width) {
        ignoreUnused(trngAmount, width);
        return std::sin(phs);
    }
    static float square(float phs, float trngAmount, float width) {
        ignoreUnused(trngAmount, width);
        //square wave with duty cycle
        if (phs < 2.f * float_Pi * width) {
            return 1.f;
        }
        else {
            return -1.f;
        }
        //return std::copysign(1.f, float_Pi - phs);
    }
    static float saw(float phs, float trngAmount, float width) {
        ignoreUnused(width);
        //return (1 - trngAmount) * phs / (float_Pi*2.f) - .5f + trngAmount * (-abs(float_Pi - phs))*(1 / float_Pi) + .5f;
        if (phs < trngAmount*float_Pi) { return (1.f - 2.f / (trngAmount*float_Pi) * phs); }
        else { return (-1.f + 2.f / (2.f*float_Pi - trngAmount*float_Pi) * (phs - trngAmount*float_Pi)); }
    }
    static float whiteNoise(float phs, float trngAmount, float width) {
        ignoreUnused(phs, trngAmount, width);
        return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f)) - 1.f;
    }
};


template<float(*_waveform)(float, float, float)>
class RandomOscillator : public Oscillator<&Waveforms::square>
{
public:
    float heldValue;

    RandomOscillator() : Oscillator()
        , heldValue(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f)) - 1.f)
    {}

    void reset()
    {
        phase = 0.f;
        phaseDelta = 0.f;
        heldValue = 0.f;
    }

    float next()
    {
        if (phase + phaseDelta > 2.0f * float_Pi) {
            heldValue = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f)) - 1.f;
        }

        phase = std::fmod(phase + phaseDelta, float_Pi * 2.0f);
        return heldValue;
    }

    float next(float pitchMod) {
        if (phase + phaseDelta > 2.0f * float_Pi) {
            heldValue = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f)) - 1.f;
        }

        phase = std::fmod(phase + phaseDelta*pitchMod, float_Pi * 2.0f);
        return heldValue;
    }
};


#endif  // OSCILLATOR_H_INCLUDED
