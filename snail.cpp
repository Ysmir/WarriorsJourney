#include "snail.h"

Snail::Snail(std::string id)
	: Animated_Game_Object(id, "Texture.Snail.Walking")
{
	_translation = Vector_2D(150, 150);
	_velocity = Vector_2D(0.01f, 0);

	_collider.set_translation(Vector_2D(_width / 2.0f, _height / 1.5f));
	_collider.set_radius(_width / 3.f);

	_mass = 200.f;

	_fast = false;
}

Snail::~Snail()
{
}

void Snail::simulate_AI(Uint32, Assets*, Input*, Scene* )
{
}

void Snail::setFast(bool fast)
{
	_fast = fast;
	if (_fast) 
	{
		_velocity.scale(10.f);
	}
	else
	{
		_velocity.scale(0.1f);
	}
}

bool Snail::fast()
{
	return _fast;
}
