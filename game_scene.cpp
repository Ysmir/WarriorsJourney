#include "game_scene.h"
#include "snail.h"
#include "player.h"
#include "portal_entry.h"
#include "portal_exit.h"
#include "fire.h"
#include "goblin.h"
#include "user_interface.h"

Game_Scene::Game_Scene()
	: Scene("Game")
{
	Game_Object* player = new Player("Player");
	_game_objects[player->id()] = player;

	Game_Object* user_interface = new User_Interface();
	_game_objects[user_interface->id()] = user_interface;

	Game_Object* snail = new Snail("Snail");
	_game_objects[snail->id()] = snail;

	Game_Object* portal_entry = new Portal_Entry();
	_game_objects[portal_entry->id()] = portal_entry;

	Game_Object* portal_exit = new Portal_Exit();
	_game_objects[portal_exit->id()] = portal_exit;

	Game_Object* fire = new Fire();
	_game_objects[fire->id()] = fire;

	Game_Object* goblin = new Goblin("Goblin.1");
	_game_objects[goblin->id()] = goblin;
	goblin->set_translation(Vector_2D(-200.f, -200.f));
}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::update(SDL_Window* window)
{
	Game_Object* player = get_game_object("Player");

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	_camera_translation = Vector_2D(-w / 2.f + player->width() / 2.f, -h / 2.f + player->height() / 2.f) + player->translation();
}
