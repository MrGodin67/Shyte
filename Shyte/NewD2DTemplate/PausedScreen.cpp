#include "PausedScreen.h"
#include "Locator.h"
#include "Graphics.h"
#include "Camera.h"


PausedScreen::PausedScreen()
{
	m_image = Locator::ImageManager()->GetImage("paused_screen")->GetTexture();
	float x = (Locator::ScreenWidth<float>() / 2) - (float)(m_image->GetSize().width / 2);
	float y = (Locator::ScreenHeight<float>() / 2) - (float)(m_image->GetSize().height / 2);
	m_frame = { x ,y,x + (float)m_image->GetSize().width ,y + (float)m_image->GetSize().height };

	m_buttons[0] = { x + 29.0f,y + 97.0f,x + 74.0f,y + 112.0f };
	m_buttons[1] = { x + 192.0f,y + 97.0f,x + 237.f,y + 112.0f };
	
}


PausedScreen::~PausedScreen()
{
}

ReturnType PausedScreen::OnMouseClick(const Vec2i & mousePos)
{
	ReturnType type;
	if (m_enabled)
	{
		type.type = MENU_TYPE_PAUSED;
		if (m_buttons[0].Contains(mousePos))
			type.result = RETURN_RESULT_RESUME;
		if (m_buttons[1].Contains(mousePos))
			type.result = RETURN_RESULT_EXIT;
	}
	return type;
}

ReturnType PausedScreen::OnMouseMove(const Vec2i & mousePos)
{
	ReturnType result;
	if (m_enabled)
	{
		for (int c = 0; c < 2; c++)
		{
			if (m_buttons[c].Contains(mousePos))
			{
				m_selectColors[c] = SELECT_COLOR_BLUE;
			}
			else
				m_selectColors[c] = SELECT_COLOR_NONE;
		}
	}
	return result;
}

ReturnType PausedScreen::OnKeyPress(const unsigned char & key)
{
	return ReturnType();
}

void PausedScreen::Draw(Graphics & gfx)
{
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), m_image);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), FULL_COLOR_WHITE);

	for (int c = 0; c < 2; c++)
	{
		gfx.DrawFilledRectangle(m_buttons[c].ToD2D(), m_selectColors[c]);
		gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_buttons[c].ToD2D(), FULL_COLOR_WHITE);
	}
}
