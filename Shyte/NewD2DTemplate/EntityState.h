#pragma once

#include "Entity.h"

class EntityState
{
private:
	static void ApplyGravity(float& val)
	{
		val += GRAVITY;
		if (val > GRAVITY * 27.0f)
			val = GRAVITY * 27.0f;
	}
	static void DoFalling(_MovementData& data)
	{
		if (fabsf(data.velocity.x) < 1.5f)
			data.velocity.x = 0.0f;
		else
		{
			if(data.moving)
			   data.velocity.x *= data.horizontalDecay;

		}
		ApplyGravity(data.velocity.y);
	}
	static void DoIdle(_MovementData& data)
	{
		data.falling = data.jumping = data.climbing = false;
		data.velocity.y = 0.0f;
		if (fabsf(data.velocity.x) < 10.5f && data.moving)
		{
			data.velocity.x = 0.0f;
			data.moving = false;
		}
		else
		{
			data.velocity.x *= data.surfaceFriction;
			
		}
		data.seq_Timer = 0;
	}
	static void DoMoving(_MovementData& data)
	{
		data.moving = true;
		if (Sign(data.velocity.x) != data.direction.GetSign())
			data.velocity.x += (data.direction.GetSign()*(data.acceleration*2.0f));
		else
			data.velocity.x += (data.direction.GetSign()*data.acceleration);

		if (abs(data.velocity.x) > data.maxSpeed)
			data.velocity.x = (data.direction.GetSign()*data.maxSpeed);
		if(data.jumping)
			ApplyGravity(data.velocity.y);
		float inc = __max(0.016f,abs(data.velocity.x) * 0.001f);
		if ((data.seq_Timer += inc) > 0.5f)
		{
			data.seq_Index++;
			if (data.seq_Index >= 4)
			{
				data.seq_Index = 0;
			}
			data.seq_Timer = 0.0f;
			
		}
	}
public:
	EntityState(){}
	static void DoState(EntityStates& m_state,_MovementData& data)
	{
		
		switch (m_state)
		{
		case EntityStates::idle:
			DoIdle( data);
			break;
		case EntityStates::moving:
			DoMoving( data);
		break;
		case EntityStates::climbing:
			break;
		
		case EntityStates::jumping:
		{
			
			DoFalling(data);
		}
		break;

		}

	}
};