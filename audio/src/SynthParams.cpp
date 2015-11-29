#include "SynthParams.h"

SynthParams::SynthParams()
: freq("Freq", "Hz", 220.f, 880.f, 440.f)
, lfo1freq("Freq", "Hz", .01f, 50.f, 1.f)
, lfo1wave("Wave", "", 0.f, 1.f, 0.f)
, osc1fine("f.tune", "ct", -100.f, 100.f, 0.f)
, osc1coarse("c.tune", "st", -11.f, 11.f, 0.f)
, osc1lfo1depth("mod", "st", 0.f, 12.f, 0.f)
, osc1trngAmount("trianlge", "prct", 0.0f, 1.0f, 0.0f)
, osc1PitchRange("Pitch", "st", 0.f, 12.f, 0.f)
, osc1pulsewidth("Width", "prct", 0.01f, 0.99f, 0.5f)
, panDir("Pan", "pct", -100.f, 100.f, 0.f)
, vol("Vol", "dB", 0.f, 1.f, .5f)
{}
 

void SynthParams::addElement(XmlElement* patch, String name, float value) {
    XmlElement* node = new XmlElement(name);
    node->setAttribute("value", value);
    patch->addChildElement(node);
}

void SynthParams::writeXMLPatchTree(XmlElement* patch) {
    // set version of the patch
    patch->setAttribute("version", version);

    addElement(patch, "freq", freq.get());
    addElement(patch, "lfo1freq", lfo1freq.get());
    addElement(patch, "lfo1wave", lfo1wave.get());
    addElement(patch, "osc1fine", osc1fine.get());
    addElement(patch, "osc1lfo1depth", osc1lfo1depth.get());
    addElement(patch, "vol", ParamDb::toDb(vol.get()));
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

void SynthParams::fillValues(XmlElement* patch) {
    // if the versions don't align, inform the user
    if (patch->getTagName() != "patch" || (static_cast<float>(patch->getDoubleAttribute("version"))) > version) {
        AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Version Conflict",
            "The file was created by a newer version of the software, some settings may be ignored.",
            "OK");
    }

    // set the values if they exist in the XML
    if (patch->getChildByName("freq") != NULL)
    {
        freq.setUI(static_cast<float>(patch->getChildByName("freq")->getDoubleAttribute("value")));
    }
    if (patch->getChildByName("lfo1freq") != NULL)
    {
        lfo1freq.setUI(static_cast<float>(patch->getChildByName("lfo1freq")->getDoubleAttribute("value")));
    }
    if (patch->getChildByName("lfo1wave") != NULL)
    {
        lfo1wave.setUI(static_cast<float>(patch->getChildByName("lfo1wave")->getDoubleAttribute("value")));
    }
    if (patch->getChildByName("osc1fine") != NULL)
    {
        osc1fine.setUI(static_cast<float>(patch->getChildByName("osc1fine")->getDoubleAttribute("value")));
    }
    if (patch->getChildByName("osc1lfo1depth") != NULL)
    {
        osc1lfo1depth.setUI(static_cast<float>(patch->getChildByName("osc1lfo1depth")->getDoubleAttribute("value")));
    }
    if (patch->getChildByName("vol") != NULL)
    {
        vol.setUI(static_cast<float>(patch->getChildByName("vol")->getDoubleAttribute("value")));
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
