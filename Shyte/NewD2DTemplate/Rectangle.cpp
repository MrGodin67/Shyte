#include "Rectangle.h"
#include "Line.h"
#include "Graphics.h"

sRectangle::sRectangle()
{
}

sRectangle::sRectangle(const RectF& rect, bool draw, bool drawFilled)
	:m_frame(rect),m_draw(draw),m_drawFilled(drawFilled)
{
	m_center = Vec2f(m_frame.left + m_frame.GetWidth() * 0.5f, m_frame.top + m_frame.GetHeight() * 0.5f);
}


sRectangle::~sRectangle()
{
}

sLine sRectangle::GetLine(const LineType& line)
{
	switch (line)
	{
	case LineType::top:
		return (sLine({ m_frame.left,m_frame.top }, { m_frame.right,m_frame.top }));
	case LineType::right:
		return (sLine({ m_frame.right,m_frame.top }, { m_frame.right,m_frame.bottom }));
	case LineType::bottom:
		return (sLine({ m_frame.right,m_frame.bottom }, { m_frame.left,m_frame.bottom }));
	case LineType::left:
		return (sLine({ m_frame.left,m_frame.bottom }, { m_frame.left,m_frame.top }));

	}
	return sLine();
}

sLine sRectangle::GetLeftLine()
{
	return GetLine(LineType::left);
}

sLine sRectangle::GetTopLine()
{
	return GetLine(LineType::top);
}
sLine sRectangle::GetRightLine()
{
	return GetLine(LineType::right);
}
sLine sRectangle::GetBottomLine()
{
	return GetLine(LineType::bottom);
}
RectF sRectangle::operator()()
{
	return m_frame;
}
void sRectangle::Draw(Graphics & gfx)
{
	if (m_draw)
	{
		if(m_drawFilled)
			gfx.DrawFilledRectangle( m_frame.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), m_matrix);
		else
		    gfx.DrawRectangle(m_matrix, m_frame.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
}





