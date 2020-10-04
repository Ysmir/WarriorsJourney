#include "smith_shop_scene.h"
#include "text_message.h"
#include "square_button.h"

Smith_Shop_Scene::Smith_Shop_Scene(Save* save)
	: Scene("Shop.Smith")
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

	Game_Object* health_upgrade_message = new Text_Message("Message.Upgrade.Health", "Buy Health Upgrade", 40, true, color);
	health_upgrade_message->set_translation(Vector_2D(100.f, 100.f));
	_game_objects[health_upgrade_message->id()] = health_upgrade_message;
	Game_Object* health_upgrade_cost_message = new Text_Message("Message.Upgrade.Health.Cost", "Cost: " + std::to_string((save->_health_upgrades+2) * 25), 30, true, color);
	health_upgrade_cost_message->set_translation(Vector_2D(120.f, 150.f));
	_game_objects[health_upgrade_cost_message->id()] = health_upgrade_cost_message;
	Game_Object* health_upgrade_owned_message = new Text_Message("Message.Upgrade.Health.Owned", "Max Health: " + std::to_string((save->_health_upgrades+10) * 10), 30, true, color);
	health_upgrade_owned_message->set_translation(Vector_2D(120.f, 200.f));
	_game_objects[health_upgrade_owned_message->id()] = health_upgrade_owned_message;
	Game_Object* health_upgrade_buy = new Square_Button(100, 100, "Button.Upgrade.Health", "Texture.Shop.Smith.Normal", "Texture.Shop.Smith.Hover");
	health_upgrade_buy->set_translation(Vector_2D(600.f, 120.f));
	_game_objects[health_upgrade_buy->id()] = health_upgrade_buy;

	Game_Object* damage_upgrade_message = new Text_Message("Message.Upgrade.Damage", "Buy Damage Upgrades", 40, true, color);
	damage_upgrade_message->set_translation(Vector_2D(100.f, 300.f));
	_game_objects[damage_upgrade_message->id()] = damage_upgrade_message;
	Game_Object* damage_upgrade_cost_message = new Text_Message("Message.Upgrade.Damage.Cost", "Cost: " + std::to_string((save->_damage_upgrades + 2) * 50), 30, true, color);
	damage_upgrade_cost_message->set_translation(Vector_2D(120.f, 350.f));
	_game_objects[damage_upgrade_cost_message->id()] = damage_upgrade_cost_message;
	Game_Object* damage_upgrade_owned_message = new Text_Message("Message.Upgrade.Damage.Owned", "Damage: " + std::to_string(save->_damage_upgrades+10), 30, true, color);
	damage_upgrade_owned_message->set_translation(Vector_2D(120.f, 400.f));
	_game_objects[damage_upgrade_owned_message->id()] = damage_upgrade_owned_message;
	Game_Object* damage_upgrade_buy = new Square_Button(100, 100, "Button.Upgrade.Damage", "Texture.Shop.Smith.Normal", "Texture.Shop.Smith.Hover");
	damage_upgrade_buy->set_translation(Vector_2D(600.f, 320.f));
	_game_objects[damage_upgrade_buy->id()] = damage_upgrade_buy;

	Game_Object* attack_speed_upgrade_message = new Text_Message("Message.Upgrade.Attack.Speed", "Buy Attack Speed Upgrades", 40, true, color);
	attack_speed_upgrade_message->set_translation(Vector_2D(100.f, 500.f));
	_game_objects[attack_speed_upgrade_message->id()] = attack_speed_upgrade_message;
	Game_Object* attack_speed_upgrade_cost_message = new Text_Message("Message.Upgrade.Attack.Speed.Cost", "Cost: " + std::to_string((save->_attack_speed_upgrades + 2) * 100), 30, true, color);
	attack_speed_upgrade_cost_message->set_translation(Vector_2D(120.f, 550.f));
	_game_objects[attack_speed_upgrade_cost_message->id()] = attack_speed_upgrade_cost_message;
	Game_Object* attack_speed_upgrade_owned_message = new Text_Message("Message.Upgrade.Attack.Speed.Owned", "Attack Speed: " + std::to_string(100 + (save->_attack_speed_upgrades)) + "%", 30, true, color);
	attack_speed_upgrade_owned_message->set_translation(Vector_2D(120.f, 600.f));
	_game_objects[attack_speed_upgrade_owned_message->id()] = attack_speed_upgrade_owned_message;
	Game_Object* attack_speed_upgrade_buy = new Square_Button(100, 100, "Button.Upgrade.Attack.Speed", "Texture.Shop.Smith.Normal", "Texture.Shop.Smith.Hover");
	attack_speed_upgrade_buy->set_translation(Vector_2D(600.f, 520.f));
	_game_objects[attack_speed_upgrade_buy->id()] = attack_speed_upgrade_buy;

	Game_Object* back_message = new Text_Message("Message.Back", "Back To Village ", 30, true, color);
	back_message->set_translation(Vector_2D(120.f, 700.f));
	_game_objects[back_message->id()] = back_message;
	Game_Object* back_button = new Square_Button(100, 40, "Button.Back", "Texture.Back.Normal", "Texture.Back.Hover");
	back_button->set_translation(Vector_2D(600.f, 700.f));
	_game_objects[back_button->id()] = back_button;
}

Smith_Shop_Scene::~Smith_Shop_Scene()
{
}

void Smith_Shop_Scene::update(SDL_Window*, Input* input, Save* save)
{
	bool click = input->is_button_state(Input::Button::CLICK, Input::Button_State::PRESSED);


	Square_Button* health_upgrade = (Square_Button*)get_game_object("Button.Upgrade.Health");
	Square_Button* damage_upgrade = (Square_Button*)get_game_object("Button.Upgrade.Damage");
	Square_Button* attack_speed_upgrade = (Square_Button*)get_game_object("Button.Upgrade.Attack.Speed");
	Square_Button* back_button = (Square_Button*)get_game_object("Button.Back");

	if (click)
	{
		if (health_upgrade->mouse_above())
		{
			if ((save->_health_upgrades + 2) * 25 <= save->_money)
			{
				save->_money -= (save->_health_upgrades + 2) * 25;
				save->_health_upgrades++;
				((Text_Message*)_game_objects["Message.Money"])->set_message("Money: " + std::to_string(save->_money));
				((Text_Message*)_game_objects["Message.Upgrade.Health.Cost"])->set_message("Cost: " + std::to_string((save->_health_upgrades + 2) * 25));
				((Text_Message*)_game_objects["Message.Upgrade.Health.Owned"])->set_message("Max Health: " + std::to_string((save->_health_upgrades + 10) * 10));
			}
		}
		else if (damage_upgrade->mouse_above())
		{
			if ((save->_damage_upgrades + 2) * 50 <= save->_money)
			{
				save->_money -= (save->_damage_upgrades + 2) * 50;
				save->_damage_upgrades++;
				((Text_Message*)_game_objects["Message.Money"])->set_message("Money: " + std::to_string(save->_money));
				((Text_Message*)_game_objects["Message.Upgrade.Damage.Cost"])->set_message("Cost: " + std::to_string((save->_damage_upgrades + 2) * 50));
				((Text_Message*)_game_objects["Message.Upgrade.Damage.Owned"])->set_message("Damage: " + std::to_string(save->_damage_upgrades + 10));
			}
		}
		else if (attack_speed_upgrade->mouse_above())
		{
			if ((save->_attack_speed_upgrades + 2) * 100 <= save->_money)
			{
				save->_money -= (save->_attack_speed_upgrades + 2) * 100;
				save->_damage_upgrades++;
				((Text_Message*)_game_objects["Message.Money"])->set_message("Money: " + std::to_string(save->_money));
				((Text_Message*)_game_objects["Message.Upgrade.Attack.Speed.Cost"])->set_message("Cost: " + std::to_string((save->_attack_speed_upgrades + 2) * 100));
				((Text_Message*)_game_objects["Message.Upgrade.Attack.Speed.Owned"])->set_message("Attack Speed: " + std::to_string(100 + (save->_attack_speed_upgrades)) + "%");
			}
		}
		else if (back_button->mouse_above())
		{
			save->commit_save();
			_scene_completed = true;
			_next_scene = nullptr;
			_destroy_on_complete = true;
		}
	}

}
