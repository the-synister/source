/*
  ==============================================================================

    StepSequencer.cpp
    Created: 6 Dec 2015 11:52:33am
    Author:  Nhat

  ==============================================================================
*/

#include "StepSequencer.h"
#include "Voice.h"
#include "HostParam.h"
#include "SynthParams.h"

//==============================================================================
// contructer & destructer
StepSequencer::StepSequencer(SynthParams &p)
    : params(p)
    , seqNote(-1)
    , seqNextStep(0.0)
    , stopNoteTime(0.0)
    , nextPlaySample(0)
    , noteOffSample(0)
    , seqIsPlaying(false)
{
    // init GUI params
    currMidiSeq[0] = static_cast<int>(params.seqStep1.get());
    currMidiSeq[1] = static_cast<int>(params.seqStep2.get());
    currMidiSeq[2] = static_cast<int>(params.seqStep3.get());
    currMidiSeq[3] = static_cast<int>(params.seqStep4.get());
    currMidiSeq[4] = static_cast<int>(params.seqStep5.get());
    currMidiSeq[5] = static_cast<int>(params.seqStep6.get());
    currMidiSeq[6] = static_cast<int>(params.seqStep7.get());
    currMidiSeq[7] = static_cast<int>(params.seqStep8.get());
    prevMidiSeq = currMidiSeq;

    seqMode = params.seqMode.getStep();
    seqNumSteps = static_cast<int>(params.seqNumSteps.get());
    seqStepSpeed = params.seqStepSpeed.get();
    seqNoteLength = jmin(params.seqStepLength.get(), seqStepSpeed);
}

StepSequencer::~StepSequencer()
{
}
//==============================================================================

/*
* Main function of stepSequencer which should be called in PluginProcessor::processBlock()
*/
void StepSequencer::runSeq(MidiBuffer & midiMessages, int bufferSize, double sampleRate)
{
    // get GUI params
    currMidiSeq[0] = static_cast<int>(params.seqStep1.get());
    currMidiSeq[1] = static_cast<int>(params.seqStep2.get());
    currMidiSeq[2] = static_cast<int>(params.seqStep3.get());
    currMidiSeq[3] = static_cast<int>(params.seqStep4.get());
    currMidiSeq[4] = static_cast<int>(params.seqStep5.get());
    currMidiSeq[5] = static_cast<int>(params.seqStep6.get());
    currMidiSeq[6] = static_cast<int>(params.seqStep7.get());
    currMidiSeq[7] = static_cast<int>(params.seqStep8.get());
    seqMode = params.seqMode.getStep();
    seqNumSteps = static_cast<int>(params.seqNumSteps.get());
    seqStepSpeed = params.seqStepSpeed.get();
    seqNoteLength = jmin(params.seqStepLength.get(), seqStepSpeed);

    // if any note changed then send noteOff message to that note
    midiNoteChanged(midiMessages);
    prevMidiSeq = currMidiSeq;

    switch (seqMode)
    {
    case eSeqModes::seqPlay:
        seqNoHostSync(midiMessages, bufferSize, sampleRate);
        break;
    case eSeqModes::seqSyncHost:
        seqHostSync(midiMessages);
        break;
    default:
        stopSeq(midiMessages);
        break;
    }
}

/*
* Called while stepSequencer is not synced with host.
*/
void StepSequencer::seqNoHostSync(MidiBuffer& midiMessages, int bufferSize, double sampleRate)
{
    // if is playing a note then prepare sending midi noteOff message
    if (seqIsPlaying)
    {
        // if midi noteOff message fits into current buffer
        if (noteOffSample < bufferSize - 1)
        {
            // send midimessage into midibuffer
            if (currMidiSeq[seqNote] != -1)
            {
                MidiMessage m = MidiMessage::noteOff(1, currMidiSeq[seqNote]);
                midiMessages.addEvent(m, noteOffSample);
            }
            seqIsPlaying = false;
        }
        else
        {
            nextPlaySample -= bufferSize - 1;
            noteOffSample -= bufferSize - 1;
        }
    }

    // if is not playing a note then prepare sending midi noteOn message
    if (!seqIsPlaying)
    {
        // if midi noteOn message fits into current buffer
        if (nextPlaySample < bufferSize - 1)
        {
            // set Note to play
            seqNote++;
            seqNote = seqNote%seqNumSteps;

            // emphasis on step 1
            float seqVelocity = 0.5f;
            if (seqNote == 0)
            {
                seqVelocity = 0.85f;
            }

            // send midimessage into midibuffer
            if (currMidiSeq[seqNote] != -1)
            {
                MidiMessage m = MidiMessage::noteOn(1, currMidiSeq[seqNote], seqVelocity);
                midiMessages.addEvent(m, nextPlaySample);
                seqIsPlaying = true;
            }

            // calculate noteOffSample and nextPlaySample
            double quarterSec = 60.0 / params.positionInfo[params.getAudioIndex()].bpm;
            int diff = bufferSize - 1 - nextPlaySample;
            noteOffSample = static_cast<int>(quarterSec * seqNoteLength * sampleRate) - diff;
            nextPlaySample = static_cast<int>(quarterSec * seqStepSpeed * sampleRate) - diff;
        }
        else
        {
            nextPlaySample -= bufferSize - 1;
            noteOffSample -= bufferSize - 1;
        }
    }
}

/*
* Called while stepSequencer is synced with host.
*/
void StepSequencer::seqHostSync(MidiBuffer& midiMessages)
{
    AudioPlayHead::CurrentPositionInfo hostPlayHead = params.positionInfo[params.getAudioIndex()];
    double currPos = hostPlayHead.ppqPosition;

    if (hostPlayHead.isPlaying)
    {
        // time for creating corresponding noteOff event to end each step
        if (currPos >= stopNoteTime)
        {
            // send midimessage into midibuffer
            if (seqIsPlaying)
            {
                if (currMidiSeq[seqNote] != -1)
                {
                    MidiMessage m = MidiMessage::noteOff(1, currMidiSeq[seqNote]);
                    midiMessages.addEvent(m, 0);
                }
                seqIsPlaying = false;
            }
        }

        // time for creating noteOn event
        if (currPos >= seqNextStep)
        {
            // stop note if could not stop before playing next note (important for seqNoteLength == seqStepSpeed)
            if (seqIsPlaying)
            {
                if (currMidiSeq[seqNote] != -1)
                {
                    MidiMessage m = MidiMessage::noteOff(1, currMidiSeq[seqNote]);
                    midiMessages.addEvent(m, 0);
                }
                seqIsPlaying = false;
            }

            // send midimessage into midibuffer
            if (!seqIsPlaying)
            {
                // calculate the right note to play
                seqNote = jmax(0, static_cast<int>(currPos / static_cast<double>(seqStepSpeed)) % seqNumSteps);
                seqNote = jmin(seqNote, seqNumSteps - 1);

                if (currMidiSeq[seqNote] != -1)
                {
                    // emphasis on step 1
                    float seqVelocity = 0.5f;
                    if (seqNote == 0)
                    {
                        seqVelocity = 0.85f;
                    }

                    MidiMessage m = MidiMessage::noteOn(1, currMidiSeq[seqNote], seqVelocity);
                    midiMessages.addEvent(m, 0);
                }
                stopNoteTime = currPos + seqNoteLength;
                seqIsPlaying = true;
            }
        }
    }
    else
    {
        // if host is not playing then stop sequencer and reset variables
        stopSeq(midiMessages);
    }
    // recalculate next step position in host sync mode
    seqNextStep = jmax(0.0, currPos) + abs(remainder(currPos, static_cast<double>(seqStepSpeed)));
}

/*
* If any seqStepNote changed then send noteOff message for the old note.
*/
void StepSequencer::midiNoteChanged(MidiBuffer & midiMessages)
{
    for (int i = 0; i < seqNumSteps; ++i)
    {
        if ((prevMidiSeq[i] != currMidiSeq[i]) && (prevMidiSeq[i] != -1))
        {
            MidiMessage m = MidiMessage::noteOff(1, prevMidiSeq[i]);
            midiMessages.addEvent(m, 0);
        }
    }
}

/*
* Stop stepSequencer and reset not GUI variables.
*/
void StepSequencer::stopSeq(MidiBuffer& midiMessages)
{
    // stop and reset only if not already stopped
    if (seqNote != -1)
    {
        //seqNextStep = 0.0;
        //stopNoteTime = 0.0;
        seqIsPlaying = false;
        seqNote = -1;
        nextPlaySample = 0;
        noteOffSample = 0;

        // stop all midimessages from sequencer
        MidiMessage m = MidiMessage::allNotesOff(1);
        midiMessages.addEvent(m, 0);
    }
}
//==============================================================================
