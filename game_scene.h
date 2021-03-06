#pragma once

#include "scene.h"
#include "player.h"

class Game_Scene : public Scene
{
public:
	Game_Scene();
	Game_Scene(float width, float height, float difficulty);
	Game_Scene(float width, float height, float difficulty, Save* save);
	Game_Scene(float width, float height, float difficulty, int score, Player* player);
	~Game_Scene();

	virtual void update(SDL_Window* window, Input* input, Save* save) override;

private:
	float _width;
	float _height;

	float _tree_size;

	float _difficulty;
	int _score;

	int _enemies;
	void spawn_enemies(float difficulty);
	std::vector<Game_Object*> _living_enemies;
};