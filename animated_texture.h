#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "texture.h"

class Animated_Texture : public Texture
{
public:
	Animated_Texture(std::string id, std::string path, SDL_Renderer* renderer, int frame_count, Uint32 frame_duration_milliseconds, bool loop = true);
	~Animated_Texture();

	void set_frame(Uint32 _total_time_milliseconds);
	void render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* destination, SDL_RendererFlip flip) override;
	bool loop();
	void reset_update();

private:
	int		 _frame_count;
	Uint32	 _frame_duration_milliseconds;
	int		 _current_frame;
	bool	 _loop;
	bool	 _updated_current_frame;
};