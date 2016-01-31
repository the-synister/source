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
    clearSources();
    clearDestinations();
}

ModulationMatrix::~ModulationMatrix()
{
    for (unsigned int i = 0; i < matrixCore.size(); ++i) {
        delete matrixCore[i];
    }
}

void ModulationMatrix::addModMatrixRow(modMatrixRow * row)
{
    // add if not already existing
    if (!modMatrixRowExists(row->sourceIndex, row->destinationIndex))
    {
        matrixCore.push_back(row);
    }
}