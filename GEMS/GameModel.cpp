#include "GameModel.h"
#include <random>
#include <chrono>

GameModel::GameModel()
{
	// Обнуление счёта
	score = 0;

	// Создание генератора случайных чисел
	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<size_t> color_distribution(1, COLOR_COUNT);

	// Инициализация игрового поля размера G_WIDTH x G_HEIGHT, и построение компонент связности
	for (size_t i = 0; i < G_HEIGHT; i++)
	{
		color_matrix.push_back(std::vector<Node*>());
		for (size_t j = 0; j < G_WIDTH; j++)
			color_matrix[i].push_back(new Node(j, i, color_distribution(rng)));
	}

	for (size_t i = 0; i < G_HEIGHT; i++)
	{
		for (size_t j = 0; j < G_WIDTH; j++)
			printf("[%d %d; %d] ", color_matrix[j][i]->_y, color_matrix[j][i]->_x, color_matrix[j][i]->_color);
		printf("\n");
	}
	printf("\n");

	components = ConnectivityComponents(color_matrix);
	printf("\n");
	printf("%d", components.get_count());

	//if (components.get_count() == 1)
		//TODO
}

GameModel::~GameModel()
{
}

bool GameModel::connecting_components_is_exist()
{
	return false;
}
