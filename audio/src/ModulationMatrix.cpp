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
}

ModulationMatrix::~ModulationMatrix()
{
}
