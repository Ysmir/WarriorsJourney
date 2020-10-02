#pragma once

#include "scene.h"

class Game_Scene : public Scene
{
public:
	Game_Scene();
	Game_Scene(float width, float height);
	~Game_Scene();

	virtual void update(SDL_Window* window) override;

private:
	float _width;
	float _height;

	float _tree_size;

	int _enemies;
	void spawn_enemies(float difficulty);
};