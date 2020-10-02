#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "village_scene.h"
#include "player.h"

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

	Game_Object* player = new Player("Player");
	_game_objects[player->id()] = player;
}

Village_Scene::~Village_Scene()
{
}

void Village_Scene::update(SDL_Window* window)
{
	{
		Game_Object* player = get_game_object("Player");

		int w, h;
		SDL_GetWindowSize(window, &w, &h);

		_camera_translation = Vector_2D(-w / 2.f + player->width() / 2.f, -h / 2.f + player->height() / 2.f) + player->translation();
	}
}
