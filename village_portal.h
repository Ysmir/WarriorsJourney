#pragma once

#include "animated_game_object.h"

class Village_Portal : public Animated_Game_Object
{
public:
	Village_Portal();
	~Village_Portal();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;

	bool mouse_above(Vector_2D location);

private:
	void set_mouse_above(bool mouse_above);
};
