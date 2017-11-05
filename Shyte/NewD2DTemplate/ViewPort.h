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
public :
	ViewPort() = default;
	ViewPort(RenderTarget* next,Vec2f& vp_size, Vec2f& windowSize)
		:m_nextRenderTarget(next)
	{
		float left = (windowSize.x * 0.5f) - (vp_size.x * 0.5f);
		float top = (windowSize.y * 0.5f) - (vp_size.y * 0.5f);
		m_view = { left,top,left + vp_size.x,top + vp_size.y };
		Locator::RenderTarget()->CreateLayer(NULL,&pLayer);
	}
	~ViewPort() { SafeRelease(&pLayer); }
	virtual void Rasterize(class Drawable& obj)override
	{
		obj.Transform(D2D1::Matrix3x2F::Translation({ (m_view.left),(m_view.top) }));

		m_nextRenderTarget->Rasterize(obj);
	};
	float Width() { return m_view.right - m_view.left; }
	float Height() { return m_view.bottom - m_view.top; }
	D2D1_RECT_F GetViewRect() { return m_view.ToD2D(); }
	Vec2f GetViewTopLeft() { return{ m_view.left,m_view.top }; }
	HRESULT BeginSceen(ID2D1Brush* brush)
	{
		Locator::RenderTarget()->PushLayer(
			D2D1::LayerParameters(
				m_view.ToD2D(),
				NULL,
				D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
				D2D1::Matrix3x2F::Translation(0.0f, 0.0f),
				1.0,
				brush,
				D2D1_LAYER_OPTIONS_NONE),

			pLayer);
		return S_OK;

	}
	HRESULT EndSceen()
	{
		Locator::RenderTarget()->PopLayer();
		return S_OK;
	}
};