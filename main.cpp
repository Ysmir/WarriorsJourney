#include <iostream>
#include <chrono>
#include <thread>
#include <stack>

#include "configuration.h"
#include "engine.h"
#include "game_scene.h"
#include "village_scene.h"
#include "input.h"
#include "editor.h"
#include "save.h"

int main(void)
{
	Configuration* config = new Configuration();
	Engine* engine		= new Engine("Game", config);
	Assets* assets		= new Assets(engine->renderer());
	Input* input		= new Input();
	Editor* editor		= new Editor(L"Game");
	Save* save			= new Save();

	save->load_save("Saves/save_1.txt");

	std::stack<Scene*> scenes;
	scenes.push(new Village_Scene(save));

	const Uint32 milliseconds_per_second = 1000;
	const Uint32 frames_per_second		 = 60;
	const Uint32 frame_time_ms			 = milliseconds_per_second/ frames_per_second;

	Uint32 frame_start_time_ms = 0;
	Uint32 frame_end_time_ms = frame_time_ms;
	while (!input->is_button_state(Input::Button::QUIT, Input::Button_State::PRESSED))
	{
		Uint32 previous_frame_duration = frame_end_time_ms - frame_start_time_ms;
		frame_start_time_ms			   = SDL_GetTicks();
		
		input->get_input();

		if (scenes.top()->scene_completed())
		{
			Scene* next_scene = scenes.top()->next_scene();
			if (scenes.top()->destroy_on_complete())
			{
				scenes.pop();
			}
			else
			{
				scenes.top()->set_scene_completed(false);
			}
			if (next_scene != nullptr)
			{
				scenes.push(next_scene);
			}
		}

		scenes.top()->update(engine->window(), input, save);
		editor->update(input, scenes.top(), config);
		engine->simulate(previous_frame_duration, assets, scenes.top(), input, config);

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