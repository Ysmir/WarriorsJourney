#include "level_portal.h"
#include "player.h"

Level_Portal::Level_Portal()
	:Animated_Game_Object("Portal.Level", "Texture.Portal.Entry")
{
	_width = 200;
	_height = 200;

	_exit_mode = false;
	_player_exit = false;
}

Level_Portal::~Level_Portal()
{
}

void Level_Portal::simulate_AI(Uint32 , Assets* , Input* , Scene* scene)
{
	if (_exit_mode)
	{
		Player* player = (Player*)scene->get_game_object("Player");

		Vector_2D portal_centre = _translation + Vector_2D((float)_width / 2, (float)_height / 2);
		Vector_2D player_centre = player->translation() + Vector_2D((float)player->width() / 2, (float)player->height() / 2);

		float distance_to_player = (portal_centre - player_centre).magnitude();

		if (distance_to_player < 60.f)
		{
			_player_exit = true;
		}
		else
		{
			_player_exit = false;
		}
	}
}

void Level_Portal::set_exit_mode(bool mode)
{
	_exit_mode = mode;
	if (mode)
	{
		_texture_id = "Texture.Portal.Exit";
	}
	else
	{
		_texture_id = "Texture.Portal.Entry";
	}
}

bool Level_Portal::player_exit()
{
	if (_exit_mode)	return _player_exit;
	return false;
}
