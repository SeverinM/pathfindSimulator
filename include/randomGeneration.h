#pragma once
#include "basicModification.h"

class randomGeneration : public basicModification {
protected:
	int randomness;
public:
	randomGeneration(int number, std::vector<std::vector<Cell>> &theGrid);
	void apply(cellGenerator* theGen);
};
