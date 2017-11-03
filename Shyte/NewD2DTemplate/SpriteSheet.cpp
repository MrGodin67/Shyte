#include "SpriteSheet.h"
#include "Locator.h"
SpriteSheet::SpriteSheet(std::wstring filename, float clipWidth, float clipHeight)
	:clipWidth(clipWidth),clipHeight(clipHeight)
{
	texture = std::make_unique<D2D1Texture>(Locator::RenderTarget(), filename);
	assert(texture);
	width = (float)texture->Width();
	height = (float)texture->Height();
	columns = (int)(width / clipWidth);
}

SpriteSheet::~SpriteSheet()
{
}

RectF SpriteSheet::GetClippedImage(const int & index)
{
	
	int col = index % columns;
	int row =  index / columns;
	return RectF((float)col*clipWidth,(float)row*clipHeight,
		((float)col*clipWidth)+clipWidth,((float)row*clipHeight)+clipHeight);
}

int SpriteSheet::Columns()
{
	return columns;
}

ID2D1Bitmap * SpriteSheet::GetTexture()
{
	return texture->GetBitmap();
}
