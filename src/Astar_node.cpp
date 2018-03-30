#include "Astar_node.h"

Astar_node::Astar_node() {
	pos.set(0, 0);
	parent.set(0,0);
	end.set(0, 0);
	G = 0;
	H = 0;
	F = G + H;

}

Astar_node::Astar_node(const int &x, const int &y, const pos_2D &_parent, const pos_2D &_end, const int &_G) {
	pos.set(x, y);
	parent = _parent;
	end = _end;
	G = _G;
	H = pos.manhatan(end);
	F = G + H;
}

Astar_node::Astar_node(const Astar_node &a) {
	pos.set(a.pos.x, a.pos.y);
	parent =a.parent;
	end = a.end;
	G = a.G;
	H = pos.manhatan(end);
	F = G + H;
}

Astar_node::Astar_node(const pos_2D &_pos, const pos_2D &_parent, const pos_2D &_end, const int&_G)
{
	pos = _pos;
	parent = _parent;
	end = _end;
	G = _G;
	H = pos.manhatan(end);
	F = G + H;
}

Astar_node::Astar_node(const pos_2D &_pos, const  pos_2D &_end)
{
	pos = _pos;
	end = _end;
	G = 0;
	H = pos.manhatan(end);
	F = G + H;
}

Astar_node Astar_node::operator=( Astar_node &a) {
	Astar_node temp(a);
	
	std::swap(a.pos, pos);
	std::swap(a.end, end);
	std::swap(a.F, F);
	std::swap(a.G, G);
	std::swap(a.H, H);
	std::swap(a.parent, parent);
	return *this;
}
//Update and all the variables
void Astar_node::update(pos_2D _parent, int _G) {
	parent = _parent;
	G = _G;
	F = G + H;
}

void Astar_node::print() {
	std::cout << "Pos: (" << pos.x << "," << pos.y << ") " << std::endl;
	std::cout << "End: (" << end.x << "," << end.y << ") " << std::endl;
	std::cout << "G: " << G << std::endl;
	std::cout << "H: " << H << std::endl;
	std::cout << "F: " << F << std::endl << std::endl;


}