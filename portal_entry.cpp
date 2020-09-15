#include "portal_entry.h"
#include "player.h"
#include "portal_exit.h"

Portal_Entry::Portal_Entry()
	:Animated_Game_Object("Portal.Entry", "Texture.Portal.Entry")
{
	_width = 200;
	_height = 200;
	_translation = Vector_2D(50, 300);
}

Portal_Entry::~Portal_Entry()
{
}

void Portal_Entry::simulate_AI(Uint32 , Assets* , Input* , Scene* scene)
{
	Player* player = (Player*)scene->get_game_object("Player");

	Vector_2D portal_centre = _translation + Vector_2D((float)_width / 2, (float)_height / 2);
	Vector_2D player_centre = player->translation() + Vector_2D((float)player->width() / 2, (float)player->height() / 2);

	float distance_to_player = (portal_centre - player_centre).magnitude();

	if (distance_to_player < 60.f)
	{
		Portal_Exit* portal_exit = (Portal_Exit*)scene->get_game_object("Portal.Exit");
		Vector_2D exit_location = portal_exit->translation() + Vector_2D(100.f, 0.f);

		player->set_translation(exit_location);
	}
}