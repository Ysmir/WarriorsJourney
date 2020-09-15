#include "animated_game_object.h"
#include "animated_texture.h"

Animated_Game_Object::Animated_Game_Object(std::string id, std::string texture_id)
	: Game_Object (id, texture_id)
{
}

Animated_Game_Object::~Animated_Game_Object()
{
}

void Animated_Game_Object::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}
