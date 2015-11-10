
#pragma once

#include "JuceHeader.h"
#include "Param.h"

class SynthParams {
public:
    SynthParams();

    Param freq;  //!< master tune in Hz

    Param lfo1freq; //!< lfo frequency in Hz

    Param osc1fine;      //!< fine tune in [-100..100] ct
    Param osc1lfo1depth; //!< modulation depth in [-12..12] st
    
    Param lpCutoff; //!< filter cutoff frequency in Hz

    ParamDb vol; //!< volume in [0..1]

    MidiKeyboardState keyboardState;

protected:
};
