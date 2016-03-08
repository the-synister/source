#include "SynthParams.h"


namespace {
    static const char *lfowavenames[] = {
        "Sine", "Square", "Smpl+Hold", nullptr
    };

    static const char *onoffnames[] = {
        "Off", "On", nullptr
    };
    
    static const char *sectionStateNames[] = {
        "Expanded", "Collapsed", nullptr
    };

    static const char *seqPlayModeNames[] = {
        "Sequential", "Up/Down", "Random", nullptr
    };

    static const char *biquadFilters[] = {
        "Lowpass", "Highpass", "Bandpass", "Ladder", nullptr
    };

    static const char *modsourcenames[] = {
        "None", "Aftertouch (AT)", "KeyBipolar (KB)", "InvertedVelocity (-Vel)", "Velocity (Vel)", "Foot (Ft)", "ExpPedal (Ped)", "Modwheel (MW)", "Pitchbend (PB)",
        "LFO1", "LFO2", "LFO3", "VolEnvelope", "Envelope2", "Envelope3", nullptr
    };

    static const char *modSourceNamesShort[] = {
        " ", "AT", "KB", "-Vel", "Vel", "Ft", "Ped", "MW", "PB",
        "1", "2", "3", "1", "2", "3", nullptr
    };

    static const char *waveformNames[] = {
        "Square", "Saw", "White-noise"
    };
}


const Colour SynthParams::oscColour (0xff6c788c);
const Colour SynthParams::envColour (0xffbfa65a);
const Colour SynthParams::lfoColour (0xff855050);
const Colour SynthParams::filterColour (0xff5b7a47);
const Colour SynthParams::fxColour (0xff2b3240);
const Colour SynthParams::stepSeqColour (0xff564c43);
const Colour SynthParams::onOffSwitchEnabled (96, 192, 96);
const Colour SynthParams::onOffSwitchDisabled (102, 102, 102);
const Colour SynthParams::envelopeCurveLine (216, 202, 155);
const Colour SynthParams::envelopeCurveBackground (116, 101, 60);
const Colour SynthParams::waveformLine (185, 189, 190);
const Colour SynthParams::waveformBackground(85, 93, 104);
const Colour SynthParams::otherModulation(180, 180, 180); // add more different colours

SynthParams::SynthParams()
    : serializeParams{
        // TODO: Think of another way to register all the struct params?
    //Oscillators PArams
    &osc[0].fine, &osc[0].coarse, &osc[0].panDir,&osc[0].vol,&osc[0].trngAmount,&osc[0].pulseWidth,&osc[0].waveForm,&osc[0].pitchModAmount1, &osc[0].pitchModAmount2,&osc[0].pitchModSrc1, &osc[0].pitchModSrc2,
    &osc[0].panModAmount1, &osc[0].panModAmount2, &osc[0].panModSrc1,&osc[0].panModSrc2,&osc[0].shapeModAmount1,&osc[0].shapeModAmount2,&osc[0].shapeModSrc1, &osc[0].shapeModSrc2,&osc[0].gainModAmount1,&osc[0].gainModAmount2,&osc[0].gainModSrc1,&osc[0].gainModSrc2,
    &osc[1].fine, &osc[1].coarse, &osc[1].panDir,&osc[1].vol,&osc[1].trngAmount,&osc[1].pulseWidth,&osc[1].waveForm,&osc[1].pitchModAmount1, &osc[1].pitchModAmount2,&osc[1].pitchModSrc1, &osc[1].pitchModSrc2,
    &osc[1].panModAmount1, &osc[1].panModAmount2, &osc[1].panModSrc1, &osc[1].panModSrc2,&osc[1].shapeModAmount1,&osc[1].shapeModAmount2,&osc[1].shapeModSrc1, &osc[1].shapeModSrc2,&osc[1].gainModAmount1,&osc[1].gainModAmount2,&osc[1].gainModSrc1,&osc[1].gainModSrc2,
    &osc[2].fine, &osc[2].coarse, &osc[2].panDir,&osc[2].vol,&osc[2].trngAmount,&osc[2].pulseWidth,&osc[2].waveForm,&osc[2].pitchModAmount1, &osc[2].pitchModAmount2,&osc[2].pitchModSrc1, &osc[2].pitchModSrc2,
    &osc[2].panModAmount1, &osc[2].panModAmount2, &osc[2].panModSrc1, &osc[0].panModSrc2, &osc[2].shapeModAmount1,&osc[2].shapeModAmount2,&osc[2].shapeModSrc1, &osc[2].shapeModSrc2,&osc[2].gainModAmount1,&osc[2].gainModAmount2,&osc[2].gainModSrc1,&osc[2].gainModSrc2,
    //Envelopes Params
    &env[0].attack, &env[0].decay, &env[0].sustain, &env[0].release, &env[0].attackShape, &env[0].decayShape, &env[0].releaseShape, &env[0].speedModAmount1, &env[0].speedModAmount2, &env[0].speedModSrc1, &env[0].speedModSrc2,
    &env[1].attack, &env[1].decay, &env[1].sustain, &env[1].release, &env[1].attackShape, &env[1].decayShape, &env[1].releaseShape, &env[1].speedModAmount1, &env[1].speedModAmount2, &env[1].speedModSrc1, &env[1].speedModSrc2,
    &envVol[0].attack, &envVol[0].decay, &envVol[0].sustain, &envVol[0].release, &envVol[0].attackShape, &envVol[0].decayShape, &envVol[0].releaseShape, &envVol[0].speedModAmount1, &envVol[0].speedModAmount2, &envVol[0].speedModSrc1, &envVol[0].speedModSrc2,
    //LFOs Params
    &lfo[0].fadeIn, &lfo[0].freq, &lfo[0].freqModSrc1, &lfo[0].freqModSrc2, &lfo[0].freqModAmount1, &lfo[0].freqModAmount2, &lfo[0].tempSync, &lfo[0].wave, &lfo[0].noteLength, &lfo[0].gainModSrc, &lfo[0].lfoTriplets, &lfo[0].lfoDottedLength,
    &lfo[1].fadeIn, &lfo[1].freq, &lfo[1].freqModSrc1, &lfo[1].freqModSrc2, &lfo[1].freqModAmount1, &lfo[1].freqModAmount2, &lfo[1].tempSync, &lfo[1].wave, &lfo[1].noteLength, &lfo[1].gainModSrc, &lfo[1].lfoTriplets, &lfo[1].lfoDottedLength,
    &lfo[2].fadeIn, &lfo[2].freq, &lfo[2].freqModSrc1, &lfo[2].freqModSrc2, &lfo[2].freqModAmount1, &lfo[2].freqModAmount2, &lfo[2].tempSync, &lfo[2].wave, &lfo[2].noteLength, &lfo[2].gainModSrc, &lfo[2].lfoTriplets, &lfo[2].lfoDottedLength,
    //Filters Params
    &filter[0].passtype, &filter[0].lpCutoff, &filter[0].hpCutoff, &filter[0].resonance, &filter[0].lpModAmount1, &filter[0].lpModAmount2, &filter[0].lpCutModSrc1, &filter[0].lpCutModSrc2, &filter[0].hpModAmount1, &filter[0].hpModAmount2, &filter[0].hpCutModSrc1, &filter[0].hpCutModSrc2, &filter[0].resModAmount1, &filter[0].resModAmount2, &filter[0].resonanceModSrc1, &filter[0].resonanceModSrc2, &filter[0].filterActivation,
    &filter[1].passtype, &filter[1].lpCutoff, &filter[1].hpCutoff, &filter[1].resonance, &filter[1].lpModAmount1, &filter[1].lpModAmount2, &filter[1].lpCutModSrc1, &filter[1].lpCutModSrc2, &filter[1].hpModAmount1, &filter[1].hpModAmount2, &filter[1].hpCutModSrc1, &filter[1].hpCutModSrc2, &filter[1].resModAmount1, &filter[1].resModAmount2, &filter[1].resonanceModSrc1, &filter[1].resonanceModSrc2, &filter[1].filterActivation,
    //Step Sequencer
    &seqPlaySyncHost, &seqPlayMode, &seqNumSteps, &seqStepSpeed, &seqStepLength, &seqTriplets, &seqDottedLength, &seqStep0, &seqStep1, &seqStep2, &seqStep3, &seqStep4, &seqStep5, &seqStep6, &seqStep7,
    &seqStepActive0, &seqStepActive1, &seqStepActive2, &seqStepActive3, &seqStepActive4, &seqStepActive5, &seqStepActive6, &seqStepActive7, &seqRandomMin, &seqRandomMax,
    //Delay
    &delayDryWet, &delayFeedback, &delayTime, &delaySync, &delayDividend, &delayDivisor, &delayCutoff, &delayResonance, &delayTriplet, &delayDottedLength, &delayRecordFilter, &delayReverse, &delayActivation, &syncToggle,
    //Others
    &freq, &masterAmp, &masterPan, &chorActivation, &chorActivation, &chorDelayLength, &chorDryWet, &chorModDepth, &chorModRate, &lowFiActivation, &nBitsLowFi, &clippingActivation, &clippingFactor,
    //Sections
    &oscSection, &envSection, &lfoSection, &filterSection, &fxSection, &seqSection
    }
    , stepSeqParams{ &seqPlaySyncHost, &seqPlayMode, &seqNumSteps, &seqStepSpeed, &seqStepLength, &seqTriplets, &seqDottedLength, &seqStep0, &seqStep1, &seqStep2, &seqStep3, &seqStep4, &seqStep5, &seqStep6, &seqStep7,
    &seqStepActive0, &seqStepActive1, &seqStepActive2, &seqStepActive3, &seqStepActive4, &seqStepActive5, &seqStepActive6, &seqStepActive7, &seqRandomMin, &seqRandomMax }
    // section states
    , oscSection("oscillator section", "oscSection", "oscillator section", eSectionState::eExpanded, sectionStateNames)
    , envSection("envelopes section", "envSection", "envelopes section", eSectionState::eCollapsed, sectionStateNames)
    , lfoSection("lfo section", "lfoSection", "lfo section", eSectionState::eCollapsed, sectionStateNames)
    , filterSection("filter section", "filterSection", "filter section", eSectionState::eCollapsed, sectionStateNames)
    , fxSection("fx section", "fxSection", "fx section", eSectionState::eCollapsed, sectionStateNames)
    , seqSection("sequencer section", "seqSection", "sequencer section", eSectionState::eCollapsed, sectionStateNames)
    , masterAmp("master amp", "masterAmp", "Master amp", "dB", -96.f, 12.f, -6.f)
    , masterPan("master pan", "masterPan", "Master pan", "%", -100.f, 100.f, 0.f)
    , freq("master freq", "freq", "freq", "Hz", 220.f, 880.f, 440.f)
    // FX
    , delayDryWet("dry/wet", "delWet", "Delay dry/wet", "", 0.f, 1.f, 0.f)
    , delayFeedback("feedback", "delFeed", "Delay feedback", "", 0.f, 1.f, 0.f)
    , delayTime("time", "delTime", "Delay time", "ms", 1., 5000., 1000.)
    , delaySync("Tempo Sync", "delSync", "Delay sync", eOnOffToggle::eOff, onoffnames)
    , delayDividend("SyncDel Dividend", "delDivd", "Delay dividend", "", 1, 5, 1)
    , delayDivisor("SyncDel Divisor", "delDivs", "Delay divisor", "", 1, 64, 4)
    , delayCutoff("cutoff", "delCut", "Delay cutoff", "Hz", 10.f, 20000.f, 20000.f)
    , delayResonance("resonance", "delRes", "Delay resonance", "dB", -25.f, 0.f, 0.f)
    , delayTriplet("Delay Triplet", "delTrip", "Delay triplet", eOnOffToggle::eOff, onoffnames)
    , delayDottedLength("Delay Dotted Length", "delDot", "Delay dotted length", eOnOffToggle::eOff, onoffnames)
    , delayRecordFilter("Delay Record", "delRec", "Delay record filter", eOnOffToggle::eOff, onoffnames)
    , delayReverse("Delay Reverse", "delRev", "Delay reverse", eOnOffToggle::eOff, onoffnames)
    , delayActivation("Delay Activation", "delayActivation", "Delay Active", eOnOffToggle::eOff, onoffnames)
    , syncToggle("Delay Sync", "syncToggle", "Sync Toggle", eOnOffToggle::eOff, onoffnames)
    , lowFiActivation("Activation", "lowFiActivation", "LowFi Active", eOnOffToggle::eOff, onoffnames)
    , nBitsLowFi("bit degr.", "nBitsLowFi", "Number Bits", "bit", 1.f, 16.f, 16.f)
    , chorDelayLength("width", "chorWidth", "Chorus Width", "s", .02f, .08f, .05f)
    , chorModRate("rate", "chorRate", "Chorus Rate", "Hz", 0.f, 1.5f, 0.5f)
    , chorDryWet("dry/wet", "ChorAmount", "Chorus Dry/Wet", "", 0.f, 1.f, 0.f)
    , chorModDepth("depth", "ChorDepth", "Chorus Depth", "ms", 1.f, 20.f, 15.f)
    , chorActivation("Activation", "chorActivation", "Chorus Active", eOnOffToggle::eOff, onoffnames)
    , clippingFactor("clipping", "clippingFactor", "Clipping", "dB", 0.f, 25.f, 0.0f)
    , clippingActivation("Activation", "clippingActivation", "Clipping Active", eOnOffToggle::eOff, onoffnames)
    // sequencer
    , seqPlaceHolder("Placeholder", "seqPlaceholder", "SeqPlaceholder", "", 0.0f, 127.0f, 126.0f)
    , seqPlayNoHost("Play No Host", "seqPlayNoHost", "seqPlayNoHost", eOnOffToggle::eOff, onoffnames)
    , seqPlaySyncHost("Play Sync Host", "seqPlaySyncHost", "seqPlaySyncHost", eOnOffToggle::eOff, onoffnames)
    , seqPlayMode("SeqPlayMode", "seqPlayMode", "SeqPlayMode", eSeqPlayModes::eSequential, seqPlayModeNames)
    , seqLastPlayedStep("Last Played Step", "lastPlayedStep", "Last Played Step", "", 0.0f, 7.0f, 0.0f)
    , seqNumSteps("Steps", "seqNumSteps", "Steps", "", 1.0f, 8.0f, 8.0f)
    , seqStepSpeed("Speed", "seqStepSpeed", "Speed", "", 1.0f, 64.0f, 4.0f)
    , seqStepLength("Length", "seqNoteLength", "Length", "", 1.0f, 64.0f, 4.0f)
    , seqTriplets("Seq Triplets", "seqTriplets", "Seq Triplets", eOnOffToggle::eOff, onoffnames)
    , seqDottedLength("Seq Dotted Length", "seqDottedLength", "Seq Dotted Length", eOnOffToggle::eOff, onoffnames)
    , seqRandomMin("Min", "seqRandomMin", "Min", "", 0.0f, 127.0f, 0.0f)
    , seqRandomMax("Max", "seqRandomMax", "Max", "", 0.0f, 127.0f, 127.0f)
    , seqStep0("Step 0", "seqNote0", "Step 0", "", 0.0f, 127.0f, 60.0f)
    , seqStep1("Step 1", "seqNote1", "Step 1", "", 0.0f, 127.0f, 62.0f)
    , seqStep2("Step 2", "seqNote2", "Step 2", "", 0.0f, 127.0f, 64.0f)
    , seqStep3("Step 3", "seqNote3", "Step 3", "", 0.0f, 127.0f, 65.0f)
    , seqStep4("Step 4", "seqNote4", "Step 4", "", 0.0f, 127.0f, 67.0f)
    , seqStep5("Step 5", "seqNote5", "Step 5", "", 0.0f, 127.0f, 69.0f)
    , seqStep6("Step 6", "seqNote6", "Step 6", "", 0.0f, 127.0f, 71.0f)
    , seqStep7("Step 7", "seqNote7", "Step 7", "", 0.0f, 127.0f, 72.0f)
    , seqStepActive0("Step 0 Active", "seqStepActive0", "Step 0 Active", eOnOffToggle::eOn, onoffnames)
    , seqStepActive1("Step 1 Active", "seqStepActive1", "Step 1 Active", eOnOffToggle::eOn, onoffnames)
    , seqStepActive2("Step 2 Active", "seqStepActive2", "Step 2 Active", eOnOffToggle::eOn, onoffnames)
    , seqStepActive3("Step 3 Active", "seqStepActive3", "Step 3 Active", eOnOffToggle::eOn, onoffnames)
    , seqStepActive4("Step 4 Active", "seqStepActive4", "Step 4 Active", eOnOffToggle::eOn, onoffnames)
    , seqStepActive5("Step 5 Active", "seqStepActive5", "Step 5 Active", eOnOffToggle::eOn, onoffnames)
    , seqStepActive6("Step 6 Active", "seqStepActive6", "Step 6 Active", eOnOffToggle::eOn, onoffnames)
    , seqStepActive7("Step 7 Active", "seqStepActive7", "Step 7 Active", eOnOffToggle::eOn, onoffnames)
    //Others
    , positionIndex(0)
{    
    positionInfo[0].resetToDefault();
    positionInfo[1].resetToDefault();

    osc[0].setName("osc 1");
    osc[1].setName("osc 2");
    osc[2].setName("osc 3");

    envVol[0].setName("env vol");
    env[0].setName("env 2");
    env[1].setName("env 3");

    lfo[0].setName("lfo 1");
    lfo[1].setName("lfo 2");
    lfo[2].setName("lfo 3");

    filter[0].setName("filter 1");
    filter[1].setName("filter 2");
}

SynthParams::Osc::Osc()
    : fine("fine", "fine", "f.tune", "ct", -100.f, 100.f, 0.f)
    , coarse("coarse", "coarse", "c.tune", "st", -36.f, 36.f, 0.f)
    , trngAmount("triangle", "trngAmount", "triangle amount", "prct", 0.0f, 1.0f, 0.0f)
    , pulseWidth("width", "pulseWidth", "pulsewidth", "prct", 0.01f, 0.99f, 0.5f)
    , waveForm("Waveform", "oscWaveform", "Waveform", eOscWaves::eOscSquare, waveformNames)
    , panDir("pan", "panDir", "pan direction", "%", -100.f, 100.f, 0.f)
    , vol("gain", "vol", "Vol", "dB", -96.f, 12.f, -6.f)
    // ModAmounts and ModSources
    , panModAmount1("PanModAmount1", "OSCPanModAmount1", "Pan ModAmount 1", "%", 0.f, 200.f, 100.f)
    , panModAmount2("PanModAmount2", "OSCPanModAmount2", "Pan ModAmount 2", "%", 0.f, 200.f, 100.f)
    , panModSrc1("PanModSrc1", "OSCPanModSrc1", "Pan ModSource 1", eModSource::eNone, modsourcenames)
    , panModSrc2("PanModSrc2", "OSCPanModSrc2", "Pan ModSource 2", eModSource::eNone, modsourcenames)
    , shapeModAmount1("ShapeModAmount1", "OSCShapeModAmount1", "Shape ModAmount 1", "", 0.f, 1.f, 0.5f)
    , shapeModAmount2("ShapeModAmount2", "OSCShapeModAmount2", "Shape ModAmount 2", "", 0.f, 1.f, 0.5f)
    , shapeModSrc1("ShapeModSrc1", "OSCShapeModSrc1", "Shape ModSource 1", eModSource::eNone, modsourcenames)
    , shapeModSrc2("ShapeModSrc2", "OSCShapeModSrc2", "Shape ModSource 2", eModSource::eNone, modsourcenames)
    , pitchModAmount1("PitchModAmount1", "OSCPitchModAmount1", "Pitch ModAmount 1", "st", 0.f, 48.f, 24.f)
    , pitchModAmount2("PitchModAmount2", "OSCPitchModAmount2", "Pitch ModAmount 2", "st", 0.f, 48.f, 24.f)
    , pitchModSrc1("PitchModSrc1", "OSCPitchModSrc1", "Pitch ModSource 1", eModSource::eNone, modsourcenames)
    , pitchModSrc2("PitchModSrc2", "OSCPitchModSrc2", "Pitch ModSource 2", eModSource::eNone, modsourcenames)
    , gainModAmount1("GainModAmount1", "OSCGainModAmount1", "Gain ModAmount 1", "dB", 0.f, 96.f, 48.0f)
    , gainModAmount2("GainModAmount2", "OSCGainModAmount2", "Gain ModAmount 2", "dB", 0.f, 96.f, 48.0f)
    , gainModSrc1("GainModSrc1", "OSCGainModSrc1", "Gain ModSource 1", eModSource::eNone, modsourcenames)
    , gainModSrc2("GainModSrc2", "OSCGainModSrc2", "Gain ModSource 2", eModSource::eNone, modsourcenames)
{
}

SynthParams::EnvBase::EnvBase()
    : attack("att.", "envAttack", "Amp Env attack", "s", 0.001f, 5.0f, 0.005f)
    , release("rel.", "envRelease", "Amp Env release", "s", 0.001f, 5.0f, 0.5f)
    , keyVelToEnv("keyVel to Env", "", "Key velocity to Amp Env", "", 0.0f, 1.0f, 0.0f)
    , attackShape("Attack Shape", "envAttackShape", "Amp Env attack shape", "", 0.01f, 10.0f, 1.0f)
    , decayShape("Decay Shape", "envDecayShape", "Amp Env decay shape", "", 0.01f, 10.0f, 1.0f)
    , releaseShape("Release Shape", "envReleaseShape", "Amp Env release shape", "", 0.01f, 10.0f, 1.0f)
    , decay("dec.", "envDecay", "Amp Env decay", "s", 0.001f, 5.0f, 0.05f)
    // ModAmounts and Sources
    , speedModAmount1("ENV SpeedModAmount1", "ENVSpeedModAmount1", "ENV Speed ModAmount 1", "", 0.f, 8.f, 4.f)
    , speedModAmount2("ENV SpeedModAmount2", "ENVSpeedModAmount2", "ENV Speed ModAmount 2", "", 0.f, 8.f, 4.f)
    , speedModSrc1("ENV Speed ModSrc1", "ENVSpeedModSrc1", "ENV Speed ModSource 1", eModSource::eNone, modsourcenames)
    , speedModSrc2("ENV Speed ModSrc2", "ENVSpeedModSrc2", "ENV Speed ModSource 2", eModSource::eNone, modsourcenames)
{
}

SynthParams::EnvVol::EnvVol()
    : EnvBase()
    , sustain("sust.", "envSustain", "Amp Env sustain", "dB", 0.f, 1.f, -6.f)
{
}

SynthParams::Env::Env()
:  EnvBase()
    , sustain("sust.", "envSustain", "sustain", "", 0.f, 1.f, 1.f)
{
}

SynthParams::Lfo::Lfo()
    : freq("Freq", "lfo1freq", "freq", "Hz", .01f, 50.f, 1.f)
    , wave("Wave", "lfo1wave", "waveform", eLfoWaves::eLfoSine, lfowavenames)
    , tempSync("TempoSync", "tempoSyncSwitch", "TempoSync", eOnOffToggle::eOff, onoffnames)
    , lfoTriplets("Lfo Triplet", "lfoTriplet", "Lfo Triplet", eOnOffToggle::eOff, onoffnames)
    , lfoDottedLength("Lfo Dotted Note Length", "lfoDottedLength", "Lfo Dotted Length", eOnOffToggle::eOff, onoffnames)
    , noteLength("Note Length", "notelength", "Note Length", "", 1.f, 64.f, 4.f)
    , fadeIn("fade-in", "lfoFadein", "fade-in", "s", 0.f, 10.f, 0.f)
    // ModAmounts and Sources
    , freqModAmount1("FreqModAmount1", "LFOFreqModAmount1", "Freq ModAmount 1", "oct", 0.f, 10.f, 5.0f)
    , freqModAmount2("FreqModAmount2", "LFOFreqModAmount2", "Freq ModAmount 2", "oct", 0.f, 10.f, 5.0f)
    , freqModSrc1("FreqModSrc1", "LFOFreqModSrc1", "Freq ModSource 1", eModSource::eNone, modsourcenames)
    , freqModSrc2("FreqModSrc2", "LFOFreqModSrc2", "Freq ModSource 2", eModSource::eNone, modsourcenames)
    , gainModSrc("GainModSrc", "LFOGainModSrc", "Gain ModSource", eModSource::eNone, modsourcenames)
{
}

SynthParams::Filter::Filter()
    : passtype("Type", "FILTERType", "Type", eBiquadFilters::eLowpass, biquadFilters)
    , lpCutoff("lp cutoff", "lpCutoff", "LP Cutoff", "Hz", 10.f, 20000.f, 20000.f)
    , hpCutoff("hp cutoff", "hpCutoff", "HP Cutoff", "Hz", 10.f, 20000.f, 10.f)
    , resonance("resonance", "FILTERResonance", "Resonance", "", 0.f, 10.f, 0.f)
    // ModAmounts and ModSources
    , lpModAmount1("Lc ModAmount1", "FILTERLcModAmount1", "Lc ModAmount 1", "oct", 0.f, 10.f, 5.f)
    , lpModAmount2("Lc ModAmnout2", "FILTERLcModAmount2", "Lc ModAmount 2", "oct", 0.f, 10.f, 5.f)
    , hpModAmount1("Hc ModAmount1", "FILTERHcModAmount1", "Hc ModAmount 1", "oct", 0.f, 8.f, 4.f)
    , hpModAmount2("Hc ModAmount2", "FILTERHcModAmount2", "Hc ModAmount 2", "oct", 0.f, 8.f, 4.f)
    , resModAmount1("Res ModAmount1", "FILTERResModAmount1", "Res ModAmount 1", "", 0.f, 10.f, 5.f)
    , resModAmount2("Res ModAmount2", "FILTERResModAmount2", "Res ModAmount 2", "", 0.f, 10.f, 5.f)
    , lpCutModSrc1("Lc ModSrc1", "FILTERLcModSrc1", "Lc ModSource 1", eModSource::eNone, modsourcenames)
    , lpCutModSrc2("Lc ModSrc2", "FILTERLcModSrc2", "Lc ModSource 2", eModSource::eNone, modsourcenames)
    , hpCutModSrc1("Hc ModSrc1", "FILTERHcModSrc1", "Hc ModSource 1", eModSource::eNone, modsourcenames)
    , hpCutModSrc2("Hc ModSrc2", "FILTERHcModSrc2", "Hc ModSource 2", eModSource::eNone, modsourcenames)
    , resonanceModSrc1("Res ModSrc1", "FILTERResModSrc1", "Res ModSource 1", eModSource::eNone, modsourcenames)
    , resonanceModSrc2("Res ModSrc2", "FILTERResModSrc2", "Res ModSource 2", eModSource::eNone, modsourcenames)
    , filterActivation("Filter Activation", "filterActivation", "LowFi Active", eOnOffToggle::eOff, onoffnames)
{
}

void SynthParams::addElement(XmlElement* patch, String name, float value) {
    XmlElement* node = new XmlElement(name);
    node->setAttribute("value", value);
    patch->addChildElement(node);
}

void SynthParams::writeXMLPatchTree(XmlElement* patch, eSerializationParams paramsToSerialize) {
    // set version of the patch
    patch->setAttribute("version", version);
    // TODO check patchname for chars that need to be replaced/escaped for correct XML
    patch->setAttribute("patchname", patchName);

    std::vector<Param*> parameters = serializeParams;
    if (paramsToSerialize == eSerializationParams::eSequencerOnly)
    {
        parameters = stepSeqParams;
    }

    // iterate over all params and insert them into the tree
    for (auto &param : parameters) {
        float value = param->getUI();
        if (param->serializationTag() != "") {
            String prefixedName = (param->prefix() + param->serializationTag()).replace(" ", "");
            addElement(patch, prefixedName, value);
    }
}
}

// TODO: add more diverse colours, note that what if lfo modulates lfo? -> same colour, currently draw saturn with saturation
Colour SynthParams::getModSourceColour(eModSource source)
{
    switch (source) {
        case eModSource::eNone:
            return Colours::black;
        case eModSource::eVolEnv:
        case eModSource::eEnv2:
        case eModSource::eEnv3:
            return SynthParams::envColour.withSaturation(1.0f).brighter();
        case eModSource::eLFO1:
        case eModSource::eLFO2:
        case eModSource::eLFO3:
            return SynthParams::lfoColour.withSaturation(1.0f).brighter(0.8f);
        default:
            return SynthParams::otherModulation;
}
}

void SynthParams::writeXMLPatchHost(MemoryBlock& destData, eSerializationParams paramsToSerialize) {
    // create an outer node of the patch
    ScopedPointer<XmlElement> patch = new XmlElement("patch");
    writeXMLPatchTree(patch, paramsToSerialize);
    AudioProcessor::copyXmlToBinary(*patch, destData);
}

void SynthParams::writeXMLPatchStandalone(eSerializationParams paramsToSerialize) {
    // create an outer node of the patch
    ScopedPointer<XmlElement> patch = new XmlElement("patch");
    writeXMLPatchTree(patch, paramsToSerialize);

    // create the output
    FileChooser saveDirChooser("Please select the place you want to save!", File::getSpecialLocation(File::userHomeDirectory), "*.xml");
    if (saveDirChooser.browseForFileToSave(true))
    {
        File saveFile(saveDirChooser.getResult());
        saveFile.create();
        patch->writeToFile(saveFile, ""); // DTD optional, no validation yet
    }
}


// adds the value if it exists in the xml
void SynthParams::fillValueIfExists(XmlElement* patch, String paramName, Param& param) {
    String prefixedName = (param.prefix() + param.serializationTag()).replace(" ", "");
    if (patch->getChildByName(prefixedName) != NULL) {
        param.setUI(static_cast<float>(patch->getChildByName(prefixedName)->getDoubleAttribute("value")));
        //! \todo dirty flag needs to be set! This is a bad hack, please use get/set instead of getUI/setUI
        param.set(param.get(),true);
        //param.set(static_cast<float>(patch->getChildByName(paramName)->getDoubleAttribute("value")), true); // NOTE: needed at least for seq standalone and envShape params but then at least
                                                                                                            // delay feedback and dry are bad and (ampVol sometimes); not further tested
    }
}

// set all values from xml file in params
void SynthParams::fillValues(XmlElement* patch, eSerializationParams paramsToSerialize) {
    // if the versions don't align, inform the user
    if (patch == NULL) return;
    if (patch->getTagName() != "patch" || (static_cast<float>(patch->getDoubleAttribute("version"))) > version) {
        AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Version Conflict",
            "The file was created by a newer version of the software, some settings may be ignored.",
            "OK");
    }

    std::vector<Param*> parameters = serializeParams;
    if (paramsToSerialize == eSerializationParams::eSequencerOnly)
    {
        parameters = stepSeqParams;
    }

    patchName = patch->getStringAttribute("patchname");
    patchNameDirty = true;

    // iterate over all params and set the values if they exist in the xml
    for (auto &param : parameters) {
        if (param->serializationTag() != "") {
        fillValueIfExists(patch, param->serializationTag(), *param);
    }
    }

}
void SynthParams::readXMLPatchHost(const void* data, int sizeInBytes, eSerializationParams paramsToSerialize) {
    ScopedPointer<XmlElement> patch = AudioProcessor::getXmlFromBinary(data, sizeInBytes);
    fillValues(patch, paramsToSerialize);
}

void SynthParams::readXMLPatchStandalone(eSerializationParams paramsToSerialize) {
    // read the xml params into the synth params
    FileChooser openFileChooser("Please select the patch you want to read!", File::getSpecialLocation(File::userHomeDirectory), "*.xml");
    if (openFileChooser.browseForFileToOpen()) {
        File openedFile(openFileChooser.getResult());
        ScopedPointer<XmlElement> patch = XmlDocument::parse(openedFile);
        fillValues(patch, paramsToSerialize);
    }
}

SynthParams::~SynthParams() {
}

const char * SynthParams::getModSrcName(int index)
{
    if (index >= 0 && index < static_cast<int>(eModSource::nSteps)) {
        return modsourcenames[index];
    } else {
        return "unknown";
    }
}


String SynthParams::getShortModSrcName(int index)
{
    if (index >= 0 && index < static_cast<int>(eModSource::nSteps)) {
        return modSourceNamesShort[index];
    } else {
        return "?";
    }
}

int SynthParams::getAudioIndex()
{
    return positionIndex.load();
}

int SynthParams::getGUIIndex()
{
    return (positionIndex.load() + 1) % 2;
}
