#include "Node.h"

Node::Node(size_t x, size_t y, size_t color)
{
	_x = x;
	_y = y;
	_color = color;
	visited = false;
}

Node::~Node()
{
}

std::tuple<size_t, size_t> Node::get_coord()
{
	return std::tuple<size_t, size_t>(_x, _y);
}
