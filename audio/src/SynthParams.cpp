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
        "None", "Aftertouch", "KeyBipolar", "InvertedVelocity", "Velocity", "Foot", "ExpPedal", "Modwheel", "Pitchbend",
        "LFO1", "LFO2", "LFO3", "VolEnvelope", "Envelope2", "Envelope3", nullptr
    };

    static const char *waveformNames[] = {
        "Square", "Saw", "White-noise"
    };
}

SynthParams::SynthParams()
    : serializeParams{ &freq,
    &osc[0].fine, &osc[0].coarse, &osc[0].pitchModAmount2,&osc[0].trngAmount, &osc[0].pitchModAmount1, &osc[0].pulseWidth, &osc[0].pitchModSrc1, &osc[0].pitchModSrc2,
    &osc[0].shapeModSrc1, &osc[0].shapeModSrc2, &osc[0].panDir, &osc[0].vol, &osc[0].volModAmount1,
    &osc[1].fine, &osc[1].coarse, &osc[1].pitchModAmount2,&osc[1].trngAmount, &osc[1].pitchModAmount1, &osc[1].pulseWidth, &osc[1].pitchModSrc1, &osc[1].pitchModSrc2, &osc[1].shapeModSrc1, &osc[1].shapeModSrc2, &osc[1].panDir, &osc[1].vol, &osc[1].volModAmount1,
    &osc[2].fine, &osc[2].coarse, &osc[2].pitchModAmount2,&osc[2].trngAmount, &osc[2].pitchModAmount1, &osc[2].pulseWidth, &osc[2].pitchModSrc1, &osc[2].pitchModSrc2, &osc[2].shapeModSrc1, &osc[2].shapeModSrc2, &osc[2].panDir, &osc[2].vol, &osc[2].volModAmount1,
  /*  &lp1Cutoff, &filter1Resonance,
    &lp1CutModSrc1, &lp1CutModSrc2, &lp1ModAmount1, &lp1ModAmount2, &hp1Cutoff, &hp1CutModSrc1, &hp1CutModSrc2, &hp1ModAmount1, &hp1ModAmount2, &filter1ResonanceModSrc1, &filter1ResonanceModSrc2,
    */
   /* TODO: Register Env, filter, and lfo params*/
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
    , positionIndex(0)
{
    positionInfo[0].resetToDefault();
    positionInfo[1].resetToDefault();

    osc[0].setName("Osc1");
}

SynthParams::Osc::Osc()
    : fine("f.tune", "fine", "OSC1 f.tune", "ct", -100.f, 100.f, 0.f)
    , coarse("c.tune", "coarse", "OSC1 c.tune", "st", -11.f, 11.f, 0.f)
    , pitchModAmount2("mod", "pitchModAmount2", "OSC1 LFO1 depth", "st", 0.f, 12.f, 0.f)
    , trngAmount("trianlge", "trngAmount", "OSC1 triangle amount", "prct", 0.0f, 1.0f, 0.0f)
    , pitchModAmount1("Pitch", "pitchModAmount1", "OSC1 pitch range", "st", 0.f, 12.f, 0.f)
    , pitchModSrc1("OSC1 PitchModSrc1", "osc1PitchModSrc1", "OSC1 pitch modSrc1", eModSource::eNone, modsourcenames)
    , pitchModSrc2("OSC1 PitchModSrc2", "osc1PitchModSrc2", "OSC1 pitch modSrc2", eModSource::eNone, modsourcenames)
    , shapeModSrc1("OSC1 PW ModSrc1", "shapeModSrc1", "OSC1 pulse width modSrc1", eModSource::eNone, modsourcenames)
    , shapeModSrc2("OSC1 PW ModSrc2", "shapeModSrc2", "OSC1 pulse width modSrc2", eModSource::eNone, modsourcenames)
    , pulseWidth("Width", "pulseWidth", "OSC1 pulsewidth", "prct", 0.01f, 0.99f, 0.5f)
    , shapeModAmount("Width Mod", "shapeModAmount", "OSC1 PWM", "", 0.f, 1.f, 0.f)
    , waveForm("Waveform", "oscWaveform", "OSC1 Waveform", eOscWaves::eOscSquare, waveformNames)
    , panDir("Pan", "panDir", "pan direction", "pct", -100.f, 100.f, 0.f)
    , vol("Vol", "vol", "Vol", "dB", -96.f, 12.f, -6.f)
    , volModAmount1("Velocity Sense", "volModAmount1", "Key velocity level", "dB", 0.f, 96.f, 0.0f)
{
}

SynthParams::EnvBase::EnvBase()
: envAttack("Attack", "envAttack", "Amp Env attack", "s", 0.001f, 5.0f, 0.005f)
, envRelease("Release", "envRelease", "Amp Env release", "s", 0.001f, 5.0f, 0.5f)
, keyVelToEnv("keyVel to Env", "", "Key velocity to Amp Env", "veloToKey", 0.0f, 1.0f, 0.0f)
, envAttackShape("Attack Shape", "envAttackShape", "Amp Env attack shape", "", 0.01f, 10.0f, 1.0f)
, envDecayShape("Decay Shape", "envDecayShape", "Amp Env decay shape", "", 0.01f, 10.0f, 1.0f)
, envReleaseShape("Release Shape", "envReleaseShape", "Amp Env release shape", "", 0.01f, 10.0f, 1.0f)
, envDecay("Decay", "envDecay", "Amp Env decay", "s", 0.001f, 5.0f, 0.05f)
{
}

SynthParams::EnvVol::EnvVol()
: EnvBase()
, envSustain("Sustain", "envSustain", "Amp Env sustain", "dB", 0.f, 1.f, -6.f)
, envVolSpeedModSrc1("VolEnv Speed ModSrc1", "volEnvSpeedModSrc1", "Vol Env modSrc1", eModSource::eNone, modsourcenames)
, envVolSpeedModSrc2("VolEnv Speed ModSrc2", "volEnvSpeedModSrc2", "Vol Env modSrc2", eModSource::eNone, modsourcenames)
{
}

SynthParams::Env::Env()
:  EnvBase()
, envSustain("Sustain", "envSustain", "Env1 sustain", " ", 0.f, 1.f, 1.f)
, env2SpeedModSrc1("Env2 Speed ModSrc1", "env2SpeedModSrc1", "Env2 speed modSrc1", eModSource::eNone, modsourcenames)
, env2SpeedModSrc2("Env2 Speed ModSrc2", "env2SpeedModSrc2", "Env2 speed modSrc2", eModSource::eNone, modsourcenames)
{
}

SynthParams::Lfo::Lfo()
: freq("Freq", "lfo1freq", "LFO1 freq", "Hz", .01f, 50.f, 1.f)
, wave("Wave", "lfo1wave", "LFO1 waveform", eLfoWaves::eLfoSine, lfowavenames)
, tempSync("TempoSync", "tempoSyncSwitch", "LFO1 TempoSync", eOnOffToggle::eOff, onoffnames)
, freqModSrc1("LFO1 Freq ModSrc1", "LFO1FreqModSrc1", "LFO1 freq modSrc1", eModSource::eNone, modsourcenames)
, freqModSrc2("LFO1 Freq ModSrc2", "LFO1FreqModSrc2", "LFO1 freq modSrc2", eModSource::eNone, modsourcenames)
, gainModSrc1("LFO1 Gain ModSrc1", "LFO1GainModSrc1", "LFO1 gain modSrc1", eModSource::eNone, modsourcenames)
, gainModSrc2("LFO1 Gain ModSrc2", "LFO1GainModSrc2", "LFO1 gain modSrc2", eModSource::eNone, modsourcenames)
, noteLength("Note Length", "notelength", "LFO1 Note Length", "", 1.f, 32.f, 4.f)
, fadeIn("FadeIn", "lfoFadein", "LFO1 fade-in", "s", 0.f, 10.f, 0.f)
{
}

SynthParams::Filter::Filter()
: passtype("Filter Type", "filterType", "Filter type", eBiquadFilters::eLowpass, biquadFilters)
, lpCutoff("LP1 Cut", "lp1Cutoff", "LP1 filter cutoff", "Hz", 10.f, 20000.f, 20000.f)
, hpCutoff("HP1 Cut", "hp1Cutoff", "HP1 filter cutoff", "Hz", 10.f, 20000.f, 10.f)
, lpCutModSrc1("LP1 Cut ModSrc1", "lp1CutModSrc1", "LP1 cut modSrc1", eModSource::eNone, modsourcenames)
, lpCutModSrc2("LP1 Cut ModSrc2", "lp1CutModSrc2", "LP1 cut modSrc2", eModSource::eNone, modsourcenames)
, lpModAmount1("LP1 ModAmnt1", "lp1ModAmout1", "LP1 mod amount1", "oct", 0.f, 8.f, 0.f)
, lpModAmount2("LP1 ModAmnt2", "lp1ModAmout2", "LP1 mod amount2", "oct", 0.f, 8.f, 0.f)
, hpCutModSrc1("HP1 Cut ModSrc1", "hp1CutModSrc1", "HP1 cut modSrc1", eModSource::eNone, modsourcenames)
, hpCutModSrc2("HP1 Cut ModSrc2", "hp1CutModSrc2", "HP1 cut modSrc2", eModSource::eNone, modsourcenames)
, hpModAmount1("HP1 ModAmnt1", "hp1ModAmount1", "HP1 mod amount1", "oct", 0.f, 8.f, 0.f)
, hpModAmount2("HP1 ModAmnt2", "hp1ModAmount2", "HP1 mod amount2", "oct", 0.f, 8.f, 0.f)
, resonance("Filter1 Reso", "filter1Resonance", "Filter1 resonance", "", 0.f, 10.f, 0.f)
, resonanceModSrc1("Filter1 Res ModSrc1", "filter1ResModSrc1", "Filter1 resonance modSrc1", eModSource::eNone, modsourcenames)
, resonanceModSrc2("Filter1 Res ModSrc2", "filter1ResModSrc2", "Filter1 resonance modSrc2", eModSource::eNone, modsourcenames)
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

int SynthParams::getAudioIndex()
{
    return positionIndex.load();
}

int SynthParams::getGUIIndex()
{
    return (positionIndex.load() + 1) % 2;
}
