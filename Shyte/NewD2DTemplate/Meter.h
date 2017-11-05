#pragma once

#include "includes.h"
#include "Rect.h"
#include "Vec2.h"
#include "Drawable.h"
// Create as horizonatal/vertical via mainFrame rect ie: height > width
class Meter
{
	RectF m_mainFrame;
	RectF m_meterRect;
	RectF m_textRect;
	float m_width;
	float m_height;
	bool m_vertical;
	int m_maxValue;
	D2D1_COLOR_F m_backColor;
	D2D1_COLOR_F m_meterColor;
	D2D1_COLOR_F m_textColor;

	IDWriteTextFormat* pTextFormat = nullptr;
	std::wstring m_caption;
	float m_textRectOffset;
public:
	Meter() = default;
	Meter(int& maxvalue, RectF mainFrame, RectF& meter_color, RectF& back_color, RectF& text_color,std::string textFont);
	void Update(const int& val);
	void Draw(class Graphics& gfx);
	void SetCaption(std::string& text);
	class Drawable : public ::Drawable
	{
		Meter& m_parent;

	public:
		Drawable(Meter& p);
		virtual ~Drawable() {};
		virtual void Rasterize(class Graphics& gfx)override;
		virtual void TranslateCoords(const Vec2f& pos)override;
		virtual void Transform(const D2D1::Matrix3x2F& mat)override;
	};
	Drawable GetDrawable();
};