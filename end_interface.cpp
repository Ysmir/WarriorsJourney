#include "end_interface.h"
#include "text.h"

End_Interface::End_Interface(int score, int level)
	: Game_Object("End.Interface", "Texture.Dino")
{
	_score = score;
	_level = level;
}

End_Interface::~End_Interface()
{
}

void End_Interface::simulate_AI(Uint32 , Assets* , Input* , Scene* )
{
}

void End_Interface::render(Uint32 , Assets* , SDL_Renderer* renderer, Configuration* , Scene* )
{
	SDL_Color text_color;
	text_color.r = 255;
	text_color.g = 0;
	text_color.b = 0;
	text_color.a = 0;

	//Level
	std::string level_s = "Levels Completed: " + std::to_string(_level);

	Text level(renderer, level_s.c_str(), text_color, "Level.Text", 30);

	level.render(renderer, Vector_2D(260.f, 150.f));

	//Score
	std::string score_s = "Score: " + std::to_string(_score);

	Text score(renderer, score_s.c_str(), text_color, "Score.Text", 30);

	score.render(renderer, Vector_2D(320.f, 300.f));

	//Click message
	std::string click_s = "Click to Continue";

	Text click(renderer, click_s.c_str(), text_color, "Click.Text", 30);

	click.render(renderer, Vector_2D(260.f, 450.f));
}