#pragma once

#include "JuceHeader.h"
#include "Param.h"
#include <array>

class SynthParams {
public:
    SynthParams();
    ~SynthParams();

    Param freq;  //!< master tune in Hz

    Param lfo1freq; //!< lfo frequency in Hz
    Param lfo1wave; //!< lfo wave switch 0 = sine wave, 0.5 = random, or 1 = square wave

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
    
    Param keyVelocityLevel;    //!< key velocity level range in [0..96]dB

    Param panDir; //!< pan R/L [-100..100]

    ParamDb vol; //!< volume in [0..1]

    MidiKeyboardState keyboardState;

    std::array<AudioPlayHead::CurrentPositionInfo, 2> positionInfo;

    std::atomic<int> positionIndex;
    
    int getGUIIndex();
    int getAudioIndex();
protected:
};
