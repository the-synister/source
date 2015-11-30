#include "SynthParams.h"

SynthParams::SynthParams()
: freq("Freq", "Hz", 220.f, 880.f, 440.f)
, lfo1freq("Freq", "Hz", .01f, 50.f, 1.f)
, decayFac("Dur", "", 0.0001f, 0.9999f, 0.0001f)
, lfo1wave("Wave", "", 0.f, 1.f, 0.f)
, osc1fine("f.tune", "ct", -100.f, 100.f, 0.f)
, osc1coarse("c.tune", "st", -11.f, 11.f, 0.f)
, osc1lfo1depth("mod", "st", 0.f, 12.f, 0.f)
, osc1trngAmount("trianlge", "prct", 0.0f, 1.0f, 0.0f)
, osc1PitchRange("Pitch", "st", 0.f, 12.f, 0.f)
, osc1pulsewidth("Width", "prct", 0.01f, 0.99f, 0.5f)
, panDir("Pan", "pct", -100.f, 100.f, 0.f)
, vol("Vol", "dB", 0.f, 1.f, .5f)
, delayDryWet("Dry / Wet", "%", 0.f, 1.f, 0.f)
, delayFeedback("Feedback", "%", 0.f, 1.f, 0.f)
, delayTime("Time", "ms", 1, 5000, 1000)
, delaySync("Tempo Sync", "", 0, 1, 0)
, delayDividend("SyncDel Dividend", "", 1, 4, 1)
, delayDivisor("SyncDel Diviser", "", 1, 16, 1)
, positionInfo()
, positionIndex(0)
, bpm("BPM", "", 0.f, 300.f, 120.f)
{}

SynthParams::~SynthParams()
{
}

int SynthParams::getAudioIndex()
{
    return positionIndex.load();
}

int SynthParams::getGUIIndex()
{
    return (positionIndex.load() + 1) % 2;
}
