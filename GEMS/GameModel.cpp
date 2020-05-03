#include "GameModel.h"
#include <random>

GameModel::GameModel()
{
	score = 0;

	std::default_random_engine random_generator;
	std::uniform_int_distribution<int> color_distribution(1, COLOR_COUNT);
	for (int i = 0; i < G_WIDTH; i++)
		for (int j = 0; j < G_HEIGHT; j++)
			color_matrix[i][j] = color_distribution(random_generator);

	while (connecting_components_is_exist())
	{

	}
}

GameModel::~GameModel()
{
}

bool GameModel::connecting_components_is_exist()
{
	return false;
}
