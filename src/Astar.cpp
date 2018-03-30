#include "Astar.h"

//constructors
Astar::Astar() {
	start = pos_2D(0, 0);
	end = pos_2D(0, 0);
}

Astar::Astar(const pos_2D &_start, const pos_2D& _end){
	start = _start;
	end = _end;
}
//Updates the end and start node.
void Astar::update(const pos_2D &_start, const pos_2D &_end) {
	start = _start;
	end = _end;
}
//Runs the A* calculations
void Astar::run(grid &temp) {
	// The openlist and closelist
	std::vector <Astar_node> ol;
	std::vector <Astar_node> cl;
	int min;
	// Temp position
	pos_2D temp_pos;
	//Nodes for the loop
	Astar_node temp_node;
	Astar_node node;
	
	//A* node that are used in the loop 
	node = Astar_node(start, end);

	//Push Start node to OL
	ol.push_back(node);
	temp.list(node.pos, "ol");
	
	// Iterator that is used in the OL and CL
	std::vector <Astar_node>::iterator temp_iterator;
	
	// A* loop
	while (!(node.pos == end)) {	
		//Checks if Ol is empty and end loop if true
		if (ol.empty()) {
			std::cout << "Openlist is empty" << std::endl;
			return;
		}

		// Search for the node in OL with lowest F
		min = 10000;
		for (std::vector <Astar_node>::iterator it = ol.begin(); it != ol.end(); ++it) {
			if (min > it->F) {
				min = it->F;
				temp_iterator = it;
			}
		}
		// Assign the best node to the current and send it to the closedlist
		node = *temp_iterator;
		cl.push_back(node);
		temp.list(node.pos, "cl");
		ol.erase(temp_iterator);

		// Loop through the neighbours
		for (int i = node.pos.x - 1; i <= node.pos.x + 1; ++i) {
			for (int j = node.pos.y - 1; j <= node.pos.y + 1; ++j) {
				
				// Checks so the neighbour is on the grid
				if (j >= 0 && i >= 0 && i < temp.get_size() && j < temp.get_size()) {
					
					//If the node is in OL or CL it doesn't search that one			
					if (!(temp.in_cl(i, j) || temp.in_ol(i, j))) {
						
						//End loop when end is found
						if (temp.type(i, j) == 2) {
							goto endloop;
						}
						// Do nothing if wall is found
						else if (temp.type(i, j) == 3) {
							//Do nothing
						}
						//Adds the new node to the ol
						else {
							// Adds the node with the cost node.g + Euclidean distance
							temp_node = Astar_node(i, j, node.pos, end, euklidiska(node.pos, i, j) + node.G);
							ol.push_back(temp_node);
							temp.list(i, j, "ol");
						}
					}
					// If the node is in OL we check if we have a faster route
					else if (temp.in_ol(i, j)) {
						
						temp_pos.set(i, j);
						//Search through the Ol for the node
						for (std::vector <Astar_node>::iterator it = ol.begin(); it != ol.end(); ++it) {
							if (temp_pos == (*it).pos) {
								temp_iterator = it;
								break;
							}
						}
						// If the new G cost i lower than the old
						if (node.G + euklidiska(node.pos, i, j) <(*temp_iterator).G) {
							//Update the node cost and parent
							(*temp_iterator).update(node.pos, node.G + euklidiska(node.pos, i, j));
						}
					}
				}	
			}
		}
	}
	//If end is found we update the colors for the route
	endloop:	
	while (!(node.pos == start)) {
		temp.road_found(node.pos);
		for (std::vector <Astar_node>::iterator it = cl.begin(); it != cl.end(); ++it) {
			if (node.parent == it->pos) {
				node = *it;
				break;
			}
		}
	}
}

//pythagoras theorem multiplied with 10
int euklidiska(pos_2D pos1, int x, int y) {
	return sqrt(pow((pos1.x - x),2) + pow((pos1.y - y),2))*10;
}