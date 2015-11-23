
#include "SynthParams.h"

SynthParams::SynthParams()
: freq("Freq", "Hz", 220.f, 880.f, 440.f)
, lfo1freq("Freq", "Hz", .01f, 50.f, 1.f)
, lfo1wave("Wave", "", 0.f, 1.f, 0.f)
, osc1fine("f.tune", "ct", -100.f, 100.f, 0.f)
, osc1lfo1depth("mod", "st", 0.f, 12.f, 0.f)
, vol("Vol", "dB", 0.f, 1.f, .5f)
{}

const float version = 1.0f;


void SynthParams::addElement(XmlElement* patch, String name, float value) {
    XmlElement* node = new XmlElement(name);
    node->setAttribute("value", value);
    patch->addChildElement(node);
}

void SynthParams::writeXMLPatch() 
{
    // create an outer node of the patch
    XmlElement* patch = new XmlElement("patch");
    patch->setAttribute("version", version);

    addElement(patch, "freq", freq.get());
    addElement(patch, "lfo1freq", lfo1freq.get());
    addElement(patch, "lfo1wave", lfo1wave.get());
    addElement(patch, "osc1fine", osc1fine.get());
    addElement(patch, "osc1lfo1depth", osc1lfo1depth.get());
    addElement(patch, "vol", ParamDb::toDb(vol.get()));

    // create the output
    FileChooser saveDirChooser("Please select the place you want to save!", File::getSpecialLocation(File::userHomeDirectory), "*.xml");
    if (saveDirChooser.browseForFileToSave(true))
    {
        File saveFile(saveDirChooser.getResult());
        saveFile.create();
        patch->writeToFile(saveFile, ""); // DTD optional, no validation yet
    }
    delete(patch);
}


void SynthParams::readXMLPatch()
{
    // read the xml params into the synth params
    FileChooser openFileChooser("Please select the patch you want to read!", File::getSpecialLocation(File::userHomeDirectory), "*.xml");
    if (openFileChooser.browseForFileToOpen())
    {
        File openedFile(openFileChooser.getResult());
        XmlElement* xmlPatch = XmlDocument::parse(openedFile);

        // if the versions don't align, inform the user
        if (xmlPatch->getTagName() != "patch" || static_cast<float>(xmlPatch->getDoubleAttribute("version")) != version) {
            AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Version Conflict", 
                "The file was not created by the current version of the software, all possible settings will be applied.",
                "OK");
        }

        // set the values if they exist in the XML
        if (xmlPatch->getChildByName("freq") != NULL)
        {
            freq.setUI(static_cast<float>(xmlPatch->getChildByName("freq")->getDoubleAttribute("value")));
        }
        if (xmlPatch->getChildByName("lfo1freq") != NULL)
        {
            lfo1freq.setUI(static_cast<float>(xmlPatch->getChildByName("lfo1freq")->getDoubleAttribute("value")));
        }
        if (xmlPatch->getChildByName("lfo1wave") != NULL)
        {
            lfo1wave.setUI(static_cast<float>(xmlPatch->getChildByName("lfo1wave")->getDoubleAttribute("value")));
        }
        if (xmlPatch->getChildByName("osc1fine") != NULL)
        {
            osc1fine.setUI(static_cast<float>(xmlPatch->getChildByName("osc1fine")->getDoubleAttribute("value")));
        }
        if (xmlPatch->getChildByName("osc1lfo1depth") != NULL)
        {
            osc1lfo1depth.setUI(static_cast<float>(xmlPatch->getChildByName("osc1lfo1depth")->getDoubleAttribute("value")));
        }
        if (xmlPatch->getChildByName("vol") != NULL)
        {
            vol.setUI(static_cast<float>(xmlPatch->getChildByName("vol")->getDoubleAttribute("value")));
        }
    }
}
