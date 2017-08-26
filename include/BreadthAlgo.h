#pragma once
#include <queue>
#include "cellGenerator.h"

class BreadthAlgo {
	protected :
		int discoveredCount;
		int pathLenght;
		std::queue<Cell *> frontierQueue;
		cellGenerator *cellHandler;
		bool stop;
		Cell * endcell = nullptr;
	public:
		BreadthAlgo(cellGenerator * theGen);
		virtual void next();
		virtual void Init();
		virtual void addFrontier(Cell * theCell);
		virtual void discover();
		virtual bool getStop();
		virtual void showPath();
		virtual void setStop(bool value);
		virtual void reset();
		int getCountDiscovered();
		int getCountPath();
};
