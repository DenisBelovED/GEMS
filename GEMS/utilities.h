#pragma once

#include <vector>
#include "Node.h"
#include "Constants.h"
#include <SDL.h>
#include <memory>
#include "GameModel.h"
#include "GameView.h"
#include "GameController.h"
#include "ViewBrik.h"

void accessible_eqal_neighbors(
	const Node* current_node,
	const std::vector<std::vector<Node*>>& nodes,
	std::vector<Node*>* accessible_nodes
);

void game_loop(GameModel* model, GameView* view, GameController* controller);

std::shared_ptr<SDL_Rect> init_shared_rect(int x, int y, int width, int height);

void compose_gravity_fall(GameModel* &model, GameView* &view, std::vector<Node*>* &exploded_nodes);
