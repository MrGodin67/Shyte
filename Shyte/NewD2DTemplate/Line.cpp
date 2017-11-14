#include "Line.h"
#include "Graphics.h"
sLine::sLine(Vec2f p0, Vec2f p1)
	:m_pt0(p0), m_pt1(p1)
{
	m_normal = (m_pt1 - m_pt0).Normalize().CCW90();
	m_length = (m_pt1 - m_pt0).Len();
	m_center = m_pt0.MidpointWith(m_pt1);
}
Vec2f sLine::operator[](int index)

{
	if (index == 0)
		return m_pt0;
	if (index == 1)
		return m_pt1;

	return Vec2f();
}
Vec2f sLine::Normal()
{
	return m_normal;
}

Vec2f sLine::GetCenter()
{
	
	return m_center = m_pt0.MidpointWith(m_pt1);
}

Vec2f sLine::GetDirectionalUnitVector()
{
	
	return (m_pt1 - m_pt0).Normalize();
}

void sLine::Draw(Graphics & gfx)
{
	gfx.DrawLine(m_matrix, m_pt0.ToD2DPointF(), m_pt1.ToD2DPointF(),
		m_color, 2.0f);
}

void sLine::Update(const float & dt)
{
}

void sLine::Translate(const Vec2f & transform)
{
	
	//m_pt0 = m_center + m_pt0.Rotation(m_rotation);
	//m_pt1 = m_center + m_pt1.Rotation(m_rotation);
	m_matrix = D2D1::Matrix3x2F::Rotation(m_rotation, m_center.ToD2DPointF()) *
		D2D1::Matrix3x2F::Scale({ m_scale.width,m_scale.height }, m_center.ToD2DPointF())*
		D2D1::Matrix3x2F::Translation({ transform.x,transform.y });
	
}


