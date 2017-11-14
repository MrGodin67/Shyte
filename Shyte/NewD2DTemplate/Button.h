#pragma once
#include "UserInterface.h"

class Button : public UserInterface
{
	RectF m_frame;
	ID2D1Bitmap* m_image;
	ReturnType m_returnType;
public:
	Button() = default;
	Button(RectF frame, ID2D1Bitmap* image,int returnValue);
	// Inherited via UserInterface
	virtual ReturnType OnMouseClick(const Vec2i & mousePos) override;
	virtual ReturnType OnKeyPress(const unsigned char & key) override;
	virtual void Draw(Graphics & gfx) override;
};