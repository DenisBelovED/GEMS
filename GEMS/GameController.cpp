#include "GameController.h"

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::game_loop(GameModel* model, GameView* view)
{
	bool LOOP_FLAG = true;
	while (LOOP_FLAG)
	{
		view->to_render(*(*view->texture_map)[1]);
		if (SDL_PollEvent(&windowEvent))
			switch (windowEvent.type)
			{
			case SDL_QUIT:				
				LOOP_FLAG = false;
				break;
			}
	}
}
