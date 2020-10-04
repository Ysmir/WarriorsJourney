#pragma once

#include "scene.h"

class Magic_Shop_Scene : public Scene
{
public:
	Magic_Shop_Scene(Save* save);
	~Magic_Shop_Scene();

	virtual void update(SDL_Window* window, Input* input, Save* save) override;

};