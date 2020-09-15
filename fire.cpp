#include "fire.h"
#include "player.h"

Fire::Fire()
	:Animated_Game_Object("Fire", "Texture.Fire")
{
	_width = 100;
	_height = 100;
	_translation = Vector_2D(150, 450);
}

Fire::~Fire()
{
}

void Fire::simulate_AI(Uint32 , Assets* , Input* , Scene* scene)
{
	Player* player = (Player*)scene->get_game_object("Player");

	Vector_2D portal_centre = _translation + Vector_2D((float)_width / 2, (float)_height / 2);
	Vector_2D player_centre = player->translation() + Vector_2D((float)player->width() / 2, (float)player->height() / 2);

	float distance_to_player = (portal_centre - player_centre).magnitude();

	if (distance_to_player < 60.f)
	{
		player->damage(10);
	}
}
