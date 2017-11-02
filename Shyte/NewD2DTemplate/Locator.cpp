#include "Locator.h"

ID2D1RenderTarget* Locator::m_RenderTarget = nullptr;
SoundManager* Locator::m_SoundEngine = nullptr;
TextHandler* Locator::m_TextManager = nullptr;
TextureManager* Locator::m_ImageManager = nullptr;
int Locator::m_screenWidth = 0;
int Locator::m_screenHeight = 0;
void Locator::SetD2DRenderTarget(ID2D1RenderTarget* rt)
{
	m_RenderTarget = rt;
}

void Locator::SetSoundManager(SoundManager * sm)
{
	m_SoundEngine = sm;
}

void Locator::SetTextManager(TextHandler * tx)
{
	m_TextManager = tx;
}

void Locator::SetImageManager(TextureManager * tmgr)
{
	m_ImageManager = tmgr;
}

void Locator::SetScreenDimensions(int width, int height)
{
	m_screenWidth = width;
	m_screenHeight = height;
}

SoundManager * Locator::SoundEngine()
{
	return m_SoundEngine;
}

ID2D1RenderTarget * Locator::RenderTarget()
{
	return m_RenderTarget;
}

TextHandler * Locator::TextManager()
{
	return m_TextManager;
}

TextureManager * Locator::ImageManager()
{
	return m_ImageManager;
}

//int Locator::ScreenHeight()
//{
//	return m_screenHeight;
//}
//
//int Locator::ScreenWidth()
//{
//	return m_screenWidth;
//}
