#pragma once
#include "pos_2D.h"
#include <iostream>
#include <algorithm> 
class Astar_node
{
public:
	//Constructors
	Astar_node();
	Astar_node(const pos_2D &_pos,const  pos_2D &_end);
	Astar_node(const int &x, const int &y, const pos_2D &_parent, const pos_2D &_end, const int &_G);
	Astar_node(const pos_2D &_pos,const pos_2D &_parent, const pos_2D &_end, const int&_G);
	Astar_node(const Astar_node &a);
	//Assignment operator
	Astar_node operator=(Astar_node &a);
	// print function
	void print();
	//Update the paraent and G cost
	void update(pos_2D _parent, int _G);

	//Variables
	pos_2D  pos;
	pos_2D parent;
	pos_2D  end;
	int F;
	int G;
	int H;
};

