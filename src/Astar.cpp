#include <cmath>

#include "AstarAlgo.h"

Cell * Astar::begin;

bool compareFunction2(Cell * cell1, Cell * cell2) {
	sf::Vector2f vec1 = cell1->getPositions() - Astar::goal->getPositions();
	sf::Vector2f vec12 = cell1->getPositions() - Astar::begin->getPositions();
	sf::Vector2f vec2 = cell2->getPositions() - Astar::goal->getPositions();
	sf::Vector2f vec22 = cell2->getPositions() - Astar::begin->getPositions();
	int distance1 = sqrt(std::pow(vec1.x, 2) + std::pow(vec1.y, 2)) + sqrt(std::pow(vec12.x, 2) + std::pow(vec12.y, 2));
	int distance2 = sqrt(std::pow(vec2.x, 2) + std::pow(vec2.y, 2)) + sqrt(std::pow(vec22.x, 2) + std::pow(vec22.y, 2));
	return (distance1 < distance2);
}

Astar::Astar(cellGenerator * theGen) : Dijkstra(theGen) {
	begin = cellHandler->getBegin();
}

void Astar::next() {
	if (allCells.size() > 0) {
		std::sort(allCells.begin(), allCells.end(), compareFunction2);
		for (Cell * theCell : cellHandler->getCellsAround(allCells[0]))
		{
			if (theCell != nullptr && theCell->getState() == Cell::statesCell::undiscovered) {
				addFrontier(theCell);
				theCell->setCameFrom(allCells[0]);
			}
			if (theCell != nullptr && theCell->getState() == Cell::statesCell::end) {
				stop = true;
				endcell = theCell;
				theCell->setCameFrom(allCells[0]);
			}
		}
		discover();
	}
	else
		stop = true;
	if (stop) {
		for (Cell * theCell : allCells)
		{
			theCell->setState(Cell::statesCell::undiscovered);
		}
	}

	if (stop && endcell != nullptr)
		showPath();
}