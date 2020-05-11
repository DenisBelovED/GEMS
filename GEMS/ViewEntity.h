#pragma once

#include<memory>
#include<vector>
#include<SDL.h>

class ViewEntity
{
public:
	void push_in_render_stack(size_t texture_id, std::shared_ptr<SDL_Rect> dst_rect)
	{
		rendering_order->push_back(std::tuple<size_t, std::shared_ptr<SDL_Rect>>(texture_id, dst_rect));
	}
	void pop_from_render_stack()
	{
		rendering_order->pop_back();
	}
	const std::vector<std::tuple<size_t, std::shared_ptr<SDL_Rect>>>* get_ordered_content()
	{
		return rendering_order;
	}
	virtual ~ViewEntity()
	{
		rendering_order->clear();
		view_rect.~shared_ptr();
	}
protected:
	ViewEntity() {};

	std::vector<std::tuple<size_t, std::shared_ptr<SDL_Rect>>>* rendering_order = nullptr;
	std::shared_ptr<SDL_Rect> view_rect = nullptr;
};

