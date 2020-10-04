#include "text_message.h"

Text_Message::Text_Message(std::string id, std::string message, int font_size, bool static_translation, SDL_Color color)
	: Game_Object(id, "Texture.Dino")
{
	_message = message;
	_font_size = font_size;
	_static_translation = static_translation;
	_color = color;
}

Text_Message::~Text_Message()
{
}

void Text_Message::simulate_AI(Uint32 , Assets* , Input* , Scene* )
{
}

void Text_Message::render(Uint32 , Assets* , SDL_Renderer* renderer, Configuration* , Scene* scene)
{
	Text message(renderer, _message.c_str(), _color, _id + ".Text", _font_size);

	if (_static_translation)
	{
		message.render(renderer, _translation);
	}
	else
	{
		message.render(renderer, _translation + scene->camera_translation());
	}
	
}

void Text_Message::set_message(std::string message)
{
	_message = message;
}
