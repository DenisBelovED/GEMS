#include "ConnectivityComponents.h"
#include <queue>
#include "utilities.h"

ConnectivityComponents::ConnectivityComponents()
{
}

ConnectivityComponents::ConnectivityComponents(std::vector<std::vector<Node*>>& nodes)
{
	for (auto& line : nodes)
	{
		for (auto& node : line)
		{
			if (!node->visited)
			{
				std::unordered_set<Node*>* component = new std::unordered_set<Node*>();
				std::queue<Node*> queue;
				queue.push(node);

				while (!queue.empty())
				{
					Node* n = queue.front();
					queue.pop();
					n->visited = true;
					component->insert(n);

					auto accessible_nodes = new std::vector<Node*>();
					accessible_neighbors(n, nodes, accessible_nodes);
					for (auto n : *accessible_nodes)
						queue.push(n);
				}

				components.push_back(component);
			}
		}
	}
	for (auto& set : components) {
		for (auto& e : *set)
			printf("[%d %d; %d] ", e->_y, e->_x, e->_color);
		printf("\n");
	}
}

ConnectivityComponents::~ConnectivityComponents()
{
}

size_t ConnectivityComponents::get_count()
{
	return components.size();
}
