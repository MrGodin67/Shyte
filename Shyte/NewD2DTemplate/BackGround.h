#pragma once

#include "Animation.h"
#include "Locator.h"
#include "Camera.h"
#include "Graphics.h"
#include "Camera.h"
class BackGround : public Animation
{
	
	D2D1_COLOR_F m_diffuseColors[4] =
	{
		BGRND_COLOR_BLUE,
		BGRND_COLOR_GREEN,
		BGRND_COLOR_BROWN,
		BGRND_COLOR_WOOD
	};
	int m_diffuseColorIndex = 0;
public:
	BackGround()
	{
		m_renderDesc.image = Locator::ImageManager()->GetImage("background")->GetTexture();
		m_renderDesc.drawRect = { -0.0f,-0.0f,800.0f,600.0f };
		m_renderDesc.clipRect = m_renderDesc.drawRect;
		
	}
	void SetColorIndex(int val)
	{
		m_diffuseColorIndex = val;
	}
	void Draw(Camera& cam,Graphics& gfx)
	{
		Vec2f pos = cam.GetPosition();
		pos /= 5.14f;
		D2D1_RECT_F r;
		r.left =  -pos.x;
		r.right =  r.left + 2024.0f;
		r.top =  -pos.y;
		r.bottom =   r.top + 2024.0f;
		
		gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), r, m_renderDesc.image);
		gfx.DrawFilledRectangle(r, m_diffuseColors[m_diffuseColorIndex]);
	}
};