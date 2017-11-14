#pragma once
#include "includes.h"


#include <d2d1.h>
class Shape
{
protected:
	D2D1_MATRIX_3X2_F m_matrix = D2D1::Matrix3x2F::Identity();
	Vec2f m_center = { 0.0f,0.0f };
	Vec2f m_scale = { 1.0f,1.0f };
	float m_rotation = 0.0f;
	D2D1_COLOR_F m_color = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);

public:
	Shape() = default;
	virtual ~Shape() {}
	virtual void Draw(class Graphics& gfx) {};
	virtual void Update(const float& dt) {};
	virtual void Translate(const Vec2f& transform);
	virtual D2D1_MATRIX_3X2_F Matrix();
	virtual void SetRotation(const float& value);
	virtual void SetScale(const float& width, const float& height);
	virtual void SetColor(const D2D1_COLOR_F color);
};


