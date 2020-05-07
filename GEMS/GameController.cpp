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
	int i = 0;
	while (LOOP_FLAG)
	{
		SDL_Rect background_RECT;
		background_RECT.x = 10;
		background_RECT.y = 10;
		background_RECT.w = 64;
		background_RECT.h = 64;
		i = (i % 4) + 1;
		view->to_render(i, &background_RECT);
		if (SDL_PollEvent(&windowEvent))
			switch (windowEvent.type)
			{
			case SDL_QUIT:				
				LOOP_FLAG = false;
				break;
			}
	}
}
