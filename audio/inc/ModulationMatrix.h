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

//! Modulation Matrix 
/*! this fixed size mod matrix is based on the book
"Designing Software Synthesizer Plug-Ins in C++"
*/

enum sources : int {
    SOURCE_NONE = -1,
    SOURCE_PITCHBEND = 0,
    SOURCE_LFO1 = 1,

	//SOURCE_ENV1,
	//SOURCE_VELOCITY,
	//SOURCE_MODWHEEL,
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
	TRANSFORM_UNIPOLAR_TO_BIPOLAR,
	TRANSFORM_BIPOLAR_TO_UNIPOLAR,
	//TRANSFORM_MIDI_NORMALIZE,
	//TRANSFORM_INVERT_MIDI_NORMALIZE,
	//TRANSFORM_MIDI_TO_BIPOLAR,
	//TRANSFORM_MIDI_TO_PAN,
	//TRANSFORM_MIDI_SWITCH,
	//TRANSFORM_MIDI_TO_ATTENUATION,
	//TRANSFORM_NOTE_NUMBER_TO_FREQUENCY,
	MAX_TRANSFORMS
};

struct modMatrixRow
{
	sources sourceIndex;
	destinations destinationIndex;
    Param* modIntensity;
    Param* modRange;
	int sourceTransform;
	bool enable;
};

inline modMatrixRow* createModMatrixRow(sources sourceIndex_,
										destinations destinationIndex_,
                                        Param* modIntensity_,
                                        Param* modRange_,
										int sourceTransform_,
										bool enable_ = true) {

	modMatrixRow* row = new modMatrixRow;
	row->sourceIndex = sourceIndex_;
	row->destinationIndex = destinationIndex_;
	row->modIntensity = modIntensity_;
	row->modRange = modRange_;
	row->sourceTransform = sourceTransform_;
	row->enable = enable_;

	return row;
}

inline modMatrixRow** createModMatrixCore()
{
	modMatrixRow** core = new modMatrixRow*[MAX_SOURCES * MAX_DESTINATIONS];
	memset(core, 0, MAX_SOURCES * MAX_DESTINATIONS * sizeof(modMatrixRow*));
	return core;
}

// core
class ModulationMatrix {
public:
	ModulationMatrix(void);
	~ModulationMatrix(void);
	
	modMatrixRow** getModMatrixCore();
	void setModMatrixCore(modMatrixRow** modMatrix);
	int getMatrixSize();
	inline void clearMatrix();
	inline void clearSources();
	inline void clearDestinations();
	void addModMatrixRow(modMatrixRow* row);
	inline bool modMatrixRowExists(int sourceIndex, int destinationIndex);
    inline void createMatrixCore();
	inline void deleteModMatrix();
	inline bool enableModMatrixRow(int sourceIndex, int destinationIndex, bool enable);
	inline bool checkDestinationLayer(int layer, modMatrixRow* row);
	inline void doModulationsMatrix(int modLayer, float** src, float** dst);

    float sources[MAX_SOURCES];
    float destinations[MAX_DESTINATIONS];

protected:
	modMatrixRow** matrixCore;
	int size;
};


inline void ModulationMatrix::doModulationsMatrix(int modLayer, float** src, float** dst)
{
    if (!matrixCore) return;
    
    // clear dest registers
    clearDestinations();
    
    for (int i = 0; i<size; i++)
    {
        // get the row
        modMatrixRow* row = matrixCore[i];
        
        // --- this should never happen!
        if (!row) continue;
        
        // --- if disabled, skip row
        if (!row->enable) continue;
        
        // --- check the mod layer
        if (!checkDestinationLayer(modLayer, row)) continue;
        
        // get the source value
        float source = *(src[row->sourceIndex]);
        
        switch (row->sourceTransform)
        {
            case TRANSFORM_UNIPOLAR_TO_BIPOLAR:
                source = Param::unipolarToBipolar(source);
                break;
                
            case TRANSFORM_BIPOLAR_TO_UNIPOLAR:
                source = Param::bipolarToUnipolar(source);
                break;
                
            //case TRANSFORM_MIDI_TO_ATTENUATION:
            //    source = Param::mmaMiditoAtten(source);
            //    break;
                
            //case TRANSFORM_MIDI_TO_PAN:
            //    source = Param::midiToPanValue(source);
            //    break;
                
            //case TRANSFORM_MIDI_SWITCH:
            //    source = source > 63.0f ? 1.0f : 0.0f;
            //    break;
                
            //case TRANSFORM_MIDI_TO_BIPOLAR:
            //    source = Param::midiToBipolar(source);
            //    break;
                
            //case TRANSFORM_NOTE_NUMBER_TO_FREQUENCY:
            //    source = midiFreqTable[(int)source];
            //    break;
            //    
            //case TRANSFORM_MIDI_NORMALIZE:
            //    source /= 127.0f; // 0->1 NOTE: MMA DLS uses divide-by-128 instead!, 0->0.9999
            //    break;
            //    
            //case TRANSFORM_INVERT_MIDI_NORMALIZE:
            //    source /= 127.0f; // 0->1 NOTE: MMA DLS uses divide-by-128 instead!, 0->0.9999
            //    source = 1.0f - source; // 1->0 NOTE: MMA DLS uses divide-by-128 instead!, 0.9999->0
            //    break;
                
            default:
                break;
        }
        
        // destination += source*intensity*range
        /* an dieser Stelle muss geguckt werden wann und wo umgerechnet werden muss!!!
        ist die Stelle Sinnvoll?
        Die Umrechnung für source MUSS woanders stattfinden!!!
        ODER ein Source checker!?
        source liefert den Pitchbend!!!*/


        float dModValue = source*100.f*(row->modIntensity->get()); //*(row->modRange->get());
//        float dModValue = source*(row->modIntensity->get()); //*(row->modRange->get());
        
        // entscheidung wann addition/multiplikation -> der erste muss ja addieren, sonst multiplizieren wir mit 0?
        *(dst[row->destinationIndex]) += Param::fromCent(dModValue);
        *(dst[row->destinationIndex]) += Param::fromSemi(dModValue);

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
inline void ModulationMatrix::clearMatrix()
{
    if (!matrixCore) return;
    
    for (int i = 0; i<(MAX_SOURCES*MAX_DESTINATIONS); i++)
    {
        matrixCore[i] = NULL;
    }
}

inline void ModulationMatrix::clearSources()
{
    for (int i = 0; i<MAX_DESTINATIONS; i++)
    {
        sources[i] = 0.0f;
    }
}

inline void ModulationMatrix::clearDestinations()
{
    for (int i = 0; i<MAX_SOURCES; i++)
    {
        destinations[i] = 0.0f;
    }
}

inline bool ModulationMatrix::modMatrixRowExists(int sourceIndex, int destinationIndex)
{
    if (!matrixCore) return false;
    
    for (int i = 0; i<size; i++)
    {
        modMatrixRow* row = matrixCore[i];
        
        // find matching source/destination pairs
        if (row->sourceIndex == sourceIndex && row->destinationIndex == destinationIndex)
        {
            return true;
        }
    }
    return false;
}

inline void ModulationMatrix::createMatrixCore()
{
    if (matrixCore)
        delete[] matrixCore;
    
    // --- dynamic allocation of matrix core
    matrixCore = new modMatrixRow*[MAX_SOURCES*MAX_DESTINATIONS];
    memset(matrixCore, 0, MAX_SOURCES*MAX_DESTINATIONS*sizeof(modMatrixRow*));
}

inline void ModulationMatrix::deleteModMatrix()
{
    if (!matrixCore) return;
    
    for (int i = 0; i<size; i++)
    {
        // delete pointer
        modMatrixRow* row = matrixCore[i];
        delete row;
        size--;
    }
    size = 0;
    delete[] matrixCore;
    matrixCore = NULL;
}

inline bool ModulationMatrix::enableModMatrixRow(int sourceIndex, int destinationIndex, bool enable)
{
    if (!matrixCore) return false;
    
    for (int i = 0; i<size; i++)
    {
        modMatrixRow* row = matrixCore[i];
        
        // find matching source/destination pairs
        if (row->sourceIndex == sourceIndex && row->destinationIndex == destinationIndex)
        {
            row->enable = enable;
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


#endif  // MODULATIONMATRIX_H_INCLUDED
