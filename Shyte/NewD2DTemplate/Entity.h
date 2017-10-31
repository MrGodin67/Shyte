#pragma once
#include "Animation.h"
#include "includes.h"

enum class EntityStates
{
	idle,
	moving,
	jumping,
	climbing,
	numbStates
};

template<typename T>
static T Sign(T val)
{
	if (val == (T)0)
		return (T)0;
	return std::signbit((float)val) ? (T)-1 : (T)1;
}

class _Direction
{
	int horizontal = 0;
public:
	
	inline int  GetSign()
	{
		if (horizontal == 0)return 0;
		return Sign<int>(horizontal);
	}
	void Set(int horz) { horizontal = horz; }
	
};
class _MovementData
{
public:
	_Direction direction;
	float verticalForce = -1.0f;
	float maxSpeed = 116.0f;
	float speed = 0.0f;
	float acceleration = 2.8f;
	float verticalDecay = 0.99f;
	float horizontalDecay = 0.99f;
	float surfaceFriction = 0.896f;
	bool jumping = false;
	bool climbing = false;
	bool falling = false;
	bool moving = false;
	int seq_Index = 0;
	float seq_Timer = 0.0f;
	Vec2f velocity = {0.0f,0.0f};
	_MovementData() {}
};


class Entity : public Animation
{
protected:
	Vec2f m_velocity = { 0.0f,0.0f };
	float m_speed = 2.0f;
	EntityStates m_currentState = EntityStates::idle;
	_MovementData m_movement;
	
public:
	Entity();
	virtual void Update(const float& dt) = 0;
	virtual RectF GetCollisionRect() { return RectF(); };
	virtual RectF GetCollisionRect(Vec2f& offset_translation) { return RectF(); };
	virtual void SetState(EntityStates& state) { m_currentState = state; };
	virtual void SetPosition(Vec2f& pos) = 0;
	virtual Vec2f GetPosition() = 0;
	virtual Vec2f GetCenter() = 0;
	_MovementData* MoveData() { return &m_movement; }
	
};