#pragma once

#include "ViewEntity.h"

class ViewBrik : public ViewEntity
{
public:
	ViewBrik(std::vector<size_t> ordered_texture_ids, int x, int y, int width, int height)
	{
		rendering_order = new std::vector<std::tuple<size_t, std::shared_ptr<SDL_Rect>>>();
		SDL_Rect* r = new SDL_Rect();
		r->x = x;
		r->y = y;
		r->w = width;
		r->h = height;
		view_rect = std::shared_ptr<SDL_Rect>(r);
		for (auto& texture_id : ordered_texture_ids)
			push_in_render_stack(texture_id, std::shared_ptr<SDL_Rect>(view_rect));
	}
};

