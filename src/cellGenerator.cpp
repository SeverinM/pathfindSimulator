#include "cellGenerator.h"
#include <iostream>
#include <stdlib.h>

cellGenerator::cellGenerator(float const &side, float const &between, int const &row, int const &column, sf::Vector2f const &startPos, sf::RenderWindow *win, int proba) {
	rend = win;
	sideLenght = side;
	LenghtBetweenCell = between;
	nbRow = row;
	nbColumn = column;
	srand(time(0));
	for (int y = 0; y < nbRow; y++) 
	{
		allCells.push_back(std::vector<Cell>());
		for (int x = 0; x < nbColumn; x++) 
		{
			allCells[y].push_back(
				Cell(sideLenght, false, 
					sf::Vector2f(startPos.x + (sideLenght + LenghtBetweenCell) * x,
					startPos.y + (sideLenght + LenghtBetweenCell) * y), win,
					sf::Vector2i(x,y)
				)
			);
			int random_integer = rand();
			if (random_integer % 100 < proba)
				allCells[y][x].setState(Cell::statesCell::obstacle);
		}
	}

	std::cout << "Test" << std::endl;
	setBegin(getCell(5, 5));
	std::cout << "Goodbye" << std::endl;
	setAsGoal(getCell(nbColumn - 5, nbRow - 5));
	theCursor = new Cursor(cellGenerator::getCell(1, 1));
	cursorPosition = sf::Vector2f(1, 1);
}

void cellGenerator::draw() {
	for (int y = 0; y < nbRow; y++) 
	{
		for (int x = 0; x < nbColumn; x++)
		{
			allCells[y][x].draw();
		}
	}
	rend->draw(*theCursor);
}

Cell * cellGenerator::getCell(float const &x, float const &y) {
	if (x >= 0 && x < nbColumn && y >= 0 && y < nbRow)
		return &allCells[y][x];
	else
		return NULL;
}

void cellGenerator::setBegin(Cell *theCell) {
	if (beginCell != nullptr) {
		beginCell->setState(Cell::statesCell::undiscovered);
	}

	std::cout << "Adress of theCell : " << theCell << std::endl;
	theCell->setState(Cell::statesCell::begin);
	beginCell = theCell;
}

void cellGenerator::setAsGoal(Cell * theCell) {
	theCell->setState(Cell::statesCell::end);
}

std::vector<Cell *> cellGenerator::getCellsAround(Cell * workingCell) {
	std::vector<Cell *> output = std::vector<Cell*>();
	output.push_back(getCell(workingCell->getCoord().x - 1, workingCell->getCoord().y));
	output.push_back(getCell(workingCell->getCoord().x , workingCell->getCoord().y + 1));
	output.push_back(getCell(workingCell->getCoord().x, workingCell->getCoord().y - 1));
	output.push_back(getCell(workingCell->getCoord().x + 1, workingCell->getCoord().y));
	return output;
}

Cell * cellGenerator::getBegin() {
	return beginCell;
}

Cell * cellGenerator::getGoal() {
	for (int y = 0; y < nbRow; y++)
	{
		for (int x = 0; x < nbColumn; x++)
		{
			if (allCells[y][x].getState() == Cell::statesCell::end)
				return &(allCells[y][x]);
		}
	}
}

void cellGenerator::moveCursor(sf::Vector2f &&dir) {
	if (getCell(dir.x + cursorPosition.x,dir.y + cursorPosition.y) != NULL){
		cursorPosition += dir;
		theCursor->setNewCell(getCell(cursorPosition.x,cursorPosition.y));
	}
}

Cursor * cellGenerator::getCursor() {
	return theCursor;
}

std::vector<Cell *> cellGenerator::getAllCells() {
	std::vector<Cell *> output;
	for (int y = 0; y < nbRow; y++) {
		for (int x = 0; x < nbColumn; x++) {
			output.push_back(getCell(x, y));
		}
	}
	return output;
}

Cursor::Cursor(Cell * startingCell) {
	setNewCell(startingCell);
	this->setFillColor(sf::Color::Black);
}

void Cursor::setNewCell(Cell * newCell) {
	currentCell = newCell;
	this->setSize(currentCell->getSize() / 1.5f);
	this->setPosition(currentCell->getPosition());
}

void Cursor::changeSide() {
	switch (currentCell->getState()) {
	case Cell::statesCell::obstacle:
		currentCell->setState(Cell::statesCell::undiscovered);
		break;
	case Cell::statesCell::undiscovered:
		currentCell->setState(Cell::statesCell::obstacle);
		break;
	}
}
