#include "GameController.h"

GameController::GameController()
{
	windowEvent = new SDL_Event();
}

GameController::~GameController()
{
}

std::pair<int, int> GameController::search_strike(FieldView* field_view)
{
	int x = -1, y = -1;
	for (int h = 0; h < G_HEIGHT; h++)
	{
		for (int w = 0; w < G_WIDTH; w++)
		{
			if (field_view->get_cell(w, h)->strike(windowEvent->button.x, windowEvent->button.y))
			{
				x = w, y = h;
				break;
			}
		}
		if (x != -1)
			break;
	}
	return std::pair<int, int>(x, y);
}
