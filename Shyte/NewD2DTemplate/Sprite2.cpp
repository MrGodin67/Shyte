#include "Sprite2.h"
#include "Camera.h"
#include "Graphics.h"


void TextSprite::UpdateText(std::wstring str)
{
	
	wsprintf(this->text, L"%s", str.c_str());
}

void TextSprite::Draw(Graphics & gfx)
{
	if (drawBackground)
	{
		gfx.DrawFilledRectangle(pos.ToD2D(), backcolor);
		gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), pos.ToD2D(), color);

	}
	gfx.RenderText(text, pFormat, pos.ToD2D(), color);
}