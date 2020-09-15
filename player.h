#pragma once

#include <stack>

#include "animated_game_object.h"

class Player : public Animated_Game_Object
{
public:
	Player(std::string id);
	~Player();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;

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

private:
	void handle_enter_state(State state, Assets* assets);
	void handle_exit_state(State state, Assets* assets);

	float _speed;
	std::stack<State> _state;

	Uint32 _damage_invulnerability_timer;
	Uint32 _damage_invulnerability_length;

	Uint32 _attack_timer;
	bool _attack_triggered;
	float _attack_range;
	float _knockback_strength;
};