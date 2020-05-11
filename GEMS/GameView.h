#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <Windows.h>
#include <string>
#include <filesystem>
#include <map>
#include <queue>
#include "Constants.h"
#include "ViewEntity.h"

class GameView 
{
public:
	GameView();
	~GameView();
	void rendering_all();
	void add_to_rendering_queue(ViewEntity* ve);
	void rendering_entity(ViewEntity* ve);
	SDL_Texture* get_texture(size_t texture_id);

	ViewEntity* background_view = nullptr;
	ViewEntity* restart_view = nullptr;
	ViewEntity* score_view = nullptr;
	std::vector<std::vector<ViewEntity*>>* field_view = nullptr;
private:
	std::map<std::string, size_t> texture_enum = {
		{"background", 0},
		{"char1", 1},
		{"char2", 2},
		{"char3", 3},
		{"char4", 4},
		{"cell", 5}
	};
	std::queue<ViewEntity*>* render_queue = nullptr;
	std::map<size_t, SDL_Texture*>* texture_map = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* render = nullptr;
};
