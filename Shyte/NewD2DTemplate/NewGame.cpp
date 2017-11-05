#include "NewGame.h"
#include "Locator.h"
#include "Graphics.h"
NewGame::NewGame()
{
	m_image = Locator::ImageManager()->GetImage("new_game")->GetTexture();
	float x = (Locator::ScreenWidth<float>() / 2) - (float)(m_image->GetSize().width / 2);
	float y = (Locator::ScreenHeight<float>() / 2) - (float)(m_image->GetSize().height / 2);
	m_frame = { x ,y,x + (float)m_image->GetSize().width ,y + (float)m_image->GetSize().height };

	m_buttons[0] = {x+56.0f,y+426.0f,x+130.0f,y+460.0f };
	m_buttons[1] = {x+376.0f,y + 426.0f,x+460.0f,y+ 460.0f };

	m_players[0].frame = {x+45.0f,y+65.0f,x+111.0f,y+138.0f};
	sprintf_s(m_players[0].info.data.name, "%s", "Maria");
	m_players[0].info.core = InitialPlayerCoreData::Get("maria");

	m_players[1].frame = {x+45.0f,y+142.0f,x+111.0f,y+214.0f};
	sprintf_s(m_players[1].info.data.name, "%s", "Hannah");
	m_players[1].info.core = InitialPlayerCoreData::Get("hannah");

	m_players[2].frame = {x+46.0f,y+222.0f,x+111.0f,y+293.0f};
	sprintf_s(m_players[2].info.data.name, "%s", "Jack");
	m_players[2].info.core = InitialPlayerCoreData::Get("jack");

	m_players[3].frame = {x+45.0f,y+300.0f,x+111.0f,y+372.0f};
	sprintf_s(m_players[3].info.data.name, "%s", "Colin");
	m_players[3].info.core = InitialPlayerCoreData::Get("colin");
}

ReturnType NewGame::OnMouseClick(const Vec2i & mousePos)
{
	ReturnType type;
	if (m_enabled)
	{
		type.type = MENU_TYPE_NEW_GAME;
		if (m_buttons[0].Contains(mousePos))
		{
			type.result = RETURN_RESULT_BACK;
			m_selectedPlayer = nullptr;
		}

		if (m_buttons[1].Contains(mousePos) && m_selectedPlayer)
		{
			type.result = RETURN_RESULT_DONE;
			type.data = &m_selectedPlayer->info;

		}
		for (int c = 0; c < 4; c++)
		{
			if (m_players[c].frame.Contains(mousePos))
			{
				m_selectedPlayer = &m_players[c];
			}

		}
	}
	return type;
}

ReturnType NewGame::OnMouseMove(const Vec2i & mousePos)
{
	ReturnType result;
	if (m_enabled)
	{
		if (m_selectedPlayer)
		{
			if (m_buttons[1].Contains(mousePos))
			{
				m_selectButtonColors[1] = SELECT_COLOR_BLUE;
			}
			else
				m_selectButtonColors[1] = SELECT_COLOR_NONE;
		}

		if (m_buttons[0].Contains(mousePos))
		{
			m_selectButtonColors[0] = SELECT_COLOR_BLUE;
		}
		else
			m_selectButtonColors[0] = SELECT_COLOR_NONE;
	}
	return result;
}

ReturnType NewGame::OnKeyPress(unsigned char & key)
{
	return ReturnType();
}

void NewGame::Draw(Graphics & gfx)
{
	
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), m_image);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_buttons[1].ToD2D(), FULL_COLOR_WHITE);
	if(!m_enabled)
		gfx.DrawFilledScreenRectangle(m_frame.ToD2D(), D2D1::ColorF(0.5f,0.25f,0.25f,0.5f));

	gfx.DrawFilledScreenRectangle(m_buttons[0].ToD2D(), m_selectButtonColors[0]);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_buttons[0].ToD2D(), FULL_COLOR_WHITE);

	if (m_selectedPlayer)
	{
		gfx.DrawFilledScreenRectangle(m_buttons[1].ToD2D(), m_selectButtonColors[1]);
		gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_buttons[1].ToD2D(), FULL_COLOR_WHITE);
		gfx.DrawFilledScreenRectangle(m_selectedPlayer->frame.ToD2D(), SELECT_COLOR_BLUE);
	}
	
}


