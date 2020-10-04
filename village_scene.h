#pragma once

#include "scene.h"

class Village_Scene : public Scene
{
public:
	Village_Scene(Save* save);
	~Village_Scene();

	virtual void update(SDL_Window* window, Input* input, Save* save) override;

private:
	int _money;
};