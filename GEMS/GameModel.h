#pragma once

#include <vector>
#include <random>
#include <chrono>
#include "Constants.h"
#include "ConnectivityComponents.h"
#include "Node.h"

class GameModel
{
public:
	GameModel();
	~GameModel();
	size_t get_score();

	std::vector<std::vector<Node*>>* color_matrix = nullptr;
private:
	size_t score;
	ConnectivityComponents* components = nullptr;
	bool moves_exist();
	bool swapable(Node* node1, Node* node2);
	bool is_explosive_touch(const Node* node);
};
