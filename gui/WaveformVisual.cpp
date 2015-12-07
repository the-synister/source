#include "WaveformVisual.h"
#include "Voice.h"

void WaveformVisual::paint(Graphics &g)
{
	g.fillAll(Colours::black);
	Path wavePath;
	const float centreY = getHeight() / 2.0f;
	const float amplitude = 0.3f;
	const int width = getWidth();
	const float step = 4*float_Pi / width;

	for (float x = 0.0f; x < width; ++x) {

		float phs = x * step;
		if (phs > (2 * float_Pi))
			phs = phs - (2 * float_Pi);

		switch (m_iWaveformKey)
		{
		case 1:
		{
			wavePath.lineTo(x, centreY - 0.4 * getHeight() * Waveforms::square(phs, m_fTrngAmount, m_fPulseWidth));
			break;
		}
		case 2:
			wavePath.lineTo(x, centreY - 0.4 * getHeight() * Waveforms::saw(phs, m_fTrngAmount, m_fPulseWidth));
			break;
		}

	}
	g.setColour(Colours::lightgreen);
	g.strokePath(wavePath, PathStrokeType(2.0f));
}
