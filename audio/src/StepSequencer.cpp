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
    , seqNoteAdd(1)
    , seqNextStep(0.0)
    , stopNoteTime(0.0)
    , currPos(0.0)
    , nextPlaySample(0)
    , noteOffSample(0)
    , seqIsPlaying(false)
    , playUpDown(false)
    , playRandom(false)
    , randomMin(0)
    , randomMax(127)
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
    currOnOffStep[0] = params.seqStepPlay1.getStep();
    currOnOffStep[1] = params.seqStepPlay2.getStep();
    currOnOffStep[2] = params.seqStepPlay3.getStep();
    currOnOffStep[3] = params.seqStepPlay4.getStep();
    currOnOffStep[4] = params.seqStepPlay5.getStep();
    currOnOffStep[5] = params.seqStepPlay6.getStep();
    currOnOffStep[6] = params.seqStepPlay7.getStep();
    currOnOffStep[7] = params.seqStepPlay8.getStep();
    seqMode = params.seqMode.getStep();
    seqNumSteps = static_cast<int>(params.seqNumSteps.get());
    seqStepSpeed = 4.0f / powf(2.0f, 6.0f - params.seqStepSpeedIndex.get());
    seqNoteLength = jmin(4.0f / powf(2.0f, 6.0f - params.seqStepLengthIndex.get()), seqStepSpeed);

    prevMidiSeq = currMidiSeq;
    prevOnOffStep = currOnOffStep;
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
    currOnOffStep[0] = params.seqStepPlay1.getStep();
    currOnOffStep[1] = params.seqStepPlay2.getStep();
    currOnOffStep[2] = params.seqStepPlay3.getStep();
    currOnOffStep[3] = params.seqStepPlay4.getStep();
    currOnOffStep[4] = params.seqStepPlay5.getStep();
    currOnOffStep[5] = params.seqStepPlay6.getStep();
    currOnOffStep[6] = params.seqStepPlay7.getStep();
    currOnOffStep[7] = params.seqStepPlay8.getStep();
    seqMode = params.seqMode.getStep();
    seqNumSteps = static_cast<int>(params.seqNumSteps.get());
    seqStepSpeed = 4.0f / powf(2.0f, 6.0f - params.seqStepSpeedIndex.get());
    seqNoteLength = jmin(4.0f / powf(2.0f, 6.0f - params.seqStepLengthIndex.get()), seqStepSpeed);

    // if any note changed then send noteOff message to that note
    midiNoteChanged(midiMessages);

    switch (seqMode)
    {
    case eSeqModes::seqPlay:
        seqNoHostSync(midiMessages, bufferSize, sampleRate);
        break;
    case eSeqModes::seqSyncHost:
        seqHostSync(midiMessages, bufferSize, sampleRate);
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
            if (currOnOffStep[seqNote] == eOnOffToggle::eOn)
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
            if (playUpDown)
            {
                // if last note then play twice and then play reverse order
                if (seqNote%seqNumSteps == seqNumSteps - 1)
                {
                    if ((seqNoteAdd == 0) || (seqNoteAdd == 1))
                    {
                        seqNoteAdd--;
                    }
                }
                // if first note then play twice
                else if (seqNote%seqNumSteps == 0)
                {
                    if ((seqNoteAdd == 0) || (seqNoteAdd == -1))
                    {
                        seqNoteAdd++;
                    }
                }
                else
                {
                    // if not first or last note then seqNoteAdd must not be 0
                    if (seqNoteAdd == 0)
                    {
                        seqNoteAdd = 1;
                    }
                }
            }
            else
            {
                seqNoteAdd = 1;
            }

            seqNote += seqNoteAdd;
            if (seqNote < 0)
            {
                seqNote = seqNumSteps - 1;
            }

            seqNote = seqNote%seqNumSteps;

            // emphasis on step 1
            float seqVelocity = 0.5f;
            // TODO: maybe velocity for each step?
            //if (seqNote == 0)
            //{
            //    seqVelocity = 0.85f;
            //}

            // send midimessage into midibuffer
            if (currOnOffStep[seqNote] == eOnOffToggle::eOn)
            {
                // set param -> update GUI klappt z.B. s.u.
                // random wie in GUI, immer note + 1 ändern
                //params.seqStep2.set(50 + seqNote % 5, true);

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
void StepSequencer::seqHostSync(MidiBuffer& midiMessages, int bufferSize, double sampleRate)
{
    AudioPlayHead::CurrentPositionInfo hostPlayHead = params.positionInfo[params.getGUIIndex()];
    currPos = hostPlayHead.ppqPosition; // TODO: wenn aus pause wieder starten, dann playhead immer etwas vorher, auch negativ
    if (hostPlayHead.isPlaying && (currPos >= 0.0))
    {
        hostPlayHead.resetToDefault();
        // time for creating corresponding noteOff event to end each step
        if (currPos >= stopNoteTime)
        {
            // send midimessage into midibuffer
            if (seqIsPlaying)
            {
                if (currOnOffStep[seqNote] == eOnOffToggle::eOn)
                {
                    MidiMessage m = MidiMessage::noteOff(1, currMidiSeq[seqNote]);
                    midiMessages.addEvent(m, 0);
                }
                seqIsPlaying = false;
            }
        }
        
        // time for creating noteOn event
        // TODO: am anfang spielt zu viel -> currPos negativ
        // warum geht er hier rein obwohl cussPos negativ und seqNextStep positiv?
        if (currPos >= seqNextStep)
        {
            // stop note if could not stop before playing next note (important for seqNoteLength == seqStepSpeed)
            // TODO: start fehler deswegen, aber wenn weg, dann überspringt noten wenn seqNoteLength == seqStepSpeed
            if (seqIsPlaying)
            {
                if (currOnOffStep[seqNote] == eOnOffToggle::eOn)
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
    
                if (playUpDown)
                {
                    // for all odd periods play reverse order
                    int upDownSeq = jmax(0, static_cast<int>(currPos / static_cast<double>(seqNumSteps) / static_cast<double>(seqStepSpeed)) % 2);
                    if (upDownSeq == 1)
                    {
                        seqNote = seqNumSteps - 1 - seqNote;
                    }
                }
    
                if (currOnOffStep[seqNote] == eOnOffToggle::eOn)
                {
                    // emphasis on step 1
                    float seqVelocity = 0.5f;
                    //if (seqNote == 0)
                    //{
                    //    seqVelocity = 0.85f;
                    //}
    
                    MidiMessage m = MidiMessage::noteOn(1, currMidiSeq[seqNote], seqVelocity);
                    midiMessages.addEvent(m, 0);
                }

                seqIsPlaying = true;
                stopNoteTime = currPos + seqNoteLength;
            }
        }
    }
    else
    {
        // if host is not playing then stop sequencer and reset variables
        stopSeq(midiMessages);
    }

    // recalculate next step position in host sync mode
    seqNextStep = jmax(0.0, currPos + fmod(jmax(0.0, currPos), static_cast<double>(seqStepSpeed)));
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //// another approach (sample), manchmal überspringt eine note aus???
    //AudioPlayHead::CurrentPositionInfo hostPlayHead = params.positionInfo[params.getGUIIndex()];
    //currPos = hostPlayHead.ppqPosition;
    //int timeInSamples = static_cast<int>(hostPlayHead.timeInSamples);
    //double quarterSec = 60.0 / hostPlayHead.bpm;

    //if (hostPlayHead.isPlaying)
    //{
    //    // if midi noteOff message fits into current buffer
    //    if (noteOffSample - timeInSamples <= bufferSize - 1)
    //    {
    //        // if is playing a note then prepare sending midi noteOff message
    //        if (seqIsPlaying)
    //        {
    //            // send midimessage into midibuffer
    //            if (currOnOffStep[seqNote] == eOnOffToggle::eOn)
    //            {
    //                MidiMessage m = MidiMessage::noteOff(1, currMidiSeq[seqNote]);
    //                midiMessages.addEvent(m, noteOffSample - timeInSamples);
    //            }
    //            seqIsPlaying = false;
    //        }
    //    }

    //    // if midi noteOn message fits into current buffer
    //    if (nextPlaySample - timeInSamples <= bufferSize - 1)
    //    {
    //        // if note is still playing then send midi noteOff message
    //        if (seqIsPlaying)
    //        {
    //            // send midimessage into midibuffer
    //            if (currOnOffStep[seqNote] == eOnOffToggle::eOn)
    //            {
    //                MidiMessage m = MidiMessage::noteOff(1, currMidiSeq[seqNote]);
    //                midiMessages.addEvent(m, 0);
    //            }
    //            seqIsPlaying = false;
    //        }

    //        // if is not playing a note then prepare sending midi noteOn message
    //        if (!seqIsPlaying)
    //        {
    //            // calculate the right note to play
    //            seqNote = jmax(0, static_cast<int>(jmax(0.0, currPos) / static_cast<double>(seqStepSpeed)) % seqNumSteps);
    //            seqNote = jmin(seqNote, seqNumSteps - 1);

    //            if (playUpDown)
    //            {
    //                // for all odd periods play reverse order
    //                int upDownSeq = jmax(0, static_cast<int>(currPos / static_cast<double>(seqNumSteps) / static_cast<double>(seqStepSpeed)) % 2);
    //                if (upDownSeq == 1)
    //                {
    //                    seqNote = seqNumSteps - 1 - seqNote;
    //                }
    //            }

    //            // emphasis on step 1
    //            float seqVelocity = 0.5f;
    //            // TODO: maybe velocity for each step?
    //            //if (seqNote == 0)
    //            //{
    //            //    seqVelocity = 0.85f;
    //            //}

    //            // send midimessage into midibuffer
    //            if (currOnOffStep[seqNote] == eOnOffToggle::eOn)
    //            {
    //                MidiMessage m = MidiMessage::noteOn(1, currMidiSeq[seqNote], seqVelocity);
    //                midiMessages.addEvent(m, nextPlaySample - timeInSamples);
    //            }

    //            // calculate noteOffSample
    //            int diff = bufferSize - 1 - (nextPlaySample - timeInSamples);
    //            noteOffSample = timeInSamples + static_cast<int>(quarterSec * seqNoteLength * sampleRate) - diff;
    //            seqIsPlaying = true;
    //        }
    //    }
    //}
    //else
    //{
    //    // if host is not playing then stop sequencer and reset variables
    //    stopSeq(midiMessages);
    //}

    //// calculate nextPlaySample 
    //nextPlaySample = timeInSamples + timeInSamples%static_cast<int>(quarterSec * seqStepSpeed * sampleRate);
    ////noteOffSample = timeInSamples + static_cast<int>(quarterSec * seqNoteLength * sampleRate) + timeInSamples%static_cast<int>(quarterSec * seqStepSpeed * sampleRate);
}

/*
* If any seqStepNote changed then send noteOff message for the old note.
*/
void StepSequencer::midiNoteChanged(MidiBuffer & midiMessages)
{
    for (int i = 0; i < seqNumSteps; ++i)
    {
        if ((prevMidiSeq[i] != currMidiSeq[i]) || (prevOnOffStep[i] != currOnOffStep[i]))
        {
            if (i == seqNote)
            {
                MidiMessage m = MidiMessage::noteOff(1, prevMidiSeq[i]);
                midiMessages.addEvent(m, 0);
            }
        }
    }
    prevMidiSeq = currMidiSeq;
    prevOnOffStep = currOnOffStep;
}

/*
* Stop stepSequencer and reset not GUI variables.
*/
void StepSequencer::stopSeq(MidiBuffer& midiMessages)
{
    // stop and reset only if not already stopped
    if (seqNote != -1)
    {
        seqNextStep = 0.0;
        stopNoteTime = 4.0;
        currPos = 0.0;
        seqIsPlaying = false;
        seqNote = -1;
        seqNoteAdd = 1;
        nextPlaySample = 0;
        noteOffSample = 0;

        // stop all midimessages from sequencer
        MidiMessage m = MidiMessage::allNotesOff(1);
        midiMessages.addEvent(m, 0);
    }
}

/*
* Getter for SeqPanel
*/
int StepSequencer::getCurrentSeqNote()
{
    return seqNote;
}

int StepSequencer::getRandMin()
{
    return randomMin;
}

int StepSequencer::getRandMax()
{
    return randomMax;
}

// for debug
double StepSequencer::getPos()
{
    return currPos;
}

/*
* Setter for SeqPanel
*/
void StepSequencer::setPlayUpDown(bool play)
{
    playUpDown = play;
}

void StepSequencer::setPlayRandom(bool play)
{
    playRandom = play;
}

void StepSequencer::setRandMin(int min)
{
    randomMin = jmin(127, jmax(0, min));
}

void StepSequencer::setRandMax(int max)
{
    randomMax = jmin(127, jmax(0, max));
}


/*
* Get Booleans for seqPanel
*/
bool StepSequencer::isPlaying()
{
    AudioPlayHead::CurrentPositionInfo hostPlayHead = params.positionInfo[params.getAudioIndex()];

    if ((seqMode == eSeqModes::seqPlay) || ((seqMode == eSeqModes::seqSyncHost && hostPlayHead.isPlaying)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool StepSequencer::isPlayUpDown()
{
    return playUpDown;
}

bool StepSequencer::isPlayRandom()
{
    return playRandom;
}

bool StepSequencer::isNoteMuted(int index)
{
    int i = jmax(0, jmin(index, 7));
    return currOnOffStep[i] == eOnOffToggle::eOff;
}
//==============================================================================