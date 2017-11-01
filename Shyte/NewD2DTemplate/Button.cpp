#include "Button.h"
#include "Graphics.h"

Button::Button(RectF frame, ID2D1Bitmap * image, int returnType)
  :m_frame(frame),m_image(image)
{
	m_returnType.type = returnType;
}
MouseReturnType Button::OnMouseClick(const Vec2i & mousePos)
{
	if (m_frame.Contains(mousePos))
		return m_returnType;

	return MouseReturnType();
}

void Button::OnKeyPress(unsigned char & key)
{
}

void Button::Draw(Graphics & gfx)
{
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), m_image);
}
