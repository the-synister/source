#include "SynthParams.h"

SynthParams::SynthParams()
: freq("Freq", "Hz", 220.f, 880.f, 440.f)
, lfo1freq("Freq", "Hz", .01f, 50.f, 1.f)
, lfo1wave("Wave", "", 0.f, 1.f, 0.f)
, osc1fine("f.tune", "ct", -100.f, 100.f, 0.f)
, osc1coarse("c.tune", "st", -11.f, 11.f, 0.f)
, osc1lfo1depth("mod", "st", 0.f, 12.f, 0.f)
, lpCutoff("LP Cut", "Hz", 10.f, 20000.f, 20000.f)
, lpResonance("LP Reso", "dB", -25.f, 25.f, 0.f)
, osc1trngAmount("trianlge", "prct", 0.0f, 1.0f, 0.0f)
, osc1PitchRange("Pitch", "st", 0.f, 12.f, 0.f)
, envAttack("Attack", "s", 0.001f, 5.0f, 0.005f)
, envDecay("Decay", "s", 0.001f, 5.0f, 0.05f)
, envSustain("Sustain", "dB", -96.0f, 0.0f, -5.0f)
, envRelease("Release", "s", 0.001f, 5.0f, 0.5f)
, osc1pulsewidth("Width", "prct", 0.01f, 0.99f, 0.5f)
, seqMode("SeqMode", "", 0.0f, 2.0f, 0.0f)
, seqNumSteps("SeqNumSteps", "steps", 1.0f, 8.0f, 4.0f)
, seqStepSpeed("SeqSpeed", "qn", 0.125f, 4.0f, 1.0f)
, seqStepLength("SeqNoteLength", "qn", 0.125f, 4.0f, 1.0f)
, seqStep1("seqNote1", "", -1, 127, 60)
, seqStep2("seqNote2", "", -1, 127, 62)
, seqStep3("seqNote3", "", -1, 127, 64)
, seqStep4("seqNote4", "", -1, 127, 65)
, seqStep5("seqNote5", "", -1, 127, 67)
, seqStep6("seqNote6", "", -1, 127, 69)
, seqStep7("seqNote7", "", -1, 127, 71)
, seqStep8("seqNote8", "", -1, 127, 72)
, panDir("Pan", "pct", -100.f, 100.f, 0.f)
, vol("Vol", "dB", 0.f, 1.f, .5f)
, positionIndex(0)
{
    positionInfo[0].resetToDefault();
    positionInfo[1].resetToDefault();
}

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