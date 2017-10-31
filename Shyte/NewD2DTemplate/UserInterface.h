#pragma once

#include "Vec2.h"
#include "includes.h"
#include "Animation.h"
#include "Rect.h"
#define RETURN_START 1
#define RETURN_EXIT 2
#define RETURN_RESUME 3
#define RETURN_NEW 4
#define RETURN_NONE 0
struct MouseReturnType
{
	int type;
	int result;
};
class UserInterface
{
public:
	
	virtual MouseReturnType OnMouseClick(const Vec2i& mousePos) = 0;
	virtual void OnKeyPress(unsigned char& key) = 0;
	virtual void Draw(class Camera& cam) = 0;
	
	
};
