#pragma once

#include <stack>

#include "animated_game_object.h"

class Player : public Animated_Game_Object
{
public:
	Player(std::string id);
	~Player();

	void load_save(Save* save);

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

	void set_speed(float speed);
	float speed();

	enum class State
	{
		Idle,
		Walking,
		Running,
		Death,
		Attack
	};
	void push_state(State state, Assets* assets);
	void pop_state(Assets* assets);

	virtual bool damage(int damage) override;
	void trigger_lifesteal(int heal_amount);

private:
	void handle_enter_state(State state, Assets* assets);
	void handle_exit_state(State state, Assets* assets);

	float _base_speed;
	float _speed;
	std::stack<State> _state;

	int _damage;
	int _attack_speed;

	Uint32 _damage_invulnerability_timer;
	Uint32 _damage_invulnerability_length;

	Uint32 _attack_timer;
	bool _attack_triggered;
	float _attack_range;
	float _knockback_strength;
	int _lifesteal;
};