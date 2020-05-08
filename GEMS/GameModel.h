#pragma once

#include <vector>
#include "Constants.h"
#include "ConnectivityComponents.h"
#include "Node.h"
#include "utilities.h"

class GameModel
{
public:
	GameModel();
	~GameModel();
	const std::vector<std::vector<Node*>>* get_field();
private:
	size_t score;
	std::vector<std::vector<Node*>> color_matrix;
	ConnectivityComponents* components;
	bool moves_exist();
	bool swapable(Node* node1, Node* node2);
	bool is_explosive_touch(const Node* node);
};
