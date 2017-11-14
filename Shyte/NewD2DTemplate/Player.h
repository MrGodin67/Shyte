#pragma once
#include "Entity.h"
#include "keyboard.h"
#include "mouse.h"
#include "EntityState.h"

class Player :
	public Entity
{
	const float collision_clip_x = 10.0f;
	const float collision_clip_y = 10.0f;
	std::unordered_map<std::string, std::array<int, 4>> seq_Indices;
	int seq_Index = 0;
	std::array<int, 4>* mp_seqPtr;
	float timer = 0.0f;
	PlayerData m_data;
	
public:
	Player();
	Player(PlayerData data,_CoreData core);
	~Player();

	// Inherited via Entity
	virtual void Update(const float & dt) override;
	virtual Vec2f GetPosition()override;
	virtual RectF GetCollisionRect()override;
	virtual RectF GetCollisionRect(Vec2f& offset_translation) override;
	virtual Vec2f GetCenter()override;
	virtual Vec2f GetVelocity()override;
	virtual void SetVelocity(const Vec2f& vel)override;
	void HandleInput(Keyboard& kbd, Mouse& mouse);
	int CurrentLevel();
	void Save(); 
};

