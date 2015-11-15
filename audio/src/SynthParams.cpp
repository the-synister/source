
#include "SynthParams.h"

SynthParams::SynthParams()
: freq("Freq", "Hz", 220.f, 880.f, 440.f)
, lfo1freq("Freq", "Hz", .01f, 50.f, 1.f)
, decayFac("Dur", "", 0.0001f, 0.9999f, 0.0001f)
, osc1fine("f.tune", "ct", -100.f, 100.f, 0.f)
, osc1lfo1depth("mod", "st", 0.f, 12.f, 0.f)
, vol("Vol", "dB", 0.f, 1.f, .5f)
, delayDryWet("Dry/Wet", "%", 0.f, 1.f, 0.f)
, delayFeedback("Feedback", "%", 0.f, 1.f, 0.f)
, delayTime("Time", "ms", 1, 2000, 1000)
, delaySync("Tempo Sync", "", 0.f, 1.f, 0.f)
{}