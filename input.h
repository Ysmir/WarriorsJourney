#pragma once

#include <map>

class Input
{
public:
	Input();
	~Input();

	enum class Button
	{
		QUIT,
		PAUSE,

		UP,
		DOWN,
		LEFT,
		RIGHT,

		RUNNING,
		ATTACK,

		INCREASE_SPEED,
		DECREASE_SPEED,

		SHOW_CREDITS,
		SHOW_LIBS,
		TOGGLE_IDS,
		TOGGLE_POS,
		TOGGLE_COLLIDERS,

		SNAIL_SPEED
	};

	enum class Button_State
	{
		PRESSED,
		DOWN,
		RELEASED,
		UP
	};

	void get_input();
	bool is_button_state(Button type, Button_State state);

private:
	std::map<Button, Button_State> _button_state;
};