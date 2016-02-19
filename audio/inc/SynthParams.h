#pragma once

#include "JuceHeader.h"
#include "Param.h"
#include <vector>
#include <array>
#include "ModulationMatrix.h"

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
    eOscSaw = 1,
    eOscNoise = 2,
    nSteps = 3
};

enum class eBiquadFilters : int {
    eLowpass = 0,
    eHighpass = 1,
    eBandpass = 2,
    eLadder = 3,
    nSteps = 4
};

enum class eOnOffToggle : int {
    eOff = 0,
    eOn = 1,
    nSteps = 2
};

enum class eSeqPlayModes : int {
    eSequential = 0,
    eUpDown = 1,
    eRandom = 2,
    nSteps = 3
};


class SynthParams {
public:
    SynthParams();
    ~SynthParams();

    static const Colour oscColour;
    static const Colour envColour;
    static const Colour lfoColour;
    static const Colour filterColour;
    static const Colour fxColour;
    static const Colour stepSeqColour;
    static const Colour onOffSwitchEnabled;
    static const Colour onOffSwitchDisabled;
    static const Colour envelopeCurveLine;
    static const Colour envelopeCurveBackground;
    static const Colour waveformLine;
    static const Colour waveformBackground;
    static const Colour otherModulation;

    static const char* getModSrcName(int index);

    Param freq;  //!< master tune in Hz

                       //Param lfoChorfreq; // delay-lfo frequency in Hz
                       //Param chorAmount; // wetness of signal [0 ... 1]
                       //Param chorSwitch; // Chorus on / off [1 / 0]

    struct BaseParamStruct {
        void setName(const String& s) {
            name = s;
        }

        String name;
    };

    struct EnvBase : public BaseParamStruct {
        EnvBase();
        Param keyVelToEnv;  //!< key velocity influence on env [0 ... 1] \todo remove this!
        Param attack;    //!< env attack in [0.001..5]s
        Param decay;     //!< env decay in [0.001..5]s
        Param release;   //!< env release in [0.001..5]s (logarithmic scaling)
        Param attackShape; //!< env attack shape in [0.01..10]
        Param decayShape; //!< env decay shape in [0.01..10]
        Param releaseShape; //!< env release shape in [0.01..10]
        //ModAmounts and Sources
        Param speedModAmount1; //!< Volume envelope speed mod amount
        Param speedModAmount2; //!< Volume envelope speed mod amount
        ParamStepped<eModSource> speedModSrc1; //!< Volume envelope speed mod source
        ParamStepped<eModSource> speedModSrc2; //!< Volume envelope speed mod source

        void setName(const String& s) {
            BaseParamStruct::setName(s);
            keyVelToEnv.setPrefix(s);
            attack.setPrefix(s);
            decay.setPrefix(s);
            release.setPrefix(s);
            attackShape.setPrefix(s);
            decayShape.setPrefix(s);
            releaseShape.setPrefix(s);
            speedModAmount1.setPrefix(s);
            speedModAmount2.setPrefix(s);
            speedModSrc1.setPrefix(s);
            speedModSrc2.setPrefix(s);
        }
    };

    struct EnvVol : public EnvBase {
        EnvVol();
        ParamDb sustain;   //!< Envelope sustain in [-96..0] dB

        void setName(const String& s) {
            EnvBase::setName(s);
            sustain.setPrefix(s);
        }
    };

    struct Env : public EnvBase {
        Env();
        Param sustain; //!< Envelope sustain in [0..1]

        void setName(const String& s) {
            EnvBase::setName(s);
            sustain.setPrefix(s);
        }
    };

    struct Lfo : public BaseParamStruct {
        Lfo();
        Param freq; //!< lfo frequency in Hz
        ParamStepped<eOnOffToggle> tempSync; //!< bool if checked or not
        ParamStepped<eOnOffToggle> lfoTriplets; //!< bool for triplet toggle in lfo
        ParamStepped<eOnOffToggle> lfoDottedLength; //!< bool for triplet toggle in lfo
        Param noteLength; //!< denominator of selected note length 1/x [1 ... 32]
        ParamStepped<eLfoWaves> wave; //!< lfo wave switch 0 = sine wave, 1 = random, or 2 = square wave
        Param fadeIn;   //!< The LFOs fade in with a range of [0..10s]
        //ModAmounts and Sources
        Param freqModAmount1; //!< lfo frequency mod amount
        Param freqModAmount2; //!< lfo frequency mod amount
        ParamStepped<eModSource> freqModSrc1; //!< lfo frequency mod source
        ParamStepped<eModSource> freqModSrc2; //!< lfo frequency mod source
        ParamStepped<eModSource> gainModSrc; //!< lfo gain mod source

        void setName(const String& s) {
            BaseParamStruct::setName(s);
            freq.setPrefix(s);
            tempSync.setPrefix(s);
            noteLength.setPrefix(s);
            wave.setPrefix(s);
            fadeIn.setPrefix(s);
            freqModAmount1.setPrefix(s);
            freqModAmount2.setPrefix(s);
            freqModSrc1.setPrefix(s);
            freqModSrc2.setPrefix(s);
            gainModSrc.setPrefix(s);
        }
    };

    struct Filter : public BaseParamStruct {
        Filter();

        ParamStepped<eBiquadFilters> passtype; //!< passtype that decides whether lowpass, highpass or bandpass filter is used
        Param lpCutoff; //!< filter cutoff frequency in Hz
        Param hpCutoff; //!< filter cutoff frequency in Hz
        Param resonance; //! filter resonance in dB
        // ModAmounts and ModSources
        Param lpModAmount1;   //! lp filter modulation amount
        Param lpModAmount2;   //! lp filter modulation amount
        Param hpModAmount1;   //! hp filter modulation amount
        Param hpModAmount2;   //! hp filter modulation amount
        Param resModAmount1;  //! resonance filter modulation amount
        Param resModAmount2;  //! resonance filter modulation amount
        ParamStepped<eModSource> lpCutModSrc1;  //! lp filter modulation source
        ParamStepped<eModSource> lpCutModSrc2;  //! lp filter modulation source
        ParamStepped<eModSource> hpCutModSrc1;  //! hp filter modulation source
        ParamStepped<eModSource> hpCutModSrc2;  //! hp filter modulation source
        ParamStepped<eModSource> resonanceModSrc1;  //! biquad filter resonance modulation source
        ParamStepped<eModSource> resonanceModSrc2;  //! biquad filter resonance modulation source
        ParamStepped<eOnOffToggle> filterActivation; //!< Activation of the filter

        void setName(const String& s) {
            BaseParamStruct::setName(s);
            passtype.setPrefix(s);
            lpCutoff.setPrefix(s);
            hpCutoff.setPrefix(s);
            resonance.setPrefix(s);
            lpModAmount1.setPrefix(s);
            lpModAmount2.setPrefix(s);
            hpModAmount1.setPrefix(s);
            hpModAmount2.setPrefix(s);
            resModAmount1.setPrefix(s);
            resModAmount2.setPrefix(s);
            lpCutModSrc1.setPrefix(s);
            lpCutModSrc2.setPrefix(s);
            hpCutModSrc1.setPrefix(s);
            hpCutModSrc2.setPrefix(s);
            resonanceModSrc1.setPrefix(s);
            resonanceModSrc2.setPrefix(s);
        }
    };

    struct Osc : public BaseParamStruct {
        Osc();

        Param fine;      //!< fine tune in [-100..100] ct
        Param coarse;    //!< coarse tune in [-11..11] st
        ParamStepped<eOscWaves> waveForm; //! waveform of the oscillator, it can be either square, saw, or noise
        Param trngAmount; //!< Triangle Amount [0 ... 1]
        Param pulseWidth; //!< pulse width in [0,01..0,99]
        ParamDb vol; //!< volume in [-96..12]
        Param panDir; //!< pan R/L [-100..100]
        //ModAmounts and Sources
        Param panModAmount1; //!< pan mod amount
        Param panModAmount2; //!< pan mod amount
        ParamStepped<eModSource> panModSrc1; //!< pan mod source
        ParamStepped<eModSource> panModSrc2; //!< pan mod source
        Param shapeModAmount1; //!< amount of pulse width modulation [0..1]
        Param shapeModAmount2; //!< amount of pulse width modulation [0..1]
        ParamStepped<eModSource> shapeModSrc1; //!< oscillator 1 pulse width modulation source
        ParamStepped<eModSource> shapeModSrc2; //!< oscillator 1 pulse width modulation source
        Param pitchModAmount1; //!< range in [0..12] st
        Param pitchModAmount2; //!< modulation depth in [-12..12] st
        ParamStepped<eModSource> pitchModSrc2; //!< oscillator 1 pitch modulation source
        ParamStepped<eModSource> pitchModSrc1; //!< oscillator 1 pitch modulation source
        Param gainModAmount1; //!< gain mod amount
        Param gainModAmount2; //!< gain mod amount
        ParamStepped<eModSource> gainModSrc1; //!< gain mod source
        ParamStepped<eModSource> gainModSrc2; //!< gain mod source

        void setName(const String& s) {
            BaseParamStruct::setName(s);
            fine.setPrefix(s);
            coarse.setPrefix(s);
            waveForm.setPrefix(s);
            trngAmount.setPrefix(s);
            pulseWidth.setPrefix(s);
            vol.setPrefix(s);
            panDir.setPrefix(s);
            panModAmount1.setPrefix(s);
            panModAmount2.setPrefix(s);
            panModSrc1.setPrefix(s);
            panModSrc2.setPrefix(s);
            shapeModAmount1.setPrefix(s);
            shapeModAmount2.setPrefix(s);
            shapeModSrc1.setPrefix(s);
            shapeModSrc2.setPrefix(s);
            pitchModAmount1.setPrefix(s);
            pitchModAmount2.setPrefix(s);
            pitchModSrc1.setPrefix(s);
            pitchModSrc2.setPrefix(s);
            gainModAmount1.setPrefix(s);
            gainModAmount2.setPrefix(s);
            gainModSrc1.setPrefix(s);
            gainModSrc2.setPrefix(s);
        }
    };

    std::array<Filter, 2> filter;
    std::array<Lfo, 3> lfo;
    std::array<EnvVol, 1> envVol;
    std::array<Env, 2> env;
    std::array<Osc, 3> osc;

    ParamDb clippingFactor;     //!< overdrive factor of the amplitude of the signal in [0..30] dB
    ParamStepped<eOnOffToggle> clippingActivation; //!< Activation of the clipping effect

    Param chorDelayLength;
    Param chorDryWet;
    Param chorModRate;
    Param chorModDepth;
    ParamStepped<eOnOffToggle> chorActivation; //!< Activation of the chorus effect

    Param seqPlaceHolder;                       //!< placeholder for register slider with exactly two thumb slider, value as int in [0..127]
    ParamStepped<eOnOffToggle> seqPlayNoHost;   //!< play without host? 0 = no, 1 = yes
    ParamStepped<eOnOffToggle> seqPlaySyncHost; //!< play synced with host? 0 = no, 1 = yes
    ParamStepped<eSeqPlayModes> seqPlayMode;    //!< 0 = sequential, 1 = upDown, 2 = random
    Param seqLastPlayedStep;                    //!< index of last played sequencer step in [0..7]
    Param seqNumSteps;                          //!< number of steps in [1..8] steps
    Param seqStepSpeed;                         //!< step speed in 1/[1 .. 64]
    Param seqStepLength;                        //!< step length in 1/[1 .. 64]
    ParamStepped<eOnOffToggle> seqTriplets;     //!< activate triplet tempo? 0 = no, 1 = active
    ParamStepped<eOnOffToggle> seqDottedLength;       //!< activate dotted tempo? 0 = no, 1 = active
    Param seqRandomMin;                         //!< randomMin value as int in [0..127]
    Param seqRandomMax;                         //!< randomMax value as int in [0..127]
    Param seqStep0;                             //!< midi note as int in [0..127]
    Param seqStep1;
    Param seqStep2;
    Param seqStep3;
    Param seqStep4;
    Param seqStep5;
    Param seqStep6;
    Param seqStep7;
    ParamStepped<eOnOffToggle> seqStepActive0;  //!< seqStep should play? 0 = mute, 1 = active
    ParamStepped<eOnOffToggle> seqStepActive1;
    ParamStepped<eOnOffToggle> seqStepActive2;
    ParamStepped<eOnOffToggle> seqStepActive3;
    ParamStepped<eOnOffToggle> seqStepActive4;
    ParamStepped<eOnOffToggle> seqStepActive5;
    ParamStepped<eOnOffToggle> seqStepActive6;
    ParamStepped<eOnOffToggle> seqStepActive7;

    ParamStepped<eOnOffToggle> lowFiActivation; //!< Activation of the low fidelity effect
    Param nBitsLowFi; //!< Bit degradation

    ModulationMatrix globalModMatrix;
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
    ParamStepped<eOnOffToggle> delayDottedLength;   //!< delay dotted note length toggle
    ParamStepped<eOnOffToggle> delayRecordFilter;   //!< delay filter record toggle
    ParamStepped<eOnOffToggle> delayReverse;        //!< delay reverse modo toggle
    ParamStepped<eOnOffToggle> delayActivation;     //!< delay activation
    ParamStepped<eOnOffToggle> syncToggle;          //!< delay sync toggle

    // list of current params, just add your new param here if you want it to be serialized
    std::vector<Param*> serializeParams; //!< vector of params to be serialized
    // list of only stepSeq params
    std::vector<Param*> stepSeqParams;

    const float version = 1.1f; // version of the program, to be written into the xml

    static Colour getModSourceColour(eModSource source);

    static String getShortModSrcName(int index);

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
