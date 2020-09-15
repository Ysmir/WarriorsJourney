#include "walking_dino.h"

Walking_Dino::Walking_Dino(std::string id)
	: Animated_Game_Object (id, "Texture.Dino.Walking")
{
	_translation = Vector_2D(150, 50);
	_velocity = Vector_2D(0.02f, 0);

	_collider.set_translation(Vector_2D(_width / 2.0f, _height / 1.5f));
	_collider.set_radius(_width / 4.f);
}

Walking_Dino::~Walking_Dino()
{
}

void Walking_Dino::simulate_AI(Uint32 , Assets*, Input*, Scene* )
{
}
