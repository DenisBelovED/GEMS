#pragma once

#include <SDL.h>

class GameView 
{
public:
	GameView();
	~GameView();
	void to_render(SDL_Surface* img);
private:
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Texture* texture;
};

