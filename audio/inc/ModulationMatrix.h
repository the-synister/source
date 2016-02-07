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
#include <atomic>
#include "Param.h"
#include <map>
//#include "..\gui\panels\PanelBase.h"

//! Modulation Matrix 
/*! this fixed size mod matrix is based on the book
"Designing Software Synthesizer Plug-Ins in C++"
*/


enum sources : int {
    SOURCE_NONE = -1,

    // Midi
    SOURCE_AFTERTOUCH,
    SOURCE_KEY_BIPOLAR,
    SOURCE_INVERTED_VELOCITY,
    SOURCE_VELOCITY,
    SOURCE_FOOT,
    SOURCE_EXPPEDAL,
    SOURCE_MODWHEEL,
    SOURCE_PITCHBEND,

    // LFOs
    SOURCE_LFO1,
    SOURCE_LFO2,
    SOURCE_LFO3,

    // Envelopes
    SOURCE_VOL_ENV,
    SOURCE_ENV2,
    SOURCE_ENV3,

    MAX_SOURCES
};

enum destinations : int {
    DEST_NONE = -1,

    // Filters
    DEST_FILTER_LC,
    DEST_FILTER_HC,
    DEST_FILTER_RES,

    // Oscillators
    DEST_AMP,
    DEST_PAN,
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
    DEST_LFO1_GAIN,
    DEST_LFO2_GAIN,
    DEST_LFO3_GAIN,

    // Envelopes
    DEST_VOL_ENV_SPEED,
    DEST_ENV2_SPEED,
    DEST_ENV3_SPEED,

    MAX_DESTINATIONS
};

inline bool isUnipolar(sources source) {
    switch (source) {
    case SOURCE_VOL_ENV:
    case SOURCE_ENV2:
    case SOURCE_ENV3:
    case SOURCE_AFTERTOUCH:
    case SOURCE_MODWHEEL:
    case SOURCE_VELOCITY:
    case SOURCE_INVERTED_VELOCITY:
    case SOURCE_FOOT:
    case SOURCE_EXPPEDAL:
        return true;
        break;
    case SOURCE_LFO1:
    case SOURCE_LFO2:
    case SOURCE_LFO3:
    case SOURCE_PITCHBEND:
    case SOURCE_KEY_BIPOLAR:
        return false;
        break;


    }
    // when the function is complete with all sources, this code should be unreachable
    return false;
}

// core
class ModulationMatrix {
public:
    ModulationMatrix();
    ~ModulationMatrix();



    struct ModMatrixRow
    {
        sources sourceIndex;
        destinations destinationIndex;
        Param* modIntensity;

        ModMatrixRow(sources s, destinations d, Param *intensity)
            : sourceIndex(s)
            , destinationIndex(d)
            , modIntensity(intensity)
        {}
    };

    std::map<String, ModulationMatrix::ModMatrixRow*> boxnameToMatrixRow;

    inline bool modMatrixRowExists(sources sourceIndex, destinations destinationIndex) const;
    inline void updateRow(String modSourceBoxName);
    inline void changeSource(String comboboxName, sources source);
    inline ModulationMatrix::ModMatrixRow* addModMatrixRow(sources s, destinations d, Param *intensity, String comboboxName);
    inline void doModulationsMatrix(float** src, float** dst) const;


protected:
    static float toUnipolar(float min, float max, float value) { return (value - min) / max - min; }
    static float toBipolar(float min, float max, float value) { return (2.0f*(value - min) / max - min) - 1.0f; }

private:


    std::vector<ModMatrixRow> matrixCore;
};


inline void ModulationMatrix::doModulationsMatrix(float** src, float** dst) const
{
    for (const ModMatrixRow &row : matrixCore)
    {
        // get the source value & mod intensity
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

// config changes

inline bool ModulationMatrix::modMatrixRowExists(sources sourceIndex, destinations destinationIndex) const
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

inline void ModulationMatrix::changeSource(String comboboxName, sources source) {

    boxnameToMatrixRow[comboboxName]->sourceIndex = source;

}


inline ModulationMatrix::ModMatrixRow* ModulationMatrix::addModMatrixRow(sources s, destinations d, Param *intensity, String comboboxName)
{
    // add if not already existing
    if (!modMatrixRowExists(s, d))
    {
        matrixCore.push_back(ModMatrixRow(s, d, intensity));
        ModMatrixRow* rowPointer = &matrixCore.back();
        ModulationMatrix::boxnameToMatrixRow[comboboxName] = rowPointer;
    }
    return NULL;
}

#endif  // MODULATIONMATRIX_H_INCLUDED