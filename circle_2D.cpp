#include "circle_2D.h"

Circle_2D::Circle_2D(float radius, Vector_2D translation)
	: _translation(translation.x(), translation.y())
{
	_radius = radius;
}

float Circle_2D::radius()
{
	return _radius;
}

void Circle_2D::set_radius(float radius)
{
	_radius = radius;
}

Vector_2D Circle_2D::translation()
{
	return _translation;
}

void Circle_2D::set_translation(Vector_2D translation)
{
	_translation = translation;
}

float Circle_2D::intersection_depth(Circle_2D other)
{
	if (_radius == 0.f || other.radius() == 0.f)
	{
		return 0;
	}

	const float distance_to_to_other_circle = (_translation - other.translation()).magnitude();
	const float collider_combined_radius = _radius + other.radius();

	if (distance_to_to_other_circle < collider_combined_radius)
	{
		return collider_combined_radius - distance_to_to_other_circle;
	}
	return 0.f;
}
