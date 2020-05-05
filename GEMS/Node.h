#pragma once

#include <tuple>

class Node
{
public:
	Node(size_t x = 0, size_t y = 0, size_t color = 0);
	~Node();
	std::tuple<size_t, size_t> get_coord();
	size_t _x, _y, _color;
	bool visited;
};
