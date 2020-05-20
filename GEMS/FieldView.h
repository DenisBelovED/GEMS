#pragma once

#include <vector>
#include "Constants.h"
#include "ViewEntity.h"

class FieldView
{
public:
	FieldView();
	~FieldView();
	void update_cell(size_t x, size_t y, ViewEntity* entity);
	ViewEntity* get_cell(size_t x, size_t y);
private:
	std::vector<std::vector<ViewEntity*>>* field_view = nullptr;
};

