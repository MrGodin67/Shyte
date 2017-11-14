#include "Player.h"
#include "Locator.h"
#include "FileManager.h"

Player::Player()
{
}

Player::Player( PlayerData data, _CoreData core)
	:m_data(data)
{
	m_renderDesc.drawRect = { 0.0f,0.0f,48.0f,64.0f };
	m_renderDesc.clipRect = Locator::ImageManager()->GetImage(std::string(data.name))->GetClippedImage(4).ToD2D();
	m_renderDesc.image = Locator::ImageManager()->GetImage(std::string(data.name))->GetTexture();
	m_coreData = core;
	m_drawWidth = m_renderDesc.drawRect.right - m_renderDesc.drawRect.left;
	m_drawHeight = m_renderDesc.drawRect.bottom - m_renderDesc.drawRect.top;
	seq_Indices["left"] = { 10,9,10,11 };
	seq_Indices["right"] = { 4,3,4,5 };
	seq_Indices["up"] = { 1,0,1,2 };
	seq_Indices["down"] = { 7,6,7,8 };
	m_type = _EntityType::player;
	mp_seqPtr = &seq_Indices["left"];
	
}


Player::~Player()
{
	
}

void Player::Update(const float & dt)
{
	
	EntityState::DoState(m_currentState, m_coreData);
	m_coreData.position += m_coreData.velocity  * dt;
	m_renderDesc.clipRect = Locator::ImageManager()->GetImage(std::string(m_data.name))->GetClippedImage(mp_seqPtr->at(m_coreData.seq_Index)).ToD2D();
	m_renderDesc.drawRect = { m_coreData.position.x,m_coreData.position.y,
		m_coreData.position.x + m_drawWidth,m_coreData.position.y + m_drawHeight };
	m_center.x = m_renderDesc.drawRect.left + (m_drawWidth * 0.5f);
	m_center.y = m_renderDesc.drawRect.top + (m_drawHeight * 0.5f);
}

Vec2f Player::GetPosition()
{
	return m_coreData.position;
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
	return  RectF(x, y, x + rect.GetWidth(), y + rect.GetHeight());
}



Vec2f Player::GetCenter()
{
	return m_center;
}

Vec2f Player::GetVelocity()
{
	return m_coreData.velocity;
}

void Player::SetVelocity(const Vec2f & vel)
{
	m_coreData.velocity = vel;
}

void Player::HandleInput(Keyboard & kbd, Mouse & mouse)
{
	Vec2f vel = { 0.0f,0.0f };
	static bool is_boosting = false;
	
	m_currentState = EntityStates::idle;
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		m_coreData.direction.Set(MOVE_RIGHT);
		m_currentState = EntityStates::moving;
		m_coreData.moving = true;
		mp_seqPtr = &seq_Indices["right"];
		
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		m_coreData.direction.Set(MOVE_LEFT);
		m_currentState = EntityStates::moving;
		mp_seqPtr = &seq_Indices["left"];
	}
	 if (kbd.KeyIsPressed(VK_UP))
	{
	
		mp_seqPtr = &seq_Indices["up"];
		
	}
	 if (kbd.KeyIsPressed(VK_DOWN))
	 {
		
		 mp_seqPtr = &seq_Indices["down"];

	 }
	 
	if (kbd.KeyIsPressed(VK_SPACE))
	{
		if (!m_coreData.jumping)
		{
			m_currentState = EntityStates::jumping;
			m_coreData.jumping = true;
			m_coreData.velocity.y = -20.1f;
			m_coreData.boosting = true;
		}
		
	}
	else
	{
		m_coreData.boosting = false;
	}
	
	
	
}

int Player::CurrentLevel()
{
	return m_coreData.level_index;
}

void Player::Save()
{
	MainPlayerData data;
	data.core = m_coreData;
	data.data = m_data;
	char fName[255];
	sprintf_s(fName, "%s%s%s", "data\\", m_data.username, ".bin");
	FileManager::WritePlayerData(fName, data);
}
