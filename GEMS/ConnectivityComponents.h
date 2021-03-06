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
	std::unordered_set<Node*>* get_component_by_node(Node* n);
	void update_components(std::vector<std::vector<Node*>>* nodes);
	bool from_common_component(Node* n1, Node* n2);
	const std::vector<std::unordered_set<Node*>*>* get_nodes();
private:
	void DFS(std::vector<std::vector<Node*>>* nodes);

	std::vector<std::unordered_set<Node*>*> components;
};

