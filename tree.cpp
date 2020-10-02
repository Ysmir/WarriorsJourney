#include "tree.h"

Tree::Tree(std::string id, Vector_2D translation)
	:Game_Object(id, "Texture.Tree")
{
	_width = 128;
	_height = 128;
	_translation = Vector_2D(translation);

	_collider.set_radius(_width / 4.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, _height * 0.75f));

	_immovable = true;
}

Tree::~Tree()
{
}

void Tree::simulate_AI(Uint32 , Assets* , Input* , Scene* )
{
}
