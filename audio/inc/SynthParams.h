
#pragma once

#include "JuceHeader.h"
#include "Param.h"

class SynthParams {
public:
    SynthParams();

    Param freq;  //!< master tune in Hz

    Param lfo1freq; //!< lfo frequency in Hz
    
    Param decayFac; //!< decay in [0.001..60] s

    Param osc1fine;      //!< fine tune in [-100..100] ct
    Param osc1lfo1depth; //!< modulation depth in [-12..12] st

    ParamDb vol; //!< volume in [0..1]

    MidiKeyboardState keyboardState;

    Param delayFeedback;
    Param delayDryWet;
    Param delayTime;
    Param delaySync;

protected:
};


