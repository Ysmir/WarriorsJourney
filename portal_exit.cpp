#include "portal_exit.h"

Portal_Exit::Portal_Exit()
	:Animated_Game_Object("Portal.Exit", "Texture.Portal.Exit")
{
	_width = 200;
	_height = 200;
	_translation = Vector_2D(400, 300);
}

Portal_Exit::~Portal_Exit()
{
}


void Portal_Exit::simulate_AI(Uint32 , Assets* , Input* , Scene*)
{
}
