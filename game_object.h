#pragma once

#include <string>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "assets.h"
#include "input.h"
#include "vector_2D.h"
#include "configuration.h"
#include "circle_2D.h"
#include "scene.h"

class Game_Object
{
public:
	Game_Object(std::string id, std::string texture_id);
	~Game_Object();

	std::string id();

	Vector_2D translation();
	void set_translation(Vector_2D translation);

	Vector_2D velocity();
	Circle_2D collider();

	int width();
	int height();

	float mass();
	bool immovable();
	virtual bool damage(int damage);

	int max_health();
	int current_health();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) = 0;
	virtual void simulate_physics(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene);
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene);

protected:
	std::string _id;
	std::string _texture_id;

	Circle_2D _collider;

	Vector_2D _translation;

	Vector_2D _velocity;

	int _width;
	int _height;
	
	float _mass;
	bool _immovable;

	int _max_health;
	int _current_health;

	Uint32 _damage_timer;
	Uint32 _damage_length;

	Uint8 _red_filter;
	Uint8 _blue_filter;
	Uint8 _green_filter;

	SDL_RendererFlip _flip;
};