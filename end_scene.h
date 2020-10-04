#pragma once

#include "scene.h"
#include "text.h"

class End_Scene : public Scene
{
public:
	End_Scene(int score, float level);
	~End_Scene();

	virtual void update(SDL_Window* window, Input* input) override;

};