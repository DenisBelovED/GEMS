#pragma once

#include "Constants.h"
#include <SDL.h>

class GameController
{
public:
	GameController();
	~GameController();

	enum size_t { background = 0, char1, char2, char3, char4, cell };
	SDL_Event* windowEvent = nullptr;
};
