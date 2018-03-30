#pragma once
#include <cmath>
class Square
{
public:
	//Constructor
	Square();
	// Set a box depending on the x and y coordinates and the length. The int n is for the indices
	void set_box(const float& x, const float &y, const float &length, const int &n);
	// This is the sum of the four hypotenuse from the point to the four edges
	float const distance(const float &x, const float &y);
	// Change the color. Four predefined colors are avaible 
	void  color(const float &f);
	// The vertices and indices
	float vertices[16];
	unsigned int indices[6];
	//Type i.e wall, start, end, nothing
	int type;
	//Is the square in the OL or CL
	bool CL = false;
	bool OL = false;
};

