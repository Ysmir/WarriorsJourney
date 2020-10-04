#pragma once

#include "game_object.h"

class User_Interface : public Game_Object
{
public:
	User_Interface();
	~User_Interface();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

	void set_counter_enemy(int counter);
	void set_counter_score(int counter);

private:
	int _counter_enemy;
	int _counter_score;
};
