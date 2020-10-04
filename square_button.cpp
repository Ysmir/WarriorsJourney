#include "square_button.h"

Square_Button::Square_Button(int width, int height, std::string id, std::string base_texture_id, std::string alt_texture_id)
	:Game_Object(id, base_texture_id)
{
	_width = width;
	_height = height;
	_base_texture_id = base_texture_id;
	_alt_texture_id = alt_texture_id;
	_mouse_above = false;
}

Square_Button::~Square_Button()
{
}

void Square_Button::simulate_AI(Uint32 , Assets* , Input* , Scene* )
{
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	Vector_2D mouse_location = Vector_2D((float)mouse_x, (float)mouse_y);

	if (mouse_location.x() > _translation.x() &&
		mouse_location.x() < _translation.x() + _width &&
		mouse_location.y() > _translation.y() &&
		mouse_location.y() < _translation.y() + _height)
	{
		set_mouse_above(true);
	}
	else
	{
		set_mouse_above(false);
	}
}

bool Square_Button::mouse_above()
{
    return _mouse_above;
}

void Square_Button::set_mouse_above(bool mouse_above)
{
	_mouse_above = mouse_above;
	if (mouse_above)
	{

		_texture_id = _alt_texture_id;
	}
	else
	{
		_texture_id = _base_texture_id;
	}
}
