#include <iostream>
#include <chrono>
#include <thread>

#include "configuration.h"
#include "engine.h"
#include "game_scene.h"
#include "input.h"
#include "editor.h"

int main(void)
{
	Configuration* config = new Configuration();
	Engine* engine		= new Engine("Game", config);
	Assets* assets		= new Assets(engine->renderer());
	Scene* game_scene   = new Game_Scene();
	Input* input		= new Input();
	Editor* editor		= new Editor(L"Game");

	const Uint32 milliseconds_per_second = 1000;
	const Uint32 frames_per_second		 = 60;
	const Uint32 frame_time_ms			 = milliseconds_per_second/ frames_per_second;

	Uint32 frame_start_time_ms = 0;
	Uint32 frame_end_time_ms = frame_time_ms;
	while (!input->is_button_state(Input::Button::QUIT, Input::Button_State::PRESSED))
	{
		Uint32 previous_frame_duration = frame_end_time_ms - frame_start_time_ms;
		frame_start_time_ms			   = SDL_GetTicks();
		
		game_scene->update(engine->window());
		input->get_input();
		editor->update(input, game_scene, config);
		engine->simulate(previous_frame_duration, assets, game_scene, input, config);

		const Uint32 current_time_ms = SDL_GetTicks();
		const Uint32 frame_duration_ms = current_time_ms - frame_start_time_ms;
		if (frame_duration_ms < frame_time_ms)
		{
			const Uint32 time_to_sleep_for = frame_time_ms - frame_duration_ms;
			std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep_for));
		}

		frame_end_time_ms = SDL_GetTicks();
	}

	return 0;
}