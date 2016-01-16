#ifndef WAVEFORMVISUAL_H_INCLUDED
#define WAVEFORMVISUAL_H_INCLUDED

//[Headers]
#include "JuceHeader.h"
#include "SynthParams.h"
//[/Headers]

class WaveformVisual : public Component
{

public:

    WaveformVisual(eOscWaves waveformKey, float pulseWidth, float trngAmount)
        : m_iWaveformKey(waveformKey)
        , m_fPulseWidth(pulseWidth)
        , m_fTrngAmount(trngAmount)
    {
    }

    void setWaveformKey(eOscWaves waveformKey) { m_iWaveformKey = waveformKey; repaint(); }
    void setPulseWidth(float pulseWidth) { m_fPulseWidth = pulseWidth; repaint(); }
    void setTrngAmount(float trngAmount) { m_fTrngAmount = trngAmount; repaint(); }

protected:
    void paint(Graphics &g);

private:
    eOscWaves m_iWaveformKey;
    float m_fPulseWidth;
    float m_fTrngAmount;

};


#endif  // WAVEFORMVISUAL_H_INCLUDED
