/*
  ==============================================================================

    ModulationMatrix.cpp
    Created: 2 Jan 2016 9:16:56pm
    Author:  nj

  ==============================================================================
*/

#include "ModulationMatrix.h" 

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