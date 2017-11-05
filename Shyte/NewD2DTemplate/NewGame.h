#pragma once

#include "UserInterface.h"
#include "Player.h"
#include "coredata.h"
class NewGame : public UserInterface
{
	struct Players
	{
		RectF frame;
		MainPlayerData info = {};
	};
	RectF        m_frame;
	ID2D1Bitmap* m_image;
	RectF        m_buttons[2];
	Players      m_players[4];
	Players*     m_selectedPlayer;
	D2D1_COLOR_F m_selectButtonColors[2] =
	{
		SELECT_COLOR_NONE ,
		SELECT_COLOR_NONE
	};
	
public:
	NewGame();

	// Inherited via UserInterface
	virtual ReturnType OnMouseClick(const Vec2i & mousePos) override;
	virtual ReturnType OnMouseMove(const Vec2i & mousePos)override;
	virtual ReturnType OnKeyPress(unsigned char & key) override;
	virtual void Draw(Graphics & gfx) override;
	
};