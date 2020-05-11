#pragma once

#include "Constants.h"
#include "ViewEntity.h"
#include <utility>
#include <SDL.h>

class GameController
{
public:
	GameController();
	~GameController();
	std::pair<int, int> search_strike(std::vector<std::vector<ViewEntity*>>* field_view);

	enum size_t { background = 0, char1, char2, char3, char4, cell };
	size_t 
		left_edge = (size_t)BIAS_X,
		size_tup_edge = (size_t)BIAS_Y,
		right_edge = (size_t)(BIAS_X + G_WIDTH * BRIK_WIDTH),
		down_edge = (size_t)(BIAS_Y + G_HEIGHT * BRIK_HEIGHT);
	SDL_Event* windowEvent = nullptr;
};
