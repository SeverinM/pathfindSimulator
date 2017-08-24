#include "DijkstraAlgo.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Cell * Dijkstra::goal;

bool compareFunction(Cell * cell1, Cell * cell2) {
	sf::Vector2f vec1 = cell1->getPositions() - Dijkstra::goal->getPositions();
	sf::Vector2f vec2 = cell2->getPositions() - Dijkstra::goal->getPositions();
	int distance1 = sqrt(std::pow(vec1.x, 2) + std::pow(vec1.y, 2));
	int distance2 = sqrt(std::pow(vec2.x, 2) + std::pow(vec2.y, 2));
	return (distance1 < distance2);
}

Dijkstra::Dijkstra(cellGenerator * theGen) : BreadthAlgo(theGen) {
	allCells = std::vector<Cell*>();
	goal = cellHandler->getGoal();
	std::cout << goal->getState() << std::endl;
};

void Dijkstra::next() {
	if (allCells.size() > 0) {
		std::sort(allCells.begin(), allCells.end(), compareFunction);
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

void Dijkstra::addFrontier(Cell * theCell) {
	allCells.push_back(theCell);
	theCell->setState(Cell::statesCell::frontier);
}

void Dijkstra::discover() {
	Cell * theCell = allCells[0];
	theCell->setState(Cell::statesCell::discovered);
	allCells.erase(allCells.begin());
}

void Dijkstra::Init() {
	stop = false;
	for (Cell * theCell : cellHandler->getCellsAround(cellHandler->getBegin()))
	{
		if (theCell != nullptr && theCell->getState() == Cell::statesCell::undiscovered) {
			addFrontier(theCell);
			theCell->setCameFrom(cellHandler->getBegin());
		}
		if (theCell != nullptr && theCell->getState() == Cell::statesCell::end)
			stop = true;
	}
}

bool Dijkstra::getStop() {
	return BreadthAlgo::getStop();
}

void Dijkstra::showPath() {
	BreadthAlgo::showPath();
}