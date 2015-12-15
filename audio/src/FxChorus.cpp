#include "FxChorus.h"

FxChorus::~FxChorus() {};

void FxChorus::init(int channelsIn, double sampleRateIn)
{
	channels = channelsIn;
	sampleRate = sampleRateIn;
	chorusBuffer = AudioSampleBuffer(channels, static_cast<int>(sampleRate * 2.0));
	currentDelayLength = static_cast<int>(params.chorDelayLength.get()*(sampleRate / 1000.0));
	modSine.phase = 0.f;
	modSine.phaseDelta = params.chorModRate.get() / sampleRate;

	for (int c = 0; c < channels; ++c) {
		chorusBuffer.clear(c, 0, chorusBuffer.getNumSamples());
	}
}

void FxChorus::render(AudioSampleBuffer& outputBuffer, int startSample) {
	int newLoopLength;

	for (int i = 0; i < outputBuffer.getNumSamples(); ++i)
	{
		newLoopLength = static_cast<int>(params.chorDelayLength.get() * (sampleRate / 1000.0));
		modSine.phaseDelta = params.chorModRate.get() / sampleRate;
		loopPosition %= newLoopLength;

		// clear old material from buffer
		if (newLoopLength < currentDelayLength) { // TODO: this is still a bit messy
			chorusBuffer.clear(newLoopLength, chorusBuffer.getNumSamples() - currentDelayLength);
		}

		for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {

			float currentSample = outputBuffer.getSample(c, startSample + i);
		// Interpolation
			// get delayed sample index
			float currentDelayMod = modSine.next() * params.chorModDepth.get();
			float deltaSample = currentDelayMod - floor(currentDelayMod);
			int delayedSample1 = static_cast<int>(loopPosition + params.chorDelayLength.get()*sampleRate + floor(currentDelayMod)) % newLoopLength;
			int delayedSample2 = static_cast<int>(loopPosition + params.chorDelayLength.get()*sampleRate + ceil(currentDelayMod)) % newLoopLength;
			// get values for interpolation
			float value1 = chorusBuffer.getSample(c, delayedSample1);
			float value2 = chorusBuffer.getSample(c, delayedSample2);

			float delta = value2 - value1;

			float interpValue = value1 + delta*deltaSample;

			outputBuffer.addSample(c, startSample + i, interpValue * params.chorDryWet.get());

			chorusBuffer.addSample(c, loopPosition + i, currentSample);

		}

		// iterate
		currentDelayLength = newLoopLength;
		++loopPosition;
	}

}