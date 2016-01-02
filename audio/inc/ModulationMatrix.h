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

//! Modulation Matrix 
/*! this fixed size mod matrix is based on the book
"Designing Software Synthesizer Plug-Ins in C++"
*/

// modulation sources
enum class sources {
	sNone = 0,

	// midi sources
	sMidiNote,
	sMidiVel,
	sMidiModW,
	sMidiPbW,

	// internal modulators
	sLfo1,
	sEnv1,
	maxSources
};

// modulation destinations
enum class destinations {
	dNone = 0,

	// layer 0
	dFilterF,

	// add more layers here
	// e.g layer 1 
	// dLfo1F (internal mod source to internal mod source)
	// or allLfoF (universal destinations)

	maxDestinations
};

// transformations
enum class transform {
	tNone = 0,
	tUniToBi,
	tBiToUni,
	tMidiNorm,
	tMidiNormInv,
	tMidiToBi,
	tMidiToUni,
	tMidiSwitch,
	maxTransforms
};

struct modMatrixRow
{
	uint8 sourceIndex;
	uint8 destinationIndex;
	float* modIntensity;
	float* modRange;
	uint8 sourceTransform;
	bool enable;
};


inline modMatrixRow* createModMatrixRow(uint8 sourceIndex_,
										uint8 destinationIndex_,
										float* modIntensity_,
										float* modRange_,
										uint8 sourceTransform_,
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

// core
class ModulationMatrix {
public:
	ModulationMatrix(void);
	~ModulationMatrix(void);
	
	modMatrixRow** getModMatrixCore();
	void setModMatrixCore(modMatrixRow** modMatrix);
	uint8 getMatrixSize();
	void clearMatrix();
	void clearSources();
	void clearDestinations();
	void addModMatrixRow(modMatrixRow*);
	bool modMatrixRowExists(modMatrixRow*);
	void createMatrixCore();
	void deleteModMatrix();
	void enableModMatrixRow();
	void checkDestinationLayer();
	void doModulationsMatrix();

	float sources[static_cast<uint8>(sources::maxSources)];
	float destinations[static_cast<uint8>(destinations::maxDestinations)];

protected:
	modMatrixRow** matrixCore;
	int size;
};

#endif  // MODULATIONMATRIX_H_INCLUDED
