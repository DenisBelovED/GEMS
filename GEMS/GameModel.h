#pragma once

#include "Constants.h"

class GameModel
{
public:
	GameModel();
	~GameModel();
private:
	unsigned int score;
	int color_matrix[G_WIDTH][G_HEIGHT];

	bool connecting_components_is_exist();
};

