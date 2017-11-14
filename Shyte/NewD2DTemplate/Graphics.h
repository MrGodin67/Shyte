#pragma once
#include "Direct3D_2D.h"
#include "DirectWrite.h"

#include "Animation.h"
#include "RenderTarget.h"
#include "randomizer.h"
#include "ViewPort.h" 
class Graphics : public Direct3D,public RenderTarget
{
private:
	TextHandler m_TextFactory;
	std::unique_ptr<ViewPort> m_viewPort;
public:
	Graphics(int screenWidth, int screenHeight, HWND & hwnd,
		bool v_sync, bool fullscreen, float scrnDepth, float scrnNear);
	
	HRESULT BeginScene(float red, float green, float blue, float alpha);
	HRESULT EndScene();
	void DrawFilledEllipse(D2D1_MATRIX_3X2_F & matTrans,D2D1_ELLIPSE& data, D2D1_COLOR_F& color);
	void DrawEllipse(D2D1_MATRIX_3X2_F & matTrans, D2D1_ELLIPSE& data, D2D1_COLOR_F& color);
	void DrawTriangle(D2D1_MATRIX_3X2_F &matTrans, D2D1_POINT_2F points[], D2D1_COLOR_F& color, float line_width);
	void DrawLine(D2D1_MATRIX_3X2_F &matTrans, D2D1_POINT_2F start, D2D1_POINT_2F end, D2D1_COLOR_F& color, float width);
	void DrawRectangle(D2D1_MATRIX_3X2_F &matTrans, D2D1_RECT_F& rect, D2D1_COLOR_F& color);
	void DrawScreenRectangle(D2D1_RECT_F rect, D2D1_COLOR_F& color);
	void DrawFilledRectangle(D2D1_RECT_F& rect, D2D1_COLOR_F& color, D2D1_MATRIX_3X2_F& matrix = D2D1::Matrix3x2F::Identity());
	void DrawSprite(D2D1_MATRIX_3X2_F &trans, D2D1_RECT_F &PosSize, ID2D1Bitmap *pSprite,
		D2D1_RECT_F *ClipRect = nullptr,float Opacity = 1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE InterpMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	void DrawSprite(D2D1_MATRIX_3X2_F &trans, Animation::RenderDesc& desc)
	{
		DrawSprite(trans, desc.drawRect, desc.image, &desc.clipRect, desc.opague, desc.interpMode);
	}
	void RenderText(LPWSTR String, IDWriteTextFormat *pFormat,
		const D2D1_RECT_F &DrawRect, D2D1_COLOR_F &Color, D2D1_MATRIX_3X2_F &trans = D2D1::Matrix3x2F::Identity() );
	virtual void Rasterize( Drawable& obj)override;
	ViewPort* GetD2DLayerViewPort() { return m_viewPort.get(); }
private:
	HRESULT CreateTextObjects();
};