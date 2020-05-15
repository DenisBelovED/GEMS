#include "utilities.h"

int main(int, char**)
{
	if ((bool)SDL_Init(SDL_INIT_EVERYTHING))
		return -1;

	GameModel* model = new GameModel();
	GameView* view = new GameView();
	GameController* controller = new GameController();
	
	game_loop(model, view, controller);

	delete model;
	delete view;
	delete controller;
	SDL_Quit();
	return 0;
}