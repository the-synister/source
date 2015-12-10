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

enum class eBiquadFilters : int {
    eLowpass = 0,
    eHighpass = 1
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

    ParamStepped<eBiquadFilters> passtype; //!< passtype that decides whether lowpass, highpass or bandpass filter is used
    
    Param lpCutoff; //!< filter cutoff frequency in Hz
    Param hpCutoff; //!< filter cutoff frequency in Hz
    Param biquadResonance; //! filter resonance in dB

    Param osc1trngAmount; //Triangle Amount [0 ... 1]
    Param osc1PitchRange; //!< range in [0..12] st
    Param osc1pulsewidth;//!< pulse width in [0,01..0,99]

    Param envAttack;    //!< env attack in [0.001..5]s (logarithmic scaling)
    Param envDecay;     //!< env decay in [0.001..5]s (logarithmic scaling)
    Param envSustain;   //!< env sustain in [0..-96]dB
    Param envRelease;   //!< env release in [0.001..5]s (logarithmic scaling)

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
