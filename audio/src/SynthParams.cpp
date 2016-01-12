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
    &lfo1freq, &lfo1wave, &lfoFadein,
    &osc1fine, &osc1coarse, &osc1lfo1depth,&osc1trngAmount, &osc1PitchRange, &osc1pulsewidth, 
    &lpCutoff, &biquadResonance, &ladderCutoff, &ladderRes,
    &lpCutoff, &biquadResonance, &ladderCutoff, &ladderRes, &lpModSource, &lpModAmout, &keyVelocityLevel,
    &envAttack, &envDecay, &envSustain, &envRelease, &envAttackShape, &envDecayShape, &envReleaseShape, &keyVelToEnv,
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
, osc1Waveform("Osc Waveform", "oscWaveform", eOscWaves::eOscSquare, waveformNames)
, lpModAmout("LP ModAmnt", "lpModAmout", "prct", 0.f, 100.f, 0.f)
, osc1trngAmount("trianlge", "osc1trngAmount", "prct", 0.0f, 1.0f, 0.0f)
, osc1PitchRange("Pitch", "osc1PitchRange", "st", 0.f, 12.f, 0.f)
, envAttack("Attack", "envAttack", "s", 0.001f, 5.0f, 0.005f)
, envDecay("Decay", "envDecay", "s", 0.001f, 5.0f, 0.05f)
, envSustain("Sustain", "envSustain", "dB", -96.0f, 0.0f, -5.0f)
, envRelease("Release", "envRelease", "s", 0.001f, 5.0f, 0.5f)
, keyVelToEnv("keyVel to Env", "", "veloToKey", 0.0f, 1.0f, 0.0f)
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
, seqMode("SeqMode", "seqMode", eSeqModes::seqStop, seqModeNames)
, seqNumSteps("SeqNumSteps", "seqNumSteps", "steps", 1.0f, 8.0f, 4.0f)
, seqStepSpeed("SeqSpeed", "seqSpeed", "qn", 0.125f, 4.0f, 1.0f)
, seqStepLength("SeqNoteLength", "seqNoteLength", "qn", 0.125f, 4.0f, 1.0f)
, seqStep1("seqNote1", "seqNote1", "", -1, 127, 60)
, seqStep2("seqNote2", "seqNote2", "", -1, 127, 62)
, seqStep3("seqNote3", "seqNote3", "", -1, 127, 64)
, seqStep4("seqNote4", "seqNote4", "", -1, 127, 65)
, seqStep5("seqNote5", "seqNote5", "", -1, 127, 67)
, seqStep6("seqNote6", "seqNote6", "", -1, 127, 69)
, seqStep7("seqNote7", "seqNote7", "", -1, 127, 71)
, seqStep8("seqNote8", "seqNote8", "", -1, 127, 72)
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

    // iterate over all params and insert them into the tree
    for (auto &param : serializeParams) {
        float value = param->getUI();
        if (param->serializationTag() != "") {
            addElement(patch, param->serializationTag(), value);
        }
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

    // iterate over all params and set the values if they exist in the xml
    for (auto &param : serializeParams) {
        if (param->serializationTag() != "") {
            fillValueIfExists(patch, param->serializationTag(), *param);
        }
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
