#include <sstream>

#include "game_object.h"
#include "texture.h"
#include "text.h"

Game_Object::Game_Object(std::string id, std::string texture_id)
	: _translation(0, 0), _velocity(0, 0), _collider(0.f, Vector_2D(0.f, 0.f))
{
	_id = id;
	_texture_id = texture_id;

	_width = 100;
	_height = 100;

	_mass = 100.f;
	_max_health = 100;
	_current_health = _max_health;

	_flip = SDL_FLIP_NONE;

	_damage_timer = 0;
	_damage_length = 0;
	
	_red_filter = 255;
	_blue_filter = 255;
	_green_filter = 255;
}

Game_Object::~Game_Object()
{
}

std::string Game_Object::id()
{
	return _id;
}

Vector_2D Game_Object::translation()
{
	return _translation;
}

void Game_Object::set_translation(Vector_2D translation)
{
	_translation = translation;
}

Vector_2D Game_Object::velocity()
{
	return _velocity;
}

Circle_2D Game_Object::collider()
{
	return _collider;
}

int Game_Object::width()
{
	return _width;
}

int Game_Object::height()
{
	return _height;
}

float Game_Object::mass()
{
	return _mass;
}

bool Game_Object::damage(int damage)
{
	if (_current_health > 0)
	{
		_current_health -= damage;
		_damage_timer = _damage_length;
		return true;
	}
	return false;
}

int Game_Object::max_health()
{
	return _max_health;
}

int Game_Object::current_health()
{
	return _current_health;
}

void Game_Object::simulate_physics(Uint32 milliseconds_to_simulate, Assets*, Scene* scene)
{
	Vector_2D velocity = _velocity;
	velocity.scale((float)milliseconds_to_simulate);

	_translation += velocity;

	for (Game_Object* game_object : scene->get_game_objects())
	{
		if (game_object->id() == _id)
		{
			continue;
		}

		Circle_2D collider = Circle_2D(_collider.radius(), _collider.translation() + _translation);
		Circle_2D other_collider = Circle_2D(game_object->collider().radius(), 
			game_object->collider().translation() + game_object->translation());
		float intersection_depth = collider.intersection_depth(other_collider);

		if (intersection_depth > 0.0f)
		{
			float total_mass = _mass + game_object->mass();

			Vector_2D other_collider_to_collider = collider.translation() - other_collider.translation();
			other_collider_to_collider.normalize();
			other_collider_to_collider.scale(intersection_depth * (1 - _mass/total_mass));
			_translation += other_collider_to_collider;

			Vector_2D collider_to_other_collider = other_collider.translation() - collider.translation();
			collider_to_other_collider.normalize();
			collider_to_other_collider.scale(intersection_depth * (1 - game_object->mass() / total_mass));
			game_object->_translation += collider_to_other_collider;
		}
	}
}

void Game_Object::render(Uint32, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	SDL_Rect destination;
	destination.x = (int)(_translation.x() - scene->camera_translation().x());
	destination.y = (int)(_translation.y() - scene->camera_translation().y());
	destination.w = _width;
	destination.h = _height;

	const float PI = 3.14159265f;
	if (_velocity.magnitude() > 0)
	{
		if (abs(_velocity.angle()) < (PI / 2.f))
		{
			_flip = SDL_FLIP_NONE;
		}
		else if (abs(_velocity.angle()) > (PI / 2.f))
		{
			_flip = SDL_FLIP_HORIZONTAL;
		}
	}

	Texture* texture = (Texture*)assets->get_asset(_texture_id);
	SDL_SetTextureColorMod(texture->data(), _red_filter, _blue_filter, _green_filter);
	texture->render(renderer, nullptr, &destination, _flip);
	SDL_SetTextureColorMod(texture->data(), 255, 255, 255);


	if (config->should_display_ids)
	{
		SDL_Color text_color;
		text_color.r = 255;
		text_color.g = 0;
		text_color.b = 63;
		text_color.a = 255;

		Text id(renderer, _id.c_str(), text_color, "ID.Text");

		id.render(renderer, _translation + Vector_2D((float)_width / 2, (float)_height) - scene->camera_translation());
	}
	if (config->should_display_pos)
	{
		SDL_Color text_color;
		text_color.r = 255;
		text_color.g = 0;
		text_color.b = 63;
		text_color.a = 255;

		std::stringstream pos_stream;
		pos_stream << (int)_translation.x() << ", " << (int)_translation.y();

		Text pos(renderer, pos_stream.str().c_str(), text_color, "Pos.Text");

		pos.render(renderer, _translation + Vector_2D((float)_width / 2, (float)_height) - scene->camera_translation());
	}
	if (config->should_display_colliders && _collider.radius() > 0.f)
	{
		Texture* collider_texture = (Texture*)assets->get_asset("Texture.Collider");

		SDL_Rect collider_destination;
		collider_destination.x = (int)(_translation.x() + _collider.translation().x() - _collider.radius() - scene->camera_translation().x());
		collider_destination.y = (int)(_translation.y() + _collider.translation().y() - _collider.radius() - scene->camera_translation().y());
		collider_destination.w = (int)(_collider.radius() * 2.0f);
		collider_destination.h = (int)(_collider.radius() * 2.0f);

		collider_texture->render(renderer, nullptr, &collider_destination, SDL_FLIP_NONE);
	}
}
