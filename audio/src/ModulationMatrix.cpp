/*
  ==============================================================================

    ModulationMatrix.cpp
    Created: 2 Jan 2016 9:16:56pm
    Author:  nj

  ==============================================================================
*/

#include "ModulationMatrix.h"

ModulationMatrix::ModulationMatrix()
{
    // assertions for how the Voices and filters work
    jassert(DEST_OSC1_GAIN + 1 == DEST_OSC2_GAIN);
    jassert(DEST_OSC1_GAIN + 2 == DEST_OSC3_GAIN);

    jassert(DEST_OSC1_PAN + 1 == DEST_OSC2_PAN);
    jassert(DEST_OSC1_PAN + 2 == DEST_OSC3_PAN);

    jassert(DEST_OSC1_PI + 1 == DEST_OSC2_PI);
    jassert(DEST_OSC1_PI + 2 == DEST_OSC3_PI);

    jassert(DEST_OSC1_PW + 1 == DEST_OSC2_PW);
    jassert(DEST_OSC1_PW + 2 == DEST_OSC3_PW);

    jassert(DEST_FILTER1_LC + 1 == DEST_FILTER2_LC);
    jassert(DEST_FILTER1_HC + 1 == DEST_FILTER2_HC);
    jassert(DEST_FILTER1_RES + 1 == DEST_FILTER2_RES);

    // TODO: hopefully the below things are correct
    jassert(DEST_LFO1_FREQ + 1 == DEST_LFO2_FREQ);
    jassert(DEST_LFO1_FREQ + 2 == DEST_LFO3_FREQ);

    jassert(DEST_VOL_ENV_SPEED + 1 == DEST_ENV2_SPEED);
    jassert(DEST_VOL_ENV_SPEED + 2 == DEST_ENV3_SPEED);
}

ModulationMatrix::~ModulationMatrix()
{
}
