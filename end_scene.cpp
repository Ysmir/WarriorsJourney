#include "end_scene.h"
#include "end_interface.h"

End_Scene::End_Scene(int score, float level)
	: Scene("End")
{
	_red = 63;
	_green = 63;
	_blue = 63;

	Game_Object* end_interface = new End_Interface(score, (int)level);
	_game_objects[end_interface->id()] = end_interface;
}

End_Scene::~End_Scene()
{
}

void End_Scene::update(SDL_Window* , Input* input)
{
	bool click = input->is_button_state(Input::Button::CLICK, Input::Button_State::PRESSED);
	if (click)
	{
		_scene_completed = true;
		_next_scene = nullptr;
		_destroy_on_complete = true;
	}
}
