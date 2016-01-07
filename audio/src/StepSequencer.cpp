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
    , seqNote(0)
    , lastPlayedNote(1)
    , seqNoteAdd(1)
    , seqNextStep(0.0)
    , stopNoteTime(0.0)
    , seqStopped(true)
    , nextPlaySample(0)
    , noteOffSample(0)
    , seqNoteIsPlaying(false)
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
    seqPlayMode = params.seqPlayMode.getStep();
    seqNumSteps = static_cast<int>(params.seqNumSteps.get());
    seqStepSpeed = 4.0f / powf(2.0f, 6.0f - params.seqStepSpeedIndex.get());
    seqNoteLength = jmin(4.0f / powf(2.0f, 6.0f - params.seqStepLengthIndex.get()), seqStepSpeed);
    randomMin = static_cast<int>(params.seqRandomMin.get());
    randomMax = static_cast<int>(params.seqRandomMax.get());

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
    seqPlayMode = params.seqPlayMode.getStep();
    seqNumSteps = static_cast<int>(params.seqNumSteps.get());
    seqStepSpeed = 4.0f / powf(2.0f, 6.0f - params.seqStepSpeedIndex.get()); // TODO: besseres konzept überlegen als indezes
    seqNoteLength = jmin(4.0f / powf(2.0f, 6.0f - params.seqStepLengthIndex.get()), seqStepSpeed);
    randomMin = static_cast<int>(params.seqRandomMin.get());
    randomMax = static_cast<int>(params.seqRandomMax.get());

    // if any note changed then send noteOff message to that note
    midiNoteChanged(midiMessages);

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

void StepSequencer::generateRandomSeq()
{
    Random r = Random();
    r.setSeedRandomly();
    params.seqStep1.set(r.nextFloat() * static_cast<float>(randomMax - randomMin) + static_cast<float>(randomMin), true);
    r.setSeedRandomly();
    params.seqStep2.set(r.nextFloat() * static_cast<float>(randomMax - randomMin) + static_cast<float>(randomMin), true);
    r.setSeedRandomly();
    params.seqStep3.set(r.nextFloat() * static_cast<float>(randomMax - randomMin) + static_cast<float>(randomMin), true);
    r.setSeedRandomly();
    params.seqStep4.set(r.nextFloat() * static_cast<float>(randomMax - randomMin) + static_cast<float>(randomMin), true);
    r.setSeedRandomly();
    params.seqStep5.set(r.nextFloat() * static_cast<float>(randomMax - randomMin) + static_cast<float>(randomMin), true);
    r.setSeedRandomly();
    params.seqStep6.set(r.nextFloat() * static_cast<float>(randomMax - randomMin) + static_cast<float>(randomMin), true);
    r.setSeedRandomly();
    params.seqStep7.set(r.nextFloat() * static_cast<float>(randomMax - randomMin) + static_cast<float>(randomMin), true);
    r.setSeedRandomly();
    params.seqStep8.set(r.nextFloat() * static_cast<float>(randomMax - randomMin) + static_cast<float>(randomMin), true);
}

/*
* Called while stepSequencer is not synced with host.
*/
void StepSequencer::seqNoHostSync(MidiBuffer& midiMessages, int bufferSize, double sampleRate)
{
    // if is playing a note then prepare sending midi noteOff message
    if (seqNoteIsPlaying)
    {
        // if midi noteOff message fits into current buffer
        if (noteOffSample < bufferSize - 1)
        {
            // send midimessage into midibuffer
            if (currOnOffStep[lastPlayedNote] == eOnOffToggle::eOn)
            {
                MidiMessage m = MidiMessage::noteOff(1, currMidiSeq[lastPlayedNote]);
                midiMessages.addEvent(m, noteOffSample);
            }
            seqNoteIsPlaying = false;
        }
        else
        {
            nextPlaySample -= bufferSize - 1;
            noteOffSample -= bufferSize - 1;
        }
    }

    // if is not playing a note then prepare sending midi noteOn message
    if (!seqNoteIsPlaying)
    {
        // if midi noteOn message fits into current buffer
        if (nextPlaySample < bufferSize - 1)
        {
            if (seqPlayMode == eSeqPlayModes::random)
            {
                // TOOD: set random param.step -> update GUI klappt z.B. s.u.
                // random wie in GUI, immer note + 1 ändern
                // wie im seqPanel array aus params erstellen
                //params.seqStep2.set(50 + seqNote % 5, true);

                //// set next random note
                //if (seq->isPlayRandom())
                //{
                //    Random r = Random();
                //    r.setSeedRandomly();
                //    int steps = static_cast<int>(params.seqNumSteps.get());
                //    seqStepArray[(lastSeqNotePos + 1) % steps]->setValue(r.nextDouble() * (seq->getRandMax() - seq->getRandMin()) + seq->getRandMin());
                //}
            }

            // emphasis on step 1
            float seqVelocity = 0.5f; // TODO: maybe velocity for each step?
            //if (seqNote == 0)
            //{
            //    seqVelocity = 0.85f;
            //}

            // send midimessage into midibuffer
            if (currOnOffStep[seqNote] == eOnOffToggle::eOn)
            {
                MidiMessage m = MidiMessage::noteOn(1, currMidiSeq[seqNote], seqVelocity);
                midiMessages.addEvent(m, nextPlaySample);
            }
            seqNoteIsPlaying = true;
            lastPlayedNote = seqNote;

            // calculate next seqNote to play after previous has been stopped
            if (seqPlayMode == eSeqPlayModes::upDown)
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
    seqStopped = false;
}

/*
* Called while stepSequencer is synced with host.
*/
void StepSequencer::seqHostSync(MidiBuffer& midiMessages)
{
    AudioPlayHead::CurrentPositionInfo hostPlayHead = params.positionInfo[params.getGUIIndex()];
    double currPos = hostPlayHead.ppqPosition;

    // if host ist playing
    // NOTE: in Cubase 5 hostPlayHead.isPlaying is true even before actual playhead starts playing,
    //       at the beginning currPos can be negative
    if (hostPlayHead.isPlaying && (currPos >= 0.0)) 
    {
        // time to stop lastPlayedNote
        if (currPos >= stopNoteTime)
        {
            if (seqNoteIsPlaying)
            {
                if (currOnOffStep[lastPlayedNote] == eOnOffToggle::eOn)
                {
                    MidiMessage m = MidiMessage::noteOff(1, currMidiSeq[lastPlayedNote]);
                    midiMessages.addEvent(m, 0);
                }
                seqNoteIsPlaying = false;
            }
        }

        // time to play next note
        if (currPos >= seqNextStep)
        {
            // play only if note to play changed OR play same note if (playUpDown or seqNumSteps == 1)
            if ((seqNote != lastPlayedNote) || (seqNote == lastPlayedNote && (seqPlayMode == eSeqPlayModes::upDown || (seqNumSteps == 1)))) // TODO: spielt am anfang zu viel, voriges problem
            {
                if (seqPlayMode == eSeqPlayModes::random)
                {
                    // TOOD: set random param.step -> update GUI klappt z.B. s.u.
                    // random wie in GUI, immer note + 1 ändern
                    // wie im seqPanel array aus params erstellen
                    //params.seqStep2.set(50 + seqNote % 5, true);

                    //// set next random note
                    //if (seq->isPlayRandom())
                    //{
                    //    Random r = Random();
                    //    r.setSeedRandomly();
                    //    int steps = static_cast<int>(params.seqNumSteps.get());
                    //    seqStepArray[(lastSeqNotePos + 1) % steps]->setValue(r.nextDouble() * (seq->getRandMax() - seq->getRandMin()) + seq->getRandMin());
                    //}
                }

                // stop note if could not stopped before playing seqNote (important for seqNoteLength == seqStepSpeed)
                if (seqNoteIsPlaying)
                {
                    if (currOnOffStep[lastPlayedNote] == eOnOffToggle::eOn)
                    {
                        MidiMessage m = MidiMessage::noteOff(1, currMidiSeq[lastPlayedNote]);
                        midiMessages.addEvent(m, 0);
                    }
                    seqNoteIsPlaying = false;
                }

                if (!seqNoteIsPlaying)
                {
                    if (currOnOffStep[seqNote] == eOnOffToggle::eOn)
                    {
                        // emphasis on step 1
                        float seqVelocity = 0.5f; // TODO: maybe velocity for each step?
                        //if (seqNote == 0)
                        //{
                        //    seqVelocity = 0.85f;
                        //}

                        MidiMessage m = MidiMessage::noteOn(1, currMidiSeq[seqNote], seqVelocity);
                        midiMessages.addEvent(m, 0);
                    }
                    seqNoteIsPlaying = true;
                    lastPlayedNote = jmax(0, jmin(seqNote, seqNumSteps - 1));

                    // calculate upcoming stopNoteTime
                    stopNoteTime = currPos + seqNoteLength;
                }
            }
        }
        seqStopped = false;
    }
    else
    {
        // if host is not playing then stop sequencer and reset variables
        stopSeq(midiMessages);
    }

    // always recalculate seqNextStep and seqNote
    if (currPos >= 0.0)
    {
        // calculate note to play
        seqNote = jmax(0, static_cast<int>(currPos / static_cast<double>(seqStepSpeed)) % seqNumSteps);
        seqNote = jmin(seqNote, seqNumSteps - 1);

        // for all odd periods play in reverse order (down sequence)
        if (seqPlayMode == eSeqPlayModes::upDown)
        {
            int upDownSeq = jmax(0, static_cast<int>(currPos / static_cast<double>(seqNumSteps) / static_cast<double>(seqStepSpeed)) % 2);
            if (upDownSeq == 1)
            {
                seqNote = seqNumSteps - 1 - seqNote;
            }
        }

        // calculate next seqNextStep while seqMode = eSeqModes::seqSyncHost; for forward, rewind or jump of hostPlayHead
        seqNextStep = jmax(0.0, currPos) + fmod(jmax(0.0, currPos), static_cast<double>(seqStepSpeed));
    }
}

/*
* If any seqStepNote changed or is muted then send noteOff message for the old note.
*/
void StepSequencer::midiNoteChanged(MidiBuffer & midiMessages)
{
    for (int i = 0; i < seqNumSteps; ++i)
    {
        if ((prevMidiSeq[i] != currMidiSeq[i]) || (prevOnOffStep[i] != currOnOffStep[i]))
        {
            if (i == lastPlayedNote)
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
    if (!seqStopped)
    {
        seqNote = 0;
        lastPlayedNote = 1; // set different than seqNote due to hostSync
        seqNoteAdd = 1;
        nextPlaySample = 0;
        noteOffSample = 0;
        seqNextStep = 0.0;
        stopNoteTime = 0.0;
        seqStopped = true;
        seqNoteIsPlaying = false;

        // stop all midimessages from sequencer
        MidiMessage m = MidiMessage::allNotesOff(1);
        midiMessages.addEvent(m, 0);
    }
}

/*
* Getter for SeqPanel
*/
int StepSequencer::getLastPlayedNote()
{
    return lastPlayedNote;
}

int StepSequencer::getNumStep()
{
    return seqNumSteps;
}

int StepSequencer::getRandMin()
{
    return randomMin;
}

int StepSequencer::getRandMax()
{
    return randomMax;
}

void StepSequencer::playNoHost()
{
    if (seqMode != eSeqModes::seqSyncHost)
    {
        params.seqMode.setStep(eSeqModes::seqPlay);
    }
}

void StepSequencer::syncToHost()
{
    params.seqMode.setStep(eSeqModes::seqSyncHost);
}

void StepSequencer::stopPlaying()
{
    params.seqMode.setStep(eSeqModes::seqStop);
}

void StepSequencer::playSequential()
{
    params.seqPlayMode.setStep(eSeqPlayModes::sequential);
}

/*
* Setter for SeqPanel
*/
void StepSequencer::playUpDown()
{
    params.seqPlayMode.setStep(eSeqPlayModes::upDown);
}

void StepSequencer::playRandom()
{
    params.seqPlayMode.setStep(eSeqPlayModes::random);
    params.seqNumSteps.set(8.0f);
}

void StepSequencer::setRandMin(int min)
{
    params.seqRandomMin.set(jmin(127.0f, jmax(0.0f, static_cast<float>(min))));
}

void StepSequencer::setRandMax(int max)
{
    params.seqRandomMax.set(jmin(127.0f, jmax(0.0f, static_cast<float>(max))));
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

bool StepSequencer::isHostSynced()
{
    return seqMode == eSeqModes::seqSyncHost;
}

bool StepSequencer::isPlayUpDown()
{
    return seqPlayMode == eSeqPlayModes::upDown;
}

bool StepSequencer::isPlayRandom()
{
    return seqPlayMode == eSeqPlayModes::random;
}

bool StepSequencer::isNoteMuted(int index)
{
    int i = jmax(0, jmin(index, seqNumSteps -1));
    return currOnOffStep[i] == eOnOffToggle::eOff;
}
//==============================================================================