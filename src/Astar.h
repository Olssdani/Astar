#pragma once
#include <iostream>
#include "grid.h"
#include "pos_2D.h"
#include <vector>
#include "Astar_node.h"

class Astar
{
public:
	//Constructor
	Astar();
	Astar(const pos_2D &_start,const pos_2D& _end);
	//Update the start and end node for the next run
	void update(const pos_2D &_start, const pos_2D &_end);
	//Start the calculations for the A*
	void run(grid &temp);

private:
	// The positions
	pos_2D start;
	pos_2D end;
	
};
// Calculate the Euclidean distance
int euklidiska(pos_2D pos1, int x, int y);


