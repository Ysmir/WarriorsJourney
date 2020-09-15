#pragma once

#include "game_object.h"

class Dino : public Game_Object
{
public:
	Dino(std::string id);
	~Dino();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
};