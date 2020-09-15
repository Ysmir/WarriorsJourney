#include "goblin.h"
#include "player.h"

Goblin::Goblin(std::string id)
	: Animated_Game_Object(id, "Texture.Goblin.Walking")
{
	_width = 64;
	_height = 64;

	_translation = Vector_2D(0, 0);
	_velocity = Vector_2D(0.f, 0.f);

	_collider.set_translation(Vector_2D(_width / 2.0f, _height / 1.5f));
	_collider.set_radius(_width / 3.f);

	_state.push(State::Idle);
	_mass = 100.f;
	_speed = 0.1f;

	_damage_length = 1000;
}

Goblin::~Goblin()
{
}

void Goblin::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input*, Scene* scene)
{

	if (_damage_timer > 0)
	{
		if (_damage_timer < milliseconds_to_simulate)
		{
			_damage_timer = 0;
			_blue_filter = 255;
			_green_filter = 255;
		}
		else
		{
			_damage_timer -= milliseconds_to_simulate;

			Uint8 non_red_filter = (Uint8)(255 - 192 * _damage_timer / _damage_length);
			_blue_filter = non_red_filter;
			_green_filter = non_red_filter;
		}
	}

	Player* player = (Player*)scene->get_game_object("Player");
	float distance_to_player = ((player->translation() + player->collider().translation()) - (_translation + _collider.translation())).magnitude();

	switch (_state.top())
	{
	case State::Idle:
		if (_health <= 0) {
			push_state(State::Death, assets);
		}
		else if (distance_to_player < 600.f)
		{
			push_state(State::Walking, assets);
		}
		break;
	case State::Walking:
		if (_health <= 0) {
			push_state(State::Death, assets);
		}
		else if (distance_to_player < 100.f)
		{
			push_state(State::Walking, assets);
		}
		break;
	case State::Attack:
		_attack_timer += milliseconds_to_simulate;
		if (_health <= 0) {
			push_state(State::Death, assets);
		}
		break;
	}
}

void Goblin::push_state(State state, Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets);
}

void Goblin::pop_state(Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets);
}

void Goblin::handle_enter_state(State state, Assets* )
{
	switch (state)
	{
	case State::Idle:
		_speed = 0.f;
		break;
	case State::Walking:
		_texture_id = "Texture.Goblin.Walking";
		_speed = 0.15f;
		break;
	case State::Attack:
		_texture_id = "Texture.Goblin.Attack";
		_speed = 0.05f;
		_attack_timer = 0;
		_attack_triggered = false;
		break;
	case State::Death:
		_texture_id = "Texture.Goblin.Death";
		_speed = 0.f;
		break;
	}
}

void Goblin::handle_exit_state(State state, Assets* )
{
	switch (state)
	{
	case State::Idle:
		break;
	case State::Walking:
		break;
	case State::Attack:
		break;
	case State::Death:
		break;
	}
}
