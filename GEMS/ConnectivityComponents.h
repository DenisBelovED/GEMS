#pragma once

#include "Node.h"
#include <vector>
#include <unordered_set>

class ConnectivityComponents
{
public:
	ConnectivityComponents();
	ConnectivityComponents(std::vector<std::vector<Node*>>* nodes);
	~ConnectivityComponents();
	size_t get_count();
	size_t get_component_length(Node* n);
	const std::vector<std::unordered_set<Node*>*>* get_nodes();
private:
	std::vector<std::unordered_set<Node*>*> components;
};

