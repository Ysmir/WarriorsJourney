#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "texture.h"
#include "asset.h"
#include "vector_2D.h"

class Text : public Asset
{
public:
	Text(SDL_Renderer* renderer, const char* text, SDL_Color color, std::string id);
	~Text();

	void render(SDL_Renderer* renderer, Vector_2D translation);

private:
	SDL_Texture* _data;
};