#pragma once

#include "animated_game_object.h"

class Snail : public Animated_Game_Object
{
public:
	Snail(std::string id);
	~Snail();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;

	void setFast(bool fast);
	bool fast();

private:
	bool _fast;
};