#include "utilities.h"

void accessible_neighbors(
	const Node* current_node,
	const std::vector<std::vector<Node*>>& nodes,
	std::vector<Node*>* accessible_nodes
)
{
	if ((0 < current_node->_x) &&
		(!nodes[current_node->_y][current_node->_x - 1]->visited) &&
		(nodes[current_node->_y][current_node->_x - 1]->_color == current_node->_color))
		accessible_nodes->push_back(nodes[current_node->_y][current_node->_x - 1]);
	if ((current_node->_x < (G_WIDTH - 1)) &&
		(!nodes[current_node->_y][current_node->_x + 1]->visited) &&
		(nodes[current_node->_y][current_node->_x + 1]->_color == current_node->_color))
		accessible_nodes->push_back(nodes[current_node->_y][current_node->_x + 1]);
	if ((0 < current_node->_y) &&
		(!nodes[current_node->_y - 1][current_node->_x]->visited) &&
		(nodes[current_node->_y - 1][current_node->_x]->_color == current_node->_color))
		accessible_nodes->push_back(nodes[current_node->_y - 1][current_node->_x]);
	if ((current_node->_y < (G_HEIGHT - 1)) &&
		(!nodes[current_node->_y + 1][current_node->_x]->visited) &&
		(nodes[current_node->_y + 1][current_node->_x]->_color == current_node->_color))
		accessible_nodes->push_back(nodes[current_node->_y + 1][current_node->_x]);
}

void game_loop(GameModel* model, GameView* view, GameController* controller)
{
	bool LOOP_FLAG = true;
	
	// Инициализация отображений, и их первичная отрисовка
	view->background_view = new ViewBrik(
		std::vector<size_t>() = { controller->background },
		0, 0, WIDTH, HEIGHT
	);
	view->add_to_rendering_queue(view->background_view);
	
	for (int h = 0; h < G_HEIGHT; h++)
	{
		for (int w = 0; w < G_WIDTH; w++)
		{
			(*view->field_view)[w][h] = new ViewBrik(
				std::vector<size_t>() = { controller->cell, (*model->color_matrix)[w][h]->_color },
				w * BRIK_WIDTH + BIAS_X,
				h * BRIK_HEIGHT + BIAS_Y,
				BRIK_WIDTH,
				BRIK_HEIGHT
			);
			view->add_to_rendering_queue((*view->field_view)[w][h]);
		}
	}
	view->rendering_all();

	while (LOOP_FLAG)
	{
		if (SDL_PollEvent(controller->windowEvent))
			switch (controller->windowEvent->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				// TODO
				break;
			case SDL_QUIT:
				LOOP_FLAG = false;
				break;
			}
	}
}
