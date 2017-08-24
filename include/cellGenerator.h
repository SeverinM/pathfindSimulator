#include <vector>
#include <SFML\Graphics.hpp>

class Cell : public sf::RectangleShape {
private:
	float sideLenght;
	sf::Vector2f start;
	sf::RenderWindow *window;
	sf::Vector2i currentCoord;
	Cell * cameFrom = nullptr;

public:
	enum statesCell
	{
		undiscovered,
		discovered,
		frontier,
		obstacle,
		begin,
		end,
		path
	};
	statesCell currentState;
	Cell(float &side, bool const &isObstacle, sf::Vector2f const &startPos, sf::RenderWindow *win, sf::Vector2i coord);
	void draw();
	void setState(statesCell newState);
	statesCell getState();
	sf::Vector2i getCoord();
	std::vector<Cell *> getCellsAround();
	void setCameFrom(Cell * theCell);
	Cell * getCameFrom();
	sf::Vector2f getPositions();
};

class Cursor : public sf::RectangleShape {
private:
	Cell * currentCell = nullptr;

public:
	Cursor(Cell * startingCell);
	void changeSide();
	void setNewCell(Cell * newCell);
};


class cellGenerator {
private:
	sf::RenderWindow * rend;
	std::vector<std::vector<Cell>> allCells;
	float sideLenght;
	float LenghtBetweenCell;
	sf::Vector2f startPos;
	int nbRow;
	int nbColumn;
	Cell *beginCell = nullptr;
	Cursor * theCursor = nullptr;
	sf::Vector2f cursorPosition;

public:
	Cursor * getCursor();
	cellGenerator(float const &side, float const &between, int const &row, int const &column, sf::Vector2f const &startPos, sf::RenderWindow *win, int proba);
	void draw();
	Cell * getCell(float const &x, float const &y);
	void setBegin(Cell *theCell);
	void setAsGoal(Cell *theCell);
	std::vector<Cell *> getCellsAround(Cell * workingCell);
	Cell * getBegin();
	Cell * getGoal();
	void moveCursor(sf::Vector2f &&dir);
	std::vector<Cell *> getAllCells();
};


