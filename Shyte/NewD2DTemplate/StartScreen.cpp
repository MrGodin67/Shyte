#include "StartScreen.h"
#include "Locator.h"
#include "Graphics.h"
#include "Camera.h"


StartScreen::StartScreen()
{
	
	m_image = Locator::ImageManager()->GetImage("start_screen")->GetTexture();
	float x = (Locator::ScreenWidth<float>() / 2) - (float)(m_image->GetSize().width / 2);
	float y = (Locator::ScreenHeight<float>() / 2) - (float)(m_image->GetSize().height / 2);
	m_frame = { x ,y,x + (float)m_image->GetSize().width ,y + (float)m_image->GetSize().height};
	
	m_buttons[0] = { x + 56.0f,y + 424.0f,x + 168.0f,y + 456.0f };
	m_buttons[1] = { x + 184.0f,y + 424.0f,x + 320.f,y + 456.0f };
	m_buttons[2] = { x + 392.0f,y + 424.0f,x + 448.0f,y + 456.0f };
}

StartScreen::~StartScreen()
{
}

ReturnType StartScreen::OnMouseClick(const Vec2i & mousePos)
{
	ReturnType type;
	if (m_enabled)
	{
		type.type = MENU_TYPE_START;
		if (m_enableContinue)
		{
			if (m_buttons[0].Contains(mousePos))
				type.result = RETURN_RESULT_CONTINUE;
		}
		if (m_buttons[1].Contains(mousePos))
			type.result = RETURN_RESULT_NEW_GAME;
		if (m_buttons[2].Contains(mousePos))
			type.result = RETURN_RESULT_EXIT;
	}
	return type;
}

ReturnType StartScreen::OnKeyPress(const unsigned char & key)
{
	return ReturnType();
}

void StartScreen::Draw(Graphics& gfx)
{
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), m_image);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), FULL_COLOR_WHITE);

	for (int c = 0; c < 3; c++)
	{
		if (!m_enableContinue && c == 0)
			continue;
		gfx.DrawFilledRectangle(m_buttons[c].ToD2D(), m_selectColors[c]);
		gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_buttons[c].ToD2D(), FULL_COLOR_WHITE);
	}
	
}

ReturnType StartScreen::OnMouseMove(const Vec2i & mousePos)
{
	ReturnType result;
	if (m_enabled)
	{
		for (int c = 0; c < 3; c++)
		{
			if (!m_enableContinue && c == 0)
				continue;
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

void StartScreen::EnableContinueButton(bool val)
{
	m_enableContinue = val;
}

