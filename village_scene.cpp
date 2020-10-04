#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "village_scene.h"
#include "game_scene.h"
#include "player.h"
#include "village_portal.h"
#include "square_button.h"
#include "text_message.h"
#include "magic_shop_scene.h"
#include "smith_shop_scene.h"

Village_Scene::Village_Scene(Save* save)
	: Scene("Village")
{
	_red = 107;
	_green = 139;
	_blue = 34;

	_money = save->_money;

	Game_Object* portal = new Village_Portal();
	portal->set_translation(Vector_2D(220.f, 200.f));
	_game_objects[portal->id()] = portal;
	Game_Object* magic_shop = new Square_Button(128, 128, "Shop.Magic", "Texture.Shop.Magic.Normal", "Texture.Shop.Magic.Hover");
	magic_shop->set_translation(Vector_2D(100.f, 250.f));
	_game_objects[magic_shop->id()] = magic_shop;
	Game_Object* smith_shop = new Square_Button(128, 128, "Shop.Smith", "Texture.Shop.Smith.Normal", "Texture.Shop.Smith.Hover");
	smith_shop->set_translation(Vector_2D(570.f, 250.f));
	_game_objects[smith_shop->id()] = smith_shop;

	SDL_Color color;
	color.r = 127;
	color.g = 63;
	color.b = 15;
	color.a = 0;

	Game_Object* title_message = new Text_Message("Message.Title", "Warrior's Journey", 80, true, color);
	title_message->set_translation(Vector_2D(110.f, 20.f));
	_game_objects[title_message->id()] = title_message;

	Game_Object* help_message = new Text_Message("Message.Help", ".", 40, true, color);
	help_message->set_translation(Vector_2D(100.f, 720.f));
	_game_objects[help_message->id()] = help_message;
}

Village_Scene::~Village_Scene()
{
}

void Village_Scene::update(SDL_Window*, Input* input, Save* save)
{
	{

		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		Vector_2D mouse_location = Vector_2D((float)mouse_x, (float)mouse_y);

		Village_Portal* portal = (Village_Portal*)get_game_object("Portal.Village");
		Square_Button* magic_shop = (Square_Button*)get_game_object("Shop.Magic");
		Square_Button* smith_shop = (Square_Button*)get_game_object("Shop.Smith");

		Text_Message* help_message = (Text_Message*)_game_objects["Message.Help"];

		bool click = input->is_button_state(Input::Button::CLICK, Input::Button_State::PRESSED);

		if (portal->mouse_above(mouse_location)) 
		{
			help_message->set_message("Click to start game");

			if (click)
			{
				_scene_completed = true;
				_destroy_on_complete = false;
				_next_scene = new Game_Scene(2048.f, 1536.f, 1.0f, save);
			}
		}
		else if (magic_shop->mouse_above())
		{
			help_message->set_message("Click to go to Magic Shop");

			if (click)
			{
				_scene_completed = true;
				_destroy_on_complete = false;
				_next_scene = new Magic_Shop_Scene(save);
			}
		}
		else if (smith_shop->mouse_above())
		{
			help_message->set_message("Click to go to Smith Shop");

			if (click)
			{
				_scene_completed = true;
				_destroy_on_complete = false;
				_next_scene = new Smith_Shop_Scene(save);
			}
		}
		else
		{
			help_message->set_message(".");
		}

	}
}
