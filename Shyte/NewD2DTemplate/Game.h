#pragma once
#include "Graphics.h"

#include <memory>

#include "Camera.h"
#include "GameState.h"
#include "SpriteSheet.h"

#include "SoundManager.h"

#include "VecRect.h"
#include "TextureManager.h"

class Game
{
	
	class Direct3DWindow& window;
	Graphics gfx;
	void EndApp();
	Camera m_cam;
	
	_GameState m_gameState = _GameState::paused;
private:
	std::unique_ptr<SoundManager> m_soundFX;
public:
	Game(class Direct3DWindow& wnd);
	bool Play(const float& deltaTime);
	HRESULT ConstructScene(const float& deltaTime);
	HRESULT RenderScene();
	
	////////////////////////////////////
	// LOGIC
	////////////////////////////////////

private:
	
	void LoadAudio();
};
