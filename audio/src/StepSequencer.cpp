/*
  ==============================================================================

    StepSequencer.cpp
    Created: 6 Dec 2015 11:52:33am
    Author:  Nhat

  ==============================================================================
*/

#include "StepSequencer.h"
#include "SynthParams.h"

//==============================================================================
// PUBLIC
//==============================================================================
// contructer & destructer
StepSequencer::StepSequencer(SynthParams &p)
    : params(p)
    , currSeqNote(0)
    , lastPlayedNote(0)
    , seqNoteAdd(1)
    , seqNextStep(0.0)
    , stopNoteTime(0.0)
    , lastPlayHeadPosition(0.0)
    , nextPlaySample(0)
    , noteOffSample(0)
    , seqNoteIsPlaying(false)
    , seqStopped(true)
{
    // save some params in arrays for easier access
    currMidiStepSeq = { &params.seqStep0,
                        &params.seqStep1,
                        &params.seqStep2,
                        &params.seqStep3,
                        &params.seqStep4,
                        &params.seqStep5,
                        &params.seqStep6,
                        &params.seqStep7 };

    currStepOnOff = { &params.seqStepActive0,
                      &params.seqStepActive1,
                      &params.seqStepActive2,
                      &params.seqStepActive3,
                      &params.seqStepActive4,
                      &params.seqStepActive5,
                      &params.seqStepActive6,
                      &params.seqStepActive7 };
    for (int i = 0; i < 8; ++i)
    {
        prevMidiStepSeq[i] = static_cast<int>(currMidiStepSeq[i]->get());
        prevStepOnOff[i] = currStepOnOff[i]->getStep();
    }

    // get GUI params
    seqStepSpeed = params.seqStepSpeed.get();
    seqStepLength = jmin(params.seqStepLength.get(), seqStepSpeed);
    seqNumSteps = static_cast<int>(params.seqNumSteps.get());
}

StepSequencer::~StepSequencer()
{
}
//==============================================================================
void StepSequencer::runSeq(MidiBuffer & midiMessages, int bufferSize, double sampleRate)
{
    // get GUI params
    seqStepSpeed = params.seqStepSpeed.get();
    seqStepLength = jmin(params.seqStepLength.get(), seqStepSpeed);
    seqNumSteps = static_cast<int>(params.seqNumSteps.get());

    if (isTripletActive())
    {
        seqStepSpeed *= 2.0f / 3.0f;
        seqStepLength *= 2.0f / 3.0f;
    }

    switch (params.seqMode.getStep())
    {
    case eSeqModes::eSeqPlay:
        seqNoHostSync(midiMessages, bufferSize, sampleRate);
        break;
    case eSeqModes::eSeqSyncHost:
        seqHostSync(midiMessages);
        break;
    default:
        stopSeq(midiMessages);
        break;
    }
}

void StepSequencer::saveSeqState()
{
    params.writeXMLPatchStandalone(eSerializationParams::eSequencerOnly);
}

void StepSequencer::loadSeqState()
{
    params.readXMLPatchStandalone(eSerializationParams::eSequencerOnly);
}
//==============================================================================
void StepSequencer::stopPlaying()
{
    params.seqMode.setStep(eSeqModes::eSeqStop);
}

void StepSequencer::playNoHost(bool play)
{
    if (params.seqMode.getStep() != eSeqModes::eSeqSyncHost)
    {
        if (play)
        {
            params.seqMode.setStep(eSeqModes::eSeqPlay);
        }
        else
        {
            stopPlaying();
        }
    }
}

void StepSequencer::syncToHost(bool sync)
{
    if (sync)
    {
        params.seqMode.setStep(eSeqModes::eSeqSyncHost);
    }
    else
    {
        stopPlaying();
    }
}

void StepSequencer::playSequential()
{
    params.seqPlayMode.setStep(eSeqPlayModes::eSequential);
}

void StepSequencer::playUpDown(bool play)
{
    if (play)
    {
        params.seqPlayMode.setStep(eSeqPlayModes::eUpDown);
    }
    else
    {
        playSequential();
    }
}

void StepSequencer::playRandom(bool play)
{
    if (play)
    {
        params.seqPlayMode.setStep(eSeqPlayModes::eRandom);
        //setNumSteps(8);
    }
    else
    {
        playSequential();
    }
}
//==============================================================================
void StepSequencer::generateRandomSeq()
{
    for (int i = 0; i < 8; ++i)
    {
        setStepRandom(i);
    }
}

void StepSequencer::setStepRandom(int step)
{
    float min = params.seqRandomMin.get();
    float max = params.seqRandomMax.get();

    Random r = Random();
    r.setSeedRandomly();
    currMidiStepSeq[step]->set(r.nextFloat() * (max - min) + min, true); // TODO: nochmal min und max abchecken (hier oder im panel)
}

void StepSequencer::setStepActive(int step, bool active)
{
    if (active)
    {
        currStepOnOff[jmax(0, jmin(step, 7))]->setStep(eOnOffToggle::eOn);
    }
    else
    {
        currStepOnOff[jmax(0, jmin(step, 7))]->setStep(eOnOffToggle::eOff);
    }
}

void StepSequencer::setNumSteps(int numSteps)
{
    //if (!isPlayRandom())
    //{
        params.seqNumSteps.set(static_cast<float>(jmax(1, jmin(numSteps, 8))));
    //}
}

void StepSequencer::setStepSpeed(float stepSpeed)
{
    params.seqStepSpeed.set(jmax(0.0625f, jmin(stepSpeed, 4.0f)));
}

void StepSequencer::setStepSpeed(const String &stepSpeed)
{
    int denominator = stepSpeed.substring(2).getIntValue();
    setStepSpeed(4.0f / static_cast<float>(denominator));
}

void StepSequencer::setStepLength(float stepLength)
{
    params.seqStepLength.set(jmax(0.0625f, jmin(stepLength, 4.0f)));
}

void StepSequencer::setStepLength(const String &stepLength)
{
    int denominator = stepLength.substring(2).getIntValue();
    setStepLength(4.0f / static_cast<float>(denominator));
}

void StepSequencer::activateTriplets(bool triplets)
{
    if (triplets)
    {
        params.seqTriplets.setStep(eOnOffToggle::eOn);
    }
    else
    {
        params.seqTriplets.setStep(eOnOffToggle::eOff);
    }
}

void StepSequencer::setRandMin(int min)
{
    params.seqRandomMin.set(jmax(0.0f, jmin(static_cast<float>(min), 127.0f)));
}

void StepSequencer::setRandMax(int max)
{
    params.seqRandomMax.set(jmax(0.0f, jmin(static_cast<float>(max), 127.0f)));
}
//==============================================================================
int StepSequencer::getLastSeqNote()
{
    return static_cast<int>(params.seqLastPlayedStep.get());
}

int StepSequencer::getNumStep()
{
    return static_cast<int>(params.seqNumSteps.get());
}

int StepSequencer::getStepNoteAsInt(int step)
{
    return static_cast<int>(currMidiStepSeq[jmax(0, jmin(step, 7))]->get());
}

int StepSequencer::getRandMin()
{
    return static_cast<int>(params.seqRandomMin.get());
}

int StepSequencer::getRandMax()
{
    return static_cast<int>(params.seqRandomMax.get());
}

String StepSequencer::getStepNoteName(int step, bool sharps, bool octaveNumber, int middleC)
{
    return MidiMessage::getMidiNoteName(getStepNoteAsInt(step), sharps, octaveNumber, middleC);
}

String StepSequencer::getStepSpeedAsString()
{
    int denominator = static_cast<int>(4.0f * (1.0f / params.seqStepSpeed.get()));
    return "1/" + String(denominator);
}

String StepSequencer::getStepLengthAsString()
{
    int denominator = static_cast<int>(4.0f * (1.0f / params.seqStepLength.get()));
    return "1/" + String(denominator);
}

String StepSequencer::getRandMinNoteName(bool sharps, bool octaveNumber, int middleC)
{
    return MidiMessage::getMidiNoteName(getRandMin(), sharps, octaveNumber, middleC);
}

String StepSequencer::getRandMaxNoteName(bool sharps, bool octaveNumber, int middleC)
{
    return MidiMessage::getMidiNoteName(getRandMax(), sharps, octaveNumber, middleC);
}
//==============================================================================
bool StepSequencer::isPlaying()
{
    AudioPlayHead::CurrentPositionInfo hostPlayHead = params.positionInfo[params.getAudioIndex()];

    if ((params.seqMode.getStep() == eSeqModes::eSeqPlay) || ((params.seqMode.getStep() == eSeqModes::eSeqSyncHost) && hostPlayHead.isPlaying))
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
    return params.seqMode.getStep() == eSeqModes::eSeqSyncHost;
}

bool StepSequencer::isPlayUpDown()
{
    return params.seqPlayMode.getStep() == eSeqPlayModes::eUpDown;
}

bool StepSequencer::isPlayRandom()
{
    return params.seqPlayMode.getStep() == eSeqPlayModes::eRandom;
}

bool StepSequencer::isTripletActive()
{
    return params.seqTriplets.getStep() == eOnOffToggle::eOn;
}

bool StepSequencer::isStepActive(int step)
{
    return currStepOnOff[jmax(0, jmin(step, 7))]->getStep() == eOnOffToggle::eOn;
}
//==============================================================================
// PRIVATE
//==============================================================================
/**
* Called if stepSequencer plays without host.
*/
void StepSequencer::seqNoHostSync(MidiBuffer& midiMessages, int bufferSize, double sampleRate)
{
    // if is playing a note then prepare sending midi noteOff message
    if (seqNoteIsPlaying)
    {
        // if midi noteOff message fits into current buffer
        if (noteOffSample < bufferSize - 1)
        {
            sendMidiNoteOffMessage(midiMessages, noteOffSample);

            // calculate currSeqNote to play after previous has been stopped
            if (params.seqPlayMode.getStep() == eSeqPlayModes::eUpDown)
            {
                // if last note then play twice and then play reverse order
                if (currSeqNote%seqNumSteps == seqNumSteps - 1)
                {
                    if ((seqNoteAdd == 0) || (seqNoteAdd == 1))
                    {
                        seqNoteAdd--;
                    }
                }
                // if first note then play twice
                else if (currSeqNote%seqNumSteps == 0)
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

            currSeqNote += seqNoteAdd;
            if (currSeqNote < 0)
            {
                currSeqNote = seqNumSteps - 1;
            }
            currSeqNote = currSeqNote%seqNumSteps;
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
            // set upcoming note to play as random
            if (params.seqPlayMode.getStep() == eSeqPlayModes:: eRandom)
            {
                setStepRandom(currSeqNote);
            }

            // if any note changed or is muted then send noteOff message to that note
            midiNoteChanged(midiMessages);

            // send midimessage into midibuffer
            sendMidiNoteOnMessage(midiMessages, nextPlaySample);

            // calculate noteOffSample and nextPlaySample
            double quarterSec = 60.0 / params.positionInfo[params.getAudioIndex()].bpm;
            int diff = bufferSize - 1 - nextPlaySample;
            noteOffSample = static_cast<int>(quarterSec * seqStepLength * sampleRate) - diff;
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

/**
* Called while stepSequencer is synced with host.
*/
void StepSequencer::seqHostSync(MidiBuffer& midiMessages)
{
    AudioPlayHead::CurrentPositionInfo hostPlayHead = params.positionInfo[params.getAudioIndex()];
    double currPos = hostPlayHead.ppqPosition;

    // if host ist playing
    // NOTE: in Cubase 5 hostPlayHead.isPlaying even before actual playhead starts playing,
    //       at the beginning currPos can be negative
    if (hostPlayHead.isPlaying && (currPos >= 0.0))
    {
        // if currPos passes stopNoteTime
        if (currPos >= stopNoteTime)
        {
            if (seqNoteIsPlaying)
            {
                sendMidiNoteOffMessage(midiMessages, 0);
            }
        }

        // if currPos passes seqNextStep or (currPos < lastPlayHeadPosition) implies loop or rewind
        if ((currPos >= seqNextStep) || (currPos < lastPlayHeadPosition))
        {
            // stop note if could not stopped before playing seqNote (important for seqNoteLength == seqStepSpeed)
            if (seqNoteIsPlaying)
            {
                sendMidiNoteOffMessage(midiMessages, 0);
            }

            // calculate note to play
            currSeqNote = jmax(0, static_cast<int>(currPos / static_cast<double>(seqStepSpeed)) % seqNumSteps);
            currSeqNote = jmin(currSeqNote, 7);

            // if play upDown -> for all odd periods, play in reverse order (down sequence)
            if (params.seqPlayMode.getStep() == eSeqPlayModes::eUpDown)
            {
                int upDownSeq = jmax(0, static_cast<int>(currPos / static_cast<double>(seqNumSteps) / static_cast<double>(seqStepSpeed)) % 2);
                if (upDownSeq == 1)
                {
                    currSeqNote = seqNumSteps - 1 - currSeqNote;
                }
            }

            // if is not playing a note then prepare sending midi noteOn message
            if (!seqNoteIsPlaying)
            {
                // set note to play as random
                if (params.seqPlayMode.getStep() == eSeqPlayModes::eRandom)
                {
                    setStepRandom(currSeqNote);
                }

                // if any note changed or is muted then send noteOff message to that note
                midiNoteChanged(midiMessages);

                // send midimessage into midibuffer
                sendMidiNoteOnMessage(midiMessages, 0);

                // calculate next stopNoteTime
                stopNoteTime = currPos + seqStepLength;
            }
        }
        // calculate next seqNextStep and save lastPlayHeadPosition
        double offset = static_cast<double>(seqStepSpeed) - fmod(jmax(0.0, currPos), static_cast<double>(seqStepSpeed));
        seqNextStep = jmax(0.0, currPos) + offset;
        lastPlayHeadPosition = currPos;
        seqStopped = false;
    }
    else
    {
        // if host is not playing then stop sequencer and reset variables
        stopSeq(midiMessages);
    }
}

/**
* Send midi note off message into buffer at given sample position.
*/
void StepSequencer::sendMidiNoteOffMessage(MidiBuffer& midiMessages, int sample)
{
    if (currStepOnOff[static_cast<int>(params.seqLastPlayedStep.get())]->getStep() == eOnOffToggle::eOn)
    {
        MidiMessage m = MidiMessage::noteOff(1, lastPlayedNote);
        midiMessages.addEvent(m, sample);
    }
    seqNoteIsPlaying = false;
}

/**
* Send midi note on message into buffer at given sample position.
*/
void StepSequencer::sendMidiNoteOnMessage(MidiBuffer & midiMessages, int sample)
{
    if (currStepOnOff[currSeqNote]->getStep() == eOnOffToggle::eOn)
    {
        // emphasis on step 1
        float seqVelocity = 0.5f;
        //if (seqNote == 0)
        //{
        //    seqVelocity = 0.85f;
        //}

        MidiMessage m = MidiMessage::noteOn(1, static_cast<int>(currMidiStepSeq[currSeqNote]->get()), seqVelocity);
        midiMessages.addEvent(m, sample);
    }
    seqNoteIsPlaying = true;
    params.seqLastPlayedStep.set(jmax(0.0f, jmin(static_cast<float>(currSeqNote), 7.0f)));
    lastPlayedNote = static_cast<int>(currMidiStepSeq[currSeqNote]->get());
}

/**
* If any seqStepNote changed or is muted then send noteOff message for the old note.
*/
void StepSequencer::midiNoteChanged(MidiBuffer & midiMessages)
{
    for (int i = 0; i < seqNumSteps; ++i)
    {
        // compare with current sequence
        if ((prevMidiStepSeq[i] != static_cast<int>(currMidiStepSeq[i]->get())) || (prevStepOnOff[i] != currStepOnOff[i]->getStep()))
        {
            if (i == static_cast<int>(params.seqLastPlayedStep.get()))
            {
                MidiMessage m = MidiMessage::noteOff(1, prevMidiStepSeq[i]);
                midiMessages.addEvent(m, 0);
            }
        }
    }

    // save new sequence
    for (int i = 0; i < 8; ++i)
    {
        prevMidiStepSeq[i] = static_cast<int>(currMidiStepSeq[i]->get());
        prevStepOnOff[i] = currStepOnOff[i]->getStep();
    }
}

/**
* Stop stepSequencer and reset not GUI variables.
*/
void StepSequencer::stopSeq(MidiBuffer& midiMessages)
{
    // stop and reset only if not already stopped
    if (!seqStopped)
    {
        params.seqLastPlayedStep.set(0.0f);
        currSeqNote = 0;
        lastPlayedNote = 0;
        seqNoteAdd = 1;
        nextPlaySample = 0;
        noteOffSample = 0;
        seqNextStep = 0.0;
        stopNoteTime = 0.0;
        lastPlayHeadPosition = 0.0;
        seqStopped = true;
        seqNoteIsPlaying = false;

        // stop all midimessages from sequencer
        MidiMessage m = MidiMessage::allNotesOff(1);
        midiMessages.addEvent(m, 0);
    }
}
//==============================================================================
