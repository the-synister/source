#pragma once

#include "JuceHeader.h"
#include "Param.h"
#include <array>

enum class eLfoWaves : int {
    eLfoSine = 0,
    eLfoSquare = 1,
    eLfoSampleHold = 2,
    nSteps = 3
    };
    
enum class eSeqModes : int 
{
    seqStop = 0,
    seqPlay = 1,
    seqSyncHost = 2,
    nSteps = 3
};

class SynthParams {
public:
    SynthParams();
    ~SynthParams();

    Param freq;  //!< master tune in Hz

    Param lfo1freq; //!< lfo frequency in Hz
    ParamStepped<eLfoWaves> lfo1wave; //!< lfo wave switch 0 = sine wave, 1 = random, or 2 = square wave

    Param osc1fine;      //!< fine tune in [-100..100] ct
    Param osc1coarse;    //!< coarse tune in [-11..11] st
    Param osc1lfo1depth; //!< modulation depth in [-12..12] st
    
    Param lpCutoff; //!< filter cutoff frequency in Hz
    Param lpResonance; //! filter resonance in dB

    Param osc1trngAmount; //Triangle Amount [0 ... 1]
    Param osc1PitchRange; //!< range in [0..12] st
    Param osc1pulsewidth;//!< pulse width in [0,01..0,99]

    Param envAttack;    //!< env attack in [0.001..5]s (logarithmic scaling)
    Param envDecay;     //!< env decay in [0.001..5]s (logarithmic scaling)
    Param envSustain;   //!< env sustain in [0..-96]dB
    Param envRelease;   //!< env release in [0.001..5]s (logarithmic scaling)

    ParamStepped<eSeqModes> seqMode; //!< 0 = pause, 1 = play, 2 = sync host
    Param seqNumSteps; //!< number of steps for sequencer [1..8]
    Param seqStepSpeed; //!< interval between each step in [0.125..4] quarter notes
    Param seqStepLength; //!< length of step note in [0.125..seqStepSpeed] quarter notes
    Param seqStep1; //!< midi note as int of step k in [-1..127]
    Param seqStep2; //!< while -1 is indicator for playing no note
    Param seqStep3;
    Param seqStep4;
    Param seqStep5;
    Param seqStep6;
    Param seqStep7;
    Param seqStep8;

    Param panDir; //!< pan R/L [-100..100]

    Param ladderCutoff; //!< Cutoff frequency for the ladder Filter [0...20K] Hz
    Param ladderRes; //< resonance gain for the ladder Filter [0...1]

    ParamDb vol; //!< volume in [0..1]

    MidiKeyboardState keyboardState;

    std::array<AudioPlayHead::CurrentPositionInfo, 2> positionInfo;

    std::atomic<int> positionIndex;
    
    int getGUIIndex();
    int getAudioIndex();
protected:
};
