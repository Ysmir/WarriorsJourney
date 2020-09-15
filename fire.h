#pragma once

#include "animated_game_object.h"

class Fire : public Animated_Game_Object
{
public:
	Fire();
	~Fire();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
};
