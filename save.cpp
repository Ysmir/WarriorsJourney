#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "save.h"

Save::Save()
{
	_money = 0;
	_health_upgrades = 0;
	_damage_upgrades = 0;
	_attack_speed_upgrades = 0;
	_speed_potions = 0;
	_lifesteal_potions = 0;

	_save_changed = false;

	_save_file = "";
}

Save::~Save()
{
}

void Save::load_save(std::string save_file)
{
	_save_file = save_file;

	std::string line;
	std::ifstream save(save_file);

	if (save.is_open())
	{
		while (std::getline(save, line))
		{
			std::istringstream line_string_stream(line);
			std::string property;
			line_string_stream >> property;
			if (property == "money")
			{
				int money;
				line_string_stream >> money;
				std::cout << money;
				_money = money;
			}
			else if (property == "health_upgrades")
			{
				int upgrades;
				line_string_stream >> upgrades;
				std::cout << upgrades;
				_health_upgrades = upgrades;
			}
			else if (property == "damage_upgrades")
			{
				int upgrades;
				line_string_stream >> upgrades;
				std::cout << upgrades;
				_damage_upgrades = upgrades;
			}
			else if (property == "attack_speed_upgrades")
			{
				int upgrades;
				line_string_stream >> upgrades;
				std::cout << upgrades;
				_attack_speed_upgrades = upgrades;
			}

		}
		save.close();
	}
}

void Save::commit_save()
{
	if (_save_file != "")
	{
		std::string line;
		std::ofstream save(_save_file);

		if (save.is_open())
		{
			save << "money " << _money << std::endl;
			save << "health_upgrades " << _health_upgrades << std::endl;
			save << "damage_upgrades " << _damage_upgrades << std::endl;
			save << "attack_speed_upgrades " << _attack_speed_upgrades << std::endl;
		}
	}
}
