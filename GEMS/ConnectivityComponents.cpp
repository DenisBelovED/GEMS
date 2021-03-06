#include "ConnectivityComponents.h"
#include <queue>
#include "utilities.h"

ConnectivityComponents::ConnectivityComponents()
{
}

ConnectivityComponents::ConnectivityComponents(std::vector<std::vector<Node*>>* nodes)
{
	DFS(nodes);

#ifdef _DEBUG
	for (size_t i = 0; i < G_HEIGHT; i++)
	{
		for (size_t j = 0; j < G_WIDTH; j++)
			printf("[%d %d; %d] ", (*nodes)[j][i]->_y, (*nodes)[j][i]->_x, (*nodes)[j][i]->_color);
		printf("\n");
	}
	printf("\n%d\n", components.size());
	for (auto& set : components) {
		for (auto& e : *set)
			printf("[%d %d; %d] ", e->_y, e->_x, e->_color);
		printf("\n");
	}
#endif // _DEBUG
}

ConnectivityComponents::~ConnectivityComponents()
{
	components.clear();
}

size_t ConnectivityComponents::get_count()
{
	return components.size();
}

size_t ConnectivityComponents::get_component_length(Node* n)
{
	for (auto& nodes_set : components)
		if (nodes_set->find(n) != nodes_set->end())
			return nodes_set->size();
}

std::unordered_set<Node*>* ConnectivityComponents::get_component_by_node(Node* n)
{
	for (auto& nodes_set : components)
		if (nodes_set->find(n) != nodes_set->end())
			return nodes_set;
}

void ConnectivityComponents::update_components(std::vector<std::vector<Node*>>* nodes)
{
	for (auto& nodes_set : *nodes)
		for (auto& node : nodes_set)
			node->visited = false;

	for (auto& set : components)
	{
		set->clear();
		delete set;
	}
	components.clear();

	DFS(nodes);
	
#ifdef _DEBUG
	for (size_t i = 0; i < G_HEIGHT; i++)
	{
		for (size_t j = 0; j < G_WIDTH; j++)
			printf("[%d %d; %d] ", (*nodes)[j][i]->_y, (*nodes)[j][i]->_x, (*nodes)[j][i]->_color);
		printf("\n");
	}
	printf("\n%d\n", components.size());
	for (auto& set : components) {
		for (auto& e : *set)
			printf("[%d %d; %d] ", e->_y, e->_x, e->_color);
		printf("\n");
	}
#endif // _DEBUG
}

bool ConnectivityComponents::from_common_component(Node* n1, Node* n2)
{
	auto comp = get_component_by_node(n1);
	return (comp->find(n2) != comp->end());
}

const std::vector<std::unordered_set<Node*>*>* ConnectivityComponents::get_nodes()
{
	return &components;
}

void ConnectivityComponents::DFS(std::vector<std::vector<Node*>>* nodes)
{
	for (auto& line : *nodes)
		for (auto& node : line)
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
					accessible_eqal_neighbors(n, *nodes, accessible_nodes);
					for (auto n : *accessible_nodes)
						queue.push(n);
				}

				components.push_back(component);
			}
}
