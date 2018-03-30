#include "grid.h"

const float grid::max = 0.9f;
//Constructor
grid::grid(const int &n)
{
	//The grid
	size = n;
	_grid = new Square*[size];
	for (int i = 0; i < size; ++i) {
		_grid[i] = new Square[size];
	}
		
	//Calculates the length of the squares
	float length = (max / size)*2;
	int counter = 0;
	//Loop and assign all the sqaures
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			//Sets the squares
			_grid[i][j].set_box(-max + j*length, max - i*length, length, counter);
			counter = counter+4;
		}
	}
	start = false;
	end = false;
}

// Destructor
grid::~grid(){

	//Free each sub-array
	for (int i = 0; i < size; ++i) {
		delete [] _grid[i];
	}
	//Free the array of pointers
	delete [] _grid;
}

//Updates the buffers
void grid::update(float vert[], unsigned int ind[]) {
	int counter = 0;
	//Loops over the grid and gives the vertices to the buffer
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			for (int k = 0; k < 16; ++k) {
				vert[counter] = _grid[i][j].vertices[k];
				++counter;
			}
		}
	}
	//Loops over the grid and gives the indices to the buffer
	counter = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			for (int k = 0; k < 6; ++k) {
				ind[counter] = _grid[i][j].indices[k];
				++counter;
			}
		}
	}
}
//Just update the vertex buffer
void grid::update(float vert[]) {
	int counter = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			for (int k = 0; k < 16; ++k) {
				vert[counter] = _grid[i][j].vertices[k];
				++counter;
			}
		}
	}
}

//Return the number of squares in each row
int grid::get_size() {
	return size;
}

//Checks which square that were pressed
void const grid::check_square(const float &x, const float &y, const std::string &temp) {
	float best = 10000000000;
	int pos_x = 0;
	int pos_y = 0;
	int counter = 0;
	
	//Checks the distance from the point to all the corners of the square and add them togheter.
	//The square with the lowest distance is the square we clicked on
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (best > _grid[i][j].distance(x, y)) {
				best = _grid[i][j].distance(x, y);
				pos_x = j;
				pos_y = i;
			}			
		}
	}
	//These lines of code checks what the purpose of the click was
	if (temp == "start") {
		// If the start node already has been assign
		if (start) {
			//Loops through and find the start node
			for (int i = 0; i < size; ++i) {
				for (int j = 0; j < size; ++j) {
					//resets the start node
					if (_grid[j][i].type == 1) {
						_grid[j][i].type = 0;
						_grid[j][i].color(0.0f);
					}
				}
			}
			//Update the new node
			_grid[pos_y][pos_x].color(0.1f);
			_grid[pos_y][pos_x].type = 1;
			pos_start.set(pos_x, pos_y);

		}
		//If the start node hasn't been pressed
		else {
			_grid[pos_y][pos_x].color(0.1f);
			start = true;
			_grid[pos_y][pos_x].type = 1;
			pos_start.set(pos_x, pos_y);
		}
		
	}
	else if (temp == "end") {
		if (end) {
			for (int i = 0; i < size; ++i) {
				for (int j = 0; j < size; ++j) {
					if (_grid[j][i].type == 2) {
						_grid[j][i].type = 0;
						_grid[j][i].color(0.0f);
					}
				}
			}
			_grid[pos_y][pos_x].color(0.2f);
			_grid[pos_y][pos_x].type = 2;
			pos_end.set(pos_x, pos_y);

		}
		else {

			_grid[pos_y][pos_x].color(0.2f);
			end = true;
			_grid[pos_y][pos_x].type = 2;
			pos_end.set(pos_x, pos_y);

		}
	
	}
	else if (temp == "wall") {
		_grid[pos_y][pos_x].color(0.3f);
		_grid[pos_y][pos_x].type = 3;
	}
}

// Return true if both start and end node has been assign.
bool const grid::redo() {
	return (start && end);
}
//Return what type the square is (Wall, start, end or regular)
int const grid::type(const int &x, const int& y) {
	return _grid[y][x].type;
}
//Returns true if square is in OL
bool const grid::in_ol(const int &x, const int &y) {
	return _grid[y][x].OL;
}
//return true if square is in CL
bool const grid::in_cl(const int &x, const int &y) {
	return _grid[y][x].CL;
}

//change the color of the road
void const grid::road_found(const pos_2D &pos) {
	_grid[pos.y][pos.x].color(0.4f);
}

//Set boolean for which list the square is in
void grid::list(const int &x, const int &y, const std::string &list) {
	//Change the status for which list the square is in
	if (list == "ol") {
		_grid[y][x].OL = true;
		_grid[y][x].CL = false;
	}else if (list == "cl") {
		_grid[y][x].CL = true;
		_grid[y][x].OL = false;
	}

}
void grid::list(const pos_2D &pos,const std::string &list) {
	if (list == "ol") {
		_grid[pos.y][pos.x].OL = true;
		_grid[pos.y][pos.x].CL = false;
	}
	else if (list == "cl") {
		_grid[pos.y][pos.x].CL = true;
		_grid[pos.y][pos.x].OL = false;
	}

}
//Reset the grid
void grid::reset() {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (_grid[j][i].type == 0) {
				_grid[j][i].color(0.0f);
			}
			_grid[j][i].OL = false;
			_grid[j][i].CL = false;
		}
	}
}

