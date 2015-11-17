
#include "SynthParams.h"

SynthParams::SynthParams()
: freq("Freq", "Hz", 220.f, 880.f, 440.f)
, lfo1freq("Freq", "Hz", .01f, 50.f, 1.f)
, lfo1wave("Wave", "", 0.f, 1.f, 0.f)
, osc1fine("f.tune", "ct", -100.f, 100.f, 0.f)
, osc1lfo1depth("mod", "st", 0.f, 12.f, 0.f)
, vol("Vol", "dB", 0.f, 1.f, .5f)
{}

void SynthParams::writeXMLPatch() {
    // create an outer node of the patch
    XmlElement patch("patch");

    // create the inner elements for the different settings
    XmlElement* freqElem = new XmlElement("freq");
    XmlElement* lfo1freqElem = new XmlElement("lfo1freq");
    XmlElement* lfo1waveElem = new XmlElement("lfo1wave");
    XmlElement* osc1fineElem = new XmlElement("osc1fine");
    XmlElement* osc1lfo1depthElem = new XmlElement("osc1lfo1depth");
    XmlElement* volElem = new XmlElement("vol");

    // fill the elements with the appropriate values
    freqElem->setAttribute("value", freq.get());
    lfo1freqElem->setAttribute("value", lfo1freq.get());
    lfo1waveElem->setAttribute("value", lfo1wave.get());
    osc1fineElem->setAttribute("value", osc1fine.get());
    osc1lfo1depthElem->setAttribute("value", osc1lfo1depth.get());
    volElem->setAttribute("value", vol.get());

    // add all settings to the patchSettings node
    patch.addChildElement(freqElem);
    patch.addChildElement(lfo1freqElem);
    patch.addChildElement(lfo1waveElem);
    patch.addChildElement(osc1fineElem);
    patch.addChildElement(osc1lfo1depthElem);
    patch.addChildElement(volElem);
    
    // create the output
    FileChooser saveDirChooser("Please select the place you want to save!", File::getSpecialLocation(File::userHomeDirectory), "*.xml");
    if (saveDirChooser.browseForFileToSave(true))
    {
        File saveFile(saveDirChooser.getResult());
        saveFile.create();
        patch.writeToFile(saveFile, ""); // DTD optional, no validation yet
    }
}

void SynthParams::readXMLPatch()
{
    // for the whole read process: DTD might be added in the future, no validation yet
    // TODO how much validation should be done? none? attribute names? attribute ranges?

    // read the xml params into the synth params
    FileChooser openFileChooser("Please select the patch you want to read!", File::getSpecialLocation(File::userHomeDirectory), "*.xml");
    if (openFileChooser.browseForFileToOpen())
    {
        File openedFile(openFileChooser.getResult());
        XmlElement* xmlPatch = XmlDocument::parse(openedFile);

        // set all the settings
        freq.setUI(static_cast<float>(xmlPatch->getChildByName("freq")->getDoubleAttribute("value")));
        lfo1freq.setUI(static_cast<float>(xmlPatch->getChildByName("lfo1freq")->getDoubleAttribute("value")));
        lfo1wave.setUI(static_cast<float>(xmlPatch->getChildByName("lfo1wave")->getDoubleAttribute("value")));
        osc1fine.setUI(static_cast<float>(xmlPatch->getChildByName("osc1fine")->getDoubleAttribute("value")));
        osc1lfo1depth.setUI(static_cast<float>(xmlPatch->getChildByName("osc1lfo1depth")->getDoubleAttribute("value")));
        vol.setUI(static_cast<float>(xmlPatch->getChildByName("vol")->getDoubleAttribute("value")));
    }
}
