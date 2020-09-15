#pragma once

#include "animated_game_object.h"

class Walking_Dino : public Animated_Game_Object
{
public:
	Walking_Dino(std::string id);
	~Walking_Dino();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
};