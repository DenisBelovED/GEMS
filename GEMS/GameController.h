#pragma once

#include "Constants.h"
#include "ViewEntity.h"
#include "FieldView.h"
#include <utility>
#include <SDL.h>

class GameController
{
public:
	GameController();
	~GameController();
	std::pair<int, int> search_strike(FieldView* field_view);

	enum size_t { 
		background = 0, char1, char2, char3, char4, cell, glass, glass_lime, 
		sp1, sp2, sp3, sp4, sp5, sp6, sp7, sp8,
		sm1, sm2, sm3, sm4, sm5, sm6, sm7, sm8
	};
	size_t 
		left_edge = (size_t)BIAS_X,
		size_tup_edge = (size_t)BIAS_Y,
		right_edge = (size_t)(BIAS_X + G_WIDTH * BRIK_WIDTH),
		down_edge = (size_t)(BIAS_Y + G_HEIGHT * BRIK_HEIGHT);
	SDL_Event* windowEvent = nullptr;
};
