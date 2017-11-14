#pragma once


#include "includes.h"

#define RETURN_RESULT_NONE 0
#define RETURN_RESULT_START 1
#define RETURN_RESULT_EXIT 2
#define RETURN_RESULT_RESUME 3
#define RETURN_RESULT_NEW_GAME 4
#define RETURN_RESULT_BACK 5
#define RETURN_RESULT_DONE 6
#define RETURN_RESULT_CONTINUE 7
#define RETURN_RESULT_ENTER 8
#define RETURN_RESULT_CANCEL 9
#define RETURN_RESULT_CREATE_NEW_GAME 10
#define RETURN_RESULT_EXIT_GAME 11
#define RETURN_RESULT_CREATE_NEW_FROM_FILE 12

#define MENU_TYPE_INPUT 1
#define MENU_TYPE_START 2
#define MENU_TYPE_NEW_GAME 3
#define MENU_TYPE_PAUSED 4
#define MENU_TYPE_SELECT_USER 5

static  D2D1_COLOR_F SELECT_COLOR_NONE = D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f);
static  D2D1_COLOR_F SELECT_COLOR_GREEN = D2D1::ColorF(0.0f, 1.0f, 0.0f, 0.5f);
static  D2D1_COLOR_F SELECT_COLOR_RED = D2D1::ColorF(1.0f, 0.0f, 0.0f, 0.5f);
static  D2D1_COLOR_F SELECT_COLOR_BLUE = D2D1::ColorF(0.0f, 0.0f, 1.0f, 0.5f);
static  D2D1_COLOR_F FULL_COLOR_WHITE = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);
static  D2D1_COLOR_F BGRND_COLOR_BLUE = D2D1::ColorF(0.2f, 0.2f, 0.8f, 0.5f);
static  D2D1_COLOR_F BGRND_COLOR_GREEN = D2D1::ColorF(0.2f, 1.0f, 0.2f, 0.5f);
static  D2D1_COLOR_F BGRND_COLOR_BROWN = D2D1::ColorF(0.5f, 0.02f, 0.02f, 0.5f);
static  D2D1_COLOR_F BGRND_COLOR_WOOD = D2D1::ColorF((230.0f / 255.0f ),  (91.0f / 255.0f),  (30.0f / 255.0f), 0.5f);

struct ReturnType
{
	int type = RETURN_RESULT_NONE;
	int result = RETURN_RESULT_NONE;
	void* data = nullptr;
};
class UserInterface
{
protected:
	bool m_enabled = true;
public:
	
	virtual ReturnType OnMouseClick(const Vec2i& mousePos) = 0;
	virtual ReturnType OnMouseMove(const Vec2i& mousePos) = 0;
	virtual ReturnType OnKeyPress(const unsigned char& key) = 0;
	virtual void Draw(class Graphics& gfx) = 0;
	virtual bool Enabled() { return m_enabled; }
	virtual void Enabled(const bool val) { m_enabled = val; }
	
	
};
