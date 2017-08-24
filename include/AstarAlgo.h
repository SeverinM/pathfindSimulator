#include "DijkstraAlgo.h"

class Astar : public Dijkstra {
public:
	static Cell * begin;
	Astar(cellGenerator * theGen);
	void next() override;
};
