#include "SynthParams.h"

SynthParams::SynthParams()
: freq("Freq", "Hz", 220.f, 880.f, 440.f)

, lfo1freq("Freq", "Hz", .01f, 50.f, 1.f)
, lfo1wave("Wave", "", 0.f, 1.f, 0.f)

, osc1fine("f.tune", "ct", -100.f, 100.f, 0.f)
, osc1coarse("c.tune", "st", -11.f, 11.f, 0.f)
, osc1lfo1depth("mod", "st", 0.f, 12.f, 0.f)
, osc1trngAmount("trianlge", "prct", 0.0f, 1.0f, 0.0f)
, osc1PitchRange("Pitch", "st", 0.f, 12.f, 0.f)
, osc1pulsewidth("Width", "prct", 0.01f, 0.99f, 0.5f)

, keyVelToEnv("keyVel to Env", "", 0.0f, 1.0f, 0.0f)
, envAttack("Attack", "s", 0.001f, 5.0f, 0.005f)
, envDecay("Decay", "s", 0.001f, 5.0f, 0.05f)
, envSustain("Sustain", "dB", -96.0f, 0.0f, -5.0f)
, envRelease("Release", "s", 0.001f, 5.0f, 0.5f)
, envAttackShape("Attack Shape", "", 0.01f, 10.0f, 1.0f)
, envDecayShape("Decay Shape", "", 0.01f, 10.0f, 1.0f)
, envReleaseShape("Release Shape", "", 0.01f, 10.0f, 1.0f)

, panDir("Pan", "pct", -100.f, 100.f, 0.f)
, vol("Vol", "dB", 0.f, 1.f, .5f)
{
}

SynthParams::~SynthParams()
{
}
