#pragma once

#include <Windows.h>
#include <string>

#include "input.h"
#include "scene.h"
#include "dino.h"

class Editor
{
public:
	Editor(std::wstring window_name);
	~Editor();

	void update(Input* input, Scene* scene, Configuration* config);

private:
	HWND _window;
	HMENU _menu;
};