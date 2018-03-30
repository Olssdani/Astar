#pragma once
#include <cmath>
class pos_2D
{
public:
	//Constructors
	pos_2D();
	pos_2D(const int &x,const int& y);
	pos_2D(const pos_2D &_pos);
	//Sets new values for the x and y
	void set(const int &_x, const int &_y);
	//The manhatan distances between this and pos
	int const manhatan(const pos_2D &_pos);
	//Operator to compare two positions
	bool const operator==(const pos_2D &temp);

	int x;
	int y;
private:

};

