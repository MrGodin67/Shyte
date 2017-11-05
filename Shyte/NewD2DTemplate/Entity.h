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

enum class _EntityType
{
	player,
	enemy,
	ridgid,
	npc,
	numbTypes
};





class Entity : public Animation
{
	friend class Level;
	_CoreData* CoreData() { return &m_coreData; }
	
protected:
	
	EntityStates m_currentState = EntityStates::idle;
	_EntityType m_type;
	_CoreData m_coreData;
	
public:
	Entity();
	virtual void Update(const float& dt) = 0;
	virtual Vec2f GetPosition() = 0;
	virtual RectF GetCollisionRect() { return RectF(); };
	virtual RectF GetCollisionRect(Vec2f& offset_translation) { return RectF(); };
	virtual void SetState(EntityStates state) { m_currentState = state; };
	virtual Vec2f GetCenter() = 0;
	virtual void UpdatePosition(Vec2f& pos) = 0;
	_EntityType Type() { return m_type; }

	
	
	
};