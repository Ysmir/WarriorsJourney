#pragma once

#include "game_object.h"

class Square_Button : public Game_Object
{
public:
	Square_Button(int width, int height, std::string id, std::string base_texture_id, std::string alt_texture_id);
	~Square_Button();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;

	bool mouse_above();

private:
	void set_mouse_above(bool mouse_above);
	bool _mouse_above;
	std::string _base_texture_id;
	std::string _alt_texture_id;
};
