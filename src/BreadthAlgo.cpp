#include "BreadthAlgo.h"
#include <iostream>
#include <chrono>
#include <thread>

BreadthAlgo::BreadthAlgo(cellGenerator * theGen) {
	frontierQueue = std::queue<Cell*>();
	cellHandler = theGen;
	stop = true;
	endcell = nullptr;
	discoveredCount = 0;
	pathLenght = 0;
}

int BreadthAlgo::getCountDiscovered() {
	return discoveredCount;
}

int BreadthAlgo::getCountPath() {
	return pathLenght;
}

void BreadthAlgo::addFrontier(Cell * theCell) {
	frontierQueue.push(theCell);
	theCell->setState(Cell::statesCell::frontier);
}

void BreadthAlgo::discover() { //Remove the buttom most element , assume this cell is discovered
	discoveredCount += 1;
	Cell * theCell = frontierQueue.front();
	theCell->setState(Cell::statesCell::discovered);
	frontierQueue.pop();
}

void BreadthAlgo::next() {
	if (frontierQueue.size() > 0) {
		for (Cell * theCell : cellHandler->getCellsAround(frontierQueue.front()))
		{
			if (theCell != nullptr && theCell->getState() == Cell::statesCell::undiscovered) {
				addFrontier(theCell);
				theCell->setCameFrom(frontierQueue.front());
			}
			if (theCell != nullptr && theCell->getState() == Cell::statesCell::end) {
				stop = true;
				endcell = theCell;
				theCell->setCameFrom(frontierQueue.front());
			}
		}
		discover();
	}
	else
		stop = true;
	if (stop) {
		while (!frontierQueue.empty()) {
			discover();
		}
	}

	if (stop && endcell != nullptr)
		showPath();
}

void BreadthAlgo::Init() {
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

bool BreadthAlgo::getStop() {
	return stop;
}

void BreadthAlgo::setStop(bool value) {
	stop = value;
}

void BreadthAlgo::showPath() {
	Cell * currentCell = endcell;
	while (currentCell->getState() != Cell::statesCell::begin) {
		pathLenght += 1;
		if (currentCell->getState() != Cell::statesCell::end)
			currentCell->setState(Cell::statesCell::path);
		currentCell = currentCell->getCameFrom();
	}
}

void BreadthAlgo::reset() {
	discoveredCount = 0;
	pathLenght = 0;
	frontierQueue = std::queue<Cell*>();
	frontierQueue.push(cellHandler->getBegin());
	next();
	setStop(true);
	for (Cell *  currentCell : cellHandler->getAllCells())
	{
		if (currentCell->getState() == Cell::statesCell::path || currentCell->getState() == Cell::statesCell::discovered || currentCell->getState() == Cell::statesCell::frontier)
			currentCell->setState(Cell::statesCell::undiscovered);
	}
}
