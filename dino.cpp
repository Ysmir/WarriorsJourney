#include "dino.h"

Dino::Dino(std::string id)
	: Game_Object(id, "Texture.Dino")
{
	_translation = Vector_2D(50, 50);
	_collider = Circle_2D(40.f, Vector_2D(50.f, 50.f));
}

Dino::~Dino()
{
}

void Dino::simulate_AI(Uint32, Assets*, Input*, Scene*)
{
}
