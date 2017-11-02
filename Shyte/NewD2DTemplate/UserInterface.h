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
#define RETURN_CONTINUE 7
#define RETURN_NONE 0

static  D2D1_COLOR_F SELECT_COLOR_GREEN = D2D1::ColorF(0.0f, 1.0f, 0.0f, 0.5f);
static  D2D1_COLOR_F SELECT_COLOR_RED = D2D1::ColorF(1.0f, 0.0f, 0.0f, 0.5f);
static  D2D1_COLOR_F SELECT_COLOR_BLUE = D2D1::ColorF(0.0f, 0.0f, 1.0f, 0.5f);
static  D2D1_COLOR_F FULL_COLOR_WHITE = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);

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
	virtual MouseReturnType OnMouseMove(const Vec2i& mousePos) = 0;
	virtual void OnKeyPress(unsigned char& key) = 0;
	virtual void Draw(class Graphics& gfx) = 0;
	
	
	
};
