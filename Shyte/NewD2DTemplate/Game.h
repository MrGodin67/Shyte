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
#include "UIManager.h"
#include "ViewPort.h"
class Game
{
	
	class Direct3DWindow& window;
	Graphics gfx;
	void EndApp(bool showMsg = false, std::wstring* msg = nullptr);
	Camera m_cam;
	_GameData m_gameData;
	_GameState m_gameState = _GameState::main;
private:
	std::unique_ptr<SoundManager> m_soundFX;
	std::unique_ptr<TextureManager> m_textureHandler;
	std::unique_ptr<UserInterfaceManager> m_userInterfaceManager;
	std::unique_ptr<Player> m_player;
	std::unique_ptr<Level> m_currLevel;
	std::unique_ptr<BackGround> m_backGroundImage;
	
	std::unordered_map<std::string, std::unique_ptr<UserInterface>> m_menus;
	UserInterface* m_currentMenu = nullptr;
	UserInterface* m_previousMenu = nullptr;
	RectF m_currentBackgroundColor;
	RectF m_backgroundColors[2] =
	{
		RectF(0.0f,0.0f,0.0f,1.0f),
		RectF(0.2f,0.4f,0.2f,1.0f)
	};
	
	std::string m_userName;
	std::vector<std::string> m_users;
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
	void CreatePlayer(MainPlayerData* data);
	void InitMenus();
	void LoadFileData();
	void CreateLevel(std::string mapFilename);
	void ConstructLevelsFromTextFile(std::string mapFilename,int levelIndex);
	void HandleUserInterface(Mouse::Event& mouse_event,Keyboard::Event& kbd_event);
	void DrawLight();
};
