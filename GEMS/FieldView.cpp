#include "FieldView.h"

FieldView::FieldView()
{
	field_view = new std::vector<std::vector<ViewEntity*>>(G_HEIGHT);
	for (size_t i = 0; i < G_HEIGHT; i++)
		(*field_view)[i] = std::vector<ViewEntity*>(G_WIDTH);
}

FieldView::~FieldView()
{
	for (auto& e : *field_view)
		for (auto& n : e)
			delete n;
}

void FieldView::update_cell(size_t x, size_t y, ViewEntity* entity)
{
	delete (*field_view)[x][y];
	(*field_view)[x][y] = entity;
}

ViewEntity* FieldView::get_cell(size_t x, size_t y)
{
	return (*field_view)[x][y];
}
