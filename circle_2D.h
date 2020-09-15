#pragma once

#include "vector_2D.h"

class Circle_2D
{
public:
	Circle_2D(float radius, Vector_2D translation);

	float radius();
	void set_radius(float radius);

	Vector_2D translation();
	void set_translation(Vector_2D translation);

	float intersection_depth(Circle_2D other);

private:
	float _radius;
	Vector_2D _translation;
};