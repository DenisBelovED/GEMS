#include "GameModel.h"
#include "GameController.h"
#include "GameView.h"

int main(int, char**)
{
	if ((bool)SDL_Init(SDL_INIT_EVERYTHING))
		throw "ERROR: SDL unavailable";

	// TODO shared_ptr
	GameModel* model = new GameModel();
	GameView* view = new GameView();
	GameController* controller = new GameController();
	
	controller->game_loop(model, view);

	delete model;
	delete view;
	delete controller;
	SDL_Quit();
	return 0;
}