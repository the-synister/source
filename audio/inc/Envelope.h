/*
  ==============================================================================

    Envelope.h
    Created: 11 Dec 2015 3:13:56pm
    Author:  Nhat Duc Tran and Anton Schmied

  ==============================================================================
*/

#ifndef ENVELOPE_H_INCLUDED
#define ENVELOPE_H_INCLUDED

#include "Synthparams.h"
#include "Param.h"

//! Envelope Class: Envelope
/*! An ADSR implementation with A,D and R shape control and an additional
    feature of "Key Velocity to Envelope", which can be regulated on the
    corresponding Panel.
    The Envelope is currently controling the amplitude (Env Panel) or can be
    can be use to modulate the cutoff frequency of the lowpass filter
*/

class Envelope{
    public:
    Envelope(SynthParams::EnvBase &_env, Param &_sustain, double _sampleRate)
        : releaseCounter(-1)
        , attackDecayCounter(0)
        , sampleRate(_sampleRate)
        , env(_env)
        , sustain(_sustain)
    {
    }

    //! Enevelope destructor
    ~Envelope(){}

    //! resets the sample counters and sets the current velocity for each new note
    void startEnvelope();

    //! get and reset the release counters for the volume envelope
    int getReleaseCounter() const { return releaseCounter; }
    void resetReleaseCounter();


    //! calculation of the volume envelope coefficients (with shape control)
    const float calcEnvCoeff(float modValue1, float modValue2);

    private:
    inline int calcModRange(float modValue, int sInput, float tRange, float modAmount) {
        int samples = static_cast<int>(sInput * std::pow(2.f, modValue * tRange * modAmount));
        int maxSamples = static_cast<int>(tRange * sampleRate);
        samples = samples > maxSamples
            ? maxSamples
            : samples;
        samples = samples <= 0
            ? 0
            : samples;
        return samples;
    }
    SynthParams::EnvBase& env;   //!< local params
    Param& sustain;         
    double sampleRate;       //!< sample rate
    float valueAtRelease;   //!< amplitude value once release phase starts
    int attackDecayCounter; //!< sample counter during the attack and decay phase
    int releaseCounter;     //!< sample counter during the release phase

    static float interpolateLog(int c, int t, float k, bool slow); //!< interpolates logarithmically from 1.0 to 0.0f in t samples (with shape control)
};

#endif  // ENVELOPE_H_INCLUDED
