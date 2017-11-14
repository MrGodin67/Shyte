#pragma once

#include "AnimationSequence.h"


class TextSprite
{
protected:
	D2D1_COLOR_F color;
	D2D1_COLOR_F backcolor;
	RectF pos;
	WCHAR text[512];
	bool drawBackground;
	IDWriteTextFormat* pFormat;
public:
	TextSprite() {}
	TextSprite(IDWriteTextFormat* format, RectF pos, std::wstring text, D2D1_COLOR_F color, D2D1_COLOR_F backColor = D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), bool drawBack = false)
		:pFormat(format), pos(pos), color(color), backcolor(backColor), drawBackground(drawBack)
	{
		wsprintf(this->text, L"%s", text.c_str());
	
	}
	virtual ~TextSprite() {}
	virtual void UpdateText(std::wstring str);
	virtual void Draw(class Graphics& gfx);

};


