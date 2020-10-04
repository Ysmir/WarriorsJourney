#include "village_portal.h"

Village_Portal::Village_Portal()
	:Animated_Game_Object("Portal.Village", "Texture.Portal.Entry")
{
	_width = 350;
	_height = 250;
}

Village_Portal::~Village_Portal()
{
}

void Village_Portal::simulate_AI(Uint32 , Assets* , Input* , Scene* )
{
}

bool Village_Portal::mouse_above(Vector_2D location)
{
	float focal_offset = _height * 0.35f;
	Vector_2D focal_point_1 = Vector_2D(_translation.x() + _width / 2.f, _translation.y() + _height / 2.f - focal_offset);
	Vector_2D focal_point_2 = Vector_2D(_translation.x() + _width / 2.f, _translation.y() + _height / 2.f + focal_offset);

	if ((location - focal_point_1).magnitude() + (location - focal_point_2).magnitude() < _height*0.8f)
	{
		set_mouse_above(true);
		return true;
	}
	set_mouse_above(false);
	return false;
}

void Village_Portal::set_mouse_above(bool mouse_above)
{
	if (mouse_above)
	{

		_texture_id = "Texture.Portal.Exit";
	}
	else
	{
		_texture_id = "Texture.Portal.Entry";
	}
}
