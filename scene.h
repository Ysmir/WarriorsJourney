#pragma once

#include <map>
#include <string>
#include <vector>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "vector_2D.h"

class Game_Object;

class Scene
{
public:
	Scene(std::string id);
	~Scene();

	virtual void update(SDL_Window* window) = 0;

	Game_Object* get_game_object(std::string id);
	std::vector<Game_Object*> get_game_objects();

	std::string id();
	Vector_2D camera_translation();

	void set_pause(bool pause);
	bool pause();

	Uint8 red();
	Uint8 green();
	Uint8 blue();

protected:
	std::map<std::string, Game_Object*> _game_objects;
	std::string							_id;
	Vector_2D							_camera_translation;
	bool _pause;

	Uint8 _red;
	Uint8 _green;
	Uint8 _blue;
};