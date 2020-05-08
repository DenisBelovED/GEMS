#include "GameModel.h"

GameModel::GameModel()
{
	// Обнуление счёта
	score = 0;

	// Создание генератора случайных чисел
	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<size_t> color_distribution(1, COLOR_COUNT);
	
	// Инициализация игрового поля размера G_WIDTH x G_HEIGHT, и построение компонент связности
	// Цикл рвётся, если компонент связности > 1 и существуют ходы
	while (true)
	{
		for (size_t i = 0; i < G_HEIGHT; i++)
		{
			color_matrix.push_back(std::vector<Node*>());
			for (size_t j = 0; j < G_WIDTH; j++)
				color_matrix[i].push_back(new Node(j, i, color_distribution(rng)));
		}

		components = new ConnectivityComponents(color_matrix);

		if (moves_exist())
			break;
		else
		{
			color_matrix.clear();
			delete components;
		}
	}
}

GameModel::~GameModel()
{
}

const std::vector<std::vector<Node*>>* GameModel::get_field()
{
	return &color_matrix;
}

bool GameModel::moves_exist()
{
	if (components->get_count() <= 1)
		return false;
	for (auto component : *components->get_nodes())
		for (Node* n : *component)
		{
			if ((0 < n->_x) &&
				(color_matrix[n->_y][n->_x - 1]->_color != n->_color) &&
				(swapable(n, color_matrix[n->_y][n->_x - 1])))
				return true;
			if ((n->_x < (G_WIDTH - 1)) &&
				(color_matrix[n->_y][n->_x + 1]->_color != n->_color) &&
				(swapable(n, color_matrix[n->_y][n->_x + 1])))
				return true;
			if ((0 < n->_y) &&
				(color_matrix[n->_y - 1][n->_x]->_color != n->_color) &&
				(swapable(n, color_matrix[n->_y - 1][n->_x])))
				return true;
			if ((n->_y < (G_HEIGHT - 1)) &&
				(color_matrix[n->_y + 1][n->_x]->_color != n->_color) &&
				(swapable(n, color_matrix[n->_y + 1][n->_x])))
				return true;
		}
	return false;
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
	if ((0 < node->_x) &&
		(color_matrix[node->_y][node->_x - 1]->_color == node->_color) &&
		(components->get_component_length(color_matrix[node->_y][node->_x - 1]) > 1))
		return true;
	if ((node->_x < (G_WIDTH - 1)) &&
		(color_matrix[node->_y][node->_x + 1]->_color == node->_color) &&
		(components->get_component_length(color_matrix[node->_y][node->_x + 1]) > 1))
		return true;
	if ((0 < node->_y) &&
		(color_matrix[node->_y - 1][node->_x]->_color == node->_color) &&
		(components->get_component_length(color_matrix[node->_y - 1][node->_x]) > 1))
		return true;
	if ((node->_y < (G_HEIGHT - 1)) &&
		(color_matrix[node->_y + 1][node->_x]->_color == node->_color) &&
		(components->get_component_length(color_matrix[node->_y + 1][node->_x]) > 1))
		return true;
	return false;
}
