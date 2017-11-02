#pragma once

#include "UserInterface.h"
#include "Player.h"

class NewGame : public UserInterface
{
	struct Players
	{
		RectF frame;
		PlayerData data = {};
	};
	RectF        m_frame;
	ID2D1Bitmap* m_image;
	RectF        m_buttons[2];
	Players      m_players[4];
	Players*     m_selectedPlayer;
	D2D1_COLOR_F m_selectButtonColors[2] =
	{
		SELECT_COLOR_GREEN ,
		SELECT_COLOR_GREEN
	};
	
public:
	NewGame();

	// Inherited via UserInterface
	virtual MouseReturnType OnMouseClick(const Vec2i & mousePos) override;
	virtual MouseReturnType OnMouseMove(const Vec2i & mousePos)override;
	virtual void OnKeyPress(unsigned char & key) override;
	virtual void Draw(Graphics & gfx) override;
	
};