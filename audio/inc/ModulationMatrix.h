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
				  //	DEST_OSC1_PULSEWIDTH,

				  // --- END OF LAYER 1 DESTINATIONS

	MAX_DESTINATIONS
};

enum transform {
    TRANSFORM_NONE = 0,
    TRANSFORM_TO_BIPOLAR,
    TRANSFORM_TO_UNIPOLAR,
	MAX_TRANSFORMS
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

struct modMatrixRow
{
	sources sourceIndex;
	destinations destinationIndex;
    Param* modIntensity;
    //Param* modRange;
	bool enable;
};

inline modMatrixRow* createModMatrixRow(sources sourceIndex_,
										destinations destinationIndex_,
                                        Param* modIntensity_,
										bool enable_ = true) {

    modMatrixRow* row = new modMatrixRow;
	row->sourceIndex = sourceIndex_;
	row->destinationIndex = destinationIndex_;
	row->modIntensity = modIntensity_;
	//row->modRange = modRange_;
	row->enable = enable_;

	return row;
}

// core
class ModulationMatrix {
public:
	ModulationMatrix();
	~ModulationMatrix();
	
	inline void clearSources();
	inline void clearDestinations();
	inline bool modMatrixRowExists(int sourceIndex, int destinationIndex);
	inline bool enableModMatrixRow(int sourceIndex, int destinationIndex, bool enable);
    void addModMatrixRow(modMatrixRow * row);
	inline bool checkDestinationLayer(int layer, modMatrixRow* row);
    inline float toUnipolar(float min, float max, float value);
    inline float toBipolar(float min, float max, float value);
	inline void doModulationsMatrix(int modLayer, float** src, float** dst);

    float sources[MAX_SOURCES];
    float destinations[MAX_DESTINATIONS];
    vector<modMatrixRow*> matrixCore;
};


inline void ModulationMatrix::doModulationsMatrix(int modLayer, float** src, float** dst)
{
    
    // clear dest registers
    //clearDestinations();


    for (unsigned int i = 0; i < matrixCore.size(); ++i)
    {
        // --- this should never happen!
        if (matrixCore[i] == nullptr) continue;
        
        // --- if disabled, skip row
        if (!matrixCore[i]->enable) continue;
        
        // --- check the mod layer
        if (!checkDestinationLayer(modLayer, matrixCore[i])) continue;
        
        // get the source value & mod intensity
        float source = *(src[matrixCore[i]->sourceIndex]);
        float intensity = matrixCore[i]->modIntensity->get();

        // get the min max values for the intensity for transformation
        float min = matrixCore[i]->modIntensity->getMin();
        float max = matrixCore[i]->modIntensity->getMax();

        if (isUnipolar(matrixCore[i]->sourceIndex)) { // if the source is unipolar, transform the intensity to bipolar
            intensity = toBipolar(min, max, intensity);
        }
        else { // else the source is bipolar, transform the intensity to unipolar
            intensity = toUnipolar(min, max, intensity);
        }
        
        // destination += source*intensity*range
        /* an dieser Stelle muss geguckt werden wann und wo umgerechnet werden muss!!!
        ist die Stelle Sinnvoll?
        Die Umrechnung fource MUSS woanders stattfinden!!!
        ODER ein Source checker!?
        source liefert den Pitchbend!!!*/


        float dModValue = source*100.f*(matrixCore[i]->modIntensity->get()); //*(row->modRange->get());
//        float dModValue = source*(row->modIntensity->get()); //*(row->modRange->get());
        
        // entscheidung wann addition/multiplikation -> der erste muss ja addieren, sonst multiplizieren wir mit 0?
        *(dst[matrixCore[i]->destinationIndex]) += Param::fromCent(dModValue);
        //*(dst[row->destinationIndex]) += Param::fromSemi(dModValue);

        // universal connections example:
        // first check DEST_ALL types
        /*switch (row->destinationIndex)
         {
         
         case DEST_ALL_OSC_FO:
         m_dDestinations[DEST_OSC1_FO] += dModValue;
         m_dDestinations[DEST_OSC2_FO] += dModValue;
         m_dDestinations[DEST_OSC3_FO] += dModValue;
         m_dDestinations[DEST_OSC4_FO] += dModValue;
         m_dDestinations[DEST_ALL_OSC_FO] += dModValue;
         break;
         
         // for all "single" source/dest, this is the modulation
         default:
         destinations[row->destinationIndex] += dModValue;
         }*/
    }
}

// config changes

inline void ModulationMatrix::clearSources()
{
    for (int i = 0; i<MAX_DESTINATIONS; ++i)
    {
        sources[i] = 0.0f;
    }
}

inline void ModulationMatrix::clearDestinations()
{
    for (int i = 0; i<MAX_SOURCES; ++i)
    {
        destinations[i] = 0.0f;
    }
}

inline bool ModulationMatrix::modMatrixRowExists(int sourceIndex, int destinationIndex)
{
    
    for (unsigned int i = 0; i<matrixCore.size(); ++i)
    {        
        // find matching source/destination pairs
        if (matrixCore[i]->sourceIndex == sourceIndex && matrixCore[i]->destinationIndex == destinationIndex)
        {
            return true;
        }
    }
    return false;
}

inline bool ModulationMatrix::enableModMatrixRow(int sourceIndex, int destinationIndex, bool enable)
{
    for (unsigned int i = 0; i<matrixCore.size(); ++i)
    {    
        // find matching source/destination pairs
        if (matrixCore[i]->sourceIndex == sourceIndex && matrixCore[i]->destinationIndex == destinationIndex)
        {
            matrixCore[i]->enable = enable;
            return true; // found it
        }
    }
    return false;
}

inline bool ModulationMatrix::checkDestinationLayer(int layer, modMatrixRow * row)
{
    bool bLayer0 = false;
    if (row->destinationIndex >= DEST_FILT_FC &&
        row->destinationIndex <= DEST_OSC1_PITCH)
        // then, we are layer 0; see modulationmatrix.h
        bLayer0 = true;
    
    if (layer == 0)
        return bLayer0;
    
    if (layer == 1)
        return !bLayer0;
    
    return false;
}

inline float ModulationMatrix::toUnipolar(float min, float max, float value) { return (value - min) / max - min;}

inline float ModulationMatrix::toBipolar(float min, float max, float value) { return (2.0f*(value-min) / max-min) - 1.0f;}



#endif  // MODULATIONMATRIX_H_INCLUDED
