#ifndef FXCHORUS_H_INCLUDED
#define FXCHORUS_H_INCLUDED


#include "SynthParams.h"


class FxChorus
{
public:
	FxChorus(SynthParams &p)
		: params(p)
		, loopPosition(0)
		//, chorDelayLength(.02f)
		//, modulationDepth(.01f)
		//, modulationRate(.5f)
		//, chorDryWet(.8)
	{
	
	}
	~FxChorus();

	void init(int channelsIn, double sampleRateIn);
	void render(AudioSampleBuffer& outputBuffer, int startSample);

private:
	SynthParams &params;
	AudioSampleBuffer chorusBuffer;
	Oscillator<&Waveforms::sinus> modSine;
	double sampleRate;
	int channels;
	int currentDelayLength;
	int loopPosition;
	//float chorDelayLength;
	//float modulationDepth;
	//float modulationRate;
	//float chorDryWet;

	
};

template<float(*_waveform)(float)>
struct Oscillator {
	float phase;
	float phaseDelta;

	Oscillator() : phase(0.f)
		, phaseDelta(0.f)
	{}

	void reset() {
		phase = 0.f;
		phaseDelta = 0.f;
	}

	bool isActive() const {
		return phaseDelta > 0.f;
	}

	float next() {
		const float result = _waveform(phase);
		phase = std::fmod(phase + phaseDelta, float_Pi * 2.0f);
		return result;
	}

	float next(float pitchMod) {
		const float result = _waveform(phase);
		phase = std::fmod(phase + phaseDelta*pitchMod, float_Pi * 2.0f);
		return result;
	}
};

struct Waveforms {
	static float sinus(float phs) {
		return std::sin(phs);
	}
};

#endif
