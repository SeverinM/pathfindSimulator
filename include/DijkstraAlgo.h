#include "BreadthAlgo.h"

class Dijkstra : public BreadthAlgo{
	protected :
		std::vector<Cell *> allCells;
	public :
		static Cell* goal;
		Dijkstra(cellGenerator * theGen);
		void next() override;
		void Init() override;
		void discover();
		bool getStop();
		void showPath();
		void addFrontier(Cell * theCell);
};
