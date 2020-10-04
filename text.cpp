#include <iostream>

#include <SDL_ttf.h>

#include "text.h"

Text::Text(SDL_Renderer* renderer, const char* text, SDL_Color color, std::string id, int size)
	: Asset(id)
{
	TTF_Font* font = TTF_OpenFont("Assets/framd.ttf", size);
	if (font == nullptr)
	{
		std::cout << "Failed to load font." << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	if (surface == nullptr)
	{
		std::cout << "Failed to create surface from font." << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	_data = SDL_CreateTextureFromSurface(renderer, surface);
	if (_data == nullptr)
	{
		std::cout << "Failed to create texture from surface." << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	SDL_FreeSurface(surface);
}

Text::~Text()
{
	SDL_DestroyTexture(_data);
}

void Text::render(SDL_Renderer* renderer, Vector_2D translation)
{
	SDL_Rect destination = { (int)translation.x(), (int)translation.y(), 0, 0 };
	SDL_QueryTexture(_data, nullptr, nullptr, &destination.w, &destination.h);
	SDL_RenderCopy(renderer, _data, NULL, &destination);
}
