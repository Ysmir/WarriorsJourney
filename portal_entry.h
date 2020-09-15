#pragma once

#include "animated_game_object.h"

class Portal_Entry : public Animated_Game_Object
{
public:
	Portal_Entry();
	~Portal_Entry();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
};
