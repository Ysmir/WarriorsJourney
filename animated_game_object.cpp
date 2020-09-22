#include "animated_game_object.h"
#include "animated_texture.h"

Animated_Game_Object::Animated_Game_Object(std::string id, std::string texture_id)
	: Game_Object (id, texture_id)
{
	_total_time_milliseconds = 0;
}

Animated_Game_Object::~Animated_Game_Object()
{
}

void Animated_Game_Object::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	_total_time_milliseconds += milliseconds_to_simulate;

	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->set_frame(_total_time_milliseconds);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}
