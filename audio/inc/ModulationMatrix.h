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

//! Modulation Matrix 
/*! this fixed size mod matrix is based on the book
"Designing Software Synthesizer Plug-Ins in C++"
*/

enum sources {
	SOURCE_NONE = 0,

	SOURCE_LFO1,

	//SOURCE_ENV1,
	//SOURCE_VELOCITY,
	//SOURCE_MODWHEEL,
	//SOURCE_PITCHBEND,
	MAX_SOURCES
};

enum destinations {
	DEST_NONE = 0,

	// --- GUI control layer modulation (-1)
	DEST_UI_OSC1_FO,
	DEST_UI_OSC2_FO,
	DEST_UI_TO_OSC3_FO,

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
	TRANSFORM_MIDI_NORMALIZE,
	TRANSFORM_INVERT_MIDI_NORMALIZE,
	TRANSFORM_MIDI_TO_BIPOLAR,
	TRANSFORM_MIDI_TO_PAN,
	TRANSFORM_MIDI_SWITCH,
	TRANSFORM_MIDI_TO_ATTENUATION,
	TRANSFORM_NOTE_NUMBER_TO_FREQUENCY,
	MAX_TRANSFORMS
};

const float midiFreqTable[128] = {
	8.1757993698120117,
	8.6619567871093750,
	9.1770238876342773,
	9.7227182388305664,
	10.3008613586425780,
	10.9133825302124020,
	11.5623254776000980,
	12.2498569488525390,
	12.9782714843750000,
	13.7500000000000000,
	14.5676174163818360,
	15.4338531494140630,
	16.3515987396240230,
	17.3239135742187500,
	18.3540477752685550,
	19.4454364776611330,
	20.6017227172851560,
	21.8267650604248050,
	23.1246509552001950,
	24.4997138977050780,
	25.9565429687500000,
	27.5000000000000000,
	29.1352348327636720,
	30.8677062988281250,
	32.7031974792480470,
	34.6478271484375000,
	36.7080955505371090,
	38.8908729553222660,
	41.2034454345703130,
	43.6535301208496090,
	46.2493019104003910,
	48.9994277954101560,
	51.9130859375000000,
	55.0000000000000000,
	58.2704696655273440,
	61.7354125976562500,
	65.4063949584960940,
	69.2956542968750000,
	73.4161911010742190,
	77.7817459106445310,
	82.4068908691406250,
	87.3070602416992190,
	92.4986038208007810,
	97.9988555908203130,
	103.8261718750000000,
	110.0000000000000000,
	116.5409393310546900,
	123.4708251953125000,
	130.8127899169921900,
	138.5913085937500000,
	146.8323822021484400,
	155.5634918212890600,
	164.8137817382812500,
	174.6141204833984400,
	184.9972076416015600,
	195.9977111816406200,
	207.6523437500000000,
	220.0000000000000000,
	233.0818786621093700,
	246.9416503906250000,
	261.6255798339843700,
	277.1826171875000000,
	293.6647644042968700,
	311.1269836425781200,
	329.6275634765625000,
	349.2282409667968700,
	369.9944152832031200,
	391.9954223632812500,
	415.3046875000000000,
	440.0000000000000000,
	466.1637573242187500,
	493.8833007812500000,
	523.2511596679687500,
	554.3652343750000000,
	587.3295288085937500,
	622.2539672851562500,
	659.2551269531250000,
	698.4564819335937500,
	739.9888305664062500,
	783.9908447265625000,
	830.6093750000000000,
	880.0000000000000000,
	932.3275146484375000,
	987.7666015625000000,
	1046.5023193359375000,
	1108.7304687500000000,
	1174.6590576171875000,
	1244.5079345703125000,
	1318.5102539062500000,
	1396.9129638671875000,
	1479.9776611328125000,
	1567.9816894531250000,
	1661.2187500000000000,
	1760.0000000000000000,
	1864.6550292968750000,
	1975.5332031250000000,
	2093.0046386718750000,
	2217.4609375000000000,
	2349.3181152343750000,
	2489.0158691406250000,
	2637.0205078125000000,
	2793.8259277343750000,
	2959.9553222656250000,
	3135.9633789062500000,
	3322.4375000000000000,
	3520.0000000000000000,
	3729.3100585937500000,
	3951.0664062500000000,
	4186.0092773437500000,
	4434.9218750000000000,
	4698.6362304687500000,
	4978.0317382812500000,
	5274.0410156250000000,
	5587.6518554687500000,
	5919.9106445312500000,
	6271.9267578125000000,
	6644.8750000000000000,
	7040.0000000000000000,
	7458.6201171875000000,
	7902.1328125000000000,
	8372.0185546875000000,
	8869.8437500000000000,
	9397.2724609375000000,
	9956.0634765625000000,
	10548.0820312500000000,
	11175.3037109375000000,
	11839.8212890625000000,
	12543.8535156250000000
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
	uint8 getMatrixSize();
	inline void clearMatrix();
	inline void clearSources();
	inline void clearDestinations();
	void addModMatrixRow(modMatrixRow* row);
	inline bool modMatrixRowExists(uint8 sourceIndex, uint8 destinationIndex);
    inline void createMatrixCore();
	inline void deleteModMatrix();
	inline bool enableModMatrixRow(uint8 sourceIndex, uint8 destinationIndex, bool enable);
	inline bool checkDestinationLayer(uint8 layer, modMatrixRow* row);
	inline void doModulationsMatrix(uint8 modLayer);

    float sources[MAX_SOURCES];
    float destinations[MAX_DESTINATIONS];

protected:
	inline float mmaMIDItoAtten(uint8 uMIDIValue);
	inline float mmaMIDItoAtten_dB(uint8 uMIDIValue);
	inline uint8 unipolarToMIDI(float fUnipolarValue);
	inline float midiToUnipolar(uint8 uMIDIValue);
	inline float bipolarToUnipolar(float dValue);
	inline float midiToPanValue(uint8 uMIDIValue);
	inline float midiToBipolar(uint8 uMIDIValue);
	inline float unipolarToBipolar(float dValue);

	modMatrixRow** matrixCore;
	uint8 size;
};

#endif  // MODULATIONMATRIX_H_INCLUDED
