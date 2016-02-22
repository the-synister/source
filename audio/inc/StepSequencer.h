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
    /**
    * Main stepSequencer call. This function should be called in processBlock() after updating host information.
      runSeq() will internally call the neccessary functions depending on its current state (3 distinct modes).
      Stop: Do nothing; idle state.
      PlayNoHost: Play without needing a host.
      PlaySyncHost: Play with host; will only play if host is playing or recording.
    */
    void runSeq(MidiBuffer& midiMessages, int bufferSize, double sampleRate);

    /**
    * Save current stepSequencer parameters by serializing it in a XML patch tree.
    */
    void saveSeqState();

    /**
    * Load stepSequencer parameters by reading these from a XML patch tree. After loadSeqState() is used,
      resized() should be called to make sure that the GUI is updated properly by using provided getters for stepSequencer parameters.
    */
    void loadSeqState();
    //==============================================================================
    /**
    * Play the sequence in sequential order.
    */
    void playSequential();

    /**
    * Set wether the stepSequencer should play sequence in upDown order, otherwise play sequential.
      Last and first note will be played twice.
      stepSequencer can not play upDown and random simultaneously (does not make much sense).
    */
    void playUpDown(bool play);

    /**
    * Set wether the stepSequencer should play random notes, otherwise play sequential.
      The max and min random note can be set with given functions.
      stepSequencer can not play upDown and random simultaneously (does not make much sense).
    */
    void playRandom(bool play);
    //==============================================================================
    /**
    * Generate a random sequence by setting each step random.
      The lowest and highest random note can be set with provided functions.
    */
    void generateRandomSeq();

    /**
    * Set a specific step note as random. The lowest and highest random note can be set with provided functions.
    @param step the (step+1)th sequence note in range of [0..7]
    */
    void setStepRandom(int step);

    /**
    * Function to set a specific step as activated or mute.
    @param step the (step+1)th sequence note in range of [0..7]
    @param active false->mute
    */
    void setStepActive(int step, bool active);

    /**
    * Set the number of steps for the sequencer.
    @param numSteps in range of [1..8]
    */
    void setNumSteps(int numSteps);

    /**
    * Set step speed with base 1.0f -> 1/4th note length (0.25f -> 1/16th and so on).
    @param stepSpeed in range of [0.0625f..4.0f]
    */
    void setStepSpeed(float stepSpeed);

    /**
    * Set step speed from a string representing note length (e.g 1/4, 1/16 ...).
    @param stepSpeed is assumed to be in the proper format; the function only takes the String after '/',
                     converts it to an int to use that as the denominator.
                     The denominator should be of {1, 2, 4, 8, 16, 32, 64}, the nominator will be ignored.
    */
    void setStepSpeed(const String &stepSpeed);

    /**
    * Set step length with base 1.0f -> 1/4th note length (0.5f -> 1/8th and so on).
    @param stepLength in range of [0.0625f..4.0f]
    */
    void setStepLength(float stepLength);

    /**
    * Set step length from a string representing note length (e.g 1/4, 1/16 ...).
    @param stepLength is assumed to be in the proper format; the function only takes the String after '/',
                      converts it to an int to use that as the denominator.
                      The denominator should be of {1, 2, 4, 8, 16, 32, 64}, the nominator will be ignored.
    */
    void setStepLength(const String &stepLength);

    /**
    * Set whether triplets are activated for step speed and step length. Internally multiply with 2/3.
    */
    void activateTriplets(bool triplets);

    /**
    * Set the lowest midi note value for generating random sequences and playing random notes.
    @param min in range of [0..127]
    */
    void setRandMin(int min);

    /**
    * Set the highest midi note value for generating random sequences and playing random notes.
    @param max in range of [0..127]
    */
    void setRandMax(int max);
    //==============================================================================
    /**
    * Get the last played sequence step in range [0..7]. Can be used to dispay playing position in GUI.
    */
    int getLastSeqNote();

    /**
    * Get the current number of steps in use for the stepSequencee in range [1..8]
    */
    int getNumStep();

    /**
    * Get the midi note value of a specific step.
    @param step in range [0..7]
    */
    int getStepNoteAsInt(int step);

    /**
    * Get the midi note value of the current minimum random note.
    */
    int getRandMin();

    /**
    * Get the midi note value of the current maximum random note.
    */
    int getRandMax();

    /**
    * Get the note name as a string of a specific step by using MidiMessage::getMidiNoteName().
    @param step in range [0..7]
    @param sharps if true use sharps and flats
    @octaveNumber if true display octave number
    @middleC number to use for middle c
    */
    String getStepNoteName(int step, bool sharps, bool octaveNumber, int middleC);

    /**
    * Get current step speed as a string in format '1/denominator'
      with denominator in {1, 2, 4, 8, 16, 32, 64}.
    */
    String getStepSpeedAsString();

    /**
    * Get current step length as a string in format '1/denominator'
      with denominator in {1, 2, 4, 8, 16, 32, 64}.
    */
    String getStepLengthAsString();

    /**
    * Get the note name of the current minimum random note by using MidiMessage::getMidiNoteName().
    @param sharps if true use sharps and flats
    @octaveNumber if true display octave number
    @middleC number to use for middle c
    */
    String getRandMinNoteName(bool sharps, bool octaveNumber, int middleC);

    /**
    * Get the note name of the current maximum random note by using MidiMessage::getMidiNoteName().
    @param sharps if true use sharps and flats
    @octaveNumber if true display octave number
    @middleC number to use for middle c
    */
    String getRandMaxNoteName(bool sharps, bool octaveNumber, int middleC);

    /**
    * Is true if stepSequencer is playing with or without host.
    */
    bool isPlaying();

    /**
    * Is true if stepSequencer is synchronized with host and only playing if host does.
    */
    bool isHostSynced();

    /**
    * Is true if stepSequencer should play in upDown sequence.
    */
    bool isPlayUpDown();

    /**
    * Is true if stepSequencer should play random generated notes.
    */
    bool isPlayRandom();

    /**
    * Is true if triplets are activated for step speed and step length.
    */
    bool isTripletActive();

    /**
    * Is true if specific step is activated and should play.
    @param step in range [0..7]
    */
    bool isStepActive(int step);

private:
    //==============================================================================
    void seqNoHostSync(MidiBuffer& midiMessages, int bufferSize, double sampleRate);
    void seqHostSync(MidiBuffer& midiMessages);
    void sendMidiNoteOffMessage(MidiBuffer& midiMessages, int sample);
    void sendMidiNoteOnMessage(MidiBuffer& midiMessages, int sample);
    void midiNoteChanged(MidiBuffer& midiMessages);
    void stopSeq(MidiBuffer& midiMessages);
    //==============================================================================
    SynthParams &params;

    // StepSequencer gui params
    std::array<int, 8> prevMidiStepSeq;
    std::array<Param*, 8> currMidiStepSeq;
    std::array<eOnOffToggle, 8> prevStepOnOff;
    std::array<ParamStepped<eOnOffToggle>*, 8> currStepOnOff;
    float seqStepSpeed;
    double seqStepLength;
    int seqNumSteps;

    // internal StepSequencer variables
    int currSeqNote;
    int lastPlayedNote;
    int seqNoteAdd;
    int nextPlaySample;
    int noteOffSample;
    double seqNextStep;
    double stopNoteTime;
    double lastPlayHeadPosition;
    bool seqNoteIsPlaying;
    bool seqStopped;
};
#endif  // STEPSEQUENCER_H_INCLUDED
