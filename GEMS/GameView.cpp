#include "GameView.h"
#include "Constants.h"

GameView::GameView()
{
	window = SDL_CreateWindow(
		"GEMS",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_ALLOW_HIGHDPI
	);
	if (window == nullptr)
		throw SDL_GetError();

	render = SDL_CreateRenderer(
		window,
		-1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (render == nullptr)
		throw SDL_GetError();
}

GameView::~GameView()
{
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(render);
}

void GameView::to_render(SDL_Surface* img)
{
	texture = SDL_CreateTextureFromSurface(render, img);
	SDL_FreeSurface(img);
	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, NULL, NULL);
	SDL_RenderPresent(render);
	//SDL_Delay(5000);
}
