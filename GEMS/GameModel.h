#pragma once

#include <vector>
#include "Constants.h"
#include "ConnectivityComponents.h"
#include "Node.h"

class GameModel
{
public:
	GameModel();
	~GameModel();
private:
	size_t score;
	std::vector<std::vector<Node*>> color_matrix;
	ConnectivityComponents components;
	bool connecting_components_is_exist();
	//bool swap(Node* n1, Node* n2);
};
