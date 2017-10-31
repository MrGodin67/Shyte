#include "StartScreen.h"
#include "Locator.h"
#include "Graphics.h"
#include "Camera.h"


StartScreen::StartScreen()
{
	Animation::RenderDesc desc;
	desc.image = Locator::ImageManager()->GetImage("start_screen")->GetTexture();
	float x = (float)(Locator::ScreenWidth() / 2) - (float)(desc.image->GetSize().width / 2);
	float y = (float)(Locator::ScreenHeight() / 2) - (float)(desc.image->GetSize().height / 2);
	desc.clipRect = { 0.0f,0.0f,(float)desc.image->GetSize().width,(float)desc.image->GetSize().height };
	desc.drawRect = { x/2 ,y/2,x + (float)desc.image->GetSize().width * 2,y + (float)desc.image->GetSize().height*2};
	
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
