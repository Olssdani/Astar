#pragma once
#include <vector>
#include "Square.h"
#include <vector>
#include <string>
#include "pos_2D.h"
//This class creates and handle the grid
class grid
{
public:
	//constructor
	grid(const int &n);
	//Destrucor
	~grid();
	//Updates the vertices array and the indices array
	void update(float vert[]);
	void update(float vert[],unsigned int ind[]);
	// Return size of the grid
	int get_size();
	//checks if both start and end nodes has been placed
	bool const redo();
	//Find and assign type to square
	void const check_square(const float &x, const float &y, const std::string &temp);
	//Return the typ for the square
	int const type(const int &x, const int& y);
	//If the square is in OL
	bool const in_ol(const int &x, const int &y);
	//If the square is in the CL
	bool const in_cl(const int &x, const int &y);
	//Change the found road
	void const road_found(const pos_2D &pos);
	//Sets the square list status to the List
	void list(const int &x, const int &y, const std::string &list);
	void list(const pos_2D &pos, const std::string &list);
	//Resets the status and the color for the grid
	void reset();
	// The start and end node
	pos_2D  pos_start;
	pos_2D  pos_end;
	
private:
	//How big the grid should be in the window
	const static float max;
	//If the start and end node has been added
	bool start;
	bool end;	
	int size = 0;
	// The grid of squares
	Square **_grid;
};
