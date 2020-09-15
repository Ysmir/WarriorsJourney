#pragma once

#include <string>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "asset.h"

class Texture : public Asset
{
public:
	Texture(std::string id, std::string path, SDL_Renderer* renderer);
	~Texture();

	SDL_Texture* data();
	
	virtual void render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* destination, SDL_RendererFlip flip);

private:
	SDL_Texture* _data;
};