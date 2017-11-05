#pragma once
#include "Rect.h"
#include "Vec2.h"
#include "Locator.h"
#include "RenderTarget.h"
class ViewPort : public RenderTarget
{
	RectF m_view;
	ID2D1Layer *pLayer = nullptr;
	RenderTarget * m_nextRenderTarget = nullptr;
	float m_transparency = 0.0f;
public :
	ViewPort() = default;
	ViewPort(RenderTarget* next, Vec2f& vp_size, Vec2f& windowSize);
	~ViewPort() { SafeRelease(&pLayer); }
	virtual void Rasterize(class Drawable& obj)override;
	float Width();
	float Height();
	RectF GetViewRect();
	Vec2f GetViewTopLeft();
	void BeginSceen(ID2D1Brush* brush);
	void EndSceen();
	void ResetTransparency();
	 
};