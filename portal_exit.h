#pragma once

#include "animated_game_object.h"

class Portal_Exit : public Animated_Game_Object
{
public:
	Portal_Exit();
	~Portal_Exit();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
};
