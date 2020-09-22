#include "animated_texture.h"

Animated_Texture::Animated_Texture(std::string id, std::string path, SDL_Renderer* renderer, int frame_count, Uint32 frame_duration_milliseconds, bool loop)
	: Texture(id, path, renderer)
{
	_frame_count = frame_count;
	_frame_duration_milliseconds = frame_duration_milliseconds;
	_current_frame = 0;
	_loop = loop;
	_updated_current_frame = false;
}

Animated_Texture::~Animated_Texture()
{
}

void Animated_Texture::set_frame(Uint32 total_time_milliseconds)
{
	if (_loop || total_time_milliseconds < _frame_duration_milliseconds * _frame_count)
	{
		_current_frame = (total_time_milliseconds / _frame_duration_milliseconds) % _frame_count;

	}
	else
	{
		_current_frame = _frame_count - 1;
	}
}

void Animated_Texture::render(SDL_Renderer* renderer, SDL_Rect*, SDL_Rect* destination, SDL_RendererFlip flip)
{
	int texture_w = 0;
	int texture_h = 0;
	const int query_texture_result = SDL_QueryTexture(data(), nullptr, nullptr, &texture_w, &texture_h);

	int frame_w = texture_w / _frame_count;
	SDL_Rect frame_clip;
	frame_clip.w = frame_w;
	frame_clip.h = texture_h;
	frame_clip.x = _current_frame * frame_w;
	frame_clip.y = 0;

	Texture::render(renderer, &frame_clip, destination, flip);
}

bool Animated_Texture::loop()
{
	return _loop;
}

void Animated_Texture::reset_update()
{
	_updated_current_frame = false;
}
