#pragma once

#include "Shape.h"
class sLine : public Shape
{
	Vec2f m_pt0;
	Vec2f m_pt1;
	Vec2f m_normal;
	float m_length;
public:
	sLine() = default;
	sLine(Vec2f p0, Vec2f p1);
		
	Vec2f operator[](int index);
	Vec2f Normal();

	Vec2f GetCenter();
	Vec2f GetDirectionalUnitVector();
	// Inherited via Shape
	virtual void Draw(Graphics & gfx) override;
	virtual void Update(const float & dt) override;
	virtual void Translate(const Vec2f & transform) override;
	

	
};