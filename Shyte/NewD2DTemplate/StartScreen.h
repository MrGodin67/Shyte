#pragma once

#include "UserInterface.h"

class StartScreen : public UserInterface
{
	std::unordered_map<std::string, std::unique_ptr<Animation>> m_images;

public:

	StartScreen();

	~StartScreen();
	// Inherited via UserInterface
	virtual MouseReturnType OnMouseClick(const Vec2i & mousePos) override;

	virtual void OnKeyPress(unsigned char & key) override;

	virtual void Draw(Camera & cam) override;
	class Drawable : public ::Drawable
	{
		StartScreen& m_parent;

	public:
		Drawable(StartScreen& p);
		virtual ~Drawable() {};
		virtual void Rasterize(class Graphics& gfx)override;
		virtual void TranslateCoords(const Vec2f& pos)override;
		virtual void Transform(const D2D1::Matrix3x2F& mat)override;
	};
	Drawable GetDrawable();

};