
#pragma once

#include "JuceHeader.h"
#include "Param.h"

class SynthParams {
public:
    SynthParams();

    Param freq;  //!< master tune in Hz

    Param lfo1freq; //!< lfo frequency in Hz
    Param lfo1wave; //!< lfo wave switch 0 = sine wave or 1 = square wave

    Param osc1fine;      //!< fine tune in [-100..100] ct
    Param osc1lfo1depth; //!< modulation depth in [-12..12] st
    Param osc1PitchRange; //!< range in [0..12] st

    Param envAttack;    //!< env attack in [0.001..5]s (logarithmic scaling)
    Param envDecay;     //!< env decay in [0.001..5]s (logarithmic scaling)
    Param envSustain;   //!< env sustain in [0..-96]dB
    Param envRelease;   //!< env release in [0.001..5]s (logarithmic scaling)

    Param panDir; //!< pan R/L [-100..100]

    ParamDb vol; //!< volume in [0..1]

    MidiKeyboardState keyboardState;

protected:
};
