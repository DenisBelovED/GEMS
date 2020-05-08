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

std::shared_ptr<SDL_Rect> init_shared_rect(int x, int y, int width, int height)
{
	SDL_Rect* r = new SDL_Rect();
	r->x = x;
	r->y = y;
	r->w = width;
	r->h = height;
	return std::shared_ptr<SDL_Rect>(r);
}

void game_loop(GameModel* model, GameView* view, GameController* controller)
{
	bool LOOP_FLAG = true;
	auto field = model->get_field();
	
	view->add_to_rendering_queue(controller->background, init_shared_rect(0, 0, WIDTH, HEIGHT));
	for (int h = 0; h < G_HEIGHT; h++)
	{
		for (int w = 0; w < G_WIDTH; w++)
		{
			auto rect_ptr1 = init_shared_rect(
				w * BRIK_WIDTH + BIAS_X,
				h * BRIK_HEIGHT + BIAS_Y,
				BRIK_WIDTH,
				BRIK_HEIGHT
			);
			std::shared_ptr<SDL_Rect> rect_ptr2(rect_ptr1);
			view->add_to_rendering_queue(controller->cell, rect_ptr1);
			view->add_to_rendering_queue((*field)[w][h]->_color, rect_ptr2);
		}
	}
	view->draw();

	while (LOOP_FLAG)
	{
		if (SDL_PollEvent(controller->windowEvent))
			switch (controller->windowEvent->type)
			{
			case SDL_QUIT:
				LOOP_FLAG = false;
				break;
			}
	}
}
