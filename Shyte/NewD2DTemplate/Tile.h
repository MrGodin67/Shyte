#pragma once

#include "includes.h"
#include "Animation.h"
#include "Vec2.h"
#include "Rect.h"
class Tile : public Animation
{
private:
	static float m_width;
	static float m_height;
	static ID2D1Bitmap* m_image;
private:
	bool m_passable;
public:
	Tile() = default;
	Tile(Vec2f& pos, RectF& imageClipRect,bool & passable);
	static void SetDimensions(const float w, const float h);
	static void SetImage(ID2D1Bitmap* image);
	void SetTransparency(float& t);
	static float Width();
	static float Height();
	bool Passable() { return m_passable; }

};