#pragma once

#include "Node.h"
#include <vector>
#include <unordered_set>

class ConnectivityComponents
{
public:
	ConnectivityComponents();
	ConnectivityComponents(std::vector<std::vector<Node*>>& nodes);
	~ConnectivityComponents();
	size_t get_count();
private:
	std::vector<std::unordered_set<Node*>*> components;
};

