#pragma once
#include "includes.h"
#include "SoundManager.h"
#include "DirectWrite.h"
#include "TextureManager.h"
class Locator
{
private:
	static SoundManager* m_SoundEngine;
	static ID2D1RenderTarget* m_RenderTarget;
	static TextHandler* m_TextManager;
	static TextureManager* m_ImageManager;
	static int m_screenWidth;
	static int m_screenHeight;
public:
	static void SetD2DRenderTarget(ID2D1RenderTarget* rt);
	static void SetSoundManager(SoundManager* sm);
	static void SetTextManager(TextHandler* tx);
	static void SetImageManager(TextureManager* tmgr);
	static void SetScreenDimensions(int width, int height);
	static SoundManager* SoundEngine();
	static ID2D1RenderTarget* RenderTarget();
	static TextHandler* TextManager();
	static TextureManager* ImageManager();
	static int ScreenHeight();
	static int ScreenWidth();
	
};