#pragma once

#include <SDL.h>
#include <Windows.h>
#include <string>
#include "Constants.h"
#include <filesystem>
#include <map>

class GameView 
{
public:
	GameView();
	~GameView();
	void to_render(SDL_Surface img);

	std::map<size_t, SDL_Surface*>* texture_map;
private:
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Texture* texture;
};
