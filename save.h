#pragma once
#include <string>

class Save
{
public:
	Save();
	~Save();

	void load_save(std::string save_file);
	void commit_save();

	int _money;
	int _health_upgrades;
	int _damage_upgrades;
	int _attack_speed_upgrades;
	int _speed_potions;
	int _lifesteal_potions;

	bool _save_changed;

private:
	std::string _save_file;
};