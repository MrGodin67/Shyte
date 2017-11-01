#include "NewGame.h"
#include "Locator.h"
#include "Graphics.h"
NewGame::NewGame()
{
	m_image = Locator::ImageManager()->GetImage("new_game")->GetTexture();
	float x = (float)(Locator::ScreenWidth() / 2) - (float)(m_image->GetSize().width / 2);
	float y = (float)(Locator::ScreenHeight() / 2) - (float)(m_image->GetSize().height / 2);
	m_frame = { x ,y,x + (float)m_image->GetSize().width ,y + (float)m_image->GetSize().height };

	m_buttons[0] = {x+56.0f,y+426.0f,x+130.0f,y+460.0f };
	m_buttons[1] = {x+376.0f,y + 426.0f,x+460.0f,y+ 460.0f };

	m_players[0].frame = {x+45.0f,y+65.0f,x+111.0f,y+138.0f};
	sprintf_s(m_players[0].data.name, "%s", "maria");
	m_players[1].frame = {x+45.0f,y+142.0f,x+111.0f,y+214.0f};
	sprintf_s(m_players[1].data.name, "%s", "hannah");
	m_players[2].frame = {x+46.0f,y+222.0f,x+111.0f,y+293.0f};
	sprintf_s(m_players[2].data.name, "%s", "jack");
	m_players[3].frame = {x+45.0f,y+300.0f,x+111.0f,y+372.0f};
	sprintf_s(m_players[3].data.name, "%s", "colin");
}

MouseReturnType NewGame::OnMouseClick(const Vec2i & mousePos)
{
	MouseReturnType type;
	
	if (m_buttons[0].Contains(mousePos))
		type.type = RETURN_NEW_BACK;

	if (m_buttons[1].Contains(mousePos) && m_selectedPlayer)
	{
		type.type = RETURN_NEW_DONE;
		type.data = &m_selectedPlayer->data;
	}
	for (int c = 0; c < 4; c++)
	{
		if (m_players[c].frame.Contains(mousePos))
		{
			m_selectedPlayer = &m_players[c];
		}
		
	}
	return type;
}

void NewGame::OnKeyPress(unsigned char & key)
{
}

void NewGame::Draw(Graphics & gfx)
{
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), m_image);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_buttons[0].ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	if (m_selectedPlayer)
	{
		gfx.DrawFilledScreenRectangle(m_buttons[1].ToD2D(), D2D1::ColorF(1.0f, 0.0f, 0.0f, 0.5f));
		gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_buttons[1].ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
		gfx.DrawFilledScreenRectangle(m_selectedPlayer->frame.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.4f));
	}
	
}


