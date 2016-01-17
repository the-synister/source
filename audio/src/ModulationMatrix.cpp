/*
  ==============================================================================

    ModulationMatrix.cpp
    Created: 2 Jan 2016 9:16:56pm
    Author:  nj

  ==============================================================================
*/

#include "ModulationMatrix.h" 

ModulationMatrix::ModulationMatrix(void)
{
	matrixCore = NULL;
	createModMatrixCore();

	size = 0;
	clearMatrix(); // fill with NULL
	clearSources();
	clearDestinations();
}

ModulationMatrix::~ModulationMatrix(void)
{
}

modMatrixRow ** ModulationMatrix::getModMatrixCore()
  {
	  return matrixCore;
  }

void ModulationMatrix::setModMatrixCore(modMatrixRow ** modMatrix)
{
	if (matrixCore) {
		for (int i = 0; i < size; ++i) {
			//delete ptr
			modMatrixRow* row = matrixCore[i];
			delete row;
			--size;
		}
		size = 0;
		delete[] matrixCore;
	}
	matrixCore = modMatrix;
	size = getMatrixSize();
}

uint8 ModulationMatrix::getMatrixSize()
{
	uint8 nSize = 0;
	if (!matrixCore) return nSize;

	for (int i = 0; i<MAX_SOURCES *
		MAX_DESTINATIONS; i++)
	{
		modMatrixRow* row = matrixCore[i];
		if (row)
			nSize++;
	}
	return nSize;
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

void ModulationMatrix::addModMatrixRow(modMatrixRow * row)
{
	if (!matrixCore)
		createMatrixCore();

	// add if not already existing
	if (!modMatrixRowExists(row->sourceIndex, row->destinationIndex))
	{
		matrixCore[size] = row;
		size++;
	}
	else
		delete row;
}

inline bool ModulationMatrix::modMatrixRowExists(uint8 sourceIndex, uint8 destinationIndex)
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

inline bool ModulationMatrix::enableModMatrixRow(uint8 sourceIndex, uint8 destinationIndex, bool enable)
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

inline bool ModulationMatrix::checkDestinationLayer(uint8 layer, modMatrixRow * row)
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

/* unipolarToBipolar()

calculates the bipolar (-1 -> +1) value from a unipolar (0 -> 1) value

dValue = the value to convert
*/
inline float ModulationMatrix::unipolarToBipolar(float dValue)
{
	return 2.0f*dValue - 1.0f;
}

/* midiToBipolar()

calculates the bipolar (-1 -> +1) value from a unipolar MIDI (0 -> 127) value

uint8 uMIDIValue = the MIDI value to convert
*/
inline float ModulationMatrix::midiToBipolar(uint8 uMIDIValue)
{
	return (2.0f*static_cast<float>(uMIDIValue) / 127.0f - 1.0f);
}

/* midiToPanValue()

calculates the pan value (-1 -> +1) value from a unipolar MIDI (0 -> 127) value

uint8 uMIDIValue = the MIDI value to convert
*/
inline float ModulationMatrix::midiToPanValue(uint8 uMIDIValue)
{
	// see MMA DLS Level 2 Spec; controls are asymmetrical
	if (uMIDIValue == 64)
		return 0.0f;
	else if (uMIDIValue <= 1) // 0 or 1
		return -1.0f;

	return (2.0f*static_cast<float>(uMIDIValue) / 127.0f - 1.0f);
}

/* bipolarToUnipolar()

calculates the unipolar (0 -> 1) value from a bipolar (-1 -> +1) value

dValue = the value to convert
*/
inline float ModulationMatrix::bipolarToUnipolar(float dValue)
{
	return 0.5f*dValue + 0.5f;
}

/* midiToUnipolar()

calculates the unipolar (0 -> 1) value from a MIDI (0 -> 127) value

dValue = the value to convert
*/
inline float ModulationMatrix::ModulationMatrix::midiToUnipolar(uint8 uMIDIValue)
{
	return static_cast<float>(uMIDIValue) / 127.0f;
}

/* unipolarToMIDI()

calculates the MIDI (0 -> 127) value from a unipolar (0 -> 1) value

dValue = the value to convert
*/
inline uint8 ModulationMatrix::unipolarToMIDI(float fUnipolarValue)
{
	return static_cast<uint8>(fUnipolarValue*127.0f);
}

/* mmaMIDItoAtten_dB()

calculates the dB of attenuation according to MMA DLS spec

uMIDIValue = the MIDI (0 -> 127) value to convert
*/
inline float ModulationMatrix::mmaMIDItoAtten_dB(uint8 uMIDIValue)
{
	if (uMIDIValue == 0)
		return -96.0f; // dB floor

	return 20.0f*log10((127.0f*127.0f) / ((static_cast<float>(uMIDIValue)*static_cast<float>(uMIDIValue))));
}

/* mmaMIDItoAtten()

calculates the raw attenuation according to MMA DLS spec

uMIDIValue = the MIDI (0 -> 127) value to convert
*/
inline float ModulationMatrix::mmaMIDItoAtten(uint8 uMIDIValue)
{
	if (uMIDIValue == 0)
		return 0.0f; // floor

	return (static_cast<float>(uMIDIValue)*static_cast<float>(uMIDIValue)) / (127.0f*127.0f);
}

inline void ModulationMatrix::doModulationsMatrix(uint8 modLayer)
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
		float source = sources[row->sourceIndex];

		switch (row->sourceTransform)
		{
		case TRANSFORM_UNIPOLAR_TO_BIPOLAR:
			source = unipolarToBipolar(source);
			break;

		case TRANSFORM_BIPOLAR_TO_UNIPOLAR:
			source = bipolarToUnipolar(source);
			break;

		case TRANSFORM_MIDI_TO_ATTENUATION:
			source = mmaMIDItoAtten(source);
			break;

		case TRANSFORM_MIDI_TO_PAN:
			source = midiToPanValue(source);
			break;

		case TRANSFORM_MIDI_SWITCH:
			source = source > 63.0f ? 1.0f : 0.0f;
			break;

		case TRANSFORM_MIDI_TO_BIPOLAR:
			source = midiToBipolar(source);
			break;

		case TRANSFORM_NOTE_NUMBER_TO_FREQUENCY:
			source = midiFreqTable[(uint8)source];
			break;

		case TRANSFORM_MIDI_NORMALIZE:
			source /= 127.0f; // 0->1 NOTE: MMA DLS uses divide-by-128 instead!, 0->0.9999
			break;

		case TRANSFORM_INVERT_MIDI_NORMALIZE:
			source /= 127.0f; // 0->1 NOTE: MMA DLS uses divide-by-128 instead!, 0->0.9999
			source = 1.0f - source; // 1->0 NOTE: MMA DLS uses divide-by-128 instead!, 0.9999->0
			break;

		default:
			break;
		}

		// destination += source*intensity*range
		//
		float dModValue = source*(row->modIntensity->get())*(row->modRange->get());

		destinations[row->destinationIndex] += dModValue;

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
