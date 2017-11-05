#include "Game.h"
#include "Direct3DWindow.h"




Game::Game(Direct3DWindow & wnd)
	:
	window(wnd),
	gfx(wnd.ScreenWidth(),wnd.ScreenHeight(),wnd.WindowHandle(),
		true, FULL_SCREEN,1000.0f,0.01f),
	m_cam(&gfx,(float)wnd.ScreenWidth(), (float)wnd.ScreenHeight())
{
	if (DXStringHandler::DXDoesFileExist("data\\gm.bin"))
	{
		FileManager::ReadGameData("data\\gm.bin",m_gameData);
		for (int c = 0; c < m_gameData.numbUsers; c++)
			m_users.push_back(m_gameData.userNames[c]);
	}
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
	if (window.kbd.KeyIsPressed('S'))
	{
		if (m_player.get())
			m_player->Save();
	}
	switch (m_gameState)
	{
	case _GameState::running:
	{
		m_currentBackgroundColor = m_backgroundColors[1];
		if (window.kbd.KeyIsPressed(VK_ESCAPE))
		{
			m_userInterfaceManager->SetCurrentScreen(std::string("paused_screen"));
			m_gameState = _GameState::paused;
			return S_OK;
		}

		m_player->HandleInput(window.kbd, window.mouse);

		
		m_currLevel->Update(deltaTime);
		m_cam.UpdatePosition(m_player->GetPosition());
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
			m_userInterfaceManager->Draw(gfx);
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
			m_userInterfaceManager->Draw(gfx);
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
	data.emplace_back("Colin", L"assets\\colin.png", 24.0f, 32.0f);
	data.emplace_back("Jack", L"assets\\jack.png", 24.0f, 32.0f);
	data.emplace_back("Maria", L"assets\\maria.png", 24.0f, 32.0f);
	data.emplace_back("Hannah", L"assets\\hannah.png", 24.0f, 32.0f);
	data.emplace_back("level1", L"assets\\level1.png", 64.0f, 64.0f);
	data.emplace_back("start_screen", L"assets\\startscreen.png", 48.0f, 16.0f);
	data.emplace_back("paused_screen", L"assets\\pausedscreen.png", 48.0f, 16.0f);
	data.emplace_back("input_screen", L"assets\\inputscreen.png", 48.0f, 16.0f);
	data.emplace_back("new_game", L"assets\\new_game.png", 512.0f, 512.0f);
	data.emplace_back("background", L"assets\\background.png", 512.0f, 512.0f);
	data.emplace_back("select_user", L"assets\\selectuser.png", 512.0f, 512.0f);
	data.emplace_back("message_box", L"assets\\messagebox.png", 256.0f, 128.0f);

	m_textureHandler->LoadImages(data);
	Locator::SetImageManager(m_textureHandler.get());
	m_currentBackgroundColor = m_backgroundColors[0];
	m_backGroundImage = std::make_unique<BackGround>();
	
}

void Game::CreatePlayer(MainPlayerData* data)
{
	
	m_player = std::make_unique<Player>(data->data,data->core);
	CreateLevel("data\\levels\\map001.bin");
	//int& maxvalue, RectF mainFrame, RectF& meter_color, RectF& back_color, RectF& text_color,std::string textFont
	
	
}

void Game::InitMenus()
{
	m_userInterfaceManager = std::make_unique<UserInterfaceManager>();
	m_userInterfaceManager->InitializeCurrentUsers(m_users);
}

void Game::CreateLevel(std::string mapFilename)
{
	if (m_currLevel.get())
		m_currLevel.reset();
	m_currLevel = std::make_unique<Level>(m_cam,*m_player.get());
	m_currLevel->Initialize(mapFilename);
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
	
	
	if (kbd_event.IsPress())
	{
		unsigned char key = kbd_event.GetCode();
		ReturnType result_key = m_userInterfaceManager->OnKeyPress(key);
		
		
	}
	ReturnType result;
	m_userInterfaceManager->OnMouseMove(Vec2i(window.mouse.GetPosX(), window.mouse.GetPosY()));
	if (mouse_event.LeftIsPressed())
	{
	
		result = m_userInterfaceManager->OnMouseClick(Vec2i( mouse_event.GetPosX(),mouse_event.GetPosY() ));
		switch (result.result)
		{
		case RETURN_RESULT_RESUME:
			m_gameState = _GameState::running;
			break;
		case RETURN_RESULT_EXIT:
			EndApp();
			break;
		case RETURN_RESULT_CREATE_NEW_GAME:
		{
			MainPlayerData* data = (MainPlayerData*)result.data;
			if (m_gameData.numbUsers >= 9)
				m_gameData.numbUsers = 9;
			m_gameData.numbUsers++;

			sprintf_s(m_gameData.userNames[m_gameData.numbUsers], "%s", data->data.username);
			FileManager::WriteGameData("data\\gm.bin", m_gameData);
			CreatePlayer(data);
			m_gameState = _GameState::running;

		}
			break;
		}
		
			
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




