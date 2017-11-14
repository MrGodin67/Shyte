#include "Shape.h"
#include "Graphics.h"

void Shape::Translate(const Vec2f & transform)
{
	m_matrix = D2D1::Matrix3x2F::Rotation(m_rotation, m_center.ToD2DPointF()) *
		D2D1::Matrix3x2F::Scale({m_scale.width,m_scale.height},m_center.ToD2DPointF())*
		D2D1::Matrix3x2F::Translation({transform.x,transform.y});
}

D2D1_MATRIX_3X2_F Shape::Matrix()
{
	return m_matrix;
}

void Shape::SetRotation(const float & value)
{
	m_rotation = value;
}

void Shape::SetScale(const float & width, const float & height)
{
	m_scale = Vec2f(width, height);
}

void Shape::SetColor(const D2D1_COLOR_F color)
{
	m_color = color;
}
