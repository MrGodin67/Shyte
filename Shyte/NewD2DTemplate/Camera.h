#pragma once


#include "includes.h"
#include "Vec2.h"
#include "Rect.h"
#include "RenderTarget.h"
class Camera : public RenderTarget
{
	RenderTarget * m_nextRenderTarget = nullptr;
public:// next = vp
	Camera(RenderTarget * next,float width, float height);
	virtual void Rasterize(class Drawable& obj)override;
	Vec2f GetPosition();
	void ConfineToMap(RectF& map_frame);
	void Resize(float& w, float& h);
	void UpdatePosition(Vec2f& in_pos);
	Vec2f ConvertToWorldSpace(Vec2f in_pos);
	RectF GetViewFrame();
	void Scroll(Vec2f& dir);
private:
	
	Vec2f m_pos;
	Vec2f m_center;
	Vec2f m_scroll_pos;
	RectF m_mapFrame;
	RectF m_viewFrame;
	float m_screen_width, m_screen_height;
};
