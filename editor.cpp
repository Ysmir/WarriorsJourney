#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_syswm.h>

#include "editor.h"
#include "resource.h"
#include "player.h"
#include "snail.h"

Editor::Editor(std::wstring window_name)
{
	_window = FindWindow(NULL, window_name.c_str());
	if (_window == NULL)
	{
		std::cout << "Failed to find window. Window Name: " << window_name.c_str() << std::endl;
		exit(1);
	}

	_menu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
	if (_menu == NULL)
	{
		std::cout << "Failed to create menu." << std::endl;
		exit(1);
	}

	BOOL set_menu_result = SetMenu(_window, _menu);
	if (set_menu_result == 0)
	{
		std::cout << "Failed to set menu." << std::endl;
		exit(1);
	}

	Uint8 event_state_result  = SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
	Uint8 event_state_success = SDL_DISABLE;
	if (event_state_result != event_state_success)
	{
		std::cout << "Failed to enable Windows event state." << std::endl;
		exit(1);
	}
}

Editor::~Editor()
{
}

INT_PTR CALLBACK Dialog_Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			EndDialog(hwnd, IDOK);
			break;
		}
		break;
	default:
		return false;
	}
	return true;
}

void Editor::update(Input* input, Scene* scene, Configuration* config)
{
	if (input->is_button_state(Input::Button::DECREASE_SPEED, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("Player");
		player->set_speed(player->speed() / 1.2f);
	}
	if (input->is_button_state(Input::Button::INCREASE_SPEED, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("Player");
		player->set_speed(player->speed() * 1.2f);
	}

	if (input->is_button_state(Input::Button::SHOW_CREDITS, Input::Button_State::PRESSED))
	{
		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG1), _window, Dialog_Proc);
	}
	if (input->is_button_state(Input::Button::SHOW_LIBS, Input::Button_State::PRESSED))
	{
		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG2), _window, Dialog_Proc);
	}
	if (input->is_button_state(Input::Button::TOGGLE_IDS, Input::Button_State::PRESSED))
	{
		config->should_display_ids = !config->should_display_ids;
	}
	if (input->is_button_state(Input::Button::TOGGLE_POS, Input::Button_State::PRESSED))
	{
		config->should_display_pos = !config->should_display_pos;
	}
	if (input->is_button_state(Input::Button::TOGGLE_COLLIDERS, Input::Button_State::PRESSED))
	{
		config->should_display_colliders = !config->should_display_colliders;
	}

	if (input->is_button_state(Input::Button::SNAIL_SPEED, Input::Button_State::PRESSED))
	{
		Snail* snail = (Snail*)scene->get_game_object("Snail");
		snail->setFast(!snail->fast());
	}

	if (input->is_button_state(Input::Button::PAUSE, Input::Button_State::PRESSED))
	{
		scene->set_pause(!scene->pause());
	}
}