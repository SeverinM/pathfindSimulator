#pragma once
#include "randomGeneration.h"
class Conway : public randomGeneration {
private:
	int step;
public:
	Conway(int nbStep, int number, std::vector<std::vector<Cell>> &theGrid);
	void apply(cellGenerator *theGen);
	int HowManyCellAround(int x, int y, cellGenerator *theGen);
};