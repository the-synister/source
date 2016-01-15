#include "FxChorus.h"

FxChorus::~FxChorus() {};

void FxChorus::init(int channelsIn, double sampleRateIn)
{
	channels = channelsIn;
	sampleRate = sampleRateIn;
	chorusBuffer = AudioSampleBuffer(channels, static_cast<int>(sampleRate * 2.0));
	//currentDelayLength = static_cast<int>(params.chorDelayLength.get()*(sampleRate / 1000.0));
	currentDelayLength = static_cast<int>(params.chorDelayLength.get()*(sampleRate));
	modSine1.phase = 0.f;
	modSine1.phaseDelta = params.chorModRate.get() / sampleRate;

	modSine2.phase = 0.f;
	modSine2.phaseDelta = params.chorModRate.get()* 1.2f / sampleRate;

	modSine3.phase = float_Pi;
	modSine3.phaseDelta = params.chorModRate.get()* 0.8f / sampleRate;

	modSine4.phase = 0.f;
	modSine4.phaseDelta = params.chorModRate.get()* 0.9f / sampleRate;

	modSine5.phase = float_Pi;
	modSine5.phaseDelta = params.chorModRate.get()* 1.1f / sampleRate;

	for (int c = 0; c < channels; ++c) {
		chorusBuffer.clear(c, 0, chorusBuffer.getNumSamples());
	}
}

void FxChorus::render(AudioSampleBuffer& outputBuffer, int startSample) {
	int newLoopLength;

	for (int i = 0; i < outputBuffer.getNumSamples(); ++i)
	{
		//newLoopLength = static_cast<int>(params.chorDelayLength.get() * (sampleRate / 1000.0));
		newLoopLength = static_cast<int>(params.chorDelayLength.get() * sampleRate);

		modSine1.phaseDelta = params.chorModRate.get() / sampleRate;
		modSine2.phaseDelta = params.chorModRate.get()* 1.2f / sampleRate;
		modSine3.phaseDelta = params.chorModRate.get()* .8f / sampleRate;
		modSine4.phaseDelta = params.chorModRate.get()* .9f / sampleRate;
		modSine5.phaseDelta = params.chorModRate.get()* 1.1f / sampleRate;

		loopPosition %= newLoopLength;

		// clear old material from buffer
		if (newLoopLength < currentDelayLength) { // TODO: this is still a bit messy
			chorusBuffer.clear(newLoopLength, chorusBuffer.getNumSamples() - currentDelayLength);
		}

		
		// Interpolation
		// get delayed sample index for both oscillators
		float currentDelayMod1 = modSine1.next() * params.chorModDepth.get();
		float currentDelayMod2 = modSine2.next() * params.chorModDepth.get();
		float currentDelayMod3 = modSine3.next() * params.chorModDepth.get();
		float currentDelayMod4 = modSine4.next() * params.chorModDepth.get();
		float currentDelayMod5 = modSine5.next() * params.chorModDepth.get();


		// get "time" in samples between two samples
		float deltaTime1 = currentDelayMod1 - floor(currentDelayMod1);
		float deltaTime2 = currentDelayMod2 - floor(currentDelayMod2);
		float deltaTime3 = currentDelayMod3 - floor(currentDelayMod3);
		float deltaTime4 = currentDelayMod4 - floor(currentDelayMod4);
		float deltaTime5 = currentDelayMod5 - floor(currentDelayMod5);

		for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {

			float currentSample = outputBuffer.getSample(c, startSample + i);
			// get values for interpolation
			// Osc 1
			float value1_1 = chorusBuffer.getSample(c, static_cast<int>(loopPosition + params.chorDelayLength.get()*sampleRate + floor(currentDelayMod1)) % newLoopLength);
			float value1_2 = chorusBuffer.getSample(c, static_cast<int>(loopPosition + params.chorDelayLength.get()*sampleRate + ceil(currentDelayMod1)) % newLoopLength);
			// Osc 2
			float value2_1 = chorusBuffer.getSample(c, static_cast<int>(loopPosition + params.chorDelayLength.get()*sampleRate + floor(currentDelayMod2)) % newLoopLength);
			float value2_2 = chorusBuffer.getSample(c, static_cast<int>(loopPosition + params.chorDelayLength.get()*sampleRate + ceil(currentDelayMod2)) % newLoopLength);
			// Osc3
			float value3_1 = chorusBuffer.getSample(c, static_cast<int>(loopPosition + params.chorDelayLength.get()*sampleRate + floor(currentDelayMod3)) % newLoopLength);
			float value3_2 = chorusBuffer.getSample(c, static_cast<int>(loopPosition + params.chorDelayLength.get()*sampleRate + ceil(currentDelayMod3)) % newLoopLength);
			// Osc 4
			float value4_1 = chorusBuffer.getSample(c, static_cast<int>(loopPosition + params.chorDelayLength.get()*sampleRate + floor(currentDelayMod4)) % newLoopLength);
			float value4_2 = chorusBuffer.getSample(c, static_cast<int>(loopPosition + params.chorDelayLength.get()*sampleRate + ceil(currentDelayMod4)) % newLoopLength);
			// Osc 5
			float value5_1 = chorusBuffer.getSample(c, static_cast<int>(loopPosition + params.chorDelayLength.get()*sampleRate + floor(currentDelayMod5)) % newLoopLength);
			float value5_2 = chorusBuffer.getSample(c, static_cast<int>(loopPosition + params.chorDelayLength.get()*sampleRate + ceil(currentDelayMod5)) % newLoopLength);
			// Calculate value difference
			float deltaValue1 = value1_2 - value1_1;
			float deltaValue2 = value2_2 - value2_1;
			float deltaValue3 = value3_2 - value3_1;
			float deltaValue4 = value4_2 - value4_1;
			float deltaValue5 = value5_2 - value5_1;

			// Make linear interpolation: add deltaValue*deltaTime to previous sample value
			float interpValue1 = value1_1 + deltaValue1*deltaTime1;
			float interpValue2 = value2_1 + deltaValue2*deltaTime2;
			float interpValue3 = value3_1 + deltaValue3*deltaTime3;
			float interpValue4 = value4_1 + deltaValue4*deltaTime4;
			float interpValue5 = value5_1 + deltaValue5*deltaTime5;

			// Amplituden anpassen und Werte in Buffer schreiben

			float currentWetness = params.chorDryWet.get();

			outputBuffer.setSample(c, startSample + i, currentSample * (1.f - currentWetness));

			if (c == 1) {
				outputBuffer.addSample(1, startSample + i, interpValue1 * currentWetness*.2f + interpValue2 * currentWetness*.05f + interpValue3 *currentWetness * .35f + interpValue4 * currentWetness * .1f + interpValue5 * currentWetness * .3f);
			}
			else if (c == 2) {
				outputBuffer.addSample(2, startSample + i, interpValue1 * currentWetness*.2f + interpValue2 * currentWetness*.35f + interpValue3 *currentWetness * .05f + interpValue4 * currentWetness * .3f + interpValue5 * currentWetness * .1f);
			}
			else {
				outputBuffer.addSample(c, startSample + i, interpValue1 * currentWetness*.2f + interpValue2 * currentWetness*.2f + interpValue3 * currentWetness * .2f + interpValue4 * currentWetness * .2f + interpValue5 * currentWetness * .2f);
			}

			chorusBuffer.setSample(c, loopPosition, currentSample);

		}

		// iterate
		currentDelayLength = newLoopLength;
		++loopPosition;
	}

}