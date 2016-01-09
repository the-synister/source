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


enum class eBiquadFilters : int {
    eLowpass = 0,
    eHighpass = 1,
    nSteps = 2
};
    
enum class eOnOffToggle : int {
    eOff = 0,
    eOn = 1,
    nSteps = 2
};

enum class eSeqModes : int 
{
    seqStop = 0,
    seqPlay = 1,
    seqSyncHost = 2,
    nSteps = 3
};

enum class eModSource : int {
    eNone = 0,
    eLFO1 = 1,
    nSteps = 2
};


class SynthParams {
public:
    SynthParams();
    ~SynthParams();

    Param freq;  //!< master tune in Hz

    Param lfo1freq; //!< lfo frequency in Hz
    ParamStepped<eLfoWaves> lfo1wave; //!< lfo wave switch 0 = sine wave, 1 = random, or 2 = square wave

    Param lfoFadein;   // The LFOs fade in with a range of [0..10s]

    Param osc1fine;      //!< fine tune in [-100..100] ct
    Param osc1coarse;    //!< coarse tune in [-11..11] st
    Param osc1lfo1depth; //!< modulation depth in [-12..12] st

    ParamStepped<eBiquadFilters> passtype; //!< passtype that decides whether lowpass, highpass or bandpass filter is used
    Param lpCutoff; //!< filter cutoff frequency in Hz
    Param hpCutoff; //!< filter cutoff frequency in Hz
    Param biquadResonance; //! filter resonance in dB
    ParamStepped<eModSource> lpModSource;  //! filter moduluation source
    Param lpModAmout;   //! filter moduluation amount

    Param osc1trngAmount; //Triangle Amount [0 ... 1]
    Param osc1PitchRange; //!< range in [0..12] st
    Param osc1pulsewidth;//!< pulse width in [0,01..0,99]

    Param keyVelToEnv;  //!< key velocity influence on env [0 ... 1]
    Param envAttack;    //!< env attack in [0.001..5]s
    Param envDecay;     //!< env decay in [0.001..5]s
    Param envSustain;   //!< env sustain in [0..-96]dB
    Param envRelease;   //!< env release in [0.001..5]s (logarithmic scaling)
    
    Param keyVelocityLevel;    //!< key velocity level range in [0..96]dB
    
    Param envAttackShape; //!< env attack shape in [0.01..10]
    Param envDecayShape; //!< env decay shape in [0.01..10]
    Param envReleaseShape; //!< env release shape in [0.01..10]

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

    Param osc1WaveForm;//!< int value for defining waveform [1..3]

    Param panDir; //!< pan R/L [-100..100]

    Param ladderCutoff; //!< Cutoff frequency for the ladder Filter [0...20K] Hz
    Param ladderRes; //< resonance gain for the ladder Filter [0...1]

    ParamDb vol; //!< volume in [0..1]

    MidiKeyboardState keyboardState;

    Param delayFeedback;    //!< delay feedback amount
    Param delayDryWet;      //!< delay wet signal
    Param delayTime;        //!< delay time in ms
    ParamStepped<eOnOffToggle> delaySync;        //!< sync / manual toggle
    Param delayDividend;    //!< sync dividend
    Param delayDivisor;     //!< sync divisor
    Param delayCutoff;       //!< delay Cutoff Frequency
    Param delayResonance;   //!< delay Resonance Frequency
    ParamStepped<eOnOffToggle> delayTriplet;        //!< delay triplet toggle
    ParamStepped<eOnOffToggle> delayRecordFilter;   //!< delay filter record toggle
    ParamStepped<eOnOffToggle> delayReverse;        //!< delay reverse modo toggle

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
