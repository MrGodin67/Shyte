#pragma once
#include "Animation.h"
#include "includes.h"
#include "CoreData.h"

enum class EntityStates
{
	idle,
	moving,
	jumping,
	climbing,
	numbStates
};







class Entity : public Animation
{
	friend class Level;
	_CoreData* CoreData() { return &m_coreData; }
protected:
	
	EntityStates m_currentState = EntityStates::idle;
	_CoreData m_coreData;
	
public:
	Entity();
	virtual void Update(const float& dt) = 0;
	virtual Vec2f GetPosition() { return m_coreData.position; }
	virtual RectF GetCollisionRect() { return RectF(); };
	virtual RectF GetCollisionRect(Vec2f& offset_translation) { return RectF(); };
	virtual void SetState(EntityStates state) { m_currentState = state; };
	virtual Vec2f GetCenter() = 0;
	
	
};