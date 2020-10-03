#include <iostream>

#include "scene.h"
#include "game_object.h"

Scene::Scene(std::string id)
	: _camera_translation(0.f, 0.f)
{
	_id = id;
	_pause = false;

	_red = 127;
	_green = 127;
	_blue = 127;
}

Scene::~Scene()
{
}

Game_Object* Scene::get_game_object(std::string id)
{
	if (_game_objects.find(id) == _game_objects.end())
	{
		std::cout << "Attempted to find a game object that doesn't exist. ID: " << id << std::endl;
		exit(1);
	}

	return _game_objects[id];
}

std::vector<Game_Object*> Scene::get_game_objects()
{
	std::vector<Game_Object*> game_objects;

	for (auto key_value : _game_objects)
	{
		game_objects.push_back(key_value.second);
	}

	return game_objects;
}

std::string Scene::id()
{
	return _id;
}

Vector_2D Scene::camera_translation()
{
	return _camera_translation;
}

void Scene::set_pause(bool pause)
{
	_pause = pause;
}

bool Scene::pause()
{
	return _pause;
}

Uint8 Scene::red()
{
	return _red;
}

Uint8 Scene::green()
{
	return _green;
}

Uint8 Scene::blue()
{
	return _blue;
}

bool Scene::scene_completed()
{
	return _scene_completed;
}

bool Scene::destroy_on_complete()
{
	return _destroy_on_complete;
}

Scene* Scene::next_scene()
{
	return _next_scene;
}
