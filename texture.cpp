#include <iostream>

#include <SDL_image.h>

#include "texture.h"

Texture::Texture(std::string id, std::string path, SDL_Renderer* renderer)
	: Asset(id)
{
	SDL_Surface* surface = nullptr;
	if (path.find("bmp") != std::string::npos)
	{
		surface = SDL_LoadBMP(path.c_str());
	}
	else if (path.find("png") != std::string::npos)
	{
		surface = IMG_Load(path.c_str());
	}
	else
	{
		std::cout << "Unknown image file extension. Path: " << path << std::endl;
		exit(1);
	}

	if (surface == nullptr)
	{
		std::cout << "Failed to create SDL Surface" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	_data = SDL_CreateTextureFromSurface(renderer, surface);
	if (_data == nullptr)
	{
		std::cout << "Failed to create SDL Surface" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	SDL_FreeSurface(surface);
}

Texture::~Texture()
{
	SDL_DestroyTexture(_data);
}

SDL_Texture* Texture::data()
{
	return _data;
}

void Texture::render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* destination, SDL_RendererFlip flip)
{
	int render_result = SDL_RenderCopyEx(renderer, _data, clip, destination, 0, NULL, flip);
	int render_success = 0;
	if (render_result != render_success)
	{
		std::cout << "Failed to render texture" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
}
