/*
==============================================================================

ModulationMatrix.h
Created: 2 Jan 2016 9:16:56pm
Author:  nj

==============================================================================
*/

#ifndef MODULATIONMATRIX_H_INCLUDED
#define MODULATIONMATRIX_H_INCLUDED

#include "JuceHeader.h"
#include "Param.h"
#include <map>

//! Modulation Matrix
/*! this fixed size mod matrix is based on the book
"Designing Software Synthesizer Plug-Ins in C++"
*/

enum eModSource : int {
    eNone = 0,

    // Midi
    eAftertouch,
    eKeyBipolar,
    eInvertedVelocity,
    eVelocity,
    eFoot,
    eExpPedal,
    eModwheel,
    ePitchbend,

    // LFOs
    eLFO1,
    eLFO2,
    eLFO3,

    // Envelopes
    eVolEnv,
    eEnv2,
    eEnv3,

    nSteps
};


enum destinations : int {
    DEST_NONE = -1,

    // Filters
    DEST_FILTER1_LC,
    DEST_FILTER2_LC,
    DEST_FILTER1_HC,
    DEST_FILTER2_HC,
    DEST_FILTER1_RES,
    DEST_FILTER2_RES,

    // Oscillators
    DEST_OSC1_GAIN,
    DEST_OSC2_GAIN,
    DEST_OSC3_GAIN,
    DEST_OSC1_PAN,
    DEST_OSC2_PAN,
    DEST_OSC3_PAN,
    DEST_OSC1_PI,
    DEST_OSC2_PI,
    DEST_OSC3_PI,
    DEST_OSC1_PW,
    DEST_OSC2_PW,
    DEST_OSC3_PW,

    // LFOs
    DEST_LFO1_FREQ,
    DEST_LFO2_FREQ,
    DEST_LFO3_FREQ,

    // Envelopes
    DEST_VOL_ENV_SPEED,
    DEST_ENV2_SPEED,
    DEST_ENV3_SPEED,

    MAX_DESTINATIONS
};

inline bool isUnipolar(eModSource source) {
    switch (source) {
    case eModSource::eVolEnv:
    case eModSource::eEnv2:
    case eModSource::eEnv3:
    case eModSource::eAftertouch:
    case eModSource::eModwheel:
    case eModSource::eVelocity:
    case eModSource::eInvertedVelocity:
    case eModSource::eFoot:
    case eModSource::eExpPedal:
        return true;
    default:
        return false;
    }
}

// TODO: need inline?
static float toUnipolar(float min, float max, float value) { return (value - min) / max - min; }
static float toBipolar(float min, float max, float value) { return (2.0f*(value - min) / max - min) - 1.0f; }

// core
class ModulationMatrix {
public:
    ModulationMatrix();
    ~ModulationMatrix();



    struct ModMatrixRow
    {
        eModSource sourceIndex;
        destinations destinationIndex;
        Param* modIntensity;
        String modSrcBox;

        ModMatrixRow(eModSource s, destinations d, Param *intensity, String boxname)
            : sourceIndex(s)
            , destinationIndex(d)
            , modIntensity(intensity)
            , modSrcBox(boxname)
        {}
    };



    inline bool modMatrixRowExists(eModSource sourceIndex, destinations destinationIndex) const;
    inline void changeSource(String comboboxName, eModSource source);
    inline void addModMatrixRow(eModSource s, destinations d, Param *intensity, String comboboxName);
    inline void doModulationsMatrix(float** src, float** dst) const;

private:
    std::vector<ModMatrixRow> matrixCore;
};


inline void ModulationMatrix::doModulationsMatrix(float** src, float** dst) const
{
    for (const ModMatrixRow &row : matrixCore)
    {
        // get the source value & mod intensity
        if (row.sourceIndex > eModSource::eNone && row.sourceIndex < eModSource::nSteps
            && row.destinationIndex > DEST_NONE && row.destinationIndex < MAX_DESTINATIONS) {
            float source = *(src[row.sourceIndex]);
            float intensity = row.modIntensity->get();

            // get the min max values for the intensity for transformation
            float min = row.modIntensity->getMin();
            float max = row.modIntensity->getMax();

            if (isUnipolar(row.sourceIndex)) {
                // if the source is unipolar, transform the intensity to bipolar
                intensity = toBipolar(min, max, intensity);
            }
            else {
                // else the source is bipolar, transform the intensity to unipolar
                intensity = toUnipolar(min, max, intensity);
            }

            float dModValue = source*intensity;
            /*we are just adding the modified values into the predefined buffers
              the conversion and application is apllied outside of the matrix*/
            *(dst[row.destinationIndex]) += dModValue;
        }


    }
}

// config changes

inline bool ModulationMatrix::modMatrixRowExists(eModSource sourceIndex, destinations destinationIndex) const
{
    for (const ModMatrixRow &row : matrixCore)
    {
        // find matching source/destination pairs
        if (row.sourceIndex == sourceIndex && row.destinationIndex == destinationIndex)
        {
            return true;
        }
    }
    return false;
}

inline void ModulationMatrix::changeSource(String comboboxName, eModSource source) {
    for (ModMatrixRow &row : matrixCore)
    {
        // find matching source/destination pairs
        if (row.modSrcBox == comboboxName)
        {
            row.sourceIndex = source;
        }
    }
}


inline void ModulationMatrix::addModMatrixRow(eModSource s, destinations d, Param *intensity, String boxname)
{
    matrixCore.push_back(ModMatrixRow(s, d, intensity, boxname));
}

#endif  // MODULATIONMATRIX_H_INCLUDED
