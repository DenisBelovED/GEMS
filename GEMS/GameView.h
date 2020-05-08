#pragma once

#include <SDL.h>
#include <SDL_image.h>
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
	void add_to_rendering_queue(size_t texture_id, std::shared_ptr<SDL_Rect> dst_rect);
	SDL_Texture* get_texture(size_t texture_id);
private:
	std::map<std::string, size_t> texture_enum = {
		{"background", 0},
		{"char1", 1},
		{"char2", 2},
		{"char3", 3},
		{"char4", 4},
		{"cell", 5}
	};
	std::queue<std::tuple<size_t, std::shared_ptr<SDL_Rect>>>* render_queue = nullptr;
	std::map<size_t, SDL_Texture*>* texture_map = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* render = nullptr;
};
