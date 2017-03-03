#include "WaveformVisual.h"
#include "Oscillator.h"

void WaveformVisual::paint(Graphics &g)
{
    FillType backgroundFill = FillType(SynthParams::waveformBackground);
    backgroundFill.setOpacity(1.0f);
    g.setFillType(backgroundFill);
    g.fillAll();

	const int width = getWidth();

	Path grid;
	//grid.startNewSubPath(0.0f, static_cast<float>(getHeight()/2));
	//grid.lineTo(width, static_cast<float>(getHeight() / 2));

	grid.addLineSegment(Line< float >(0.f, static_cast<float>(getHeight() / 2), width, static_cast<float>(getHeight() / 2)), 1.f);
	grid.addLineSegment(Line< float >(static_cast<float>(width / 2), 0, static_cast<float>(width / 2), static_cast<float>(getHeight())), 1.f);
	grid.addLineSegment(Line< float >(static_cast<float>(width / 4), 0, static_cast<float>(width / 4), static_cast<float>(getHeight())), 1.f);
	grid.addLineSegment(Line< float >(static_cast<float>(width * 3 / 4), 0, static_cast<float>(width * 3 / 4), static_cast<float>(getHeight())), 1.f);

	g.setColour(SynthParams::oscColour);
	g.setOpacity(.4f);
	g.strokePath(grid, PathStrokeType(1.f));

    Path wavePath;
    const float centreY = getHeight() / 2.0f;
    const float amplitude = 0.4f;
    const float step = 4*float_Pi / width;
    wavePath.startNewSubPath(0, centreY);

    for (int x = 0; x < width; ++x) {

        float phs = static_cast<float>(x) * step;
        if (phs > (2 * float_Pi))
            phs = phs - (2 * float_Pi);

        switch (m_iWaveformKey)
        {
            case eOscWaves::eOscSquare:
                wavePath.lineTo(static_cast<float>(x), centreY - amplitude * static_cast<float>(getHeight()) * Waveforms::square(phs, m_fTrngAmount, m_fPulseWidth));
                break;

            case eOscWaves::eOscSaw:
                wavePath.lineTo(static_cast<float>(x), centreY - amplitude * static_cast<float>(getHeight()) * Waveforms::saw(phs, m_fTrngAmount, m_fPulseWidth));
                break;

            case eOscWaves::eOscNoise:

                // only calculate new noise if waveform changed otherwise it always recalculates a different noise which can lead to bad behaviour on GUI
                if (!needNewNoise) {
                    wavePath = Path(noise);

                } else {
                    if (x == 0) {
                        noise.clear();
                    }
                    noise.lineTo(static_cast<float>(x), centreY - amplitude * static_cast<float>(getHeight()) * Waveforms::whiteNoise(0.0f, 0.0f, 0.0f));

                    if (x == width - 1) {
                        wavePath = Path(noise);
                        needNewNoise = false;
                    }
                }
                break;

        }
    }

    g.setColour(SynthParams::waveformLine);
    g.strokePath(wavePath, PathStrokeType(2.5f));
    g.drawRect(getLocalBounds(), 3);
    g.setColour(Colours::darkgrey);
    g.drawRect(getLocalBounds(), 1);
}
