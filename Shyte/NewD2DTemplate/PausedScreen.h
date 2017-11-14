#pragma once
#include "UserInterface.h"
class PausedScreen :
	public UserInterface
{
	RectF m_frame;
	ID2D1Bitmap* m_image;
	RectF m_buttons[3];
	D2D1_COLOR_F m_selectColors[3] =
	{
		SELECT_COLOR_NONE ,
		SELECT_COLOR_NONE ,
		SELECT_COLOR_NONE
	};
public:
	PausedScreen();
	~PausedScreen();

	// Inherited via UserInterface
	virtual ReturnType OnMouseClick(const Vec2i & mousePos) override;
	virtual ReturnType OnMouseMove(const Vec2i & mousePos) override;
	virtual ReturnType OnKeyPress(const unsigned char & key) override;
	virtual void Draw(Graphics & gfx) override;
};

