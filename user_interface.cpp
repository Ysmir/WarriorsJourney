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
	std::string enemy_counter = "Enemies Remaining: " + std::to_string(_counter_enemy);

	SDL_Color text_color;
	text_color.r = 255;
	text_color.g = 0;
	text_color.b = 0;
	text_color.a = 0;

	Text enemy(renderer, enemy_counter.c_str(), text_color, "Enemy.Counter.Text", 20);

	enemy.render(renderer, Vector_2D(320.f, 20.f));

	//score counter
	std::string score_counter = "Score: " + std::to_string(_counter_score);

	//SDL_Color text_color;
	text_color.r = 127;
	text_color.g = 255;
	text_color.b = 127;
	text_color.a = 0;

	Text score(renderer, score_counter.c_str(), text_color, "Score.Counter.Text", 30);

	score.render(renderer, Vector_2D(560.f, 20.f));
}

void User_Interface::set_counter_enemy(int counter)
{
	_counter_enemy = counter;
}

void User_Interface::set_counter_score(int counter)
{
	_counter_score = counter;
}

