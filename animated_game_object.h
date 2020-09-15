#pragma once

#include "game_object.h"

class Animated_Game_Object : public Game_Object
{
public:
	Animated_Game_Object(std::string id, std::string texture_id);
	~Animated_Game_Object();

	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;
};