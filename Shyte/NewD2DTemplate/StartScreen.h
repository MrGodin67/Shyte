#pragma once

#include "UserInterface.h"

class StartScreen : public UserInterface
{
	RectF m_frame;
	ID2D1Bitmap* m_image;
	RectF m_buttons[2];
public:

	StartScreen();

	~StartScreen();
	// Inherited via UserInterface
	virtual MouseReturnType OnMouseClick(const Vec2i & mousePos) override;

	virtual void OnKeyPress(unsigned char & key) override;

	virtual void Draw(class Graphics& gfx) override;
	

};