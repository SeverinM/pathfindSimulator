#include "cellGenerator.h"
#include <iostream>

Cell::Cell(float &side, bool const &isObstacle, sf::Vector2f const &startPos, sf::RenderWindow *win, sf::Vector2i coord) : RectangleShape(sf::Vector2f(side,side)){
	sideLenght = side;
	start = startPos;
	window = win;
	currentCoord = coord;
	this->setPosition(startPos);
	
	if (isObstacle)
		currentState = statesCell::obstacle;
	else
		currentState = statesCell::undiscovered;
}

void Cell::draw() {
	window->draw(*this);
}

void Cell::setState(Cell::statesCell newState) {
	currentState = newState;
	switch (currentState) {
		case statesCell::undiscovered:
			setFillColor(sf::Color::White);
			break;
		case statesCell::discovered:
			setFillColor(sf::Color::Yellow);
			break;
		case statesCell::frontier:
			setFillColor(sf::Color::Blue);
			break;
		case statesCell::obstacle:
			setFillColor(sf::Color::Red);
			break;
		case statesCell::begin:
			setFillColor(sf::Color::Green);
			break;
		case statesCell::end:
			setFillColor(sf::Color::Magenta);
			break;
		case statesCell::path:
			setFillColor(sf::Color::Cyan);
			break;
	}
}

Cell::statesCell Cell::getState() {
	return currentState;
}

sf::Vector2i Cell::getCoord() {
	return currentCoord;
}

std::vector<Cell *> Cell::getCellsAround() {
	std::vector<Cell *> output = std::vector<Cell*>();

	return output;
}

void Cell::setCameFrom(Cell * theCell) {
	cameFrom = theCell;
}

Cell * Cell::getCameFrom() {
	return cameFrom;
}

sf::Vector2f Cell::getPositions() {
	return RectangleShape::getPosition();
}