#pragma once
#include "includes.h"
#include "D2D1Texture.h"


class SpriteSheet
{
	float width;
	float height;
	float clipWidth;
	float clipHeight;
	int columns;
	std::unique_ptr<D2D1Texture> texture;
public:
	SpriteSheet(std::wstring filename,float clipWidth,float clipHeight);
	~SpriteSheet();
	RectF GetClippedImage(const int& index);
	int Columns();
	ID2D1Bitmap* GetTexture();
};
