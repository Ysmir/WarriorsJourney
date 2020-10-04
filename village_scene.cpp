#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "village_scene.h"
#include "game_scene.h"
#include "player.h"
#include "village_portal.h"

Village_Scene::Village_Scene()
	: Scene("Village")
{
	_money = 0;

	std::string line;
	std::ifstream save ("save_1.txt");

	if (save.is_open())
	{
		while (std::getline(save, line))
		{
			std::istringstream line_string_stream(line);
			std::string property;
			line_string_stream >> property;
			if (property == "money") {
				int money;
				line_string_stream >> money;
				std::cout << money;
				_money = money;
			}

		}
		save.close();
	}

	Game_Object* portal = new Village_Portal();
	portal->set_translation(Vector_2D(200.f, 200.f));
	_game_objects[portal->id()] = portal;
}

Village_Scene::~Village_Scene()
{
}

void Village_Scene::update(SDL_Window*, Input* input)
{
	{
		/*
		Game_Object* player = get_game_object("Player");
		
		int w, h;
		SDL_GetWindowSize(window, &w, &h);

		_camera_translation = Vector_2D(-w / 2.f + player->width() / 2.f, -h / 2.f + player->height() / 2.f) + player->translation();
		*/

		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		Vector_2D mouse_location = Vector_2D((float)mouse_x, (float)mouse_y);

		Village_Portal* portal = (Village_Portal*)get_game_object("Portal.Village");

		bool click = input->is_button_state(Input::Button::CLICK, Input::Button_State::PRESSED);

		if (portal->mouse_above(mouse_location)) {
			if (click)
			{
				_scene_completed = true;
				_destroy_on_complete = false;
				_next_scene = new Game_Scene(2048.f, 1536.f, 1.0f);
			}
		}

	}
}
