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
	void to_render(size_t texture_id, const SDL_Rect* dst_rect = NULL);
	SDL_Texture* get_texture(size_t texture_id);
private:
	std::map<size_t, SDL_Texture*>* texture_map = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* render = nullptr;
};
