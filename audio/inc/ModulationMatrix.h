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

//! Enumeration of all mod sources
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

//! Enumeration of all mod destinations
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

//! mapping for mod sources to uni-/bipolar.
/*!
The static mapping function that returns whether a modulation source if uni- or bipolar. 
This can  be used to determine how a modulation amount might have to be transformed.
@param source the source to be mapped
@returns true if unipolar, else false
*/
static inline bool isUnipolar(eModSource source) {
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

//! Transformation for mod amounts to unipolar.
/*!
The static transformation function that returns a unipolar value, transformed from the range and current value of a mod amount.
@param min the minimum value of the mod amount
@param max the maximum value of the mod amount
@param value the current value of the mod amount
@returns transformed value between 0 and 1
*/
static float toUnipolar(float min, float max, float value) { return (value - min) / max - min; }

//! Transformation for mod amounts to bipolar.
/*!
The static transformation function that returns a bipolar value, transformed from the range and current value of a mod amount.
@param min the minimum value of the mod amount
@param max the maximum value of the mod amount
@param value the current value of the mod amount
@returns transformed value between -1 and 1
*/
static float toBipolar(float min, float max, float value) { return (2.0f*(value - min) / max - min) - 1.0f; }

//! Modulation Matrix Class
/*! This fixed size mod matrix is based on the book "Designing Software Synthesizer Plug-Ins in C++".
It contains a row for each possible modulation source setting in the GUI, together with its amount and the name of its corresponding Combobox.
Within the synister synthesizer, it is maintained and instanced in the SynthParams as a global modulation matrix. Its doModulationsMatrix method
that applies the modulation is called from the Voice for each sample.
*/
class ModulationMatrix {
public:
    //! ModulationMatrix constructor.
    ModulationMatrix();
    //! ModulationMatrix destructor.
    ~ModulationMatrix();

    //! ModMatrixRow structure.
    struct ModMatrixRow
    {
        ParamStepped<eModSource>* modSrc; //!< mod source enum/index
        destinations destinationIndex; //!< mod destination enum/index
        Param* modIntensity; //!< pointer to mod intensity param
        String modSrcBox; //!< mod source box name

        //! ModMatrixRow constructor.
        ModMatrixRow(ParamStepped<eModSource> *s, destinations d, Param *intensity, String boxname)
            : modSrc(s)
            , destinationIndex(d)
            , modIntensity(intensity)
            , modSrcBox(boxname)
        {}
    };

    //! Check whether a ModMatrixRow exists.
    /*!
    @param sourceIndex the minimum value of the mod amount
    @param destinationIndex the maximum value of the mod amount
    @returns true if a row exists, else false
    */
    inline bool modMatrixRowExists(eModSource sourceIndex, destinations destinationIndex) const;

    //! Changes the source of a destination that belongs to a specific combobox.
    /*!
    Method that is called when the user selects a new source in a combobox. This combobox belongs to a
    row in the matrix, which is then updated.
    @param comboBoxName name of the combobox the information comes from
    @param source the source to be changed to
    */
    inline void changeSource(const String &comboBoxName, eModSource source);

    //! Adds a row to the modulation matrix.
    /*!
    Method that is called for each row to be added when the matrix is initialized.
    @param s the initial source
    @oaram d the destination
    @param intensity the initial intensity value
    @param comboboxName the name of the combobox the row belongs to
    */
    inline void addModMatrixRow(ParamStepped<eModSource> *s, destinations d, Param *intensity, String comboboxName);

    //! Applies the modulation for a sample.
    /*!
    Method that is called for each sample when the modulation of all sources to all destinations has to be applied.
    @param src the pointer to the source values
    @oaram dst the pointer to the destination the results are written to
    */
    inline void doModulationsMatrix(const float** src, float** dst) const;


private:
    std::vector<ModMatrixRow> matrixCore; //!< matrix core that keeps all the rows of the matrix in a vector
};

inline void ModulationMatrix::doModulationsMatrix(const float** src, float** dst) const
{
    for (const ModMatrixRow &row : matrixCore)
    {
        // get the source value & mod intensity
        if (row.modSrc->getStep() > eModSource::eNone && row.modSrc->getStep() < eModSource::nSteps
            && row.destinationIndex > DEST_NONE && row.destinationIndex < MAX_DESTINATIONS) {
            float source = *(src[row.modSrc->getStep()]);
            float intensity = row.modIntensity->get();

            // get the min max values for the intensity for transformation
            float min = row.modIntensity->getMin();
            float max = row.modIntensity->getMax();

            if (isUnipolar(row.modSrc->getStep())) {
                // if the source is unipolar, transform the intensity to bipolar
                intensity = toBipolar(min, max, intensity);
            }
            else {
                // else the source is bipolar, transform the intensity to unipolar
                intensity = toUnipolar(min, max, intensity);
            }

            float dModValue = source*intensity;
            /*we are just adding the modified values into the predefined buffers
              the conversion and application is applied outside of the matrix*/
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
        if (row.modSrc->getStep() == sourceIndex && row.destinationIndex == destinationIndex)
        {
            return true;
        }
    }
    return false;
}

inline void ModulationMatrix::changeSource(const String &comboBoxName, eModSource source) {
    for (ModMatrixRow &row : matrixCore)
    {
        // find matching source/destination pairs
        if (row.modSrcBox == comboBoxName)
        {
            // before we change the old source, we gotta check whether it is a switch between unipolar<->bipolar (for conversion reasons)
            eModSource oldSource = row.modSrc->getStep();
            Param* modAmountParam = row.modIntensity;
            float newModAmountValue;

            // derived from the initial values, eNone should be considered as "unipolar" here since the  initial modAmount is set to a value fit for unipolar sources
            bool newSourcePolarity = (source == eNone) ? true : isUnipolar(source);
            bool oldSourcePolarity = (oldSource == eNone) ? true : isUnipolar(oldSource);

            if (newSourcePolarity < oldSourcePolarity) {
                // uni- to bipolar source -> mod amount [-x, x] to [0, x]
                newModAmountValue = modAmountParam->getUI();

                // find the middle
                float middle = (modAmountParam->getMax() + modAmountParam->getMin()) / 2.f;

                // get the absolute value if it's negative
                if (modAmountParam->getUI() < middle) newModAmountValue = modAmountParam->getUI() + 2.f * (middle - modAmountParam->getUI());

                // transform
                newModAmountValue = (newModAmountValue - middle) * 2.f;
                modAmountParam->setHost(newModAmountValue);
            }
            else if (newSourcePolarity > oldSourcePolarity) {
                // bi- to unipolar source -> mod amount [0, x] to [-x, x]

                // find the middle
                float middle = (modAmountParam->getMax() + modAmountParam->getMin()) / 2.f;

                // transform
                newModAmountValue = middle + (modAmountParam->getUI() / 2.f);
                modAmountParam->setHost(newModAmountValue);
            }
            
            // the new source is already set, since it's a Param*
        }
    }
}

inline void ModulationMatrix::addModMatrixRow(ParamStepped<eModSource> *s, destinations d, Param *intensity, String boxname)
{
    matrixCore.push_back(ModMatrixRow(s, d, intensity, boxname));
}

#endif  // MODULATIONMATRIX_H_INCLUDED
