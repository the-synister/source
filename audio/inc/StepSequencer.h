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

    int getCurrentSeqNote();
    int getRandMin();
    int getRandMax();

    void setPlayUpDown(bool play);
    void setPlayRandom(bool play);
    void setRandMin(int min);
    void setRandMax(int max);

    bool isPlaying();
    bool isPlayUpDown();
    bool isPlayRandom();
    bool isNoteMuted(int index);

private:
    //==============================================================================
    void seqNoHostSync(MidiBuffer& midiMessages, int bufferSize, double sampleRate);
    void seqHostSync(MidiBuffer& midiMessages);
    void midiNoteChanged(MidiBuffer& midiMessages);
    void stopSeq(MidiBuffer& midiMessages);
    //==============================================================================
    SynthParams &params;

    // StepSequencer gui params
    std::array<int, 8> prevMidiSeq;
    std::array<int, 8> currMidiSeq;
    std::array<eOnOffToggle, 8> prevOnOffStep;
    std::array<eOnOffToggle, 8> currOnOffStep;
    eSeqModes seqMode;
    int seqNumSteps;
    float seqStepSpeed;
    double seqNoteLength;

    // internal StepSequencer variables
    int seqNote;
    int seqNoteAdd;
    int nextPlaySample;
    int noteOffSample;
    double seqNextStep;
    double stopNoteTime;

    bool seqIsPlaying;
    bool playUpDown;
    bool playRandom;
    int randomMin;
    int randomMax;
};
#endif  // STEPSEQUENCER_H_INCLUDED