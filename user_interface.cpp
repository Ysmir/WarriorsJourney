#include "user_interface.h"
#include "player.h"
#include "text.h"

User_Interface::User_Interface()
	: Game_Object("User.Interface", "Texture.Dino")
{
	_width = 0;
	_height = 0;

	_translation = Vector_2D(0.f, 12800000000000.f);
}

User_Interface::~User_Interface()
{
}

void User_Interface::simulate_AI(Uint32, Assets* , Input* , Scene* scene)
{
	Game_Object* player = scene->get_game_object("Player");
	_max_health = player->max_health();
	_current_health = player->current_health();
}

void User_Interface::render(Uint32 , Assets* , SDL_Renderer* renderer, Configuration* , Scene* scene)
{
	//Healthbar
	SDL_Rect health_bar = SDL_Rect();
	health_bar.x = 20;
	health_bar.y = 20;
	health_bar.w = 250;
	health_bar.h = 50;
	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 63);
	SDL_RenderFillRect(renderer, &health_bar);
	health_bar.w = 250 * _current_health / _max_health;
	SDL_SetRenderDrawColor(renderer, 255, 10, 10, 255);
	SDL_RenderFillRect(renderer, &health_bar);
	const Uint8 red = scene->red();
	const Uint8 green = scene->green();
	const Uint8 blue = scene->blue();
	SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
	
	//Enemy Counter
	std::string enemy_counter = "Enemies Remaining: " + std::to_string(_counter);

	SDL_Color text_color;
	text_color.r = 255;
	text_color.g = 0;
	text_color.b = 0;
	text_color.a = 0;

	Text id(renderer, enemy_counter.c_str(), text_color, "Enemy.Counter.Text");

	id.render(renderer, Vector_2D(300.f, 20.f));
}

void User_Interface::set_counter(int counter)
{
	_counter = counter;
}
