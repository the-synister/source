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

