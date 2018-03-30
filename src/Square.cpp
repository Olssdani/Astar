#include "Square.h"
#include <iostream>


Square::Square()
{
	type = 0;
	CL = false;
	OL = false;
}

void Square::set_box(const float& x, const float &y, const float &length,const int &n) {
	//Sets out the vertices depending on x,y position
	vertices[0] = x;
	vertices[1] = y;
	vertices[2] = 0.0f;
	vertices[3] = 0.0f;

	vertices[4] = x;
	vertices[5] = y-length;
	vertices[6] = 0.0f;
	vertices[7] = 0.0f;

	vertices[8] = x+length;
	vertices[9] = y-length;
	vertices[10] = 0.0f;
	vertices[11] = 0.0f;

	vertices[12] = x+length;
	vertices[13] = y;
	vertices[14] = 0.0f;
	vertices[15] = 0.0f;

	indices[0] = n;
	indices[1] = n+1;
	indices[2] = n+2;
	indices[3] = n;
	indices[4] = n+2;
	indices[5] = n+3;


}

float const Square::distance(const float &x, const float &y) {
	float point1 = sqrt(pow(vertices[0]-x,2) + pow(vertices[1]-y,2));
	float point2 = sqrt(pow(vertices[4] - x, 2) + pow(vertices[5] - y, 2));
	float point3 = sqrt(pow(vertices[8] - x, 2) + pow(vertices[9] - y, 2));
	float point4 = sqrt(pow(vertices[12] - x, 2) + pow(vertices[13] - y, 2));

	return point1 + point2 + point3 + point4;
}
// Just change the vertices that goes into the fragment shader
void Square::color(const float &f) {
	vertices[3] = f;
	vertices[7] = f;
	vertices[11] = f;
	vertices[15] = f;
}