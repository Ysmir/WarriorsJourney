#include "goblin.h"
#include "player.h"

Goblin::Goblin(std::string id)
	: Animated_Game_Object(id, "Texture.Goblin.Walking")
{
	_width = 66;
	_height = 64;

	_translation = Vector_2D(0, 0);
	_velocity = Vector_2D(0.f, 0.f);

	_collider.set_translation(Vector_2D(_width / 2.0f, _height / 1.6f));
	_collider.set_radius(_width / 4.f);

	_state.push(State::Idle);
	_mass = 100.f;
	_speed = 0.01f;

	_max_health = 30;
	_current_health = _max_health;

	_damage_length = 1000;
	_attack_range = 35.f;
}

Goblin::~Goblin()
{
}

void Goblin::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input*, Scene* scene)
{
	_velocity = Vector_2D(0, 0);

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
		if (_current_health <= 0) {
			push_state(State::Death, assets, scene);
		}
		else if (distance_to_player < 600.f)
		{
			push_state(State::Walking, assets, scene);
		}
		break;
	case State::Walking:
		if (_current_health <= 0) {
			push_state(State::Death, assets, scene);
		}
		else if (distance_to_player < (_attack_range + player->collider().radius()))
		{
			push_state(State::Attack, assets, scene);
		}
		else
		{
			_velocity = (player->translation() + player->collider().translation()) - (_translation + _collider.translation());
			_velocity.normalize();
			_velocity.scale(_speed);
		}
		break;
	case State::Attack:
		_attack_timer += milliseconds_to_simulate;
		if (_current_health <= 0) {
			push_state(State::Death, assets, scene);
		}
		else if (_attack_timer >= 200 && !_attack_triggered)
		{
			_attack_triggered = true;

			Circle_2D attack_collider = Circle_2D(_attack_range, _collider.translation() + _translation);
			Circle_2D player_collider = Circle_2D(player->collider().radius(),
				player->collider().translation() + player->translation());
			float intersection_depth = attack_collider.intersection_depth(player_collider);

			if (_flip == SDL_FLIP_NONE && player_collider.translation().x() > attack_collider.translation().x() || 
				_flip != SDL_FLIP_NONE && player_collider.translation().x() < attack_collider.translation().x())
			{
				if (intersection_depth > 0.0f)
				{
					player->damage(10);
				}
			}
		}
		else if (_attack_timer >= 400)
		{
			pop_state(assets, scene);
		}
		break;
	}
}

void Goblin::push_state(State state, Assets* assets, Scene* scene)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets, scene);
}

void Goblin::pop_state(Assets* assets, Scene* scene)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets, scene);
}

void Goblin::handle_enter_state(State state, Assets* , Scene* scene)
{
	switch (state)
	{
	case State::Idle:
		_speed = 0.f;
		break;
	case State::Walking:
		_texture_id = "Texture.Goblin.Walking";
		_total_time_milliseconds = 0;
		_speed = 0.15f;
		break;
	case State::Attack:
		_texture_id = "Texture.Goblin.Attack";
		_total_time_milliseconds = 0;
		_speed = 0.05f;
		_attack_timer = 0;
		_attack_triggered = false;
		{
			Player* player = (Player*)scene->get_game_object("Player");
			if (player->collider().translation().x() + player->translation().x() < _collider.translation().x() + _translation.x())
			{
				_flip = SDL_FLIP_HORIZONTAL;
			}
			else
			{
				_flip = SDL_FLIP_NONE;
			}
		}
		break;
	case State::Death:
		_texture_id = "Texture.Goblin.Death";
		_total_time_milliseconds = 0;
		_speed = 0.f;
		_collider.set_radius(0.f);
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
		_collider.set_radius(_width / 4.f);
		break;
	}
}
