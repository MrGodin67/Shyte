#include "UserInput.h"
#include "Locator.h"
#include "Graphics.h"
#include "Camera.h"
#include "StringHandler.h"

UserInput::UserInput()
{
	m_image = Locator::ImageManager()->GetImage("input_screen")->GetTexture();
	float x = (Locator::ScreenWidth<float>() / 2) - (float)(m_image->GetSize().width / 2);
	float y = (Locator::ScreenHeight<float>() / 2) - (float)(m_image->GetSize().height / 2);
	m_frame = { x ,y,x + (float)m_image->GetSize().width ,y + (float)m_image->GetSize().height };
	m_inputFrame = { x + 20.0f ,y + 80.0f,x + ((float)m_image->GetSize().width -20.0f) ,y + 102.0f };
	m_drawRect = { m_inputFrame.left + 4.0f,m_inputFrame.top + 4.0f,m_inputFrame.right,m_inputFrame.bottom };
}


UserInput::~UserInput()
{
}

ReturnType UserInput::OnMouseClick(const Vec2i & mousePos)
{
	return ReturnType();
}

ReturnType UserInput::OnMouseMove(const Vec2i & mousePos)
{
	return ReturnType();
}

ReturnType UserInput::OnKeyPress(unsigned char & key)
{
	ReturnType result;
	result.type = MENU_TYPE_INPUT;
	if (key == VK_RETURN)
	{
		if (m_text.size() > 0)
		{
			while (m_text.front() == ' ')
				m_text.erase(m_text.begin());
			while (m_text.back() == ' ')
				m_text.pop_back();
			result.result = RETURN_ENTER;
			result.data = &m_text;
			return result;
		}
	}
	if (key == VK_BACK)
	{
		if(m_text.size() > 0)
		   m_text.erase(m_text.begin() + m_text.size() - 1);
	}
	else
	{
		int iKey = (int)key;
		if ((iKey > 64 && iKey < 91) || (iKey > 47 && iKey < 58) || iKey == 32)
		{
			if (m_text.size() < 16u)
				m_text.push_back(key);
		}
	}
	return ReturnType();
}

void UserInput::Draw(Graphics & gfx)
{
	std::wstring out_text;
	DXStringHandler::DXConvertFromStrToWStr(m_text, out_text);
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), m_image);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), FULL_COLOR_WHITE);
	gfx.DrawFilledScreenRectangle(m_inputFrame.ToD2D(), SELECT_COLOR_BLUE);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_inputFrame.ToD2D(), FULL_COLOR_WHITE);
	gfx.RenderText((LPWSTR)out_text.c_str(), Locator::TextManager()->GetFormat("Tahoma12"),
		m_drawRect.ToD2D(), FULL_COLOR_WHITE);
}
