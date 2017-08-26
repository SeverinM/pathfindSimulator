#include <vector>
#include "cellGenerator.h"

class basicModification {
protected :
	std::vector<std::vector<Cell>> workingGrid;
public:
	virtual void apply(cellGenerator* theGen) = 0;
};
