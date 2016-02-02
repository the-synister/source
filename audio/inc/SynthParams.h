#pragma once

#include "JuceHeader.h"
#include "Param.h"
#include <vector>
#include <array>

enum class eSerializationParams : int {
    eAll = 0,
    eSequencerOnly = 1
};

enum class eLfoWaves : int {
    eLfoSine = 0,
    eLfoSquare = 1,
    eLfoSampleHold = 2,
    nSteps = 3
    };

enum class eOscWaves : int {
    eOscSquare = 0,
    eOscSaw    = 1,
    eOscNoise  = 2,
    nSteps     = 3
};

enum class eBiquadFilters : int {
    eLowpass = 0,
    eHighpass = 1,
    eBandpass = 2,
    nSteps = 3
};

enum class eOnOffToggle : int {
    eOff = 0,
    eOn = 1,
    nSteps = 2
};

enum class eSeqModes : int {
    eSeqStop = 0,
    eSeqPlay = 1,
    eSeqSyncHost = 2,
    nSteps = 3
};

enum class eSeqPlayModes : int {
    eSequential = 0,
    eUpDown = 1,
    eRandom = 2,
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
    ParamStepped<eOnOffToggle> lfo1TempSync; //!< bool if checked or not
    Param noteLength; //!< denominator of selected note length 1/x [1 ... 32]
    ParamStepped<eLfoWaves> lfo1wave; //!< lfo wave switch 0 = sine wave, 1 = random, or 2 = square wave

    Param lfoFadein;   // The LFOs fade in with a range of [0..10s]

    //Param lfoChorfreq; // delay-lfo frequency in Hz
    //Param chorAmount; // wetness of signal [0 ... 1]
    //Param chorSwitch; // Chorus on / off [1 / 0]

    Param osc1fine;      //!< fine tune in [-100..100] ct
    Param osc1coarse;    //!< coarse tune in [-11..11] st
    Param osc1lfo1depth; //!< modulation depth in [-12..12] st

    ParamStepped<eBiquadFilters> passtype; //!< passtype that decides whether lowpass, highpass or bandpass filter is used
    Param lpCutoff; //!< filter cutoff frequency in Hz
    Param hpCutoff; //!< filter cutoff frequency in Hz
    Param biquadResonance; //! filter resonance in dB
    ParamStepped<eModSource> lpModSource;  //! lp filter modulation source
    Param lpModAmount;   //! lp filter modulation amount
    ParamStepped<eModSource> hpModSource;  //! hp filter modulation source
    Param hpModAmount;   //! hp filter modulation amount

    ParamStepped<eOscWaves> osc1Waveform; //! waveform of the oscillator, it can be either square, saw, or noise

    Param osc1trngAmount; //Triangle Amount [0 ... 1]
    Param osc1PitchRange; //!< range in [0..12] st
    Param osc1pulsewidth; //!< pulse width in [0,01..0,99]
    Param osc1AmountWidthMod; //!< amount of pulse width modulation [0..1]

    Param keyVelToEnv;  //!< key velocity influence on env [0 ... 1]
    Param envAttack;    //!< env attack in [0.001..5]s
    Param envDecay;     //!< env decay in [0.001..5]s
    Param envSustain;   //!< env sustain in [0..-96]dB
    Param envRelease;   //!< env release in [0.001..5]s (logarithmic scaling)

    ParamDb clippingFactor;     //!< overdrive factor of the amplitude of the signal in [0..30] dB

    Param keyVelocityLevel;    //!< key velocity level range in [0..96]dB
    Param envAttackShape; //!< env attack shape in [0.01..10]
    Param envDecayShape; //!< env decay shape in [0.01..10]
    Param envReleaseShape; //!< env release shape in [0.01..10]

    ParamStepped<eSeqModes> seqMode;         //!< 0 = pause, 1 = play no sync, 2 = sync host
    ParamStepped<eSeqPlayModes> seqPlayMode; //!< 0 = sequential, 1 = upDown, 2 = random
    Param seqLastPlayedStep;                 //!< index of last played sequencer step in [0..7]
    Param seqNumSteps;                       //!< number of steps in [1..8] steps
    Param seqStepSpeed;                      //!< step speed in [0.0625..4] quarter notes
    Param seqStepLength;                     //!< step length in [0.0625..4] quarter notes
    ParamStepped<eOnOffToggle> seqTriplets;  //!< activate triplet tempo? 0 = no, 1 = active
    Param seqRandomMin;                      //!< randomMin value as int in [0..127]
    Param seqRandomMax;                      //!< randomMax value as int in [0..127]
    Param seqStep0;                          //!< midi note as int in [0..127]
    Param seqStep1;
    Param seqStep2;
    Param seqStep3;
    Param seqStep4;
    Param seqStep5;
    Param seqStep6;
    Param seqStep7;
    ParamStepped<eOnOffToggle> seqStepActive0;    //!< seqStep should play? 0 = mute, 1 = active
    ParamStepped<eOnOffToggle> seqStepActive1;
    ParamStepped<eOnOffToggle> seqStepActive2;
    ParamStepped<eOnOffToggle> seqStepActive3;
    ParamStepped<eOnOffToggle> seqStepActive4;
    ParamStepped<eOnOffToggle> seqStepActive5;
    ParamStepped<eOnOffToggle> seqStepActive6;
    ParamStepped<eOnOffToggle> seqStepActive7;

    Param panDir; //!< pan R/L [-100..100]

    Param ladderCutoff; //!< Cutoff frequency for the ladder Filter [0...20K] Hz
    Param ladderRes; //< resonance gain for the ladder Filter [0...1]

    ParamStepped<eOnOffToggle> lowFiActivation; //!< Activation of the low fidelity effect
    Param nBitsLowFi; //!< Bit degradation

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
    // list of only stepSeq params
    std::vector<Param*> stepSeqParams;

    const float version = 1.1f; // version of the program, to be written into the xml

    /**
    * Store host state by creating XML file to serialize specified parameters by using writeXMLPatchTree().
    @param destData host data
    @param paramsToSerialize specify which parameters should be used (all or only sequencer parameters)
    */
    void writeXMLPatchHost(MemoryBlock& destData, eSerializationParams paramsToSerialize);

    /**
    * Create XML file to serialize specified parameters by using writeXMLPatchTree().
    @param paramsToSerialize specify which parameters should be used (all or only sequencer parameters)
    */
    void writeXMLPatchStandalone(eSerializationParams paramsToSerialize);

    /**
    * Set the parameters if they exist in the XML patch.
    @param patch XML patch to work on
    @param paramName name to check whether parameter exist in XML patch
    @param param parameter to set
    */
    void fillValueIfExists(XmlElement * patch, String paramName, Param& param);

    /**
    * Iterate over specified parameters and set the values in the xml by using fillValueIfExists().
    @param patch XML patch to work on
    @param paramsToSerialize specify which parameters should be used (all or only sequencer parameters)
    */
    void fillValues(XmlElement * patch, eSerializationParams paramsToSerialize);

    /**
    * Restore host state by converting binary data into a XML file and set serialized parameters by using fillValues().
    @param data binary data to return to XML
    @param sizeInBytes data size
    @param paramsToSerialize specify which parameters should be used (all or only sequencer parameters)
    */
    void readXMLPatchHost(const void * data, int sizeInBytes, eSerializationParams paramsToSerialize);

    /**
    * Read XML file to set serialized parameters by using fillValues().
    @param paramsToSerialize specify which parameters should be used (all or only sequencer parameters)
    */
    void readXMLPatchStandalone(eSerializationParams paramsToSerialize);

    Param chorDelayLength;
    Param chorDryWet;
    Param chorModRate;
    Param chorModDepth;

    std::array<AudioPlayHead::CurrentPositionInfo, 2> positionInfo;

    std::atomic<int> positionIndex;

    int getGUIIndex();
    int getAudioIndex();

protected:
private:
    void addElement(XmlElement* patch, String name, float value); // adds an element to the XML tree

    /**
    * Write the XML patch tree for parameters to be serialized.
    @param patch XML patch to work on
    @param paramsToSerialize specify which parameters should be used (all or only sequencer parameters)
    */
    void writeXMLPatchTree(XmlElement * patch, eSerializationParams paramsToSerialize);
};
