#include "Meter.h"
#include "Graphics.h"
#include "Locator.h"
#include "StringHandler.h"
Meter::Meter(int& maxvalue, RectF mainFrame, RectF& meter_color, RectF& back_color,  RectF& text_color,std::string textFont)
	:m_maxValue(maxvalue),m_mainFrame(mainFrame),m_vertical(false)
{
	m_meterColor = D2D1::ColorF(meter_color.r, meter_color.g, meter_color.b, meter_color.a);
	m_backColor = D2D1::ColorF(back_color.r, back_color.g, back_color.b, back_color.a);
	m_textColor = D2D1::ColorF(text_color.r, text_color.g, text_color.b, text_color.a);
	std::string str = textFont.substr(textFont.size() - 2, 2);
	m_textRectOffset = (float)atoi(str.c_str()) + 4.0f;
	pTextFormat = Locator::TextManager()->GetFormat(textFont);

	m_width = m_mainFrame.right - m_mainFrame.left;
	m_height = m_mainFrame.bottom - m_mainFrame.top;
	// if height is greater than width then ... yup it's vertical
	m_vertical = m_height > m_width;
	if (m_vertical)
	{
		m_textRect = RectF(m_mainFrame.left, m_mainFrame.bottom, 400.0f, m_mainFrame.bottom + m_textRectOffset);
		m_meterRect = RectF(m_mainFrame.left + 1.0f, m_mainFrame.bottom, m_mainFrame.right - 1.0f, m_mainFrame.bottom );
	}
	else
	{
		m_textRect = RectF(m_mainFrame.left, m_mainFrame.top - m_textRectOffset, 400.0f, m_mainFrame.top);
		m_meterRect = RectF(m_mainFrame.left, m_mainFrame.top + 1.0f, m_mainFrame.left, m_mainFrame.bottom - 1.0f);
	}
	
	
}

void Meter::Update(const int & val)
{
	int value;
	// cap to max

	// expression      // if true           // if false
	(val > m_maxValue) ? value = m_maxValue : value = val;
	// create a percentage
	float percentage = (float)value / (float)m_maxValue;
	// move meter to percentage of main frame width
	;
	if (m_vertical)
		m_meterRect.top = m_mainFrame.bottom - m_height * percentage;
	else
	    m_meterRect.right = m_mainFrame.left + m_width * percentage;
}

void Meter::Draw(Graphics & gfx)
{
	float x = gfx.GetD2DLayerViewPort()->GetViewTopLeft().x;
	float y = gfx.GetD2DLayerViewPort()->GetViewTopLeft().y;
	RectF mFrame = RectF(m_mainFrame.left + x, m_mainFrame.top + y,
		(m_mainFrame.left + x) + m_mainFrame.GetWidth(), (m_mainFrame.top + y) + m_mainFrame.GetHeight());
	if (m_vertical)
	{
		m_textRect = RectF(mFrame.left, mFrame.bottom, 400.0f, mFrame.bottom + m_textRectOffset);
		m_meterRect = RectF(mFrame.left + 1.0f, mFrame.bottom, mFrame.right - 1.0f, mFrame.bottom);
	}
	else
	{
		m_textRect = RectF(mFrame.left,  mFrame.top - m_textRectOffset, 400.0f, mFrame.top);
		m_meterRect = RectF(mFrame.left, mFrame.top + 1.0f, mFrame.left, mFrame.bottom - 1.0f);
	}
	gfx.DrawFilledRectangle(mFrame.ToD2D(), m_backColor);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), mFrame.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	gfx.DrawFilledRectangle(m_meterRect.ToD2D(), m_meterColor);
	gfx.RenderText((LPWSTR)m_caption.c_str(), pTextFormat, m_textRect.ToD2D(), m_textColor);

}

void Meter::SetCaption(std::string & text)
{
	DXStringHandler::DXConvertFromStrToWStr(text, m_caption);
}


Meter::Drawable::Drawable(Meter& p)
	:
	m_parent(p)

{
	matTrans = D2D1::Matrix3x2F::Identity();
	matRot = D2D1::Matrix3x2F::Identity();
	matScale = D2D1::Matrix3x2F::Identity();


}

Meter::Drawable Meter::GetDrawable()
{
	return Drawable(*this);
}

void Meter::Drawable::Rasterize(Graphics& gfx)
{
	gfx.DrawFilledRectangle(m_parent.m_mainFrame.ToD2D(), m_parent.m_backColor, matTrans);
	gfx.DrawRectangle(matTrans, m_parent.m_mainFrame.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	gfx.DrawFilledRectangle(m_parent.m_meterRect.ToD2D(), m_parent.m_meterColor, matTrans);
	gfx.RenderText((LPWSTR)m_parent.m_caption.c_str(), m_parent.pTextFormat, m_parent.m_textRect.ToD2D(), m_parent.m_textColor,matTrans);
	

}
void Meter::Drawable::Transform(const D2D1::Matrix3x2F& mat)
{
	matTrans = mat * matTrans;
}
void Meter::Drawable::TranslateCoords(const Vec2f &pos)
{
	matTrans = D2D1::Matrix3x2F::Translation({ pos.x, pos.y });

}

