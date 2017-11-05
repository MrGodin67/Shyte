
#include "Camera.h"
#include "Drawable.h"

Camera::Camera(RenderTarget * next,float width, float height)
	:
	m_pos({ 0.0f,0.0f }),
	m_center({ width / 2.0f,height / 2.0f }),
	m_screen_width(width),
	m_screen_height(height),
	m_nextRenderTarget(next)
{
	
	m_viewFrame.left = m_pos.x;
	m_viewFrame.top = m_pos.y;
	m_viewFrame.right = m_viewFrame.left + m_screen_width;
	m_viewFrame.bottom = m_viewFrame.top + m_screen_height;
	Resize(width, height);
	m_scroll_pos = m_center;
}
void Camera::Rasterize(Drawable & obj)
{
	obj.Transform(D2D1::Matrix3x2F::Translation({ -(m_pos.x ),-(m_pos.y) }));
	
	m_nextRenderTarget->Rasterize(obj);
}
void Camera::Scroll(Vec2f& dir)
{
	
	m_scroll_pos += dir;
	if (m_scroll_pos.x < m_center.x)m_scroll_pos.x = m_center.x;
	if (m_scroll_pos.x > m_mapFrame.right -m_center.x)m_scroll_pos.x = m_mapFrame.right - m_center.x;
	if (m_scroll_pos.y < m_center.y)m_scroll_pos.y = m_center.y;
	if (m_scroll_pos.y > m_mapFrame.bottom - m_center.y)m_scroll_pos.y = m_mapFrame.bottom - m_center.y;

	this->UpdatePosition(m_scroll_pos);

}


Vec2f Camera::GetPosition() { return m_pos; }
void Camera::ConfineToMap(RectF& map_frame) { m_mapFrame = map_frame; }

Vec2f Camera:: ConvertToWorldSpace(Vec2f in_pos)
{
	return Vec2f (in_pos + m_pos);
}
RectF Camera::GetViewFrame()
{
	return m_viewFrame;
}
void Camera::Resize(float& w, float& h)
{
	m_screen_width = w;
	m_screen_height = h;
	m_center = Vec2f(m_screen_width / 2, m_screen_height / 2);
	m_viewFrame.left = m_pos.x;
	m_viewFrame.top = m_pos.y;
	m_viewFrame.right = m_viewFrame.left + m_screen_width;
	m_viewFrame.bottom = m_viewFrame.top + m_screen_height;

};

void Camera::UpdatePosition(Vec2f& in_pos)
{
	
	m_pos = in_pos  - m_center ;
	
	m_pos.x = __max(m_pos.x, m_mapFrame.left);
	m_pos.y = __max(m_pos.y, m_mapFrame.top);
	m_pos.x = __min(m_pos.x, m_mapFrame.right - m_screen_width);
	m_pos.y = __min(m_pos.y, (m_mapFrame.bottom - m_screen_height) );
	m_pos.y = __max(m_pos.y, 0.0f);

	m_viewFrame.left = m_pos.x;
	m_viewFrame.top = m_pos.y;
	m_viewFrame.right = m_viewFrame.left + m_screen_width;
	m_viewFrame.bottom = m_viewFrame.top + m_screen_height;
}
