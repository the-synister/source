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
        "Lowpass", "Highpass", nullptr
    };
    
    static const char *modsourcenames[] = {
        "None", "LFO1", nullptr
    };
    
    static const char *waveformNames[] = {
        "Square", "Saw", "White-noise"
    };
}

SynthParams::SynthParams()
: serializeParams{ &freq,
    &lfo1freq, &lfo1wave, &lfoFadein,&lfo1TempSync, &noteLength,
    &osc1fine, &osc1coarse, &osc1lfo1depth,&osc1trngAmount, &osc1PitchRange, &osc1pulsewidth, 
    &lpCutoff, &biquadResonance, &ladderCutoff, &ladderRes,
    &lpCutoff, &biquadResonance, &ladderCutoff, &ladderRes, &lpModSource, &lpModAmout, &keyVelocityLevel,
    &envAttack, &envDecay, &envSustain, &envRelease, &envAttackShape, &envDecayShape, &envReleaseShape, &keyVelToEnv,
    &seqPlayMode, &seqNumSteps, &seqStepSpeed, &seqStepLength, &seqTriplets, &seqStep0, &seqStep1, &seqStep2, &seqStep3, &seqStep4, &seqStep5, &seqStep6, &seqStep7,
    &seqStepActive0, &seqStepActive1, &seqStepActive2, &seqStepActive3, &seqStepActive4, &seqStepActive5, &seqStepActive6, &seqStepActive7, &seqRandomMin, &seqRandomMax,
    &panDir, &vol, 
    &delayDryWet, &delayFeedback, &delayTime, &delaySync, &delayDividend, &delayDivisor, &delayCutoff, &delayResonance, &delayTriplet, &delayRecordFilter, &delayReverse }
, stepSeqParams{ &seqPlayMode, &seqNumSteps, &seqStepSpeed, &seqStepLength, &seqTriplets, &seqStep0, &seqStep1, &seqStep2, &seqStep3, &seqStep4, &seqStep5, &seqStep6, &seqStep7,
    &seqStepActive0, &seqStepActive1, &seqStepActive2, &seqStepActive3, &seqStepActive4, &seqStepActive5, &seqStepActive6, &seqStepActive7, &seqRandomMin, &seqRandomMax}
, freq("Freq", "freq", "Hz", 220.f, 880.f, 440.f)
, lfo1freq("Freq", "lfo1freq", "Hz", .01f, 50.f, 1.f)
, lfo1TempSync("TempoSyncSwitch", "tempoSyncSwitch", eOnOffToggle::eOff, onoffnames)
, noteLength("Note Length", "notelength", "", 1.f, 32.f, 4.f)
, lfo1wave("Wave", "lfo1wave", eLfoWaves::eLfoSine, lfowavenames)
, osc1fine("f.tune", "osc1fine", "ct", -100.f, 100.f, 0.f)
, osc1coarse("c.tune", "osc1coarse", "st", -11.f, 11.f, 0.f)
, osc1lfo1depth("mod", "osc1lfo1depth", "st", 0.f, 12.f, 0.f)
, passtype("Filter Type", "filterType", eBiquadFilters::eLowpass, biquadFilters)
, lpCutoff("LP Cut", "lpCutoff", "Hz", 10.f, 20000.f, 20000.f)
, biquadResonance("Filter Reso", "filterResonance", "dB", -25.f, 25.f, 0.f)
, hpCutoff("HP Cut", "hpCutoff", "Hz", 10.f, 20000.f, 10.f)
, lpModSource("LP ModSrc", "lpMod", eModSource::eNone, modsourcenames)
, osc1Waveform("Osc Waveform", "oscWaveform", eOscWaves::eOscSquare, waveformNames)
, lpModAmout("LP ModAmnt", "lpModAmout", "prct", 0.f, 100.f, 0.f)
, osc1trngAmount("trianlge", "osc1trngAmount", "prct", 0.0f, 1.0f, 0.0f)
, osc1PitchRange("Pitch", "osc1PitchRange", "st", 0.f, 12.f, 0.f)
, envAttack("Attack", "envAttack", "s", 0.001f, 5.0f, 0.005f)
, envDecay("Decay", "envDecay", "s", 0.001f, 5.0f, 0.05f)
, envSustain("Sustain", "envSustain", "dB", -96.0f, 0.0f, -5.0f)
, envRelease("Release", "envRelease", "s", 0.001f, 5.0f, 0.5f)
, keyVelToEnv("keyVel to Env", "veloToKey", "", 0.0f, 1.0f, 0.0f)
, envAttackShape("Attack Shape", "envAttackShape", "", 0.01f, 10.0f, 1.0f)
, envDecayShape("Decay Shape", "envDecayShape", "", 0.01f, 10.0f, 1.0f)
, envReleaseShape("Release Shape", "envReleaseShape", "", 0.01f, 10.0f, 1.0f)
, osc1pulsewidth("Width", "osc1pulsewidth", "prct", 0.01f, 0.99f, 0.5f)
, panDir("Pan", "panDir", "pct", -100.f, 100.f, 0.f)
, keyVelocityLevel("Velocity Sense", "keyVelocityLevel", "dB", 0.f, 96.f, 0.0f)
, vol("Vol", "vol", "dB", 0.f, 1.f, .5f)
, ladderCutoff("LadderFreq", "ladderCutoff", "Hz", 10.f, 20000.f, 20000.f)
, ladderRes("LadderRes", "ladderRes", "  ", 0.f, 10.f, 0.f)
, lfoFadein("FadeIn","lfoFadein", "s", 0.f, 10.f, 0.f)
, delayDryWet("Dry / Wet", "delWet", "%", 0.f, 1.f, 0.f)
, delayFeedback("Feedback", "delFeed", "%", 0.f, 1.f, 0.f)
, delayTime("Time", "delTime", "ms", 1., 5000., 1000.)
, delaySync("Tempo Sync", "delSync", eOnOffToggle::eOff, onoffnames)
, delayDividend("SyncDel Dividend", "delDivd", "", 1, 5, 1)
, delayDivisor("SyncDel Divisor", "delDivs", "", 1, 32, 4)
, delayCutoff("Cutoff", "delCut", "Hz", 10.f, 20000.f, 20000.f)
, delayResonance("Resonance", "delRes", "dB", -25.f, 0.f, 0.f)
, delayTriplet("Delay Triplet", "delTrip", eOnOffToggle::eOff, onoffnames)
, delayRecordFilter("Delay Record", "delRec", eOnOffToggle::eOff, onoffnames)
, delayReverse("Delay Reverse", "delRev", eOnOffToggle::eOff, onoffnames)
, seqMode("SeqMode", "seqMode", eSeqModes::eSeqStop, seqModeNames)
, seqPlayMode("SeqPlayMode", "seqPlayMode", eSeqPlayModes::eSequential, seqPlayModeNames)
, seqLastPlayedStep("Last Played Step", "lastPlayedStep", "", 0.0f, 7.0f, 0.0f)
, seqNumSteps("Steps", "seqNumSteps", "steps", 1.0f, 8.0f, 8.0f)
, seqStepSpeed("Speed", "seqStepSpeed", "qn", 0.0625f, 4.0f, 1.0f)
, seqStepLength("Length", "seqNoteLength", "qn", 0.0625f, 4.0f, 1.0f)
, seqTriplets("Seq Triplets", "seqTriplets", eOnOffToggle::eOff, onoffnames)
, seqRandomMin("Min", "seqRandomMin", "", 0.0f, 127.0f, 0.0f)
, seqRandomMax("Max", "seqRandomMax", "", 0.0f, 127.0f, 127.0f)
, seqStep0("Step 0", "seqNote0", "", 0.0f, 127.0f, 60.0f)
, seqStep1("Step 1", "seqNote1", "", 0.0f, 127.0f, 62.0f)
, seqStep2("Step 2", "seqNote2", "", 0.0f, 127.0f, 64.0f)
, seqStep3("Step 3", "seqNote3", "", 0.0f, 127.0f, 65.0f)
, seqStep4("Step 4", "seqNote4", "", 0.0f, 127.0f, 67.0f)
, seqStep5("Step 5", "seqNote5", "", 0.0f, 127.0f, 69.0f)
, seqStep6("Step 6", "seqNote6", "", 0.0f, 127.0f, 71.0f)
, seqStep7("Step 7", "seqNote7", "", 0.0f, 127.0f, 72.0f)
, seqStepActive0("Step 0 Active", "seqStepActive0", eOnOffToggle::eOn, onoffnames)
, seqStepActive1("Step 1 Active", "seqStepActive1", eOnOffToggle::eOn, onoffnames)
, seqStepActive2("Step 2 Active", "seqStepActive2", eOnOffToggle::eOn, onoffnames)
, seqStepActive3("Step 3 Active", "seqStepActive3", eOnOffToggle::eOn, onoffnames)
, seqStepActive4("Step 4 Active", "seqStepActive4", eOnOffToggle::eOn, onoffnames)
, seqStepActive5("Step 5 Active", "seqStepActive5", eOnOffToggle::eOn, onoffnames)
, seqStepActive6("Step 6 Active", "seqStepActive6", eOnOffToggle::eOn, onoffnames)
, seqStepActive7("Step 7 Active", "seqStepActive7", eOnOffToggle::eOn, onoffnames)
, positionIndex(0)
{
    positionInfo[0].resetToDefault();
    positionInfo[1].resetToDefault();
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
    if (openFileChooser.browseForFileToOpen())
{
        File openedFile(openFileChooser.getResult());
        ScopedPointer<XmlElement> patch = XmlDocument::parse(openedFile);
        fillValues(patch, paramsToSerialize);
    }
}

SynthParams::~SynthParams() {
}

int SynthParams::getAudioIndex()
{
    return positionIndex.load();
}

int SynthParams::getGUIIndex()
{
    return (positionIndex.load() + 1) % 2;
}
