#pragma once

#include "JuceHeader.h"
#include "Param.h"

class SynthParams {
public:
    SynthParams();
    ~SynthParams();

    Param freq;  //!< master tune in Hz

    Param lfo1freq; //!< lfo frequency in Hz
    Param lfo1wave; //!< lfo wave switch 0 = sine wave or 1 = square wave

    Param osc1fine;      //!< fine tune in [-100..100] ct
    Param osc1coarse;    //!< coarse tune in [-11..11] st
    Param osc1lfo1depth; //!< modulation depth in [-12..12] st
    Param osc1trngAmount; //Triangle Amount [0 ... 1]
    Param osc1PitchRange; //!< range in [0..12] st
    Param osc1pulsewidth;//!< pulse width in [0,01..0,99]

    Param panDir; //!< pan R/L [-100..100]

    ParamDb vol; //!< volume in [0..1]

    MidiKeyboardState keyboardState;

    const float version = 1.1f; // version of the program, to be written into the xml

    void writeXMLPatchHost(MemoryBlock& destData);

    void writeXMLPatchStandalone();

    void fillValueIfExists(XmlElement * patch, String paramName, Param param);

    void fillValues(XmlElement * patch);

    void readXMLPatchHost(const void * data, int sizeInBytes);

    void readXMLPatchStandalone();

    //void readXMLPatch(XmlElement* patch); // fill the synth params with data from a file

protected:
private:
    void addElement(XmlElement* patch, String name, float value); // adds an element to the XML tree
    void writeXMLPatchTree(XmlElement * patch);
};
