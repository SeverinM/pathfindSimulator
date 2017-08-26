#include "randomGeneration.h"
#include <iostream>

randomGeneration::randomGeneration(int number, std::vector<std::vector<Cell>> &theGrid) {
	randomness = number;
	workingGrid = theGrid;
}

void randomGeneration::apply(cellGenerator* theGen) {
	int lenght = workingGrid.size();
	for (int y = 0; y < lenght; y++) {
		int lenght2 = workingGrid[y].size();
		for (int x = 0; x < lenght2; x++) {
			int random = rand() % 100;
			if (random < randomness && workingGrid[y][x].getState() == Cell::statesCell::undiscovered) {
				workingGrid[y][x].setState(Cell::statesCell::obstacle);
			}
		}
	}
	theGen->setAllCells(workingGrid);
}