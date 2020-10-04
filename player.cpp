#include <cstdlib>

#include "player.h"
#include "sound.h"

Player::Player(std::string id)
	: Animated_Game_Object(id, "Texture.Player.Idle")
{
	_width = 204;
	_height = 136;

	_translation = Vector_2D(0, 0);
	_base_speed = 0.15f;
	_speed = 0.15f;

	_damage = 10;
	_attack_speed = 100;

	_collider.set_radius(_width / 7.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, _height * 0.7f));
	
	_state.push(State::Idle);
	_max_health = 100;
	_current_health = 100;

	_damage_invulnerability_timer = 0;
	_damage_invulnerability_length = 1000;
	_attack_range = 95.f;
	_knockback_strength = 20.f;
}

Player::~Player()
{
}

void Player::load_save(Save* save)
{
	_max_health = 100 + save->_health_upgrades * 10;
	_current_health = _max_health;
	_damage = 10 + save->_damage_upgrades;
	_base_speed = 0.15f * (100.f + ((float) save->_speed_potions)*5) / 100.f;
	_attack_speed = 100 + save->_attack_speed_upgrades;
	_lifesteal = save->_lifesteal_potions;
}

void Player::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene)
{
	if (_damage_invulnerability_timer > 0)
	{
		if (_damage_invulnerability_timer < milliseconds_to_simulate)
		{
			_damage_invulnerability_timer = 0;
			_blue_filter = 255;
			_green_filter = 255;
		}
		else
		{
			_damage_invulnerability_timer -= milliseconds_to_simulate;

			Uint8 non_red_filter = (Uint8)(255 - 192 * _damage_invulnerability_timer / _damage_invulnerability_length);
			_blue_filter = non_red_filter;
			_green_filter = non_red_filter;
		}
	}

	switch (_state.top())
	{
	case State::Idle:
		if (_current_health <=0) {
			push_state(State::Death, assets);
		}
		else if (input->is_button_state(Input::Button::ATTACK, Input::Button_State::DOWN))
		{
			push_state(State::Attack, assets);
		}
		else if (input->is_button_state(Input::Button::RUNNING, Input::Button_State::DOWN) && _velocity.magnitude() > 0.0f)
		{
			push_state(State::Running, assets);
		} 
		else if (_velocity.magnitude() > 0.0f)
		{
			push_state(State::Walking, assets);
		}
		break;
	case State::Walking:
		if (_current_health <= 0) {
			push_state(State::Death, assets);
		}
		else if (input->is_button_state(Input::Button::ATTACK, Input::Button_State::DOWN))
		{
			push_state(State::Attack, assets);
		}
		else if (_velocity.magnitude() == 0.0f)
		{
			pop_state(assets);
		}
		else if (input->is_button_state(Input::Button::RUNNING, Input::Button_State::DOWN))
		{
			push_state(State::Running, assets);
		}
		break;
	case State::Running:
		if (_current_health <= 0) {
			push_state(State::Death, assets);
		}
		else if (input->is_button_state(Input::Button::ATTACK, Input::Button_State::DOWN))
		{
			push_state(State::Attack, assets);
		}
		else if (_velocity.magnitude() == 0.0f)
		{
			pop_state(assets);
		}
		else if (input->is_button_state(Input::Button::RUNNING, Input::Button_State::RELEASED))
		{
			pop_state(assets);
		}
		break;
	case State::Attack:
		_attack_timer += milliseconds_to_simulate * _attack_speed/100;
		if (_current_health <= 0) {
			push_state(State::Death, assets);
		}
		else if (_attack_timer >= 360 && !_attack_triggered)
		{
			_attack_triggered = true;

			for (Game_Object* game_object : scene->get_game_objects())
			{
				if (game_object->id() == _id)
				{
					continue;
				}

				Circle_2D attack_collider = Circle_2D(_attack_range, _collider.translation() + _translation);
				Circle_2D enemy_collider = Circle_2D(game_object->collider().radius(),
					game_object->collider().translation() + game_object->translation());
				float intersection_depth = attack_collider.intersection_depth(enemy_collider);

				if (_flip == SDL_FLIP_NONE)
				{
					if (enemy_collider.translation().x() < attack_collider.translation().x())
					{
						continue;
					}
				}
				else
				{
					if (enemy_collider.translation().x() > attack_collider.translation().x())
					{
						continue;
					}
				}

				if (intersection_depth > 0.0f)
				{
					if (game_object->damage(_damage) && !game_object->immovable())
					{
						Vector_2D knockback = ((game_object->translation() + game_object->collider().translation()) - (_translation + _collider.translation()));
						knockback.normalize();
						knockback.scale(_mass/(_mass + game_object->mass()) * _knockback_strength);
						game_object->set_translation(game_object->translation() + knockback);
					}
				}
			}
		}
		else if (_attack_timer >= 840)
		{
			pop_state(assets);
		}
		break;
	case State::Death:
		break;
	}

	_velocity = Vector_2D(0, 0);
	if (input->is_button_state(Input::Button::UP, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(0, -1.0f);
	}
	
	if (input->is_button_state(Input::Button::DOWN, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(0, 1.0f);
	}
	
	if (input->is_button_state(Input::Button::LEFT, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(-1.0f, 0);
	}

	if (input->is_button_state(Input::Button::RIGHT, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(1.0f, 0);
	}

	_velocity.normalize();
	_velocity.scale(_speed);
}

void Player::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Uint32 milliseconds_to_animate = milliseconds_to_simulate;
	if (_state.top() == State::Attack) milliseconds_to_animate = milliseconds_to_animate * _attack_speed / 100;
	Animated_Game_Object::render(milliseconds_to_animate, assets, renderer, config, scene);
}

void Player::set_speed(float speed)
{
	_speed = speed;
}

float Player::speed()
{
	return _speed;
}

void Player::push_state(State state, Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets);
}

void Player::pop_state(Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets);
}

bool Player::damage(int damage)
{
	if (_damage_invulnerability_timer == 0 && damage > 0 && _current_health > 0)
	{
		_current_health -= damage;
		_damage_invulnerability_timer = _damage_invulnerability_length;
		return true;
	}
	return false;
}

void Player::trigger_lifesteal(int heal_amount)
{
	if (rand() % 100 < _lifesteal)
	{
		_current_health += heal_amount;
		if (_current_health > _max_health)
		{
			_current_health = _max_health;
		}
	}
}

void Player::handle_enter_state(State state, Assets* assets)
{
	switch (state)
	{
	case State::Idle:
		_texture_id = "Texture.Player.Idle";
		_total_time_milliseconds = 0;
		break;
	case State::Walking:
	{
		_texture_id = "Texture.Player.Walking";
		_total_time_milliseconds = 0;
		_speed = _base_speed;
		const int walking_channel = 1;
		Sound* sound = (Sound*)assets->get_asset("Sound.Walking");
		Mix_PlayChannel(walking_channel, sound->data(), -1);
		break;
	}
	case State::Running:
	{
		_texture_id = "Texture.Player.Running";
		_total_time_milliseconds = 0;
		_speed = _base_speed*2;
		const int running_channel = 1;
		Sound* sound = (Sound*)assets->get_asset("Sound.Running");
		Mix_PlayChannel(running_channel, sound->data(), -1);
		break;
	}
	case State::Attack:
	{
		_texture_id = "Texture.Player.Attack";
		_total_time_milliseconds = 0;
		_speed = _base_speed * 0.25f;
		_attack_timer = 0;
		_attack_triggered = false;
		const int attack_channel = 2;
		Sound* sound = (Sound*)assets->get_asset("Sound.Attack");
		Mix_PlayChannel(attack_channel, sound->data(), 0);
		break;
	}
	case State::Death:
	{
		_texture_id = "Texture.Player.Death";
		_total_time_milliseconds = 0;
		_speed = 0.f;
		const int death_channel = 2;
		Sound* sound = (Sound*)assets->get_asset("Sound.Death");
		Mix_PlayChannel(death_channel, sound->data(), 0);
		break;
	}
	}
}

void Player::handle_exit_state(State state, Assets* )
{
	switch (state)
	{
	case State::Idle:
		break;
	case State::Walking:
	{
		const int walking_channel = 1;
		Mix_HaltChannel(walking_channel);
		break;
	}
	case State::Running:
	{
		const int running_channel = 1;
		Mix_HaltChannel(running_channel);
		break;
	}
	case State::Attack:
	{
		const int attack_channel = 2;
		Mix_HaltChannel(attack_channel);
		break;
	}
	case State::Death:
		const int death_channel = 2;
		Mix_HaltChannel(death_channel);
		break;
	}
}
