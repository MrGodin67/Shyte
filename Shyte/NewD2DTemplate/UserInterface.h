#pragma once

#include "Vec2.h"
#include "includes.h"
#include "Rect.h"
#define RETURN_START 1
#define RETURN_EXIT 2
#define RETURN_RESUME 3
#define RETURN_NEW 4
#define RETURN_NEW_BACK 5
#define RETURN_NEW_DONE 6
#define RETURN_NONE 0
struct MouseReturnType
{
	int type = RETURN_NONE;
	int result = RETURN_NONE;
	void* data = nullptr;
};
class UserInterface
{
public:
	
	virtual MouseReturnType OnMouseClick(const Vec2i& mousePos) = 0;
	virtual void OnKeyPress(unsigned char& key) = 0;
	virtual void Draw(class Graphics& gfx) = 0;
	
	
	
};
