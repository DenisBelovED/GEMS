#pragma once

#include <vector>
#include "Node.h"
#include "Constants.h"
#include <SDL.h>
#include <memory>
#include "GameModel.h"
#include "GameView.h"
#include "GameController.h"

void accessible_neighbors(
	const Node* current_node,
	const std::vector<std::vector<Node*>>& nodes,
	std::vector<Node*>* accessible_nodes
);

std::shared_ptr<SDL_Rect> init_shared_rect(int x, int y, int width, int height);

void game_loop(GameModel* model, GameView* view, GameController* controller);
