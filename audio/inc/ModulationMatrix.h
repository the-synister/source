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

using namespace std;

//! Modulation Matrix 
/*! this fixed size mod matrix is based on the book
"Designing Software Synthesizer Plug-Ins in C++"
*/

enum sources : int {
    SOURCE_NONE = -1,
    SOURCE_PITCHBEND,
    SOURCE_MODWHEEL,
    SOURCE_VELOCITY,
    // SOURCE_UI_FILTER,

    // SOURCE_LFO_FADER,
    SOURCE_LFO1,
    SOURCE_LFO2,
    SOURCE_LFO3,

    // SOURCE_VOL_ENV,
    SOURCE_ENV1,
    SOURCE_ENV2,
    SOURCE_ENV3,

    MAX_SOURCES
};

enum destinations : int {

    DEST_NONE = -1,

    // --- GUI control layer modulation (-1)
    DEST_UI_OSC1_FO,
    DEST_UI_OSC2_FO,
    DEST_UI_OSC3_FO,

    DEST_UI_FILTER1_FC,
    DEST_UI_FILTER2_FC,

    // --- LAYER 0 DESTINATIONS 
    //     add more L0 destinations in this chunk
    //     see CModulationMatrix::checkDestinationLayer())

    DEST_FILT_FC,       // <- keep this first
    DEST_OSC1_PITCH,    // <- keep this last

                        // --- END OF LAYER 0 DESTINATIONS

                        // --- LAYER 1 DESTINATIONS 
                        //    DEST_OSC1_PULSEWIDTH,

                        // --- END OF LAYER 1 DESTINATIONS

    MAX_DESTINATIONS
};

inline bool isUnipolar(sources source) {
    switch (source) {
    case (SOURCE_ENV1) :
    case (SOURCE_ENV2) :
    case (SOURCE_ENV3) :
        return true;
        break;
    case (SOURCE_LFO1) :
    case (SOURCE_LFO2) :
    case (SOURCE_LFO3) :
    case (SOURCE_PITCHBEND) :
        return false;
        break;

        // yet to be completed not sure about the following yet
        // case (SOURCE_VELOCITY) :
        // case (SOURCE_MODWHEEL) :
        // case (SOURCE_UI_FILTER) :
        // case (SOURCE_LFO_FADER) :
        // case (SOURCE_VOL_ENV) : 
    }
    return false; // when the function is complete with all sources, this code should be unreachable
}



// core
class ModulationMatrix {
public:
    ModulationMatrix();
    ~ModulationMatrix();

    inline bool modMatrixRowExists(sources sourceIndex, destinations destinationIndex) const;
    inline bool enableModMatrixRow(sources sourceIndex, destinations destinationIndex, bool enable);

    inline void addModMatrixRow(sources s, destinations d, Param *intensity, bool b = false);

    inline void doModulationsMatrix(float** src, float** dst) const;

protected:
    static float toUnipolar(float min, float max, float value) { return (value - min) / max - min; }
    static float toBipolar(float min, float max, float value) { return (2.0f*(value - min) / max - min) - 1.0f; }

private:
    struct ModMatrixRow
    {
        sources sourceIndex;
        destinations destinationIndex;
        Param* modIntensity;
        bool enable;

        ModMatrixRow(sources s, destinations d, Param *intensity, bool b = false)
            : sourceIndex(s)
            , destinationIndex(d)
            , modIntensity(intensity)
            , enable(b)
        {}
    };

    vector<ModMatrixRow> matrixCore;
};


inline void ModulationMatrix::doModulationsMatrix(float** src, float** dst) const
{
    for (const ModMatrixRow &row : matrixCore)
    {        
        // --- if disabled, skip row
        if (!row.enable) continue;
                
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

inline bool ModulationMatrix::enableModMatrixRow(sources sourceIndex, destinations destinationIndex, bool enable)
{
    for (ModMatrixRow &row : matrixCore)
    {
        // find matching source/destination pairs
        if (row.sourceIndex == sourceIndex && row.destinationIndex == destinationIndex)
        {
            row.enable = enable;
            return true; // found it
        }
    }
    return false;
}

inline void ModulationMatrix::addModMatrixRow(sources s, destinations d, Param *intensity, bool b)
{
    // add if not already existing
    if (!modMatrixRowExists(s, d))
    {
        matrixCore.push_back(ModMatrixRow(s,d,intensity,b));
    }
}

#endif  // MODULATIONMATRIX_H_INCLUDED
