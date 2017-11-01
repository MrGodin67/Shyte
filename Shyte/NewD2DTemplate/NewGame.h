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
	RectF m_frame;
	ID2D1Bitmap* m_image;
	RectF m_buttons[2];
	Players m_players[4];
	Players* m_selectedPlayer;

	
public:
	NewGame();

	// Inherited via UserInterface
	virtual MouseReturnType OnMouseClick(const Vec2i & mousePos) override;
	virtual void OnKeyPress(unsigned char & key) override;
	virtual void Draw(Graphics & gfx) override;
	
};