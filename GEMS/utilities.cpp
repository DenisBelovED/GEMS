#include "utilities.h"

void accessible_eqal_neighbors(
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

std::vector<std::pair<int, int>>* accessible_neighbors(int x, int y)
{
	auto v = new std::vector<std::pair<int, int>>();
	if (0 < x) v->push_back(std::pair<int, int>(x - 1, y));
	if (x < (G_WIDTH - 1)) v->push_back(std::pair<int, int>(x + 1, y));
	if (0 < y) v->push_back(std::pair<int, int>(x, y - 1));
	if (y < (G_HEIGHT - 1)) v->push_back(std::pair<int, int>(x, y + 1));
	return v;
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

	// Инициализация отображений, и их первичная отрисовка
	view->clear_render();

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
	view->rendering_score(model->get_score());

	int
		click_w = -1,
		click_h = -1;
	std::vector<std::pair<int, int>>* available_briks = nullptr;

	while (LOOP_FLAG)
	{
		if (SDL_PollEvent(controller->windowEvent))
			switch (controller->windowEvent->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				if (controller->windowEvent->button.button != SDL_BUTTON_LEFT)
					break;
				
				if (click_w == -1)
				{
					auto pair = controller->search_strike(view->field_view);
					if (pair.first != -1)
					{
						click_w = pair.first, click_h = pair.second;
						available_briks = accessible_neighbors(click_w, click_h);

						(*view->field_view)[click_w][click_h]->push_in_render_stack(
							controller->glass_lime,
							init_shared_rect(
								click_w * BRIK_WIDTH + BIAS_X,
								click_h * BRIK_HEIGHT + BIAS_Y,
								BRIK_WIDTH,
								BRIK_HEIGHT
							)
						);
						view->add_to_rendering_queue((*view->field_view)[click_w][click_h]);

						for (auto& pair : *available_briks)
						{
							(*view->field_view)[pair.first][pair.second]->push_in_render_stack(
								controller->glass,
								init_shared_rect(
									pair.first * BRIK_WIDTH + BIAS_X,
									pair.second * BRIK_HEIGHT + BIAS_Y,
									BRIK_WIDTH,
									BRIK_HEIGHT
								)
							);
							view->add_to_rendering_queue((*view->field_view)[pair.first][pair.second]);
						}

						view->rendering_all();
					}
				}
				else
				{
					auto pair = controller->search_strike(view->field_view);
					if ((pair.first == click_w) && (pair.second == click_h))
					{
						(*view->field_view)[click_w][click_h]->pop_from_render_stack();
						view->add_to_rendering_queue((*view->field_view)[click_w][click_h]);
						
						for (auto& pair : *available_briks)
						{
							(*view->field_view)[pair.first][pair.second]->pop_from_render_stack();
							view->add_to_rendering_queue((*view->field_view)[pair.first][pair.second]);
						}

						view->rendering_all();
							
						click_w = -1, click_h = -1;
						available_briks->clear();
						available_briks = nullptr;
					}
				}

				/*if (view->restart_view->strike(
					controller->windowEvent->button.x,
					controller->windowEvent->button.y))
				{
					// TODO restart
				}*/
				view->rendering_score(model->get_score());
				break;
			case SDL_QUIT:
				LOOP_FLAG = false;
				break;
			}
	}
}
