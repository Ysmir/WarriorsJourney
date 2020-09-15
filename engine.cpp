#include <iostream>
#include <algorithm>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "engine.h"
#include "texture.h"
#include "animated_texture.h"
#include "game_object.h"

Engine::Engine(std::string window_name, Configuration* config)
{	
	int init_result			= SDL_Init(0);
	int init_result_success = 0;
	if (init_result != init_result_success)
	{
		std::cout << "Failed to initialize SDL" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const char* game_title = window_name.c_str();
	const int x			   = 100;
	const int y			   = 100;

	_window = SDL_CreateWindow(game_title, x, y, config->window_width, config->window_height, SDL_WINDOW_RESIZABLE);
	if (_window == nullptr)
	{
		std::cout << "Failed to create SDL Window" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	_renderer = SDL_CreateRenderer(_window, -1, 0);
	if (_renderer == nullptr)
	{
		std::cout << "Failed to create SDL Renderer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const int image_init_result = IMG_Init(IMG_INIT_PNG);
	const int image_init_success = IMG_INIT_PNG;
	if (image_init_result != image_init_success)
	{
		std::cout << "Failed to initialize SDL Image" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const int ttf_init_result = TTF_Init();
	const int ttf_init_success = 0;
	if (ttf_init_result != ttf_init_success)
	{
		std::cout << "Failed to initialize SDL TTF" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const int mixer_init_result = Mix_Init(MIX_INIT_MOD);
	const int mixer_init_failure = 0;
	if (mixer_init_result == mixer_init_failure)
	{
		std::cout << "Failed to initialize SDL mixer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		std::cout << "Mixer Error: " << Mix_GetError() << std::endl;
		exit(1);
	}

	const int mixer_open_audio_result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	const int mixer_open_audio_success = 0;
	if (mixer_open_audio_result != mixer_open_audio_success)
	{
		std::cout << "Failed to open audio" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	Mix_AllocateChannels(3);
}

Engine::~Engine()
{
}

void Engine::simulate(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Input* input, Configuration* config)
{
	if (!scene->pause())
	{
		simulate_AI(milliseconds_to_simulate, assets, scene, input);
		simulate_physics(milliseconds_to_simulate, assets, scene);
	}
	render(milliseconds_to_simulate, assets, scene, config);
}

SDL_Renderer* Engine::renderer()
{
	return _renderer;
}

SDL_Window* Engine::window()
{
	return _window;
}

void Engine::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Input* input)
{
	std::vector<Game_Object*> game_objects = scene->get_game_objects();
	for (Game_Object* game_object : game_objects)
	{
		game_object->simulate_AI(milliseconds_to_simulate, assets, input, scene);
	}
}

void Engine::simulate_physics(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene)
{
	std::vector<Game_Object*> game_objects = scene->get_game_objects();
	for (Game_Object* game_object : game_objects)
	{
		game_object->simulate_physics(milliseconds_to_simulate, assets, scene);
	}
}

void Engine::render(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Configuration* config)
{
	int render_clear_result  = SDL_RenderClear(_renderer);
	int render_clear_success = 0;
	if (render_clear_result != render_clear_success)
	{
		std::cout << "Failed to clear renderer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const Uint8 red   = 127;
	const Uint8 green = 255;
	const Uint8 blue  = 0;
	const Uint8 alpha = 255;

	int render_color_result = SDL_SetRenderDrawColor(_renderer, red, green, blue, alpha);
	int render_color_success = 0;
	if (render_color_result != render_color_success)
	{
		std::cout << "Failed to set render color" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	assets->reset_animated_textures();

	std::vector<Game_Object*> sorted_game_objects = scene->get_game_objects();
	const struct
	{
		bool operator()(Game_Object* a, Game_Object* b)
		{
			return a->translation().y() < b->translation().y();
		}
	} sort_by_y_order;
	std::sort(sorted_game_objects.begin(), sorted_game_objects.end(), sort_by_y_order);

	for (Game_Object* game_object : sorted_game_objects)
	{
		game_object->render(milliseconds_to_simulate, assets, _renderer, config, scene);
	}

	SDL_RenderPresent(_renderer);
}
