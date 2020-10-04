#pragma once

#include "game_object.h"

class End_Interface : public Game_Object
{
public:
	End_Interface(int score, int level);
	~End_Interface();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

private:
	int _score;
	int _level;
};
