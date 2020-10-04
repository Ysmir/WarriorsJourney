#include "magic_shop_scene.h"
#include "text_message.h"
#include "square_button.h"

Magic_Shop_Scene::Magic_Shop_Scene(Save* save)
	: Scene("Shop.Magic")
{

	_red = 245;
	_green = 222; 
	_blue = 179;

	SDL_Color color;
	color.r = 127;
	color.g = 63;
	color.b = 15;
	color.a = 0;

	Game_Object* money_message = new Text_Message("Message.Money", "Money: " + std::to_string(save->_money), 50, true, color);
	money_message->set_translation(Vector_2D(100.f, 20.f));
	_game_objects[money_message->id()] = money_message;

	Game_Object* speed_potion_message = new Text_Message("Message.Potion.Speed", "Buy Speed Potion", 40, true, color);
	speed_potion_message->set_translation(Vector_2D(100.f, 100.f));
	_game_objects[speed_potion_message->id()] = speed_potion_message;
	Game_Object* speed_potion_cost_message = new Text_Message("Message.Potion.Speed.Cost", "Cost: " + std::to_string((save->_speed_potions + 2) * 50), 30, true, color);
	speed_potion_cost_message->set_translation(Vector_2D(120.f, 150.f));
	_game_objects[speed_potion_cost_message->id()] = speed_potion_cost_message;
	Game_Object* speed_potion_owned_message = new Text_Message("Message.Potion.Speed.Owned", "Owned: " + std::to_string(save->_speed_potions), 30, true, color);
	speed_potion_owned_message->set_translation(Vector_2D(120.f, 200.f));
	_game_objects[speed_potion_owned_message->id()] = speed_potion_owned_message;
	Game_Object* speed_potion_buy = new Square_Button(100, 100, "Button.Potion.Speed", "Texture.Shop.Magic.Normal", "Texture.Shop.Magic.Hover");
	speed_potion_buy->set_translation(Vector_2D(600.f, 120.f));
	_game_objects[speed_potion_buy->id()] = speed_potion_buy;

	Game_Object* lifesteal_potion_message = new Text_Message("Message.Potion.Lifesteal", "Buy Lifesteal Potion", 40, true, color);
	lifesteal_potion_message->set_translation(Vector_2D(100.f, 300.f));
	_game_objects[lifesteal_potion_message->id()] = lifesteal_potion_message;
	Game_Object* lifesteal_potion_cost_message = new Text_Message("Message.Potion.Lifesteal.Cost", "Cost: " + std::to_string((save->_lifesteal_potions + 4) * 150), 30, true, color);
	lifesteal_potion_cost_message->set_translation(Vector_2D(120.f, 350.f));
	_game_objects[lifesteal_potion_cost_message->id()] = lifesteal_potion_cost_message;
	Game_Object* lifesteal_potion_owned_message = new Text_Message("Message.Potion.Lifesteal.Owned", "Owned: " + std::to_string(save->_lifesteal_potions), 30, true, color);
	lifesteal_potion_owned_message->set_translation(Vector_2D(120.f, 400.f));
	_game_objects[lifesteal_potion_owned_message->id()] = lifesteal_potion_owned_message;
	Game_Object* lifesteal_potion_buy = new Square_Button(100, 100, "Button.Potion.Lifesteal", "Texture.Shop.Magic.Normal", "Texture.Shop.Magic.Hover");
	lifesteal_potion_buy->set_translation(Vector_2D(600.f, 320.f));
	_game_objects[lifesteal_potion_buy->id()] = lifesteal_potion_buy;


	Game_Object* back_message = new Text_Message("Message.Back", "Back To Village ", 30, true, color);
	back_message->set_translation(Vector_2D(120.f, 700.f));
	_game_objects[back_message->id()] = back_message;
	Game_Object* back_button = new Square_Button(100, 40, "Button.Back", "Texture.Back.Normal", "Texture.Back.Hover");
	back_button->set_translation(Vector_2D(600.f, 700.f));
	_game_objects[back_button->id()] = back_button;
}

Magic_Shop_Scene::~Magic_Shop_Scene()
{
}

void Magic_Shop_Scene::update(SDL_Window*, Input* input, Save* save)
{
	bool click = input->is_button_state(Input::Button::CLICK, Input::Button_State::PRESSED);


	Square_Button* speed_potion = (Square_Button*)get_game_object("Button.Potion.Speed");
	Square_Button* lifesteal_potion = (Square_Button*)get_game_object("Button.Potion.Lifesteal");
	Square_Button* back_button = (Square_Button*)get_game_object("Button.Back");

	if (click)
	{
		if (speed_potion->mouse_above())
		{
			if ((save->_speed_potions + 2) * 50 <= save->_money)
			{
				save->_money -= (save->_speed_potions + 2) * 50;
				save->_speed_potions++;
				((Text_Message*)_game_objects["Message.Money"])->set_message("Money: " + std::to_string(save->_money));
				((Text_Message*)_game_objects["Message.Potion.Speed.Cost"])->set_message("Cost: " + std::to_string((save->_speed_potions + 2) * 50));
				((Text_Message*)_game_objects["Message.Potion.Speed.Owned"])->set_message("Owned: " + std::to_string(save->_speed_potions));
			}
		}
		else if (lifesteal_potion->mouse_above())
		{
			if ((save->_lifesteal_potions + 4) * 150 <= save->_money)
			{
				save->_money -= (save->_lifesteal_potions + 4) * 150;
				save->_lifesteal_potions++;
				((Text_Message*)_game_objects["Message.Money"])->set_message("Money: " + std::to_string(save->_money));
				((Text_Message*)_game_objects["Message.Potion.Lifesteal.Cost"])->set_message("Cost: " + std::to_string((save->_lifesteal_potions + 4) * 150));
				((Text_Message*)_game_objects["Message.Potion.Lifesteal.Owned"])->set_message("Owned: " + std::to_string(save->_lifesteal_potions));
			}
		}
		else if (back_button->mouse_above())
		{
			_scene_completed = true;
			_next_scene = nullptr;
			_destroy_on_complete = true;
		}
	}
	
}
