#pragma once

#include "scene.h"

class Village_Scene : public Scene
{
public:
	Village_Scene();
	~Village_Scene();

	virtual void update(SDL_Window* window, Input* input) override;

private:
	int _money;
};