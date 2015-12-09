/*
  ==============================================================================

    StepSequencer.h
    Created: 6 Dec 2015 11:52:10am
    Author:  Nhat

  ==============================================================================
*/

#ifndef STEPSEQUENCER_H_INCLUDED
#define STEPSEQUENCER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "SynthParams.h"

class StepSequencer
{
public:
    //==============================================================================
    StepSequencer(SynthParams &p);
    ~StepSequencer();
    //==============================================================================
    void runSeq(MidiBuffer& midiMessages, int bufferSize, double sampleRate);

private:
    //==============================================================================
    void seqNoHostSync(MidiBuffer& midiMessages, int bufferSize, double sampleRate);
    void seqHostSync(MidiBuffer& midiMessages);
    void midiNoteChanged(MidiBuffer& midiMessages);
    void stopSeq(MidiBuffer& midiMessages);
    //==============================================================================
    SynthParams &params;

    // StepSequencer gui params
    // TODO: start error if high bpm and short steps plays first note twice
    std::array<int, 8> prevMidiSeq;
    std::array<int, 8> currMidiSeq;
    int seqMode;
    int seqNumSteps;
    float seqStepSpeed;
    double seqNoteLength;

    // internal StepSequencer variables
    int seqNote;
    double seqNextStep;
    double stopNoteTime;
    int nextPlaySample;
    int noteOffSample;
    bool seqIsPlaying;
};
#endif  // STEPSEQUENCER_H_INCLUDED