#pragma once

#include "Constants.h"
#include "GameModel.h"
#include "GameView.h"

class GameController
{
public:
	GameController();
	~GameController();
	void game_loop(GameModel* model, GameView* view);
private:
	SDL_Event windowEvent;
};
