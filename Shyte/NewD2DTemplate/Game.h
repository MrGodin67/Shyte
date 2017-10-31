#pragma once
#include "Graphics.h"

#include <memory>

#include "Camera.h"
#include "GameState.h"
#include "SpriteSheet.h"

#include "SoundManager.h"
#include "Locator.h"
#include "VecRect.h"
#include "TextureManager.h"
#include "Level.h"
#include "randomizer.h"
#include "FileManager.h"
#include "StartScreen.h"


class Game
{
	
	class Direct3DWindow& window;
	Graphics gfx;
	void EndApp();
	Camera m_cam;
	
	_GameState m_gameState = _GameState::paused;
private:
	std::unique_ptr<SoundManager> m_soundFX;
	std::unique_ptr<TextureManager> m_textureHandler;
	std::unique_ptr<Player> m_player;
	std::unique_ptr<Level> m_currLevel;

	std::unordered_map<std::string, std::unique_ptr<UserInterface>> m_menus;
	UserInterface* m_currentMenu = nullptr;
	
public:
	Game(class Direct3DWindow& wnd);
	~Game();
	bool Play(const float& deltaTime);
	HRESULT ConstructScene(const float& deltaTime);
	HRESULT RenderScene();
	
	////////////////////////////////////
	// LOGIC
	////////////////////////////////////

private:
	
	void LoadAudio();
	void LoadImages();
	void CreatePlayer();
	void InitCamera();
	void InitMenus();
	void CreateLevel(std::string mapFilename);

	void ConstructLevelsFromTextFile(std::string mapFilename);
	void ToggleGameState();
};
