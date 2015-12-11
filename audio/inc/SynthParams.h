#pragma once

#include "JuceHeader.h"
#include "Param.h"
#include <vector>
#include <array>

enum class eLfoWaves : int {
    eLfoSine = 0,
    eLfoSquare = 1,
    eLfoSampleHold = 2,
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

    Param keyVelToEnv;  //!< key velocity influence on env [0 ... 1]
    Param envAttack;    //!< env attack in [0.001..5]s
    Param envDecay;     //!< env decay in [0.001..5]s
    Param envSustain;   //!< env sustain in [0..-96]dB
    Param envRelease;   //!< env release in [0.001..5]s
    Param envAttackShape; //!< env attack shape in [0.01..10]
    Param envDecayShape; //!< env decay shape in [0.01..10]
    Param envReleaseShape; //!< env release shape in [0.01..10]

    Param panDir; //!< pan R/L [-100..100]

    Param ladderCutoff; //!< Cutoff frequency for the ladder Filter [0...20K] Hz
    Param ladderRes; //< resonance gain for the ladder Filter [0...1]

    ParamDb vol; //!< volume in [0..1]

    MidiKeyboardState keyboardState;

    // list of current params, just add your new param here if you want it to be serialized
    std::vector<Param*> serializeParams;

    const float version = 1.1f; // version of the program, to be written into the xml

    void writeXMLPatchHost(MemoryBlock& destData);

    void writeXMLPatchStandalone();

    void fillValueIfExists(XmlElement * patch, String paramName, Param& param);

    void fillValues(XmlElement * patch);

    void readXMLPatchHost(const void * data, int sizeInBytes);

    void readXMLPatchStandalone();

    std::array<AudioPlayHead::CurrentPositionInfo, 2> positionInfo;

    std::atomic<int> positionIndex;
    
    int getGUIIndex();
    int getAudioIndex();

protected:
private:
    void addElement(XmlElement* patch, String name, float value); // adds an element to the XML tree
    void writeXMLPatchTree(XmlElement * patch);
};
