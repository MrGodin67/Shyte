#pragma once
#include "UserInterface.h"
#include "Sprite2.h"
class UserInput :
	public UserInterface
{
	std::string m_text;
	RectF m_drawRect = {100.0f,100.0f,300.0f,120.0f};
	RectF m_inputFrame;
	RectF m_frame;
	ID2D1Bitmap* m_image;
	
public:
	UserInput();
	~UserInput();

	// Inherited via UserInterface
	virtual ReturnType OnMouseClick(const Vec2i & mousePos) override;
	virtual ReturnType OnMouseMove(const Vec2i & mousePos) override;
	virtual ReturnType OnKeyPress(unsigned char & key) override;
	virtual void Draw(Graphics & gfx) override;
};

