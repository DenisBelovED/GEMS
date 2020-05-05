#include "GameController.h"

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::game_loop(GameModel* model, GameView* view)
{
	SDL_Surface* bmp = SDL_LoadBMP("C:\\Users\\Denis\\Downloads\\test.bmp");
	if (bmp == nullptr)
		throw SDL_GetError();
	view->to_render(bmp);

	bool LOOP_FLAG = true;
	while (LOOP_FLAG)
	{
		if (SDL_PollEvent(&windowEvent))
			switch (windowEvent.type)
			{
			case SDL_QUIT:				
				LOOP_FLAG = false;
				break;
			}
	}
}
