#pragma once

#include <vector>
#include <random>
#include <chrono>
#include <map>
#include "Constants.h"
#include "ConnectivityComponents.h"
#include "Node.h"

class GameModel
{
public:
	GameModel();
	~GameModel();
	size_t get_score();
	std::vector<Node*>* swap(size_t x1, size_t y1, size_t x2, size_t y2);
	std::vector<std::vector<std::vector<size_t>>>* apply_gravity(std::vector<Node*>* exploded_nodes);
	bool explosion_at_impact(std::vector<Node*>* &exploded_nodes);
	bool moves_exist();
	bool random_event(size_t percent_bias = 0);
	size_t get_random(size_t max);
	std::vector<Node*>* repaint();
	std::vector<Node*>* bomb();

	std::vector<std::vector<Node*>>* color_matrix = nullptr;
private:
	std::mt19937 rng;
	std::uniform_int_distribution<size_t> color_clamp;
	size_t score;
	ConnectivityComponents* components = nullptr;

	bool swapable(Node* node1, Node* node2);
	bool is_explosive_touch(const Node* node);
	size_t explosion(Node* node);
};
