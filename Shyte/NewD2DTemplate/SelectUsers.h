#pragma once
#include "UserInterface.h"
class SelectUsers :
	public UserInterface
{
	struct TextLine
	{
		RectF frame;
		bool selected = false;
	};
	D2D1_COLOR_F m_textColor;
	IDWriteTextFormat* pFormat;
	int m_nextLineIndex;
	ID2D1Bitmap* m_image;
	std::string m_selectedUser;
	int m_selectedIndex = -1;
	bool m_isSelected = false;
	RectF m_frame;
	RectF m_textDisplayFrame;
	RectF m_selectedRect;
	RectF m_buttons[2] =
	{
		RectF(68.0f,426.0f,144.0f,458.0f),
		RectF(362.0f,426.0f,454.0f,458.0f)
	};
	D2D1_COLOR_F m_selectButtonColors[2] =
	{
		SELECT_COLOR_NONE ,
		SELECT_COLOR_BLUE
	};
	TextLine m_lines[10];
	std::vector<std::string> m_usersNames;
public:
	SelectUsers();
	~SelectUsers();

	// Inherited via UserInterface
	virtual ReturnType OnMouseClick(const Vec2i & mousePos) override;
	virtual ReturnType OnMouseMove(const Vec2i & mousePos) override;
	virtual ReturnType OnKeyPress(const unsigned char & key) override;
	virtual void Draw(Graphics & gfx) override;
	void SetUsers(std::vector<std::string>& users);
private:
	void GetSelected(Vec2f& mousePos);
};

