
#pragma once

#include "JuceHeader.h"
#include "Param.h"

class SynthParams {
public:
    SynthParams();

    Param freq;  //!< master tune in Hz

    Param lfo1freq; //!< lfo frequency in Hz
    Param lfo1wave; //!< lfo wave switch 0 = sine wave or 1 = square wave
	Param lfo1TempSync; //!< bool if checked or not
	Param noteLength; //!< denominator of selected note length 1/x [1 ... 32]

    Param osc1fine;      //!< fine tune in [-100..100] ct
    Param osc1lfo1depth; //!< modulation depth in [-12..12] st
    Param osc1PitchRange; //!< range in [0..12] st

    Param panDir; //!< pan R/L [-100..100]

    ParamDb vol; //!< volume in [0..1]

    MidiKeyboardState keyboardState;

protected:
};
