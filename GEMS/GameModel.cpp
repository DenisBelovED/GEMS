#include "GameModel.h"

GameModel::GameModel()
{
	// Обнуление счёта
	score = 0;
	color_matrix = new std::vector<std::vector<Node*>>();

	// Создание генератора случайных чисел
	rng = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());
	color_clamp = std::uniform_int_distribution<size_t>(1, COLOR_COUNT);
	
	// Инициализация игрового поля размера G_WIDTH x G_HEIGHT, и построение компонент связности
	// Цикл рвётся, если компонент связности > 1 и существуют ходы
	while (true)
	{
		for (size_t i = 0; i < G_HEIGHT; i++)
		{
			color_matrix->push_back(std::vector<Node*>());
			for (size_t j = 0; j < G_WIDTH; j++)
				(*color_matrix)[i].push_back(new Node(j, i, color_clamp(rng)));
		}

		components = new ConnectivityComponents(color_matrix);

		if (moves_exist())
			break;
		else
		{
			color_matrix->clear();
			delete components;
		}
	}
}

GameModel::~GameModel()
{
	for (auto& e : *color_matrix)
		for (auto& n : e)
			delete n;
	delete components;
}

size_t GameModel::get_score()
{
	return score;
}

std::vector<Node*>* GameModel::swap(size_t x1, size_t y1, size_t x2, size_t y2)
{
	auto node1 = (*color_matrix)[x1][y1];
	auto node2 = (*color_matrix)[x2][y2];
	auto explosive = new std::vector<Node*>();

	if ((components->from_common_component(node1, node2)) || (!swapable(node1, node2)))
		return explosive;

	size_t t_color = node2->_color;
	node2->_color = node1->_color;
	node1->_color = t_color;

	components->update_components(color_matrix);

	size_t d1 = explosion(node1);
	size_t d2 = explosion(node2);
	if (d1 > 0)
		for (auto& n : *components->get_component_by_node(node1))
			explosive->push_back(n);
	if (d2 > 0)
		for (auto& n : *components->get_component_by_node(node2))
			explosive->push_back(n);
	score += d1 + d2;
	return explosive;
}

std::vector<std::vector<std::vector<size_t>>>* GameModel::apply_gravity(
	std::vector<Node*>* exploded_nodes
)
{
	std::unordered_set<size_t> change_columns;
	auto snapshots = new std::vector<std::vector<std::vector<size_t>>>();

	for (auto& n : *exploded_nodes)
		change_columns.insert(n->_y);

	auto out_condition = [](std::vector<std::vector<Node*>>* color_matrix) -> bool {
		for (auto& l : *color_matrix)
			for (auto& n : l)
				if (n->_color == EXPLOSION)
					return true;
		return false;
	};

	size_t snapshot_index = 0;
	while (out_condition(color_matrix))
	{
		snapshots->push_back(std::vector<std::vector<size_t>>());
		for (auto w : change_columns)
		{
			for (size_t h = G_HEIGHT - 1; h > 0; h--)
				if (((*color_matrix)[w][h]->_color == EXPLOSION) &&
					((*color_matrix)[w][h - 1]->_color != EXPLOSION))
				{
					(*color_matrix)[w][h]->_color = (*color_matrix)[w][h - 1]->_color;
					(*color_matrix)[w][h - 1]->_color = EXPLOSION;
				}
			if ((*color_matrix)[w][0]->_color == EXPLOSION)
				(*color_matrix)[w][0]->_color = color_clamp(rng);
		}

		for (size_t i = 0; i < G_HEIGHT; i++)
		{
			(*snapshots)[snapshot_index].push_back(std::vector<size_t>());
			for (size_t j = 0; j < G_WIDTH; j++)
				(*snapshots)[snapshot_index][i].push_back((*color_matrix)[i][j]->_color);
		}
		snapshot_index++;
	}

	if (snapshots->size() > 0)
		components->update_components(color_matrix);
	return snapshots;
}

bool GameModel::explosion_at_impact(std::vector<Node*>* &exploded_nodes)
{
	auto explosive = new std::vector<Node*>();
	std::map<size_t, Node*> impact_nodes;

	for (auto& n : *exploded_nodes)
	{
		if (impact_nodes.find(n->_y) != impact_nodes.end())
		{
			if (impact_nodes[n->_y]->_x < n->_x)
				impact_nodes[n->_y] = n;
		}
		else
			impact_nodes[n->_y] = n;
	}

	for (auto item : impact_nodes)
	{
		if (item.second->_color != EXPLOSION)
		{
			size_t d = explosion(item.second);
			if (d > 0)
				for (auto& n : *components->get_component_by_node(item.second))
					explosive->push_back(n);
			score += d;
		}
	}
	
	exploded_nodes->clear();
	delete exploded_nodes;
	exploded_nodes = explosive;

	return (bool)(explosive->size());
}

bool GameModel::moves_exist()
{
	if (components->get_count() <= 1)
		return false;
	for (auto component : *components->get_nodes())
		for (Node* n : *component)
		{
			if ((0 < n->_x) &&
				((*color_matrix)[n->_y][n->_x - 1]->_color != n->_color) &&
				(swapable(n, (*color_matrix)[n->_y][n->_x - 1])))
				return true;
			if ((n->_x < (G_WIDTH - 1)) &&
				((*color_matrix)[n->_y][n->_x + 1]->_color != n->_color) &&
				(swapable(n, (*color_matrix)[n->_y][n->_x + 1])))
				return true;
			if ((0 < n->_y) &&
				((*color_matrix)[n->_y - 1][n->_x]->_color != n->_color) &&
				(swapable(n, (*color_matrix)[n->_y - 1][n->_x])))
				return true;
			if ((n->_y < (G_HEIGHT - 1)) &&
				((*color_matrix)[n->_y + 1][n->_x]->_color != n->_color) &&
				(swapable(n, (*color_matrix)[n->_y + 1][n->_x])))
				return true;
		}
	return false;
}

bool GameModel::random_event(size_t percent_bias)
{
	return (get_random(100) % 100) <= percent_bias;
}

size_t GameModel::get_random(size_t max)
{
	std::uniform_int_distribution<size_t> range(0, max);
	return range(rng);
}

std::vector<Node*>* GameModel::repaint()
{
	size_t x = 1 + (size_t)(get_random(100) % (G_WIDTH - 2));
	size_t y = 1 + (size_t)(get_random(100) % (G_HEIGHT - 2));
	size_t x1, y1, x2, y2;
	switch (get_random(100) % 4)
	{
	case 0:
		x1 = x - 1;
		x2 = x - 1;
		y1 = y + 1;
		y2 = y - 1;
		break;
	case 1:
		x1 = x - 1;
		x2 = x + 1;
		y1 = y - 1;
		y2 = y - 1;
		break;
	case 2:
		x1 = x + 1;
		x2 = x + 1;
		y1 = y + 1;
		y2 = y - 1;
		break;
	case 3:
		x1 = x - 1;
		x2 = x + 1;
		y1 = y + 1;
		y2 = y + 1;
		break;
	}
	(*color_matrix)[x1][y1]->_color = (*color_matrix)[x][y]->_color;
	(*color_matrix)[x2][y2]->_color = (*color_matrix)[x][y]->_color;
	(*color_matrix)[x][y]->_color = color_clamp(rng);
	components->update_components(color_matrix);
}

std::vector<Node*>* GameModel::bomb()
{
	auto explosive = new std::vector<Node*>();
	std::unordered_set<size_t> u_set_x, u_set_y;
	for (int i = 0; i < 5; i++)
	{
		size_t x, y;
		do
		{
			x = get_random(100) % G_WIDTH;
			y = get_random(100) % G_HEIGHT;
		} while ((u_set_x.find(x) != u_set_x.end()) && (u_set_y.find(y) != u_set_y.end()));
		u_set_x.insert(x);
		u_set_y.insert(y);
		(*color_matrix)[x][y]->_color = EXPLOSION;
		explosive->push_back((*color_matrix)[x][y]);
	}
	return explosive;
}

bool GameModel::swapable(Node* node1, Node* node2)
{
	size_t t_color = node2->_color;
	node2->_color = node1->_color;
	node1->_color = t_color;
	
	bool res = is_explosive_touch(node1) || is_explosive_touch(node2);

	node1->_color = node2->_color;
	node2->_color = t_color;

	return res;
}

bool GameModel::is_explosive_touch(const Node* node)
{
	size_t count = 1;
	if ((0 < node->_x) &&
		((*color_matrix)[node->_y][node->_x - 1]->_color == node->_color))
		count += components->get_component_length((*color_matrix)[node->_y][node->_x - 1]);
	if ((node->_x < (G_WIDTH - 1)) &&
		((*color_matrix)[node->_y][node->_x + 1]->_color == node->_color))
		count += components->get_component_length((*color_matrix)[node->_y][node->_x + 1]);
	if ((0 < node->_y) &&
		((*color_matrix)[node->_y - 1][node->_x]->_color == node->_color))
		count += components->get_component_length((*color_matrix)[node->_y - 1][node->_x]);
	if ((node->_y < (G_HEIGHT - 1)) &&
		((*color_matrix)[node->_y + 1][node->_x]->_color == node->_color))
		count += components->get_component_length((*color_matrix)[node->_y + 1][node->_x]);
	return (count > 2);
}

size_t GameModel::explosion(Node* node)
{
	size_t sc = components->get_component_length(node);
	if (sc > 2)
	{
		for(auto& n : *components->get_component_by_node(node))
			n->_color = EXPLOSION;
		return sc;
	}
	return 0;
}
