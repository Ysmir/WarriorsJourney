#pragma once

#include <map>
#include <vector>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "asset.h"

class Assets
{
public:
	Assets(SDL_Renderer* renderer);
	~Assets();

	Asset* get_asset(std::string id);
	void reset_animated_textures();

private:
	std::map<std::string, Asset*> _assets;
	std::vector<std::string> _animated_texture_ids;
};
