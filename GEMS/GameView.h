#pragma once

#include <SDL.h>
#include <Windows.h>
#include <string>
#include "Constants.h"
#include <filesystem>
#include <map>
#include <queue>

class GameView 
{
public:
	GameView();
	~GameView();
	void draw();
	void add_to_rendering_queue(size_t texture_id, const SDL_Rect* dst_rect = NULL);
	SDL_Texture* get_texture(size_t texture_id);
private:
	std::queue<std::tuple<size_t, const SDL_Rect*>>* render_queue = nullptr;
	std::map<size_t, SDL_Texture*>* texture_map = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* render = nullptr;
};
