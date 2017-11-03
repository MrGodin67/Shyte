#include "Game.h"
#include "Direct3DWindow.h"




Game::Game(Direct3DWindow & wnd)
	:
	window(wnd),
	gfx(wnd.ScreenWidth(),wnd.ScreenHeight(),wnd.WindowHandle(),
		true, FULL_SCREEN,1000.0f,0.01f),
	m_cam(&gfx,(float)wnd.ScreenWidth(), (float)wnd.ScreenHeight())
{
	Locator::SetScreenDimensions(wnd.ScreenWidth(), wnd.ScreenHeight());
	ConstructLevelsFromTextFile("map001.txt",0);
	ConstructLevelsFromTextFile("map002.txt", 1);
	ConstructLevelsFromTextFile("map003.txt", 2);
	LoadImages();
	InitMenus();
}

Game::~Game()
{
	
}

bool Game::Play(const float& deltaTime)
{
	HRESULT hr;
	if (FAILED(hr = ConstructScene(deltaTime))) 
	{ return false; }
	if (FAILED(hr = RenderScene())) { return false; }
	return true;
}

HRESULT Game::ConstructScene(const float& deltaTime)
{
	
	Mouse::Event mouse_event = window.mouse.Read();
	Keyboard::Event kbd_event = window.kbd.ReadKey();
	
	switch (m_gameState)
	{
	case _GameState::running:
	{
		m_currentBackgroundColor = m_backgroundColors[1];
		if (window.kbd.KeyIsPressed(VK_ESCAPE))
		{
			m_currentMenu = m_menus["paused_screen"].get();
			m_previousMenu = nullptr;
			m_gameState = _GameState::paused;
			return S_OK;
		}

		m_player->HandleInput(window.kbd, window.mouse);

		m_currLevel->DoCollision(m_player.get());
		m_currLevel->DoSupported(m_player.get());
		m_player->Update(deltaTime);
		m_cam.UpdatePosition(m_player->GetPosition());
		m_currLevel->Update(deltaTime);
	}
	break;
	case _GameState::main:
	case _GameState::paused:
	{
		m_currentBackgroundColor = m_backgroundColors[0];
		HandleUserInterface(mouse_event,kbd_event);
	}
	break;
	}
	
	return S_OK;
}

HRESULT Game::RenderScene()
{
	HRESULT hr;
	hr = gfx.BeginScene(m_currentBackgroundColor.r, m_currentBackgroundColor.g, m_currentBackgroundColor.b, m_currentBackgroundColor.a);
	if (FAILED(hr)) { return hr; }

	switch (m_gameState)
	{
		case _GameState::paused:
		{
			m_backGroundImage->Draw(m_cam, gfx);
			m_currLevel->Draw(gfx);
			m_cam.Rasterize(m_player->GetDrawable());
			m_currentMenu->Draw(gfx);
		}
		break;
		case _GameState::running:
		{
			m_backGroundImage->Draw(m_cam, gfx);
			m_currLevel->Draw(gfx);
			m_cam.Rasterize(m_player->GetDrawable());
		}break;
		case _GameState::main:
		{
			m_currentMenu->Draw(gfx);
		}break;
	};
	
	
	
	
	hr = gfx.EndScene();
	if (FAILED(hr)) { return hr; }
	return hr;
}

void Game::EndApp()
{
	PostQuitMessage(0);
}

void Game::LoadAudio()
{
	m_soundFX = std::make_unique<SoundManager>();
	
	

}

void Game::LoadImages()
{
	m_textureHandler = std::make_unique<TextureManager>();
	std::vector<TextureManager::ImageData> data;
	data.emplace_back("colin", L"assets\\colin.png", 24.0f, 32.0f);
	data.emplace_back("jack", L"assets\\jack.png", 24.0f, 32.0f);
	data.emplace_back("maria", L"assets\\maria.png", 24.0f, 32.0f);
	data.emplace_back("hannah", L"assets\\hannah.png", 24.0f, 32.0f);
	data.emplace_back("level1", L"assets\\level1.png", 64.0f, 64.0f);
	data.emplace_back("start_screen", L"assets\\startscreen.png", 48.0f, 16.0f);
	data.emplace_back("paused_screen", L"assets\\pausedscreen.png", 48.0f, 16.0f);
	data.emplace_back("input_screen", L"assets\\inputscreen.png", 48.0f, 16.0f);
	data.emplace_back("new_game", L"assets\\new_game.png", 512.0f, 512.0f);
	data.emplace_back("background", L"assets\\background.png", 1024.0f, 1024.0f);

	m_textureHandler->LoadImages(data);
	Locator::SetImageManager(m_textureHandler.get());
	m_currentBackgroundColor = m_backgroundColors[0];
	m_backGroundImage = std::make_unique<BackGround>();
	
}

void Game::CreatePlayer(PlayerData* data)
{
	Animation::RenderDesc desc;
	
	
	desc.drawRect = { 0.0f,0.0f,48.0f,64.0f };
	desc.clipRect = m_textureHandler->GetImage(std::string(data->name))->GetClippedImage(4).ToD2D();
	desc.image = m_textureHandler->GetImage(std::string(data->name))->GetTexture();
	m_player = std::make_unique<Player>(desc,*data, InitialPlayerCoreData::Get(std::string(data->name)));
	
	CreateLevel("data\\levels\\map003.bin");
}

void Game::InitMenus()
{
	m_menus["start_screen"] = std::make_unique<StartScreen>();
	m_menus["paused_screen"] = std::make_unique<PausedScreen>();
	m_menus["new_game"] = std::make_unique<NewGame>();
	m_menus["user_input"] = std::make_unique<UserInput>();
	m_currentMenu = m_menus["start_screen"].get();
}

void Game::CreateLevel(std::string mapFilename)
{
	if (m_currLevel.get())
		m_currLevel.reset();
	m_currLevel = std::make_unique<Level>(m_cam);
	m_currLevel->Initialize(mapFilename, m_player.get());
	m_backGroundImage->SetColorIndex(m_currLevel->CurrentLevelIndex());
}

void Game::ConstructLevelsFromTextFile(std::string mapFilename,int levelIndex)
{
	_LevelFileData levelData;
	std::string fName;
	DXStringHandler::DXExtractNameFromFile(mapFilename, fName);
	
	levelData.levelIndex = levelIndex;
	
	std::vector<std::string> lines;
	bool result = DXStringHandler::DXLoadTextFile(mapFilename, lines);
	assert(result);
	std::vector<std::string> tokens;
	DXStringHandler::Tokenize(&tokens, lines[0], " ");
	assert(tokens.size() == 4);
	levelData.tileDimensions = Vec2f( (float)atoi(tokens[0].c_str()), (float)atoi(tokens[1].c_str()));
	levelData.rowsColumns = { atoi(tokens[3].c_str()), atoi(tokens[2].c_str()) };
	lines.erase(lines.begin());
	Vec2f startPos(0.0f, 0.0f);
	
	for (int r = 0; r < lines.size(); r++)
	{
		startPos.x = 0.0f;
		for (int c = 0; c < lines[r].size(); c++)
		{

			const int index = r * levelData.rowsColumns.x + c;

			switch (lines[r][c])
			{
			case ' ':
			{
				
				levelData.map[r][c] = 64;

			}
			break;
			case '4':
			{
				
				levelData.map[r][c] = 4;
			}
			break;
			case '0':
				levelData.map[r][c] = 0;
			break;
			case '1':
				levelData.map[r][c] = 1;
				break;
			case '2':
				levelData.map[r][c] = 2;
				break;
			case '3':
				levelData.map[r][c] = 3;
				break;
			case 'p':
			{
				
				levelData.playerPos = startPos;
				levelData.map[r][c] = 64;

			}
			break;
			case 'x':
			{

				
				levelData.map[r][c] = 7;

			}
			break;
			}
			
			startPos.x += levelData.tileDimensions.x;
		}
		startPos.y += levelData.tileDimensions.y;
	}
	std::string f = "data\\levels\\" + fName + ".bin";
	FileManager::WriteLevelData(f.c_str(), levelData);
}



void Game::HandleUserInterface(Mouse::Event& mouse_event, Keyboard::Event& kbd_event)
{
	if (!m_currentMenu)
		return;
	
	if (kbd_event.IsPress())
	{
		unsigned char key = kbd_event.GetCode();
		ReturnType result_key = m_currentMenu->OnKeyPress(key);
		switch (result_key.result)
		{
			case RETURN_ENTER:
			{
				switch (result_key.type)
				{
					case MENU_TYPE_INPUT:
					{
						m_userName = *(std::string*)result_key.data;
						m_currentMenu = m_menus["new_game"].get();
					}
					break;
				};
			
			}
			break;// RETURN ENTER
		}
		
	}
	ReturnType result;
	
	if (mouse_event.LeftIsPressed())
	{
	
		result = m_currentMenu->OnMouseClick({ mouse_event.GetPosX(),mouse_event.GetPosY() });
		switch (result.result)
		{
		case RETURN_NEW_BACK:
			if (m_previousMenu != nullptr)
			{
				m_currentMenu = m_previousMenu;
				m_previousMenu = nullptr;
			}
		case RETURN_RESUME:
		{
			if (m_player.get())
			{
				m_gameState = _GameState::running;
				m_currentMenu = m_previousMenu = nullptr;
			}
		}
			break;
		case RETURN_EXIT:
			EndApp();
			break;
		case RETURN_NEW:
			m_previousMenu = m_currentMenu;
			m_currentMenu = m_menus["user_input"].get();
			break;
		case RETURN_NEW_DONE:
		{
			PlayerData* data = (PlayerData*)result.data;
			sprintf_s(data->username, "%s", m_userName.c_str());
			CreatePlayer(data);
			m_gameState = _GameState::running;

		}
			break;
		}
		
			
	}
	else
	{
		m_currentMenu->OnMouseMove({ window.mouse.GetPos().first,window.mouse.GetPos().second });
	}
}

void Game::DrawLight()
{
	Vec2f position = m_player->GetCenter() + -m_cam.GetPosition();
	D2D1_ELLIPSE e;
	e.point = { position.x,position.y };
	e.radiusX = 100.0f;
	e.radiusY = 100.0f;
	float diffuse = 0.0f;
	for (float c = 100.0f; c > 0.0f; c -= 1.0f)
	{
		e.radiusX = c;
		e.radiusY = c;
		float diffuse = c * 0.01f;
		gfx.DrawEllipse(D2D1::Matrix3x2F::Identity(), e, D2D1::ColorF(1.0f, 1.0f, 1.0f,diffuse));
	}
}




