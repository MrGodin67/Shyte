#include "SelectUsers.h"

#include "Graphics.h"
#include "Locator.h"
#include "StringHandler.h"
SelectUsers::SelectUsers()
{
	m_image = Locator::ImageManager()->GetImage("select_user")->GetTexture();
	float x = (Locator::ScreenWidth<float>() / 2) - (float)(m_image->GetSize().width / 2);
	float y = (Locator::ScreenHeight<float>() / 2) - (float)(m_image->GetSize().height / 2);
	m_frame = { x ,y,x + (float)m_image->GetSize().width ,y + (float)m_image->GetSize().height };

	m_textDisplayFrame = { x+32.0f*2.0f,y+32.0f * 3,x+(512.0f - (32.0f*2.0f)),y+32.0f* 12.0f };
	m_buttons[0] = RectF(x+68.0f, y+426.0f, x+144.0f, y+458.0f);
	m_buttons[1] = RectF(x + 362.0f, y + 426.0f, x + 454.0f, y + 458.0f);
	pFormat = Locator::TextManager()->GetFormat("Tahoma12");
	m_textColor = FULL_COLOR_WHITE;
	Vec2f pos = { m_textDisplayFrame.left + 4.0f,m_textDisplayFrame.top + 4.0f };

	for (int c = 0; c < 10; c++)
	{
		m_lines[c].frame = { pos.x,pos.y,m_textDisplayFrame.right,pos.y + 22.0f };
		pos.y += 22.0f;
	}
	
}


SelectUsers::~SelectUsers()
{
}

ReturnType SelectUsers::OnMouseClick(const Vec2i & mousePos)
{
	ReturnType type;
	if (m_enabled)
	{
		type.type = MENU_TYPE_SELECT_USER;
		if (m_buttons[0].Contains(mousePos) && m_selectedIndex > -1)
		{
			type.result = RETURN_RESULT_BACK;
			type.data = &m_selectedUser;
			m_selectedIndex = -1;
		}

		if (m_buttons[1].Contains(mousePos))
		{
			type.result = RETURN_RESULT_CANCEL;

			m_selectedIndex = -1;
		}
		
		for (int c = 0; c < m_usersNames.size(); c++)
		{
			m_lines[c].selected = false;
			if (m_lines[c].frame.Contains(mousePos))
			{
				m_selectedIndex = c;
				m_selectedUser = m_usersNames[c];
				m_selectedRect = m_lines[c].frame;
				m_selectedRect.left -= 1.0f;
				m_selectedRect.top -= 1.0f;
				m_selectedRect.bottom -= 1.0f;
				m_lines[c].selected = true;
				m_isSelected = true;
			}
		}
	}
	return type;
}

ReturnType SelectUsers::OnMouseMove(const Vec2i & mousePos)
{
	ReturnType result;
	if (m_enabled)
	{
		if (!m_isSelected)
			GetSelected(Vec2f(mousePos));

		if (m_buttons[1].Contains(mousePos))
		{
			m_selectButtonColors[1] = SELECT_COLOR_BLUE;
		}
		else
			m_selectButtonColors[1] = SELECT_COLOR_NONE;


		if (m_buttons[0].Contains(mousePos))
		{
			m_selectButtonColors[0] = SELECT_COLOR_BLUE;
		}
		else
			m_selectButtonColors[0] = SELECT_COLOR_NONE;
	}
	return result;
}

ReturnType SelectUsers::OnKeyPress(unsigned char & key)
{
	return ReturnType();
}

void SelectUsers::Draw(Graphics & gfx)
{
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), m_image);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), FULL_COLOR_WHITE);
	if (!m_enabled)
		gfx.DrawFilledScreenRectangle(m_frame.ToD2D(), D2D1::ColorF(0.5f, 0.25f, 0.25f, 0.5f));
	gfx.DrawFilledScreenRectangle(m_buttons[0].ToD2D(), m_selectButtonColors[0]);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_buttons[0].ToD2D(), FULL_COLOR_WHITE);
	gfx.DrawFilledScreenRectangle(m_buttons[1].ToD2D(), m_selectButtonColors[1]);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_buttons[1].ToD2D(), FULL_COLOR_WHITE);
	gfx.DrawFilledScreenRectangle(m_textDisplayFrame.ToD2D(), BGRND_COLOR_WOOD);
	for (int c = 0; c < m_usersNames.size(); c++)
	{
		std::wstring str;
		DXStringHandler::DXConvertFromStrToWStr(m_usersNames[c], str);
		
		if (m_lines[c].selected)
		{

			gfx.DrawFilledScreenRectangle(m_selectedRect.ToD2D(), SELECT_COLOR_BLUE);
		}
		else
			gfx.RenderText((LPWSTR)str.c_str(), pFormat, m_lines[c].frame.ToD2D(), BGRND_COLOR_WOOD);
		
		gfx.RenderText((LPWSTR)str.c_str(), pFormat, m_lines[c].frame.ToD2D(), m_textColor);
			

	}
	
}

void SelectUsers::SetUsers(std::vector<std::string>& users)
{
	m_usersNames = users;
	
}

void SelectUsers::GetSelected(Vec2f & mousePos)
{
	
	for (int c = 0; c < m_usersNames.size(); c++)
	{
		
		if (m_lines[c].frame.Contains(mousePos))
		{
			
			
			m_selectedRect = m_lines[c].frame;
			m_selectedRect.left -= 4.0f;
			m_selectedRect.top -= 4.0f;
			m_selectedRect.bottom -= 4.0f;
			
		}
	}
}
