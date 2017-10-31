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
class _CoreData
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
	Vec2f position = {0.0f,0.0f};
	_CoreData() {}
};


class Entity : public Animation
{
protected:
	
	EntityStates m_currentState = EntityStates::idle;
	_CoreData m_coreData;
	
public:
	Entity();
	virtual void Update(const float& dt) = 0;
	virtual RectF GetCollisionRect() { return RectF(); };
	virtual RectF GetCollisionRect(Vec2f& offset_translation) { return RectF(); };
	virtual void SetState(EntityStates state) { m_currentState = state; };
	virtual Vec2f GetCenter() = 0;
	_CoreData* CoreData() { return &m_coreData; }
	
};