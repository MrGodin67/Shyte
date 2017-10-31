#include "StartScreen.h"
#include "Locator.h"
#include "Graphics.h"
#include "Camera.h"


StartScreen::StartScreen()
{
	Animation::RenderDesc desc;
	desc.clipRect = { 0.0f,0.0f,256.0f,128.0f };
	desc.drawRect = { 100.0f ,100.0f,356.0f,228.0f };
	desc.image = Locator::ImageManager()->GetImage("start_screen")->GetTexture();
	m_images["main_image"] = std::make_unique<Animation>(desc);
}

StartScreen::~StartScreen()
{
}

MouseReturnType StartScreen::OnMouseClick(const Vec2i & mousePos)
{
	return MouseReturnType();
}

void StartScreen::OnKeyPress(unsigned char & key)
{
}

void StartScreen::Draw(Camera & cam)
{
	for (auto& it : m_images)
		cam.Rasterize(it.second->GetDrawable());

	cam.Rasterize(GetDrawable());
}

StartScreen::Drawable::Drawable(StartScreen& p)
	:
	m_parent(p)

{
	matTrans = D2D1::Matrix3x2F::Identity();
	matRot = D2D1::Matrix3x2F::Identity();
	matScale = D2D1::Matrix3x2F::Identity();


}

StartScreen::Drawable StartScreen::GetDrawable()
{
	return Drawable(*this);
}

void StartScreen::Drawable::Rasterize(Graphics& gfx)
{
	
	
}
void StartScreen::Drawable::Transform(const D2D1::Matrix3x2F& mat)
{
	
}
void StartScreen::Drawable::TranslateCoords(const Vec2f &pos)
{
	matTrans = D2D1::Matrix3x2F::Translation({ pos.x, pos.y });

}
