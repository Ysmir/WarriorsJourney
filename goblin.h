#pragma once

#include <stack>

#include "animated_game_object.h"

class Goblin : public Animated_Game_Object
{
public:
	Goblin(std::string id);
	~Goblin();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;

	enum class State
	{
		Idle,
		Walking,
		Death,
		Attack
	};
	void push_state(State state, Assets* assets);
	void pop_state(Assets* assets);

private:
	void handle_enter_state(State state, Assets* assets);
	void handle_exit_state(State state, Assets* assets);

	float _speed;
	std::stack<State> _state;

	Uint32 _attack_timer;
	bool _attack_triggered;
};