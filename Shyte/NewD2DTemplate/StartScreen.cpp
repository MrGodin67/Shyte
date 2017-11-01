#include "StartScreen.h"
#include "Locator.h"
#include "Graphics.h"
#include "Camera.h"


StartScreen::StartScreen()
{
	
	m_image = Locator::ImageManager()->GetImage("start_screen")->GetTexture();
	float x = (float)(Locator::ScreenWidth() / 2) - (float)(m_image->GetSize().width / 2);
	float y = (float)(Locator::ScreenHeight() / 2) - (float)(m_image->GetSize().height / 2);
	m_frame = { x ,y,x + (float)m_image->GetSize().width ,y + (float)m_image->GetSize().height};
	
	m_buttons[0] = { x+16.0f,y+16.0f * 6.0f,x+16.0f* 5.0f,y+16.0f * 7.0f };
	m_buttons[1] = { x+16.0f*11.0f,y+16.0f * 6.0f,x+16.0f* 15.0f,y+16.0f * 7.0f };
}

StartScreen::~StartScreen()
{
}

MouseReturnType StartScreen::OnMouseClick(const Vec2i & mousePos)
{
	MouseReturnType type;
	if (m_buttons[0].Contains(mousePos))
		type.type = RETURN_START;

	if (m_buttons[1].Contains(mousePos))
		type.type = RETURN_NEW;

	return type;
}

void StartScreen::OnKeyPress(unsigned char & key)
{
}

void StartScreen::Draw(Graphics& gfx)
{
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), m_image);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_buttons[0].ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_buttons[1].ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
}

