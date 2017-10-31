#include "Game.h"
#include "Direct3DWindow.h"




Game::Game(Direct3DWindow & wnd)
	:
	window(wnd),
	gfx(wnd.ScreenWidth(),wnd.ScreenHeight(),wnd.WindowHandle(),
		true, FULL_SCREEN,1000.0f,0.01f),
	m_cam(&gfx,(float)wnd.ScreenWidth(), (float)wnd.ScreenHeight())
{
	
	
	ConstructLevelsFromTextFile("map001.txt");
	ConstructLevelsFromTextFile("map002.txt");
	LoadImages();
	CreatePlayer();
	InitCamera();
	//CreateLevel("data\\levels\\map001.bin");
	CreateLevel("data\\levels\\map002.bin");
	
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
	
	if (window.kbd.KeyIsPressed(VK_ESCAPE))
		EndApp();
	
	m_player->HandleInput(window.kbd, window.mouse);
	
	m_currLevel->DoCollision(m_player.get());
	m_currLevel->DoSupported(m_player.get());
	m_player->Update(deltaTime);
	m_cam.UpdatePosition(m_player->GetPosition());
	return S_OK;
}

HRESULT Game::RenderScene()
{
	HRESULT hr;
	hr = gfx.BeginScene(0.2f, 0.4f, 0.2f, 1.0f);
	if (FAILED(hr)) { return hr; }
	m_currLevel->Draw(gfx);
	m_cam.Rasterize(m_player->GetDrawable());
	//gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_player->GetCollisionRect(-m_cam.GetPos()).ToD2D(), D2D1::ColorF(1.0f,1.0f,1.0f,1.0f));;
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
	data.emplace_back("char1", L"assets\\char1.png", 24.0f, 32.0f);
	data.emplace_back("char2", L"assets\\char2.png", 24.0f, 32.0f);
	data.emplace_back("level1", L"assets\\level1.png", 64.0f, 64.0f);
	m_textureHandler->LoadImages(data);
	Locator::SetImageManager(m_textureHandler.get());
}

void Game::CreatePlayer()
{
	Animation::RenderDesc desc;
	desc.drawRect = { 0.0f,0.0f,48.0f,64.0f };
	desc.clipRect = m_textureHandler->GetImage("char1")->GetClippedImage(4).ToD2D();
	desc.image = m_textureHandler->GetImage("char1")->GetTexture();
	m_player = std::make_unique<Player>(desc);
	m_player->MoveData()->acceleration = 4.0f;
	m_player->MoveData()->horizontalDecay = 0.987f;
	m_player->MoveData()->maxSpeed = 152.0f;
	m_player->MoveData()->surfaceFriction = 0.876f;
	m_player->MoveData()->verticalForce = -400.0f;
}

void Game::InitCamera()
{
	m_cam.ConfineToMap(RectF(0.0f, 0.0f, 20.0f*64.0f, 20.0f*64.0f));
	m_cam.UpdatePosition(m_player->GetPosition());
}

void Game::CreateLevel(std::string mapFilename)
{
	if (m_currLevel.get())
		m_currLevel.reset();
	m_currLevel = std::make_unique<Level>(m_cam);
	m_currLevel->Initialize(mapFilename, m_player.get());
}

void Game::ConstructLevelsFromTextFile(std::string mapFilename)
{
	_LevelFileData levelData;
	std::string fName;
	DXStringHandler::DXExtractNameFromFile(mapFilename, fName);
	std::vector<std::string> lines;
	bool result = DXStringHandler::DXLoadTextFile(mapFilename, lines);
	assert(result);
	std::vector<std::string> tokens;
	DXStringHandler::Tokenize(&tokens, lines[0], " ");
	assert(tokens.size() == 4);
	levelData.tileDimensions = Vec2f( (float)atoi(tokens[0].c_str()), (float)atoi(tokens[1].c_str()));
	levelData.rowsColumns = { atoi(tokens[2].c_str()), atoi(tokens[3].c_str()) };
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
				
				levelData.map[r][c] = 1;

			}
			break;
			case '*':
			{
				
				levelData.map[r][c] = 0;
			}
			break;
			case 'p':
			{
				
				levelData.playerPos = startPos;
				levelData.map[r][c] = 2;

			}
			break;
			case 'c':
			{

				
				levelData.map[r][c] = 4;

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




