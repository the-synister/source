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
}

SynthParams::SynthParams()
: serializeParams{ &freq,
    &lfo1freq, &lfo1wave,
    &osc1fine, &osc1coarse, &osc1lfo1depth,&osc1trngAmount, &osc1PitchRange, &osc1pulsewidth,
    &lpCutoff, &biquadResonance, &ladderCutoff, &ladderRes,
    &lpCutoff, &biquadResonance, &ladderCutoff, &ladderRes, &lpModSource, &lpModAmout,
    &envAttack, &envDecay, &envSustain, &envRelease, &envAttackShape, &envDecayShape, &envReleaseShape, &keyVelToEnv,
    &seqPlayMode, &seqNumSteps, &seqStepSpeedIndex, &seqStepLengthIndex, &seqStep1, &seqStep2, &seqStep3, &seqStep4, &seqStep5, &seqStep6, &seqStep7, &seqStep8,
    &seqStepPlay1, &seqStepPlay2, &seqStepPlay3, &seqStepPlay4, &seqStepPlay5, &seqStepPlay6, &seqStepPlay7, &seqStepPlay8, &seqRandomMin, &seqRandomMax,
    &panDir, &vol, 
    &delayDryWet, &delayFeedback, &delayTime, &delaySync, &delayDividend, &delayDivisor, &delayCutoff, &delayResonance, &delayTriplet, &delayRecordFilter, &delayReverse }
, freq("Freq", "freq", "Hz", 220.f, 880.f, 440.f)
, lfo1freq("Freq", "lfo1freq", "Hz", .01f, 50.f, 1.f)
, lfo1wave("Wave", "lfo1wave", eLfoWaves::eLfoSine, lfowavenames)
, osc1fine("f.tune", "osc1fine", "ct", -100.f, 100.f, 0.f)
, osc1coarse("c.tune", "osc1coarse", "st", -11.f, 11.f, 0.f)
, osc1lfo1depth("mod", "osc1lfo1depth", "st", 0.f, 12.f, 0.f)
, passtype("Filter Type", "filterType", eBiquadFilters::eLowpass, biquadFilters)
, lpCutoff("LP Cut", "lpCutoff", "Hz", 10.f, 20000.f, 20000.f)
, biquadResonance("Filter Reso", "filterResonance", "dB", -25.f, 25.f, 0.f)
, hpCutoff("HP Cut", "hpCutoff", "Hz", 10.f, 20000.f, 10.f)
, lpModSource("LP ModSrc", "lpMod", eModSource::eNone, modsourcenames)
, lpModAmout("LP ModAmnt", "lpModAmout", "prct", 0.f, 100.f, 0.f)
, osc1trngAmount("trianlge", "osc1trngAmount", "prct", 0.0f, 1.0f, 0.0f)
, osc1PitchRange("Pitch", "osc1PitchRange", "st", 0.f, 12.f, 0.f)
, envAttack("Attack", "envAttack", "s", 0.001f, 5.0f, 0.005f)
, envDecay("Decay", "envDecay", "s", 0.001f, 5.0f, 0.05f)
, envSustain("Sustain", "envSustain", "dB", -96.0f, 0.0f, -5.0f)
, envRelease("Release", "envRelease", "s", 0.001f, 5.0f, 0.5f)
, keyVelToEnv("keyVel to Env", "", "veloToKey", 0.0f, 1.0f, 0.0f) // 2nd and 3rd param swapped?
, envAttackShape("Attack Shape", "envAttackShape", "", 0.01f, 10.0f, 1.0f)
, envDecayShape("Decay Shape", "envDecayShape", "", 0.01f, 10.0f, 1.0f)
, envReleaseShape("Release Shape", "envReleaseShape", "", 0.01f, 10.0f, 1.0f)
, osc1pulsewidth("Width", "osc1pulsewidth", "prct", 0.01f, 0.99f, 0.5f)
, osc1WaveForm("Waveform", "Waveform", "int", 1.0f, 3.0f, 1.0f)
, panDir("Pan", "panDir", "pct", -100.f, 100.f, 0.f)
, vol("Vol", "vol", "dB", 0.f, 1.f, .5f)
, ladderCutoff("LadderFreq", "ladderCutoff", "Hz", 10.f, 20000.f, 20000.f)
, ladderRes("LadderRes", "ladderRes", "  ", 0.f, 10.f, 0.f)
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
, seqMode("SeqMode", "seqMode", eSeqModes::seqStop, seqModeNames)
, seqPlayMode("SeqPlayMode", "seqPlayMode", eSeqPlayModes::sequential, seqPlayModeNames)
, seqNumSteps("Steps", "seqNumSteps", "steps", 1.0f, 8.0f, 8.0f)
, seqStepSpeedIndex("Speed", "seqStepSpeed", "qn", 0.0f, 7.0f, 4.0f)
, seqStepLengthIndex("Length", "seqNoteLength", "qn", 0.0f, 7.0f, 4.0f)
, seqRandomMin("Min", "randomMin", "", 0.0f, 127.0f, 0.0f)
, seqRandomMax("Max", "randomMax", "", 0.0f, 127.0f, 127.0f)
, seqStep1("Step 1", "seqNote1", "", 0.0f, 127.0f, 60.0f)
, seqStep2("Step 2", "seqNote2", "", 0.0f, 127.0f, 62.0f)
, seqStep3("Step 3", "seqNote3", "", 0.0f, 127.0f, 64.0f)
, seqStep4("Step 4", "seqNote4", "", 0.0f, 127.0f, 65.0f)
, seqStep5("Step 5", "seqNote5", "", 0.0f, 127.0f, 67.0f)
, seqStep6("Step 6", "seqNote6", "", 0.0f, 127.0f, 69.0f)
, seqStep7("Step 7", "seqNote7", "", 0.0f, 127.0f, 71.0f)
, seqStep8("Step 8", "seqNote8", "", 0.0f, 127.0f, 72.0f)
, seqStepPlay1("StepPlay1", "seqNotePlay1", eOnOffToggle::eOn, onoffnames)
, seqStepPlay2("StepPlay2", "seqNotePlay2", eOnOffToggle::eOn, onoffnames)
, seqStepPlay3("StepPlay3", "seqNotePlay3", eOnOffToggle::eOn, onoffnames)
, seqStepPlay4("StepPlay4", "seqNotePlay4", eOnOffToggle::eOn, onoffnames)
, seqStepPlay5("StepPlay5", "seqNotePlay5", eOnOffToggle::eOn, onoffnames)
, seqStepPlay6("StepPlay6", "seqNotePlay6", eOnOffToggle::eOn, onoffnames)
, seqStepPlay7("StepPlay7", "seqNotePlay7", eOnOffToggle::eOn, onoffnames)
, seqStepPlay8("StepPlay8", "seqNotePlay8", eOnOffToggle::eOn, onoffnames)
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

void SynthParams::writeXMLPatchTree(XmlElement* patch) {
    // set version of the patch
    patch->setAttribute("version", version);

    // TODO: branch for seq params only?
    // iterate over all params and insert them into the tree
    for (auto &param : serializeParams) {
        float value = param->getUI();
        addElement(patch, param->serializationTag(), value);
    }
}

void SynthParams::writeXMLPatchHost(MemoryBlock& destData) {
    // create an outer node of the patch
    ScopedPointer<XmlElement> patch = new XmlElement("patch");
    writeXMLPatchTree(patch);
    AudioProcessor::copyXmlToBinary(*patch, destData);
}

void SynthParams::writeXMLPatchStandalone() {
    // create an outer node of the patch
    ScopedPointer<XmlElement> patch = new XmlElement("patch");
    writeXMLPatchTree(patch);

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
        param.set(static_cast<float>(patch->getChildByName(paramName)->getDoubleAttribute("value")), true); // NOTE: needed at least for seq standalone and envShape params, why?
                                                                                                            // not tested for others yet
    }
}

// set all values from xml file in params
void SynthParams::fillValues(XmlElement* patch) {
    // if the versions don't align, inform the user
    if (patch == NULL) return;
    if (patch->getTagName() != "patch" || (static_cast<float>(patch->getDoubleAttribute("version"))) > version) {
        AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Version Conflict",
            "The file was created by a newer version of the software, some settings may be ignored.",
            "OK");
    }

    // TODO: branch for seq params only?
    // iterate over all params and set the values if they exist in the xml
    for (auto &param : serializeParams) {
        fillValueIfExists(patch, param->serializationTag(), *param);
    }

}
void SynthParams::readXMLPatchHost(const void* data, int sizeInBytes) {
    ScopedPointer<XmlElement> patch = AudioProcessor::getXmlFromBinary(data, sizeInBytes);
    fillValues(patch);
}

void SynthParams::readXMLPatchStandalone() {
    // read the xml params into the synth params
    FileChooser openFileChooser("Please select the patch you want to read!", File::getSpecialLocation(File::userHomeDirectory), "*.xml");
    if (openFileChooser.browseForFileToOpen())
{
        File openedFile(openFileChooser.getResult());
        ScopedPointer<XmlElement> patch = XmlDocument::parse(openedFile);
        fillValues(patch);
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
