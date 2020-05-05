#pragma once

#include <vector>
#include "Node.h"
#include "Constants.h"

void accessible_neighbors(
	const Node* current_node,
	const std::vector<std::vector<Node*>>& nodes,
	std::vector<Node*>* accessible_nodes
);
