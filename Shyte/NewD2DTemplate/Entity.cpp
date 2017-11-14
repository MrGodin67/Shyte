#include "Entity.h"
#include "EntityState.h"
#include "Graphics.h"
Entity::Entity() 
{}

void Entity::SetPosition(Vec2f & pos)
{
	m_renderDesc.drawRect = RectF(pos.x, pos.y, pos.x + m_drawWidth, pos.y + m_drawHeight).ToD2D();
	m_center.x = pos.x + (m_drawWidth * 0.5f);
	m_center.y = pos.y + (m_drawHeight * 0.5f);
	m_coreData.position = pos;
}

