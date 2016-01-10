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

enum class eSeqPlayModes : int
{
    sequential = 0,
    upDown = 1,
    random = 2,
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
    Param envRelease;   //!< env release in [0.001..5]s
    Param envAttackShape; //!< env attack shape in [0.01..10]
    Param envDecayShape; //!< env decay shape in [0.01..10]
    Param envReleaseShape; //!< env release shape in [0.01..10]

    ParamStepped<eSeqModes> seqMode;         //!< 0 = pause, 1 = play no sync, 2 = sync host
    ParamStepped<eSeqPlayModes> seqPlayMode; //!< 0 = sequential, 1 = upDown, 2 = random
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
    // list of only stepSeq params, specified with @param allParams = false
    std::vector<Param*> stepSeqParams;

    const float version = 1.1f; // version of the program, to be written into the xml

    void writeXMLPatchHost(MemoryBlock& destData, bool allParams);

    void writeXMLPatchStandalone(bool allParams);

    void fillValueIfExists(XmlElement * patch, String paramName, Param& param);

    void fillValues(XmlElement * patch, bool allParams);

    void readXMLPatchHost(const void * data, int sizeInBytes, bool allParams);

    void readXMLPatchStandalone(bool allParams);

    std::array<AudioPlayHead::CurrentPositionInfo, 2> positionInfo;

    std::atomic<int> positionIndex;
    
    int getGUIIndex();
    int getAudioIndex();

protected:
private:
    void addElement(XmlElement* patch, String name, float value); // adds an element to the XML tree
    void writeXMLPatchTree(XmlElement * patch, bool allParams);
};
