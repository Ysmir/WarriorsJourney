#include <random>
#include <time.h>

#include "game_scene.h"
#include "end_scene.h"
#include "snail.h"
#include "player.h"
#include "fire.h"
#include "goblin.h"
#include "tree.h"
#include "user_interface.h"
#include "level_portal.h"

Game_Scene::Game_Scene()
	: Scene("Game")
{
	_width = 0.f;
	_height = 0.f;

	_difficulty = 0.f;
	_score = 0;	

	_tree_size = 128.f;

	_enemies = 0;

	Game_Object* player = new Player("Player");
	_game_objects[player->id()] = player;

	Game_Object* user_interface = new User_Interface();
	_game_objects[user_interface->id()] = user_interface;

	Game_Object* level_portal = new Level_Portal();
	_game_objects[level_portal->id()] = level_portal;
}

Game_Scene::Game_Scene(float width, float height, float difficulty)
	:Game_Scene()
{
	_width = width;
	_height = height;
	_difficulty = difficulty;

	int tree_counter = 0;
	Game_Object* tree;
	for (float x = -_tree_size; x <= _width; x += _tree_size/2.f)
	{
		tree = new Tree("Tree." + std::to_string(tree_counter), Vector_2D(x, -_tree_size));
		_game_objects[tree->id()] = tree;
		tree_counter++;

		tree = new Tree("Tree." + std::to_string(tree_counter), Vector_2D(x, _height));
		_game_objects[tree->id()] = tree;
		tree_counter++;
	}

	for (float y = -_tree_size/2.f; y < _height; y += _tree_size/2.f)
	{
		tree = new Tree("Tree." + std::to_string(tree_counter), Vector_2D(-_tree_size, y));
		_game_objects[tree->id()] = tree;
		tree_counter++;

		tree = new Tree("Tree." + std::to_string(tree_counter), Vector_2D(_width, y));
		_game_objects[tree->id()] = tree;
		tree_counter++;
	}

	Game_Object* player = _game_objects["Player"];
	player->set_translation(Vector_2D(_width/2.f, _height / 2.f));
	Game_Object* portal = _game_objects["Portal.Level"];
	portal->set_translation(Vector_2D((_width - portal->width())/2.f, (_height - portal->height())/2.f));

	spawn_enemies(difficulty);

}

Game_Scene::Game_Scene(float width, float height, float difficulty, Save* save)
	:Game_Scene(width, height, difficulty)
{
	Player* player = (Player*)_game_objects["Player"];
	player->load_save(save);
	save->_speed_potions = 0;
}

Game_Scene::Game_Scene(float width, float height, float difficulty, int score, Player* player)
	:Game_Scene(width, height, difficulty)
{
	_score = score;

	_game_objects["Player"] = player;
	player->set_translation(Vector_2D(_width / 2.f, _height / 2.f));
}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::update(SDL_Window* window, Input*, Save* save)
{
	//move camera
	Game_Object* player = get_game_object("Player");

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	_camera_translation = Vector_2D(-w / 2.f + player->width() / 2.f, -h / 2.f + player->height() / 2.f) + player->translation();
	if (_width > 0) {
		if (_camera_translation.x() < -_tree_size/2.f) _camera_translation = Vector_2D(-_tree_size / 2.f, _camera_translation.y());
		else if(_camera_translation.x() > (_width - w + _tree_size/2.f)) _camera_translation = Vector_2D(_width - w + _tree_size / 2.f, _camera_translation.y());
		if (_camera_translation.y() < -_tree_size / 2.f) _camera_translation = Vector_2D(_camera_translation.x(), -_tree_size / 2.f);
		else if (_camera_translation.y() > (_height - h + _tree_size / 2.f)) _camera_translation = Vector_2D(_camera_translation.x(), _height - h + _tree_size / 2.f);
	}

	//check for dead enemies
	for (int i = 0; i <_living_enemies.size(); i++)
	{
		if (_living_enemies.at(i)->current_health() <= 0)
		{
			_living_enemies.erase(_living_enemies.begin()+i);
			_enemies--;
			i--;
			_score++;

			if (_enemies == 0)
			{
				Level_Portal* level_portal = (Level_Portal*)get_game_object("Portal.Level");
				level_portal->set_exit_mode(true);
			}
		}
		
	}

	//Check for dead player
	if (player->current_health() == 0)
	{
		_scene_completed = true;
		_destroy_on_complete = true;
		_next_scene = new End_Scene(_score, _difficulty, save);
	}

	//update UI
	User_Interface* UI = (User_Interface*)get_game_object("User.Interface");
	UI->set_counter_enemy(_enemies);
	UI->set_counter_score(_score);

	if (_enemies == 0)
	{
		Level_Portal* level_portal = (Level_Portal*)get_game_object("Portal.Level");
		if (level_portal->player_exit())
		{
			_scene_completed = true;
			_destroy_on_complete = true;
			_next_scene = new Game_Scene(2048.f, 1536.f, _difficulty + 1.f, _score, (Player*)_game_objects["Player"]);
		}
	}
}

void Game_Scene::spawn_enemies(float difficulty)
{
	int enemies_to_spawn = (int)(5 + 2 * difficulty);
	_enemies = enemies_to_spawn;

	int seed = (int)time(NULL);
	std::minstd_rand0 generator(seed);

	while (enemies_to_spawn > 0)
	{
		//generate spawn location
		float random_x = (float)generator() / generator.max() * _width;
		float random_y = (float)generator() / generator.max() * _height;
		Vector_2D spawn_location = Vector_2D(random_x, random_y);
		//check if location is valid
		bool valid_location = (spawn_location - Vector_2D(_width / 2.f, _height / 2.f)).magnitude() > 200.f;
		if (valid_location)
		{
			//generate enemy and add it
			Game_Object* enemy;
			enemy = new Goblin("Goblin." + std::to_string(_enemies-enemies_to_spawn));
			enemy->set_translation(spawn_location);
			_game_objects[enemy->id()] = enemy;
			enemies_to_spawn--;
			_living_enemies.push_back(enemy);
		}
	}
}
