#pragma once
#include "Entity.h"
#include "keyboard.h"
#include "mouse.h"
#include "EntityState.h"
struct PlayerData
{
	char name[255];
	int hit_points;
	int current_level;
	int numbPotions;
	int numbKeys;
	int exp_points;
};
class Player :
	public Entity
{
	const float collision_clip_x = 10.0f;
	const float collision_clip_y = 10.0f;
	std::unordered_map<std::string, std::array<int, 4>> seq_Indices;
	int seq_Index = 0;
	std::array<int, 4>* mp_seqPtr;
	float timer = 0.0f;
	PlayerData data;
	
public:
	Player();
	Player(Animation::RenderDesc& desc,PlayerData data);
	~Player();

	// Inherited via Entity
	virtual void Update(const float & dt) override;
	virtual RectF GetCollisionRect()override;
	virtual RectF GetCollisionRect(Vec2f& offset_translation) override;
	virtual Vec2f GetCenter()override;
	void HandleInput(Keyboard& kbd, Mouse& mouse);
};

