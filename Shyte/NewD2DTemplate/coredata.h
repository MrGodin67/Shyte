#pragma once
#include "includes.h"

class _Direction
{
	int horizontal = 0;
public:

	inline int  GetSign()
	{
		return Sign<int>(horizontal);
	}
	void Set(int horz) { horizontal = horz; }

};
class _CoreData
{
public:
	_Direction direction;
	float verticalForce = 0.0f;
	float max_verticalForce = 0.0f;
	float maxSpeed = 0.0f;
	float speed = 0.0f;
	float acceleration = 0.0f;
	float verticalDecay = 0.0f;
	float horizontalDecay = 0.0f;
	float surfaceFriction = 0.0f;
	bool jumping = false;
	bool climbing = false;
	bool falling = false;
	bool moving = false;
	bool boosting = false;
	int seq_Index = 0;
	float seq_Timer = 0.0f;
	Vec2f velocity = { 0.0f,0.0f };
	Vec2f position = { 0.0f,0.0f };
	_CoreData() {}
};
class InitialPlayerCoreData
{
public:
	static _CoreData Get(std::string name)
	{
		if (name == "maria")
			return Maria();
		if (name == "hannah")
			return Hannah();
		if (name == "jack")
			return Jack();
		if (name == "colin")
			return Colin();
		// no case so default;
		return _CoreData();
	}
private:
	static _CoreData Maria()
	{
		_CoreData data;
		data.max_verticalForce = 250.0f;
		data.acceleration = 4.0f;
		data.horizontalDecay = 0.987f;
		data.maxSpeed = 152.0f;
		data.surfaceFriction = 0.876f;
		data.verticalForce = GRAVITY*1.5f;
		data.verticalDecay = GRAVITY;
		return data;
	}
	static _CoreData Hannah()
	{
		_CoreData data;
		data.max_verticalForce = 300.0f;
		data.acceleration = 4.0f;
		data.horizontalDecay = 0.987f;
		data.maxSpeed = 152.0f;
		data.surfaceFriction = 0.876f;
		data.verticalForce = GRAVITY*2.0f;
		data.verticalDecay = GRAVITY;
		return data;
	}
	static _CoreData Jack()
	{
		_CoreData data;
		data.max_verticalForce = 300.0f;
		data.acceleration = 4.0f;
		data.horizontalDecay = 0.987f;
		data.maxSpeed = 252.0f;
		data.surfaceFriction = 0.876f;
		data.verticalForce = GRAVITY*2.0f;
		data.verticalDecay = GRAVITY;
		return data;
	}
	static _CoreData Colin()
	{
		_CoreData data;
		data.max_verticalForce = 300.0f;
		data.acceleration = 4.0f;
		data.horizontalDecay = 0.987f;
		data.maxSpeed = 152.0f;
		data.surfaceFriction = 0.876f;
		data.verticalForce = GRAVITY*2.0f;
		data.verticalDecay = GRAVITY;
		return data;
	}
};