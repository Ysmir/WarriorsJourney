#pragma once

#include <SDL_mixer.h>

#include "asset.h"

class Sound : public Asset
{
public:
	Sound(std::string id, std::string path);

	Mix_Chunk* data();

private:
	Mix_Chunk* _data;
};