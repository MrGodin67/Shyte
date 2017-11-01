#pragma once

#include "Entity.h"
#include "includes.h"
class EntityState
{
private:
	static void ApplyGravity(float& val)
	{
		val += GRAVITY;
		
	}
	static void DoFalling(_CoreData& data)
	{
		if (fabsf(data.velocity.x) < 1.5f)
			data.velocity.x = 0.0f;
		
			
		if (data.boosting)
		{
			if (data.velocity.y > -(data.max_verticalForce))
			{
			   data.velocity.y += -(data.verticalForce);
			}
			else
			{
				data.boosting = false;
			}
		}
		else
		{
			data.velocity.x *= data.horizontalDecay;
		}
		
		ApplyGravity(data.velocity.y);
	}
	static void DoIdle(_CoreData& data)
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
		data.seq_Index = 0;
	}
	static void DoMoving(_CoreData& data)
	{
		data.moving = true;
		//allow for skidding when changing direction
		if (Sign(data.velocity.x) != data.direction.GetSign())
			data.velocity.x += (data.direction.GetSign()*(data.acceleration*2.0f));
		else
			data.velocity.x += (data.direction.GetSign()*data.acceleration);
		// cap speed
		if (abs(data.velocity.x) > data.maxSpeed)
			data.velocity.x = (data.direction.GetSign()*data.maxSpeed);
		
		// percentage of max speed
		float inc = abs(data.velocity.x) / data.maxSpeed;
		if ((data.seq_Timer +=  inc) > 5.0f)
		{
			// step through image indices
			data.seq_Index++;
			if(data.seq_Index >= 4)
				 data.seq_Index = 0;
			data.seq_Timer = 0.0f;
		}
	}
public:
	EntityState(){}
	static void DoState(EntityStates& m_state,_CoreData& data)
	{
		
		switch (m_state)
		{
		case EntityStates::idle:
			data.seq_Index = 0;
			DoIdle( data);
			break;
		case EntityStates::moving:
			DoMoving( data);
		break;
		case EntityStates::climbing:
			break;
		
		case EntityStates::jumping:
		{
			if (data.direction.GetSign() < 0)
				data.seq_Index = 3;
			if (data.direction.GetSign() > 0)
				data.seq_Index = 1;
			DoFalling(data);
		}
		break;

		}

	}
};