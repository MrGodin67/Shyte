#pragma once

#include "Line.h"
#include "Rectangle.h"

struct ShapeCollisionData
{
	Vec2f intersectPoints[2] = {Vec2f(),Vec2f()};
	float distance[2] = {0.0f,0.0f};
	bool  intersect = false;
};

class ShapeCollisions
{
public:
	static ShapeCollisionData LineIntersect(const sLine& line, const sRectangle& rect);
};