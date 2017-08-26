#pragma once
#include "Conway.h"
#include <iostream>
#include <SFML/Main.hpp>

Conway::Conway(int nbStep, int number, std::vector<std::vector<Cell>> &theGrid) : randomGeneration(number,theGrid) {
	step = nbStep;
}


int Conway::HowManyCellAround(int x, int y, cellGenerator *theGen) {
	int count = 0;
	std::vector<sf::Vector2f> allVec{ sf::Vector2f(x - 1,y),sf::Vector2f(x - 1,y - 1),sf::Vector2f(x,y - 1),sf::Vector2f(x + 1,y - 1),sf::Vector2f(x + 1,y),sf::Vector2f(x + 1,y + 1),sf::Vector2f(x,y + 1),sf::Vector2f(x - 1,y + 1) };
	for (int i = 0; i < allVec.size(); i++) {
		if (!(allVec[i].x < 0 || allVec[i].y < 0 || allVec[i].y >= theGen->nbRow|| allVec[i].x >= theGen->nbColumn)) {
			if (theGen->getCell(allVec[i].x,allVec[i].y)->getState() == Cell::statesCell::obstacle) {
				count += 1;
			}
		}	
	}
	return count;
}


void Conway::apply(cellGenerator *theGen) {
	std::vector<std::vector<Cell>> newGrid;
	randomGeneration rand(randomness, theGen->copyList());
	rand.apply(theGen);
	workingGrid = theGen->copyList();

	for (int i = 0; i < step; i++){
		for (int y = 0; y < workingGrid.size(); y++) {
			newGrid.push_back(std::vector<Cell>{});
			for (int x = 0; x < workingGrid[y].size(); x++) {
				float number = 8;
				int number2;
				number2 = HowManyCellAround(x, y, theGen);
				Cell newCell(number, false, sf::Vector2f(9 * x + theGen->startPos.x, 9 * y + theGen->startPos.y), theGen->getRender(), sf::Vector2i(x, y));
				if (workingGrid[y][x].getState() == Cell::statesCell::undiscovered && number2 >= 5) {
					newCell.setState(Cell::statesCell::obstacle);
				}
				if (workingGrid[y][x].getState() == Cell::statesCell::obstacle && number2 >= 4) {
					newCell.setState(Cell::statesCell::obstacle);
				}
				newGrid[y].push_back(newCell);
			}
		}
		theGen->setAllCells(newGrid);
		workingGrid = std::vector<std::vector<Cell>>(newGrid);
		newGrid = std::vector<std::vector<Cell>>();
	}
	theGen->setAsGoal(theGen->getCell(95, 95));
	std::cout << "hiu" << std::endl;
	theGen->setBegin(theGen->getCell(5, 5));
}