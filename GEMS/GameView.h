#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <string>
#include <filesystem>
#include <map>
#include <queue>
#include "Constants.h"
#include "ViewEntity.h"
#include "Node.h"

class GameView 
{
public:
	GameView();
	~GameView();
	void clear_render();
	void rendering_all();
	void add_to_rendering_queue(ViewEntity* ve);
	void rendering_entity(ViewEntity* ve);
	SDL_Texture* get_texture(size_t texture_id);
	void rendering_score(int score);
	void synchronize(
		std::vector<std::vector<Node*>>* color_matrix, 
		std::vector<std::vector<ViewEntity*>>* field_view,
		int x1, int y1, int x2, int y2,
		size_t score, 
		std::vector<std::pair<int, int>>* selected_briks,
		std::vector<Node*>* explosive_nodes = nullptr
	);

	ViewEntity* background_view = nullptr;
	ViewEntity* explosive_animation = nullptr;
	ViewEntity* score_view = nullptr;
	std::vector<std::vector<ViewEntity*>>* field_view = nullptr;
private:
	std::map<std::string, size_t> texture_enum = {
		{"background", 0},
		{"char1", 1},
		{"char2", 2},
		{"char3", 3},
		{"char4", 4},
		{"cell", 5},
		{"glass", 6},
		{"glass_lime", 7},
		{"spiral1", 8},
		{"spiral2", 9},
		{"spiral3", 10},
		{"spiral4", 11},
		{"spiral5", 12},
		{"spiral6", 13},
		{"spiral7", 14},
		{"spiral8", 15}
	};
	std::queue<ViewEntity*>* render_queue = nullptr;
	std::map<size_t, SDL_Texture*>* texture_map = nullptr;
	TTF_Font* font = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* render = nullptr;
};
