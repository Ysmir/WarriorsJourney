#pragma once

#include "animated_game_object.h"

class Level_Portal : public Animated_Game_Object
{
public:
	Level_Portal();
	~Level_Portal();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;

	void set_exit_mode(bool mode);
	bool player_exit();

private:
	bool _exit_mode;
	bool _player_exit;
};
