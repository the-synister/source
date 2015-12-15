/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "Voice.h"
#include "HostParam.h"

// UI header, should be hidden behind a factory
#include <PluginEditor.h>

//==============================================================================
PluginAudioProcessor::PluginAudioProcessor()
{
    addParameter(new HostParam<Param>(osc1fine));
    addParameter(new HostParam<Param>(osc1coarse));

    addParameter(new HostParam<ParamStepped<eLfoWaves>>(lfo1wave));
    addParameter(new HostParam<Param>(lfo1freq));
    addParameter(new HostParam<Param>(osc1lfo1depth));

    addParameter(new HostParam<Param>(osc1trngAmount));
    addParameter(new HostParam<Param>(osc1pulsewidth));

    addParameter(new HostParam<Param>(lpCutoff));
    addParameter(new HostParam<Param>(lpResonance));

    addParameter(new HostParam<Param>(envAttack));
    addParameter(new HostParam<Param>(envDecay));
    addParameter(new HostParam<Param>(envSustain));
    addParameter(new HostParam<Param>(envRelease));

    addParameter(new HostParam<Param>(panDir));

	addParameter(new HostParam<ParamStepped<eOnOff>>(lowFiActivation));
}

PluginAudioProcessor::~PluginAudioProcessor()
{
}

//==============================================================================
const String PluginAudioProcessor::getName() const
{
#ifdef JucePlugin_Name
    return JucePlugin_Name;
#else
    // standalone
    return "plugin";
#endif
}

const String PluginAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String PluginAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool PluginAudioProcessor::isInputChannelStereoPair (int index) const
{
    ignoreUnused(index);
    return true;
}

bool PluginAudioProcessor::isOutputChannelStereoPair (int index) const
{
    ignoreUnused(index);
    return true;
}

bool PluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double PluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluginAudioProcessor::setCurrentProgram (int index)
{
    ignoreUnused(index);
}

const String PluginAudioProcessor::getProgramName (int index)
{
    ignoreUnused(index);
    return String();
}

void PluginAudioProcessor::changeProgramName (int index, const String& newName)
{
    ignoreUnused(index,newName);
}

//==============================================================================
void PluginAudioProcessor::prepareToPlay (double sRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    synth.setCurrentPlaybackSampleRate(sRate);
    synth.clearVoices();
    for (int i = 8; --i >= 0;)
    {
        synth.addVoice(new Voice(*this, samplesPerBlock));
    }
    synth.clearSounds();
    synth.addSound(new Sound());
}

void PluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void PluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    updateHostInfo();
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // pass these messages to the keyboard state so that it can update the component
    // to show on-screen which keys are being pressed on the physical midi keyboard.
    // This call will also add midi messages to the buffer which were generated by
    // the mouse-clicking on the on-screen keyboard.
    keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);


    // and now get the synth to process the midi events and generate its output.
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

	// Low fidelity effect
	//////////////////////
	float nBitsLowFi = 1.f;   // New bit resolution (temporary variable before the knob is added)

	// If the effect is activated, the algorithm is applied
	if (lowFiActivation.getStep() == eOnOff::eOn) {

		float coeff = 1;          // Initialization of coeff ( 2^(0)=1 )
		for (int i = 0; i < (static_cast <int>(round(nBitsLowFi)) - 1); ++i) {    // coeff = 2^(nBitsLowFi-1)
			coeff = coeff * 2.f;
		}

		//For all the outputs
		for (int c = 0; c < buffer.getNumChannels(); ++c)
		{
			// Bit degradation
			for (int s = 0; s < buffer.getNumSamples(); ++s)
			{
				buffer.setSample(c, s, (floor(coeff*(buffer.getSample(c, s)) + 0.5f) / coeff));
			}
		}
	}
}

void PluginAudioProcessor::updateHostInfo()
{
    // currentPositionInfo used for getting the bpm.
    if (AudioPlayHead* pHead = getPlayHead())
    {
        if (pHead->getCurrentPosition (positionInfo[getAudioIndex()])) {
            positionIndex.exchange(getGUIIndex());
            return;
        }
    }

    positionInfo[getAudioIndex()].resetToDefault();

}

//==============================================================================
bool PluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PluginAudioProcessor::createEditor()
{
    return new PluginAudioProcessorEditor (*this);
}

//==============================================================================
void PluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    SynthParams::writeXMLPatchHost(destData);
}

void PluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    SynthParams::readXMLPatchHost(data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginAudioProcessor();
}
