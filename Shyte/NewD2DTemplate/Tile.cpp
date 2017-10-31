#include "Tile.h"

float Tile::m_width = 0.0f;
float Tile::m_height = 0.0f;
ID2D1Bitmap* Tile::m_image = nullptr;

Tile::Tile(Vec2f & pos, RectF& imageClipRect, bool & passable)
	:m_passable(passable)
{
	m_renderDesc.drawRect = { pos.x ,pos.y,pos.x + m_width,pos.y + m_height };
	m_renderDesc.clipRect = imageClipRect.ToD2D();
	m_renderDesc.image = m_image;
}

void Tile::SetDimensions(const float w, const float h)
{
	m_width = w;
	m_height = h;
}

void Tile::SetImage(ID2D1Bitmap * image)
{
	m_image = image;
}

void Tile::SetTransparency(float & t)
{
	m_renderDesc.opague = t;
}

float Tile::Width()
{

	return m_width;
}

float Tile::Height()
{
	return m_height;
}
