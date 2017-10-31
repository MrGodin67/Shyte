#include "Player.h"
#include "Locator.h"


Player::Player()
{
}

Player::Player(Animation::RenderDesc & desc)
{
	m_drawWidth = desc.drawRect.right - desc.drawRect.left;
	m_drawHeight = desc.drawRect.bottom - desc.drawRect.top;
	m_renderDesc = desc;
	seq_Indices["left"] = { 10,9,10,11 };
	seq_Indices["right"] = { 4,3,4,5 };
	mp_seqPtr = &seq_Indices["left"];
	
}


Player::~Player()
{
}

void Player::Update(const float & dt)
{
	
	EntityState::DoState(m_currentState, m_movement);
	Vec2f pos = GetPosition() + m_movement.velocity  * dt;
	SetPosition(pos);
	m_renderDesc.clipRect = Locator::ImageManager->GetImage("char1")->GetClippedImage(mp_seqPtr->at(m_movement.seq_Index)).ToD2D();
}

RectF Player::GetCollisionRect()
{
	RectF rect = m_renderDesc.drawRect;
	rect.left += collision_clip_x;
	rect.right -= collision_clip_x;
	rect.top += collision_clip_y;
	return rect;
}

RectF Player::GetCollisionRect(Vec2f& offset_translation)
{
	RectF rect = m_renderDesc.drawRect;
	rect.left += collision_clip_x;
	rect.right -= collision_clip_x;
	rect.top += collision_clip_y;
	float x = rect.left + offset_translation.x;
	float y = rect.top + offset_translation.y;
	return RectF(x,y,x+rect.GetWidth(),y + rect.GetHeight());
}

void Player::SetPosition(Vec2f & pos)
{
	m_renderDesc.drawRect = { pos.x,pos.y,pos.x + m_drawWidth,pos.y + m_drawHeight };
	m_center.x = m_renderDesc.drawRect.left + (m_drawWidth * 0.5f);
	m_center.y = m_renderDesc.drawRect.top + (m_drawHeight * 0.5f);
}

Vec2f Player::GetPosition()
{
	return Vec2f(m_renderDesc.drawRect.left, m_renderDesc.drawRect.top);
}

Vec2f Player::GetCenter()
{
	return m_center;
}

void Player::HandleInput(Keyboard & kbd, Mouse & mouse)
{
	Vec2f vel = { 0.0f,0.0f };
	
	
	m_currentState = EntityStates::idle;
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		m_movement.direction.Set(MOVE_RIGHT);
		m_currentState = EntityStates::moving;
		m_movement.moving = true;
		mp_seqPtr = &seq_Indices["right"];
		
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		m_movement.direction.Set(MOVE_LEFT);
		m_currentState = EntityStates::moving;
		mp_seqPtr = &seq_Indices["left"];
		
		
				
	}
	 if (kbd.KeyIsPressed(VK_UP))
	{
		m_currentState = EntityStates::jumping;
		
	}
	
	if (kbd.KeyIsPressed(VK_SPACE) && !m_movement.jumping)
	{
		m_currentState = EntityStates::jumping;
		m_movement.jumping = true;
		m_movement.velocity.y = -400.0f;
	}
	
	
	
}
