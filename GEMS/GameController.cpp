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
		view->add_to_rendering_queue(1);
		SDL_Rect rect;
		rect.x = 10;
		rect.y = 10;
		rect.w = BRIK_WIDTH;
		rect.h = BRIK_HEIGHT;
		view->add_to_rendering_queue(2, &rect);
		if (SDL_PollEvent(&windowEvent))
			switch (windowEvent.type)
			{
			case SDL_QUIT:				
				LOOP_FLAG = false;
				break;
			}
		view->draw();
	}
}
