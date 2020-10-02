#include <iostream>

#include "assets.h"
#include "texture.h"
#include "animated_texture.h"
#include "sound.h"

Assets::Assets(SDL_Renderer* renderer)
{
	//dino Textures
	{
		Texture* dino_texture = new Texture("Texture.Dino", "Assets/dino.png", renderer);
		_assets[dino_texture->id()] = dino_texture;
	
		const int frame_count = 10;
		const Uint32 frame_duration_milliseconds = 100;
		Animated_Texture* walking_dino_texture = new Animated_Texture("Texture.Dino.Walking", "Assets/dino.walking.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[walking_dino_texture->id()] = walking_dino_texture;
		_animated_texture_ids.push_back(walking_dino_texture->id());
	}
	//snail Texture
	{
		const int snail_frame_count = 3;
		const Uint32 snail_frame_duration_milliseconds = 200;
		Animated_Texture* walking_snail_texture = new Animated_Texture("Texture.Snail.Walking", "Assets/snail.walking.png", renderer, snail_frame_count, snail_frame_duration_milliseconds);
		_assets[walking_snail_texture->id()] = walking_snail_texture;
		_animated_texture_ids.push_back(walking_snail_texture->id());
	}
	//player Assets
	{
		const int frame_count_seven = 7;
		const int frame_count_four = 4;
		const int frame_count_three = 3;
		const Uint32 frame_duration_milliseconds = 120;
		const Uint32 running_frame_duration_milliseconds = frame_duration_milliseconds /2;

		Animated_Texture* walking_player_texture = new Animated_Texture("Texture.Player.Walking", "Assets/odyssey_knight/odyssey_knight_walk.png", renderer, frame_count_four, frame_duration_milliseconds);
		_assets[walking_player_texture->id()] = walking_player_texture;
		_animated_texture_ids.push_back(walking_player_texture->id());
		
		Animated_Texture* idle_player_texture = new Animated_Texture("Texture.Player.Idle", "Assets/odyssey_knight/odyssey_knight_idle.png", renderer, frame_count_three, frame_duration_milliseconds);
		_assets[idle_player_texture->id()] = idle_player_texture;
		_animated_texture_ids.push_back(idle_player_texture->id());

		Animated_Texture* running_player_texture = new Animated_Texture("Texture.Player.Running", "Assets/odyssey_knight/odyssey_knight_walk.png", renderer, frame_count_four, running_frame_duration_milliseconds);
		_assets[running_player_texture->id()] = running_player_texture;
		_animated_texture_ids.push_back(running_player_texture->id());

		Animated_Texture* death_player_texture = new Animated_Texture("Texture.Player.Death", "Assets/odyssey_knight/odyssey_knight_death.png", renderer, frame_count_three, frame_duration_milliseconds, false);
		_assets[death_player_texture->id()] = death_player_texture;
		_animated_texture_ids.push_back(death_player_texture->id());

		Animated_Texture* attack_player_texture = new Animated_Texture("Texture.Player.Attack", "Assets/odyssey_knight/odyssey_knight_attack.png", renderer, frame_count_seven, frame_duration_milliseconds);
		_assets[attack_player_texture->id()] = attack_player_texture;
		_animated_texture_ids.push_back(attack_player_texture->id());

		/*
		Animated_Texture* hurt_player_texture = new Animated_Texture("Texture.Player.Hurt", "Assets/SteamMan/SteamMan_hurt.png", renderer, frame_count_three, frame_duration_milliseconds);
		_assets[hurt_player_texture->id()] = hurt_player_texture;
		_animated_texture_ids.push_back(hurt_player_texture->id());
		*/

		Sound* running = new Sound("Sound.Running", "Assets/running.wav");
		_assets[running->id()] = running;

		Sound* walking = new Sound("Sound.Walking", "Assets/walking.wav");
		_assets[walking->id()] = walking;

		Sound* attack = new Sound("Sound.Attack", "Assets/swish_2.wav");
		_assets[attack->id()] = attack;

		Sound* death = new Sound("Sound.Death", "Assets/f_death.wav");
		_assets[death->id()] = death;
	}
	// collider Texture
	{
		Texture* texture = new Texture("Texture.Collider", "Assets/collider.png", renderer);
		_assets[texture->id()] = texture;
	}
	// music sound
	{
		Sound* sound = new Sound("Sound.Music", "Assets/cannontube_loop_low.ogg");
		_assets[sound->id()] = sound;

		Mix_PlayChannel(0, sound->data(), -1);
	}
	// portal textures
	{
		const int frame_count = 8;
		const Uint32 frame_duration_milliseconds = 100;
		Animated_Texture* portal_entry_texture = new Animated_Texture("Texture.Portal.Entry", "Assets/portal.green.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[portal_entry_texture->id()] = portal_entry_texture;
		_animated_texture_ids.push_back(portal_entry_texture->id());
		Animated_Texture* portal_exit_texture = new Animated_Texture("Texture.Portal.Exit", "Assets/portal.purple.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[portal_exit_texture->id()] = portal_exit_texture;
		_animated_texture_ids.push_back(portal_exit_texture->id());
	}
	// fire texture
	{
		const int frame_count = 5;
		const Uint32 frame_duration_milliseconds = 100;
		Animated_Texture* fire_texture = new Animated_Texture("Texture.Fire", "Assets/fire.camp.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[fire_texture->id()] = fire_texture;
		_animated_texture_ids.push_back(fire_texture->id());
	}
	// tree texture
	{
		Texture* tree_texture = new Texture("Texture.Tree", "Assets/tree.png", renderer);
		_assets[tree_texture->id()] = tree_texture;
	}
	// goblin texture
	{
		const int walking_frame_count = 7;
		const int attack_frame_count = 4;
		const int death_frame_count = 5;
		const Uint32 frame_duration_milliseconds = 100;

		Animated_Texture* walking_goblin_texture = new Animated_Texture("Texture.Goblin.Walking", "Assets/enemies/goblin_walk.png", renderer, walking_frame_count, frame_duration_milliseconds);
		_assets[walking_goblin_texture->id()] = walking_goblin_texture;
		_animated_texture_ids.push_back(walking_goblin_texture->id());

		Animated_Texture* attack_goblin_texture = new Animated_Texture("Texture.Goblin.Attack", "Assets/enemies/goblin_attack.png", renderer, attack_frame_count, frame_duration_milliseconds);
		_assets[attack_goblin_texture->id()] = attack_goblin_texture;
		_animated_texture_ids.push_back(attack_goblin_texture->id());

		Animated_Texture* death_goblin_texture = new Animated_Texture("Texture.Goblin.Death", "Assets/enemies/goblin_death.png", renderer, death_frame_count, frame_duration_milliseconds, false);
		_assets[death_goblin_texture->id()] = death_goblin_texture;
		_animated_texture_ids.push_back(death_goblin_texture->id());
	}
}

Assets::~Assets()
{
}

Asset* Assets::get_asset(std::string id)
{
	if (_assets.find(id) == _assets.end())
	{
		std::cout << "Attempted to find an asset that was not loaded. ID: " << id << std::endl;
		exit(1);
	}
	return _assets[id];
}

void Assets::reset_animated_textures()
{
	for (auto id : _animated_texture_ids)
	{
		Animated_Texture* asset = (Animated_Texture*)_assets[id];
		asset->reset_update();
	}
}
