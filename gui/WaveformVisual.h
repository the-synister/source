#ifndef WAVEFORMVISUAL_H_INCLUDED
#define WAVEFORMVISUAL_H_INCLUDED

//[Headers]
#include "JuceHeader.h"
//[/Headers]

class WaveformVisual : public Component
{

public:

	WaveformVisual(int waveformKey, float pulseWidth, float trngAmount)
		: m_iWaveformKey(waveformKey)
		, m_fPulseWidth(pulseWidth)
		, m_fTrngAmount(trngAmount)
	{
	}

	void paint(Graphics &g);
	void setWaveformKey(int waveformKey) { m_iWaveformKey = waveformKey; }
	void setPulseWidth(float pulseWidth) { m_fPulseWidth = pulseWidth; }
	void setTrngAmount(float trngAmount) { m_fTrngAmount = trngAmount; }

private:
	float m_fTrngAmount;
	float m_fPulseWidth;
	int m_iWaveformKey;



};


#endif  // WAVEFORMVISUAL_H_INCLUDED
