#include "utilities.h"

 void accessible_neighbors(
	const Node* current_node, 
	const std::vector<std::vector<Node*>>& nodes,
	 std::vector<Node*>* accessible_nodes
)
{
	if ((0 < current_node->_x) &&
		(!nodes[current_node->_y][current_node->_x - 1]->visited) &&
		(nodes[current_node->_y][current_node->_x - 1]->_color == current_node->_color))
		accessible_nodes->push_back(nodes[current_node->_y][current_node->_x - 1]);
	if ((current_node->_x < (G_WIDTH - 1)) &&
		(!nodes[current_node->_y][current_node->_x + 1]->visited) &&
		(nodes[current_node->_y][current_node->_x + 1]->_color == current_node->_color))
		accessible_nodes->push_back(nodes[current_node->_y][current_node->_x + 1]);
	if ((0 < current_node->_y) &&
		(!nodes[current_node->_y - 1][current_node->_x]->visited) &&
		(nodes[current_node->_y - 1][current_node->_x]->_color == current_node->_color))
		accessible_nodes->push_back(nodes[current_node->_y - 1][current_node->_x]);
	if ((current_node->_y < (G_HEIGHT - 1)) &&
		(!nodes[current_node->_y + 1][current_node->_x]->visited) &&
		(nodes[current_node->_y + 1][current_node->_x]->_color == current_node->_color))
		accessible_nodes->push_back(nodes[current_node->_y + 1][current_node->_x]);
}