#include "SynthParams.h"


namespace {
    static const char *lfowavenames[] = {
        "Sine", "Square", "Smpl+Hold", nullptr
    };

    static const char *onoffnames[] = {
        "Off", "On", nullptr
    };

    static const char *seqModeNames[] = {
        "Stop", "Play", "SyncHost", nullptr
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
const Colour SynthParams::envColour (0xffcbca63);
const Colour SynthParams::lfoColour (0xffb16565);
const Colour SynthParams::filterColour (0xff40ae69);
const Colour SynthParams::fxColour (0xff2b3240);
const Colour SynthParams::stepSeqColour (0xff564c43);
const Colour SynthParams::onOffSwitchEnabled (114, 136, 98);
const Colour SynthParams::onOffSwitchDisabled (102, 102, 102);
const Colour SynthParams::envelopeCurveLine (216, 202, 155);
const Colour SynthParams::envelopeCurveBackground (116, 101, 60);
const Colour SynthParams::waveformLine (185, 189, 190);
const Colour SynthParams::waveformBackground(85, 93, 104);
const Colour SynthParams::otherModulation(0, 0, 255); // add more different colours

SynthParams::SynthParams()
    : serializeParams{ &freq,
        // TODO: Think of another way to register all the struct params?
    //Oscillators PArams
    &osc[0].fine, &osc[0].coarse, &osc[0].panDir,&osc[0].vol,&osc[0].trngAmount,&osc[0].pulseWidth,&osc[0].waveForm,&osc[0].pitchModAmount1, &osc[0].pitchModAmount2,&osc[0].pitchModSrc1, &osc[0].pitchModSrc2,
    &osc[0].panModAmount1, &osc[0].panModAmount2, &osc[0].panModSrc1,&osc[0].panModSrc2,&osc[0].shapeModAmount1,&osc[0].shapeModAmount2,&osc[0].shapeModSrc1, &osc[0].shapeModSrc2,&osc[0].gainModAmount1,&osc[0].gainModAmount2,&osc[0].gainModSrc1,&osc[0].gainModSrc2,
    &osc[1].fine, &osc[1].coarse, &osc[1].panDir,&osc[1].vol,&osc[1].trngAmount,&osc[1].pulseWidth,&osc[1].waveForm,&osc[1].pitchModAmount1, &osc[1].pitchModAmount2,&osc[1].pitchModSrc1, &osc[1].pitchModSrc2,
    &osc[1].panModAmount1, &osc[1].panModAmount2, &osc[1].panModSrc1, &osc[1].panModSrc2,&osc[1].shapeModAmount1,&osc[1].shapeModAmount2,&osc[1].shapeModSrc1, &osc[1].shapeModSrc2,&osc[1].gainModAmount1,&osc[1].gainModAmount2,&osc[1].gainModSrc1,&osc[1].gainModSrc2,
    &osc[2].fine, &osc[2].coarse, &osc[2].panDir,&osc[2].vol,&osc[2].trngAmount,&osc[2].pulseWidth,&osc[2].waveForm,&osc[2].pitchModAmount1, &osc[2].pitchModAmount2,&osc[2].pitchModSrc1, &osc[2].pitchModSrc2,
    &osc[2].panModAmount1, &osc[2].panModAmount2, &osc[2].panModSrc1, &osc[0].panModSrc2,&osc[2].shapeModAmount1,&osc[2].shapeModAmount2,&osc[2].shapeModSrc1, &osc[2].shapeModSrc2,&osc[2].gainModAmount1,&osc[2].gainModAmount2,&osc[2].gainModSrc1,&osc[2].gainModSrc2,
    //Envelopes Params
    &env[0].attack, &env[0].decay, &env[0].sustain, &env[0].release, &env[0].attackShape, &env[0].decayShape, &env[0].releaseShape, &env[0].speedModAmount1, &env[0].speedModAmount2, &env[0].speedModSrc1, &env[0].speedModSrc2,
    &env[1].attack, &env[1].decay, &env[1].sustain, &env[1].release, &env[1].attackShape, &env[1].decayShape, &env[1].releaseShape, &env[1].speedModAmount1, &env[1].speedModAmount2, &env[1].speedModSrc1, &env[1].speedModSrc2,
    &envVol[0].attack, &envVol[0].decay, &envVol[0].sustain, &envVol[0].release, &envVol[0].attackShape, &envVol[0].decayShape, &envVol[0].releaseShape, &envVol[0].speedModAmount1, &envVol[0].speedModAmount2, &envVol[0].speedModSrc1, &envVol[0].speedModSrc2,
    //LFOs Params
    &lfo[0].fadeIn, &lfo[0].freq, &lfo[0].freqModSrc1, &lfo[0].freqModSrc2, &lfo[0].freqModAmount1, &lfo[0].freqModAmount2, &lfo[0].tempSync, &lfo[0].wave, &lfo[0].noteLength, &lfo[0].gainModSrc,
    &lfo[1].fadeIn, &lfo[1].freq, &lfo[1].freqModSrc1, &lfo[1].freqModSrc2, &lfo[1].freqModAmount1, &lfo[1].freqModAmount2, &lfo[1].tempSync, &lfo[1].wave, &lfo[1].noteLength, &lfo[1].gainModSrc,
    &lfo[2].fadeIn, &lfo[2].freq, &lfo[2].freqModSrc1, &lfo[2].freqModSrc2, &lfo[2].freqModAmount1, &lfo[2].freqModAmount2, &lfo[2].tempSync, &lfo[2].wave, &lfo[2].noteLength, &lfo[2].gainModSrc,
    //Filters Params
    &filter[0].lpCutoff, &filter[0].hpCutoff, &filter[0].resonance, &filter[0].lpModAmount1, &filter[0].lpModAmount2, &filter[0].lpCutModSrc1, &filter[0].lpCutModSrc2, &filter[0].hpModAmount1, &filter[0].hpModAmount2, &filter[0].hpCutModSrc1, &filter[0].hpCutModSrc2, &filter[0].resModAmount1, &filter[0].resModAmount2, &filter[0].resonanceModSrc1, &filter[0].resonanceModSrc2,
    &filter[1].lpCutoff, &filter[1].hpCutoff, &filter[1].resonance, &filter[1].lpModAmount1, &filter[1].lpModAmount2, &filter[1].lpCutModSrc1, &filter[1].lpCutModSrc2, &filter[1].hpModAmount1, &filter[1].hpModAmount2, &filter[1].hpCutModSrc1, &filter[1].hpCutModSrc2, &filter[1].resModAmount1, &filter[1].resModAmount2, &filter[1].resonanceModSrc1, &filter[1].resonanceModSrc2,
//Others
    &seqPlayMode, &seqNumSteps, &seqStepSpeed, &seqStepLength, &seqTriplets, &seqStep0, &seqStep1, &seqStep2, &seqStep3, &seqStep4, &seqStep5, &seqStep6, &seqStep7,
    &seqStepActive0, &seqStepActive1, &seqStepActive2, &seqStepActive3, &seqStepActive4, &seqStepActive5, &seqStepActive6, &seqStepActive7, &seqRandomMin, &seqRandomMax,
    &delayDryWet, &delayFeedback, &delayTime, &delaySync, &delayDividend, &delayDivisor, &delayCutoff, &delayResonance, &delayTriplet, &delayRecordFilter, &delayReverse,
    &lowFiActivation, &nBitsLowFi }
    , stepSeqParams{ &seqPlayMode, &seqNumSteps, &seqStepSpeed, &seqStepLength, &seqTriplets, &seqStep0, &seqStep1, &seqStep2, &seqStep3, &seqStep4, &seqStep5, &seqStep6, &seqStep7,
    &seqStepActive0, &seqStepActive1, &seqStepActive2, &seqStepActive3, &seqStepActive4, &seqStepActive5, &seqStepActive6, &seqStepActive7, &seqRandomMin, &seqRandomMax }
    , freq("Freq", "freq", "freq", "Hz", 220.f, 880.f, 440.f)
    , delayDryWet("Dry / Wet", "delWet", "Delay dry/wet", "", 0.f, 1.f, 0.f)
    , delayFeedback("Feedback", "delFeed", "Delay feedback", "", 0.f, 1.f, 0.f)
    , delayTime("Time", "delTime", "Delay time", "ms", 1., 5000., 1000.)
    , delaySync("Tempo Sync", "delSync", "Delay sync", eOnOffToggle::eOff, onoffnames)
    , delayDividend("SyncDel Dividend", "delDivd", "Delay dividend", "", 1, 5, 1)
    , delayDivisor("SyncDel Divisor", "delDivs", "Delay divisor", "", 1, 32, 4)
    , delayCutoff("Cutoff", "delCut", "Delay cutoff", "Hz", 10.f, 20000.f, 20000.f)
    , delayResonance("Resonance", "delRes", "Delay resonance", "dB", -25.f, 0.f, 0.f)
    , delayTriplet("Delay Triplet", "delTrip", "Delay triplet", eOnOffToggle::eOff, onoffnames)
    , delayRecordFilter("Delay Record", "delRec", "Delay record filter", eOnOffToggle::eOff, onoffnames)
    , delayReverse("Delay Reverse", "delRev", "Delay reverse", eOnOffToggle::eOff, onoffnames)
    , lowFiActivation("Activation", "lowFiActivation", "LowFi Active", eOnOffToggle::eOff, onoffnames)
    , nBitsLowFi("Bit Degr", "nBitsLowFi", "Number Bits", "bit", 1.f, 16.f, 16.f)
    , chorDelayLength("Width", "chorWidth", "Chorus Width", "s", .02f, .08f, .05f)
    , chorModRate("Rate", "chorRate", "Chorus Rate", "Hz", 0.f, 1.5f, 0.5f)
    , chorDryWet("Dry/Wet", "ChorAmount", "Chorus Dry/Wet", "", 0.f, 1.f, 0.f)
    , chorModDepth("Depth", "ChorDepth", "Chorus Depth", "ms", 1.f, 20.f, 15.f)
    , clippingFactor("Clipping", "clippingFactor", "Clipping", "dB", 0.f, 25.f, 0.0f)
    , seqMode("SeqMode", "seqMode", "SeqMode", eSeqModes::eSeqStop, seqModeNames)
    , seqPlayMode("SeqPlayMode", "seqPlayMode", "SeqPlayMode", eSeqPlayModes::eSequential, seqPlayModeNames)
    , seqLastPlayedStep("Last Played Step", "lastPlayedStep", "Last Played Step", "", 0.0f, 7.0f, 0.0f)
    , seqNumSteps("Steps", "seqNumSteps", "Steps", "", 1.0f, 8.0f, 8.0f)
    , seqStepSpeed("Speed", "seqStepSpeed", "Speed", "qn", 0.0625f, 4.0f, 1.0f)
    , seqStepLength("Length", "seqNoteLength", "Length", "qn", 0.0625f, 4.0f, 1.0f)
    , seqTriplets("Seq Triplets", "seqTriplets", "Seq Triplets", eOnOffToggle::eOff, onoffnames)
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

    envVol[0].setName("vol env");
    env[0].setName("env 2");
    env[1].setName("env 3");

    lfo[0].setName("lfo 1");
    lfo[1].setName("lfo 2");
    lfo[2].setName("lfo 3");

    filter[0].setName("filter 1");
    filter[1].setName("filter 2");
}

SynthParams::Osc::Osc()
    : fine("fine", "fine", "OSC1 f.tune", "ct", -100.f, 100.f, 0.f)
    , coarse("coarse", "coarse", "OSC1 c.tune", "st", -11.f, 11.f, 0.f)
    , trngAmount("trianlge", "trngAmount", "OSC triangle amount", "prct", 0.0f, 1.0f, 0.0f)
    , pulseWidth("width", "pulseWidth", "OSC pulsewidth", "prct", 0.01f, 0.99f, 0.5f)
    , waveForm("Waveform", "oscWaveform", "OSC1 Waveform", eOscWaves::eOscSquare, waveformNames)
    , panDir("pan", "panDir", "pan direction", "pct", -100.f, 100.f, 0.f)
    , vol("gain", "vol", "Vol", "dB", -96.f, 12.f, -6.f)
    // ModAmounts and ModSources
    , panModAmount1("OSC PanModAmount1", "OSCPanModAmount1", "OSC Pan ModAmount 1", "", 0.f, 100.f, 0.f)
    , panModAmount2("OSC PanModAmount2", "OSCPanModAmount2", "OSC Pan ModAmount 2", "", 0.f, 100.f, 0.f)
    , panModSrc1("OSC PanModSrc1", "OSCPanModSrc1", "OSC Pan ModSource 1", eModSource::eNone, modsourcenames)
    , panModSrc2("OSC PanModSrc2", "OSCPanModSrc2", "OSC Pan ModSource 2", eModSource::eNone, modsourcenames)
    , shapeModAmount1("OSC ShapeModAmount1", "OSCShapeModAmount1", "OSC Shape ModAmount 1", "", 0.f, 1.f, 0.f)
    , shapeModAmount2("OSC ShapeModAmount2", "OSCShapeModAmount2", "OSC Shape ModAmount 2", "", 0.f, 1.f, 0.f)
    , shapeModSrc1("OSC ShapeModSrc1", "OSCShapeModSrc1", "OSC Shape ModSource 1", eModSource::eNone, modsourcenames)
    , shapeModSrc2("OSC ShapeModSrc2", "OSCShapeModSrc2", "OSC Shape ModSource 2", eModSource::eNone, modsourcenames)
    , pitchModAmount1("OSC PitchModAmount1", "OSCPitchModAmount1", "OSC Pitch ModAmount 1", "st", 0.f, 12.f, 0.f)
    , pitchModAmount2("OSC PitchModAmount2", "OSCPitchModAmount2", "OSC Pitch ModAmount 2", "st", 0.f, 12.f, 0.f)
    , pitchModSrc1("OSC PitchModSrc1", "OSCPitchModSrc1", "OSC Pitch ModSource 1", eModSource::eNone, modsourcenames)
    , pitchModSrc2("OSC PitchModSrc2", "OSCPitchModSrc2", "OSC Pitch ModSource 2", eModSource::eNone, modsourcenames)
    , gainModAmount1("OSC GainModAmount1", "OSCGainModAmount1", "OSC Gain ModAmount 1", "dB", 0.f, 96.f, 0.0f)
    , gainModAmount2("OSC GainModAmount2", "OSCGainModAmount2", "OSC Gain ModAmount 2", "dB", 0.f, 96.f, 0.0f)
    , gainModSrc1("OSC GainModSrc1", "OSCGainModSrc1", "OSC Gain ModSource 1", eModSource::eNone, modsourcenames)
    , gainModSrc2("OSC GainModSrc2", "OSCGainModSrc2", "OSC Gain ModSource 2", eModSource::eNone, modsourcenames)
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
    , speedModAmount1("ENV SpeedModAmount1", "ENVSpeedModAmount1", "ENV Speed ModAmount 1", "", 0.f, 1.f, 0.0f)
    , speedModAmount2("ENV SpeedModAmount2", "ENVSpeedModAmount2", "ENV Speed ModAmount 2", "", 0.f, 1.f, 0.0f)
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
    : freq("LFO Freq", "LFOfreq", "LFO Freq", "Hz", .01f, 50.f, 1.f)
    , wave("LFO Wave", "LFO1wave", "LFO Waveform", eLfoWaves::eLfoSine, lfowavenames)
    , tempSync("LFO TempoSync", "LFOtempoSyncSwitch", "LFO TempoSync", eOnOffToggle::eOff, onoffnames)
    , noteLength("LFO Note Length", "LFOnotelength", "LFO Note Length", "", 1.f, 32.f, 4.f)
    , fadeIn("LFO FadeIn", "LFOFadein", "LFO Fade In", "s", 0.f, 10.f, 0.f)
    // ModAmounts and Sources
    , freqModAmount1("LFO FreqModAmount1", "LFOFreqModAmount1", "LFO Freq ModAmount 1", "oct", 0.f, 4.f, 0.f)
    , freqModAmount2("LFO FreqModAmount2", "LFOFreqModAmount2", "LFO Freq ModAmount 2", "oct", 0.f, 4.f, 0.f)
    , freqModSrc1("LFO Freq ModSrc1", "LFOFreqModSrc1", "LFO Freq ModSource 1", eModSource::eNone, modsourcenames)
    , freqModSrc2("LFO Freq ModSrc2", "LFOFreqModSrc2", "LFO Freq ModSource 2", eModSource::eNone, modsourcenames)
    , gainModSrc("LFO Gain ModSrc", "LFOGainModSrc", "LFO Gain ModSource", eModSource::eNone, modsourcenames)
{
}

SynthParams::Filter::Filter()
    : passtype("FILTER Type", "FILTERType", "FILTER Type", eBiquadFilters::eLowpass, biquadFilters)
    , lpCutoff("LP Cutoff", "lpCutoff", "LP Cutoff", "Hz", 10.f, 20000.f, 20000.f)
    , hpCutoff("HP Cutoff", "hpCutoff", "HP Cutoff", "Hz", 10.f, 20000.f, 10.f)
    , resonance("FILTER Res", "FILTERResonance", "FILTER Resonance", "", 0.f, 10.f, 0.f)
    // ModAmounts and ModSources
    , lpModAmount1("FILTER Lc ModAmount1", "FILTERLcModAmount1", "FILTER Lc ModAmount 1", "oct", 0.f, 8.f, 0.f)
    , lpModAmount2("FILTER Lc ModAmnout2", "FILTERLcModAmount2", "FILTER Lc ModAmount 2", "oct", 0.f, 8.f, 0.f)
    , hpModAmount1("FILTER Hc ModAmount1", "FILTERHcModAmount1", "FILTER Hc ModAmount 1", "oct", 0.f, 8.f, 0.f)
    , hpModAmount2("FILTER Hc ModAmount2", "FILTERHcModAmount2", "FILTER Hc ModAmount 2", "oct", 0.f, 8.f, 0.f)
    , resModAmount1("FILTER Res ModAmount1", "FILTERResModAmount1", "FILTER Res ModAmount 1", "", 0.f, 10.f, 0.f)
    , resModAmount2("FILTER Res ModAmount2", "FILTERResModAmount2", "FILTER Res ModAmount 2", "", 0.f, 10.f, 0.f)
    , lpCutModSrc1("FILTER Lc ModSrc1", "FILTERLcModSrc1", "FILTER Lc ModSource 1", eModSource::eNone, modsourcenames)
    , lpCutModSrc2("FILTER Lc ModSrc2", "FILTERLcModSrc2", "FILTER Lc ModSource 2", eModSource::eNone, modsourcenames)
    , hpCutModSrc1("FILTER Hc ModSrc1", "FILTERHcModSrc1", "FILTER Hc ModSource 1", eModSource::eNone, modsourcenames)
    , hpCutModSrc2("FILTER Hc ModSrc2", "FILTERHcModSrc2", "FILTER Hc ModSource 2", eModSource::eNone, modsourcenames)
    , resonanceModSrc1("FILTER Res ModSrc1", "FILTERResModSrc1", "FILTER Res ModSource 1", eModSource::eNone, modsourcenames)
    , resonanceModSrc2("FILTER Res ModSrc2", "FILTERResModSrc2", "FILTER Res ModSource 2", eModSource::eNone, modsourcenames)
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

    std::vector<Param*> parameters = serializeParams;
    if (paramsToSerialize == eSerializationParams::eSequencerOnly)
    {
        parameters = stepSeqParams;
    }

    // iterate over all params and insert them into the tree
    for (auto &param : parameters) {
        float value = param->getUI();
        if (param->serializationTag() != "") {
        addElement(patch, param->serializationTag(), value);
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
            return SynthParams::lfoColour.withSaturation(1.0f).brighter();
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
    if (patch->getChildByName(paramName) != NULL) {
        param.setUI(static_cast<float>(patch->getChildByName(paramName)->getDoubleAttribute("value")));
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
    }
    else 
    {
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
