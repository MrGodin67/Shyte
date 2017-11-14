#include "Mushroom.h"

#include "Locator.h"
#include "EntityState.h"


Mushroom::Mushroom(_CoreData core)
{
	m_coreData = core;
	m_type = _EntityType::enemy;
	m_renderDesc.drawRect = { 0.0f,0.0f,48.0f,64.0f };
	m_renderDesc.clipRect = Locator::ImageManager()->GetImage("mushroom")->GetClippedImage(4).ToD2D();
	m_renderDesc.image = Locator::ImageManager()->GetImage("mushroom")->GetTexture();
	m_coreData = core;
	m_coreData.velocity.x = -1.0f;
	m_coreData.direction.Set(-1);
	m_drawWidth = m_renderDesc.drawRect.right - m_renderDesc.drawRect.left;
	m_drawHeight = m_renderDesc.drawRect.bottom - m_renderDesc.drawRect.top;
	seq_Indices["left"] = { 10,9,10,11 };
	seq_Indices["right"] = { 4,3,4,5 };
	seq_Indices["up"] = { 1,0,1,2 };
	seq_Indices["down"] = { 7,6,7,8 };
	m_currentState = EntityStates::moving;
	mp_seqPtr = &seq_Indices["left"];
}


Mushroom::~Mushroom()
{
}

void Mushroom::Update(const float & dt)
{
	EntityState::DoState(m_currentState, m_coreData);
	m_coreData.position += m_coreData.velocity  * dt;
	m_renderDesc.clipRect = Locator::ImageManager()->GetImage("mushroom")->GetClippedImage(mp_seqPtr->at(m_coreData.seq_Index)).ToD2D();
	m_renderDesc.drawRect = { m_coreData.position.x,m_coreData.position.y,
		m_coreData.position.x + m_drawWidth,m_coreData.position.y + m_drawHeight };
	m_center.x = m_renderDesc.drawRect.left + (m_drawWidth * 0.5f);
	m_center.y = m_renderDesc.drawRect.top + (m_drawHeight * 0.5f);
}

Vec2f Mushroom::GetPosition()
{
	return m_coreData.position;
}

Vec2f Mushroom::GetCenter()
{
	return Vec2f();
}

RectF Mushroom::GetCollisionRect()
{
	RectF rect = m_renderDesc.drawRect;
	rect.left += collision_clip_x;
	rect.right -= collision_clip_x;
	rect.top += collision_clip_y;
	return rect;
}
