#pragma once
#include "Entity.h"
class Mushroom :
	public Entity
{
	const float collision_clip_x = 4.0f;
	const float collision_clip_y = 16.0f;
	std::unordered_map<std::string, std::array<int, 4>> seq_Indices;
	int seq_Index = 0;
	std::array<int, 4>* mp_seqPtr;
	float timer = 0.0f;
public:
	Mushroom() = default;
	Mushroom(_CoreData core);
	~Mushroom();

	// Inherited via Entity
	virtual void Update(const float & dt) override;
	virtual Vec2f GetPosition() override;
	virtual Vec2f GetCenter() override;
	virtual RectF GetCollisionRect()override;
	virtual Vec2f GetVelocity()override { return m_coreData.velocity; };
	virtual void SetVelocity(const Vec2f& vel) { m_coreData.velocity = vel; };
};

