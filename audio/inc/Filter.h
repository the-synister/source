#pragma once

#include "JuceHeader.h"
#include "SynthParams.h"

//! \brief multi-mode audio filter code
class Filter {
public:
    Filter(SynthParams::Filter &f)
        : filter(f)
    {
    }

    //! \brief reset the internal state
    /** \param sRate sample rate in Hz
    */
    void reset(float sRate)
    {
        sampleRate = sRate;

        lastSample = 0.f;
        inputDelay1 = 0.f;
        inputDelay2 = 0.f;
        outputDelay1 = 0.f;
        outputDelay2 = 0.f;

        bandpassDelay1 = 0.f;
        bandpassDelay2 = 0.f;

        //for ladder filter
        ladderOut = 0.f;
        ladderInDelay = 0.f;
        lpOut1 = 0.f;
        lpOut2 = 0.f;
        lpOut3 = 0.f;
        lpOut1Delay = 0.f;
        lpOut2Delay = 0.f;
        lpOut3Delay = 0.f;
    }

    //! \brief apply the filter to a single sample
    /** \param inputSignal audio sample to filter
     *  \param modValue cutoff modulation in abstract modulation range (i.e., [-1;1] per modulation source)
     *  \return filtered audio sample
     */
    float run(float inputSignal, float modValue) {
        if (filter.passtype.getStep() == eBiquadFilters::eLadder) {
            return ladderFilter(inputSignal, modValue);
        } else {
            return biquadFilter(inputSignal, modValue);
        }
    }

protected:
    float biquadFilter(float inputSignal, float modValue) {

        // get mod frequency from active filter type
        float cutoffFreq;
        switch (filter.passtype.getStep()) {
        case eBiquadFilters::eLowpass:
            cutoffFreq = filter.lpCutoff.get();
            break;
        case eBiquadFilters::eHighpass:
            cutoffFreq = filter.hpCutoff.get();
            break;
        case eBiquadFilters::eBandpass:
            cutoffFreq = (filter.lpCutoff.get() + filter.hpCutoff.get()) / 2.f;
            if (filter.lpCutoff.get() < filter.hpCutoff.get()) {
                return 0.f;
            }
            break;
        default: // should never happen if everybody uses it correctly! but in case it does, don't crash but return no sound instead
            return 0.f;
        }

        //! \todo mod range must come from somewhere else
        cutoffFreq = Param::bipolarToFreq(modValue, cutoffFreq, 8.f);

        // check range
        if (cutoffFreq < filter.lpCutoff.getMin()) { // assuming that min/max are identical for low and high pass filters
            cutoffFreq = filter.lpCutoff.getMin();
        }
        else if (cutoffFreq > filter.lpCutoff.getMax()) {
            cutoffFreq = filter.lpCutoff.getMax();
        }

        cutoffFreq /= sampleRate;

        // LP and HP: Filter Design: Biquad (2 delays) Source: http://www.musicdsp.org/showArchiveComment.php?ArchiveID=259
        // BP: based on http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt, except for bw calculation
        float k, coeff1, coeff2, coeff3, b0 = 0.0f, b1 = 0.0f, b2 = 0.0f, a0 = 0.0f, a1 = 0.0f, a2 = 0.0f, bw, w0;

        const float currentResonance = pow(10.f, (-filter.resonance.get() * 2.5f) / 20.f); /*so ist die resonanz bei 10 maximal*/

        if (static_cast<eBiquadFilters>(filter.passtype.getStep()) == eBiquadFilters::eLowpass) {

            // coefficients for lowpass, depending on resonance and lowcut frequency
            k = 0.5f * currentResonance * sin(2.f * float_Pi * cutoffFreq);
            coeff1 = 0.5f * (1.f - k) / (1.f + k);
            coeff2 = (0.5f + coeff1) * cos(2.f * float_Pi * cutoffFreq);
            coeff3 = (0.5f + coeff1 - coeff2) * 0.25f;

            b0 = 2.f * coeff3;
            b1 = 2.f * 2.f * coeff3;
            b2 = 2.f * coeff3;
            a1 = 2.f * -coeff2;
            a2 = 2.f * coeff1;

        }
        else if (filter.passtype.getStep() == eBiquadFilters::eHighpass) {

            // coefficients for highpass, depending on resonance and highcut frequency
            k = 0.5f * currentResonance * sin(float_Pi * cutoffFreq);
            coeff1 = 0.5f * (1.f - k) / (1.f + k);
            coeff2 = (0.5f + coeff1) * cos(float_Pi * cutoffFreq);
            coeff3 = (0.5f + coeff1 + coeff2) * 0.25f;

            b0 = 2.f * coeff3;
            b1 = -4.f * coeff3;
            b2 = 2.f * coeff3;
            a1 = -2.f * coeff2;
            a2 = 2.f * coeff1;

        }
        else if (filter.passtype.getStep() == eBiquadFilters::eBandpass) {

            // coefficients for bandpass, depending on low- and highcut frequency
            w0 = 2.f * float_Pi*cutoffFreq;
            bw = (log2(filter.lpCutoff.get() / filter.hpCutoff.get())); // bandwidth in octaves
            coeff1 = sin(w0)*sinh(log10(2.f) / 2.f * bw * w0 / sin(w0)); // intermediate value for coefficient calc

            b0 = coeff1;
            b1 = 0.f;
            b2 = -coeff1;
            a0 = 1.f + coeff1;
            a1 = -2.f * cos(w0);
            a2 = 1.f - coeff1;
        }

        lastSample = inputSignal;

        // different biquad form for bandpass filter, it has more coefficients as well
        if (filter.passtype.getStep() == eBiquadFilters::eBandpass) {
            inputSignal = (b0 / a0)* inputSignal + (b1 / a0)*inputDelay1 + (b2 / a0)*inputDelay2 - (a1 / a0)*outputDelay1 - (a2 / a0)*outputDelay2;
        }
        else {
            inputSignal = b0*inputSignal + b1*inputDelay1 + b2*inputDelay2 - a1*outputDelay1 - a2*outputDelay2;
        }

        //delaying samples
        inputDelay2 = inputDelay1;
        inputDelay1 = lastSample;
        outputDelay2 = outputDelay1;
        outputDelay1 = inputSignal;

        if (inputSignal > 1.f) {
            inputSignal = 1.f;
        }
        else if (inputSignal < -1.f) {
            inputSignal = -1.f;
        }
        return inputSignal;
    }

    //apply ladder filter to the current Sample in renderNextBlock() - Zavalishin approach
    //naive 1 pole filters wigh a hyperbolic tangent saturator
    float ladderFilter(float ladderIn, float modValue)
    {
        float cutoffFreq = filter.lpCutoff.get();
        float currentResonance = filter.resonance.get();

        cutoffFreq = Param::bipolarToFreq(modValue, cutoffFreq, 8.f);

        // TODO can't this be shortened?
        if (cutoffFreq < filter.lpCutoff.getMin()) { // assuming that min/max are identical for low and high pass filters
            cutoffFreq = filter.lpCutoff.getMin();
        }
        else if (cutoffFreq > filter.lpCutoff.getMax()) {
            cutoffFreq = filter.lpCutoff.getMax();
        }

        //coeffecients and parameters
        float omega_c = 2.f * float_Pi * cutoffFreq / sampleRate;
        float g = omega_c / 2.f;
        float a = (1.f - g) / (1.f + g);
        float b = g / (1.f + g);

        // subtract the feedback
        // inverse hyperbolic Sinus
        // ladderIn = tanh(ladderIn) - asinh(currentResonance * ladderOut);
        // hyperbolic tangent
        ladderIn = tanh(ladderIn) - tanh(currentResonance * ladderOut);

        // proecess through 1 pole Filters 4 times
        lpOut1 = b*(ladderIn + ladderInDelay) + a*tanh(lpOut1);
        ladderInDelay = ladderIn;

        lpOut2 = b*(lpOut1 + lpOut1Delay) + a* tanh(lpOut2);
        lpOut1Delay = lpOut1;

        lpOut3 = b*(lpOut2 + lpOut2Delay) + a* tanh(lpOut3);
        lpOut2Delay = lpOut2;

        ladderOut = b*(lpOut3 + lpOut3Delay) + a* tanh(ladderOut);
        lpOut3Delay = lpOut3;

        return ladderOut;
    }

    SynthParams::Filter &filter;

    float sampleRate;

    //! \name biquad internal state
    ///@{
    float lastSample, inputDelay1, inputDelay2, outputDelay1, outputDelay2, bandpassDelay1, bandpassDelay2;
    ///@}

    //! \name ladder internal state
    ///@{
    float ladderOut;
    float ladderInDelay;
    float lpOut1;
    float lpOut2;
    float lpOut3;
    float lpOut1Delay;
    float lpOut2Delay;
    float lpOut3Delay;
    ///@}
};
