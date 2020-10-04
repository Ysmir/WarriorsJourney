#pragma once

#include "scene.h"

class Smith_Shop_Scene : public Scene
{
public:
	Smith_Shop_Scene(Save* save);
	~Smith_Shop_Scene();

	virtual void update(SDL_Window* window, Input* input, Save* save) override;

};