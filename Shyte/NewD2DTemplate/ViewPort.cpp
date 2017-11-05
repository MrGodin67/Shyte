#include "ViewPort.h"
#include "Drawable.h"
ViewPort::ViewPort(RenderTarget * next, Vec2f & vp_size, Vec2f & windowSize)
	:m_nextRenderTarget(next)
{
	float left = (windowSize.x * 0.5f) - (vp_size.x * 0.5f);
	float top = (windowSize.y * 0.5f) - (vp_size.y * 0.5f);
	m_view = { left,top,left + vp_size.x,top + vp_size.y };
	Locator::RenderTarget()->CreateLayer(NULL, &pLayer);
}

void ViewPort::Rasterize(Drawable & obj)
{
		obj.Transform(D2D1::Matrix3x2F::Translation({ m_view.left,m_view.top }));
		m_nextRenderTarget->Rasterize(obj);
}

float ViewPort::Width()
{
	return m_view.right - m_view.left;
}

float ViewPort::Height()
{
	return m_view.bottom - m_view.top;
}

RectF ViewPort::GetViewRect()
{
	return m_view;
}

Vec2f ViewPort::GetViewTopLeft()
{
	return{ m_view.left,m_view.top };
}

void ViewPort::BeginSceen(ID2D1Brush * brush)

{
	m_transparency += 0.0160f;
	if (m_transparency > 1.0f)m_transparency = 1.0f;
	Locator::RenderTarget()->PushLayer(	D2D1::LayerParameters(
			m_view.ToD2D(),NULL,D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
			D2D1::Matrix3x2F::Identity(), m_transparency,brush,D2D1_LAYER_OPTIONS_NONE),
			pLayer);


}

void ViewPort::EndSceen()
{
	Locator::RenderTarget()->PopLayer();
	
}

void ViewPort::ResetTransparency()
{
	m_transparency = 0.0f;
}
