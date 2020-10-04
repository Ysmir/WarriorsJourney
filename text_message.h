#pragma once

#include "game_object.h"
#include "text.h"

class Text_Message : public Game_Object
{
public:
	Text_Message(std::string id, std::string message, int font_size, bool static_translation, SDL_Color color);
	~Text_Message();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

	void set_message(std::string message);

private:
	std::string _message;
	bool _static_translation;
	int _font_size;
	SDL_Color _color;
};
