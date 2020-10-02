#pragma once

#include "animated_game_object.h"

class Tree : public Game_Object
{
public:
	Tree(std::string id, Vector_2D translation);
	~Tree();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
};
