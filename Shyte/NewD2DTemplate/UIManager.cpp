#include "UIManager.h"
#include "Graphics.h"
#include "StringHandler.h"
ReturnType UserInterfaceManager::HandleStartScreen(ReturnType & data)
{
	switch (data.result)
	{
	case RETURN_RESULT_CONTINUE:
	{
		m_perviousScreen = m_currentScreen;
		m_currentScreen = m_screens["select_user"].get();
		m_currentScreen->Enabled(true);
		
	}
		break;
	case RETURN_RESULT_NEW_GAME:
	{
		m_perviousScreen = m_currentScreen;
		m_currentScreen = m_screens["new_game"].get();
		m_currentScreen->Enabled(false);
		m_pUserInput = new UserInput(L"Enter Username",L"Username",MENU_TYPE_START);
	}
		break;
	case RETURN_RESULT_EXIT:
		return data;
		break;
	}
	return ReturnType();
}
ReturnType UserInterfaceManager::HandleInputScreen(const unsigned char& key)
{
	ReturnType result;
	if (m_pUserInput != nullptr)
	{
		result = m_pUserInput->OnKeyPress(key);
		if (result.result == RETURN_RESULT_ENTER)
		{
			std::string* str = (std::string*)result.data;
			if (!DoesUserExist(*str))
			{
				m_newUserName = *str;
				m_currentScreen->Enabled(true);
			}
			else
			{
				m_pMessageBox = new Message(L"User already Exists", L"Error",MENU_TYPE_INPUT);
				m_currentScreen->Enabled(false);
			}
			SAFE_DELETE(m_pUserInput);
			
		}

	}
	return ReturnType();
}
ReturnType UserInterfaceManager::HandleInputScreen(ReturnType & data)
{
	switch (data.result)
	{
	case RETURN_RESULT_DONE:
	{
		std::string* str = (std::string*)data.data;
		if (!DoesUserExist(*str))
		{
			m_newUserName = *str;
			m_currentScreen->Enabled(true);
		}
		else
		{
			m_pMessageBox = new Message(L"User already Exists", L"Error", MENU_TYPE_INPUT);
			m_currentScreen->Enabled(false);
		}
		SAFE_DELETE(m_pUserInput);
	}
	break;
	case RETURN_RESULT_CANCEL:
	{
		SAFE_DELETE(m_pUserInput);
		m_currentScreen->Enabled(true);
		m_currentScreen = m_perviousScreen;
	}
	}
	return ReturnType();
}
ReturnType UserInterfaceManager::HandlePausedScreen(ReturnType & data)
{
	ReturnType result = data;
	switch (result.result)
	{
	case RETURN_RESULT_EXIT:
	{
	  result.result = RETURN_RESULT_EXIT_GAME;
	  m_currentScreen = m_screens["start_screen"].get();
	  m_perviousScreen = nullptr;
	}
	}
	return result;
}
ReturnType UserInterfaceManager::HandleSelectUserScreen(ReturnType & data)
{
	ReturnType result = data;

	switch (result.result)
	{
	case RETURN_RESULT_BACK:
		result.result = RETURN_RESULT_CREATE_NEW_FROM_FILE;
		 
		break;
	case RETURN_RESULT_CANCEL:
		m_currentScreen = m_perviousScreen;
		m_currentScreen->Enabled(true);
	}
	return result;
}
ReturnType UserInterfaceManager::HandleNewGameScreen(ReturnType & data)
{
	switch (data.result)
	{
		case RETURN_RESULT_DONE:
		{
			data.result = RETURN_RESULT_CREATE_NEW_GAME;
			MainPlayerData* pd = (MainPlayerData*)data.data;

			sprintf_s(pd->data.username, "%s", m_newUserName.c_str());
			AddUser(m_newUserName);
			return data;
		}
			break;
		case RETURN_RESULT_BACK:
			m_currentScreen = m_perviousScreen;
			m_currentScreen->Enabled(true);
			break;
	}
	return ReturnType();
}
bool UserInterfaceManager::DoesUserExist(std::string user)
{
	for (int i = 0; i < m_users.size(); i++)
	{
		if (m_users[i] == user)
			return true;
	}
	return false;
}
UserInterfaceManager::UserInterfaceManager()
{
	m_screens["start_screen"] = std::make_unique<StartScreen>();
	m_screens["paused_screen"] = std::make_unique<PausedScreen>();
	m_screens["new_game"] = std::make_unique<NewGame>();
	//m_screens["user_input"] = std::make_unique<UserInput>();
	m_screens["select_user"] = std::make_unique<SelectUsers>();
	m_currentScreen = m_screens["start_screen"].get();
	
	
}
UserInterfaceManager::~UserInterfaceManager()
{
	SAFE_DELETE(m_pUserInput);
	SAFE_DELETE(m_pMessageBox);
}
void UserInterfaceManager::AddUser(std::string & user)
{
	m_users.push_back(user);
	SelectUsers* sel = (SelectUsers*)m_screens["select_user"].get();
	sel->SetUsers(m_users);
	StartScreen* scrn = (StartScreen*)m_screens["start_screen"].get();
	scrn->EnableContinueButton(true);
}
void UserInterfaceManager::Draw(Graphics & gfx)
{
	
	

	m_currentScreen->Draw(gfx);
	if (m_pUserInput)
		m_pUserInput->Draw(gfx);
	if (m_pMessageBox)
		m_pMessageBox->Draw(gfx);
}
ReturnType UserInterfaceManager::OnMouseClick(Vec2i & mousePos)
{
	if (!m_currentScreen)
		return ReturnType();
	
	ReturnType returnResult;
	
	if (m_pUserInput != nullptr)
	{
		return HandleInputScreen(m_pUserInput->OnMouseClick(mousePos));
		
	}
	if (m_pMessageBox != nullptr)
	{
		ReturnType result = m_pMessageBox->OnMouseClick(mousePos);
		if (result.result == RETURN_RESULT_DONE)
		{
			switch (result.type)
			{
			case MENU_TYPE_INPUT:
			{
				m_currentScreen->Enabled(false);
				m_pUserInput = new UserInput(L"Enter Username", L"Username", MENU_TYPE_START);
			}
			};
			
			SAFE_DELETE(m_pMessageBox);
		}

	}
	
	returnResult = m_currentScreen->OnMouseClick(mousePos);
	if (returnResult.result != RETURN_RESULT_NONE)
	{
		switch (returnResult.type)
		{
		
		case MENU_TYPE_START:
			return HandleStartScreen(returnResult);
		case MENU_TYPE_NEW_GAME:
			return HandleNewGameScreen(returnResult);
		case MENU_TYPE_PAUSED:
			return HandlePausedScreen(returnResult);
		case MENU_TYPE_SELECT_USER:
			return HandleSelectUserScreen(returnResult);
		}
	}
	return returnResult;
}
ReturnType UserInterfaceManager::OnMouseMove(Vec2i & mousePos)
{
	m_currentScreen->OnMouseMove(mousePos);
	if (m_pMessageBox)
		m_pMessageBox->OnMouseMove(mousePos);
	if (m_pUserInput)
		m_pUserInput->OnMouseMove(mousePos);
	return ReturnType();
}
ReturnType UserInterfaceManager::OnKeyPress(const unsigned char & key)
{
	return HandleInputScreen(key);
}

void UserInterfaceManager::SetCurrentScreen(const std::string & name)
{
	assert(m_screens[name].get());
	m_currentScreen = m_screens[name].get();
}

void UserInterfaceManager::InitializeCurrentUsers(std::vector<std::string>& usernames)
{
	m_users = usernames;
	if (m_users.size() > 0)
	{
		StartScreen* scrn = (StartScreen*)m_screens["start_screen"].get();
		scrn->EnableContinueButton(true);
		SelectUsers* sel = (SelectUsers*)m_screens["select_user"].get();
		sel->SetUsers(m_users);
	}
}

void UserInterfaceManager::Message::Draw(Graphics & gfx)
{
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), m_image);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), FULL_COLOR_WHITE);

	
	gfx.RenderText((LPWSTR)m_msg.c_str(), pTextFormat, m_msgRect.ToD2D(), FULL_COLOR_WHITE);
	gfx.RenderText((LPWSTR)m_caption.c_str(), pTextFormat, m_captionRect.ToD2D(), FULL_COLOR_WHITE);
	for (int c = 0; c < 2; c++)
	{
		gfx.DrawFilledRectangle(m_buttons[c].ToD2D(), m_selectedColors[c]);
		gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_buttons[c].ToD2D(), FULL_COLOR_WHITE);
	}
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	gfx.RenderText(L"Ok", pTextFormat, m_buttons[0].ToD2D(), FULL_COLOR_WHITE);
	gfx.RenderText(L"Cancel", pTextFormat, m_buttons[1].ToD2D(), FULL_COLOR_WHITE);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
}
/////////////////////////////////////////////////////////////////////////////////////////
// MESSAGE
/////////////////////////////////////////////////////////////////////////////////////////
ReturnType UserInterfaceManager::Message::OnMouseClick(const Vec2i & mousePos)
{
	ReturnType result;
	for (int c = 0; c < 2; c++)
	{
		if (m_buttons[c].Contains(mousePos))
		{
			result.result = RETURN_RESULT_DONE;
			result.type = m_owner;
			return result;
		}
	}
	return result;
}

ReturnType UserInterfaceManager::Message::OnMouseMove(const Vec2i & mousePos)
{
	ReturnType result;
	
		for (int c = 0; c < 2; c++)
		{
			if (m_buttons[c].Contains(mousePos))
			{
				m_selectedColors[c] = SELECT_COLOR_BLUE;
			}
			else
				m_selectedColors[c] = SELECT_COLOR_NONE;
		}
	
	return result;
}
////////////////////////////////////////////////////////////////////////////////////////
//USER INPUT
////////////////////////////////////////////////////////////////////////////////////////
UserInterfaceManager::UserInput::UserInput()
{
	
}


UserInterfaceManager::UserInput::UserInput(std::wstring msg, std::wstring caption, int owner)
	:m_msg(msg),m_caption(caption),m_owner(owner)
{
	m_image = Locator::ImageManager()->GetImage("message_box")->GetTexture();
	pTextFormat = Locator::TextManager()->GetFormat("Tahoma12");
	float x = (Locator::ScreenWidth<float>() / 2) - (float)(m_image->GetSize().width / 2);
	float y = (Locator::ScreenHeight<float>() / 2) - (float)(m_image->GetSize().height / 2);
	m_frame = { x ,y,x + (float)m_image->GetSize().width ,y + (float)m_image->GetSize().height };
	m_buttons[0] = RectF(x + 16.0f*1.0f, y + 16.0f * 6.0f, x + 16.0f * 5.0f, y + 16.0f*7.0f);
	m_buttons[1] = RectF(x + 16.0f*11.0f, y + 16.0f * 6.0f, x + 16.0f * 15.0f, y + 16.0f*7.0f);
	m_msgRect = RectF( x + 16.0f ,y + 40.0f,x + ((float)m_image->GetSize().width - 20.0f) ,y + 62.0f );
	m_captionRect = RectF(x + 16.0f, y + 12.0f, x + m_image->GetSize().width - (16.0f * 2.0f), y + 16.0f * 3.0f);
	m_inputFrame = 	RectF(x + 16.0f, y + 16.0f * 4.0f, x + 16.0f * 15.0f, y + 84.0f);
	m_drawRect = { m_inputFrame.left + 4.0f,m_inputFrame.top + 4.0f,m_inputFrame.right,m_inputFrame.bottom };
}

UserInterfaceManager::UserInput::~UserInput()
{
}

ReturnType  UserInterfaceManager::UserInput::OnMouseClick(const Vec2i & mousePos)
{
	ReturnType result;
	
		if (m_buttons[0].Contains(mousePos))
		{			
			if (m_text.size() > 0)
			{
				while (m_text.front() == ' ')
					m_text.erase(m_text.begin());
				while (m_text.back() == ' ')
					m_text.pop_back();
				
				result.data = &m_text;
				result.result = RETURN_RESULT_DONE;
				result.type = m_owner;
				
			}
			
		}
		if (m_buttons[1].Contains(mousePos))
		{
			result.result = RETURN_RESULT_CANCEL;
			result.type = m_owner;
		}
	
	return result;
}

ReturnType  UserInterfaceManager::UserInput::OnMouseMove(const Vec2i & mousePos)
{
	ReturnType result;

	for (int c = 0; c < 2; c++)
	{
		if (m_buttons[c].Contains(mousePos))
		{
			m_selectedColors[c] = SELECT_COLOR_BLUE;
		}
		else
			m_selectedColors[c] = SELECT_COLOR_NONE;
	}

	return result;
}

ReturnType  UserInterfaceManager::UserInput::OnKeyPress(const unsigned char & key)
{
	ReturnType result;
	
		result.type = MENU_TYPE_INPUT;
		if (key == VK_RETURN)
		{
			if (m_text.size() > 0)
			{
				while (m_text.front() == ' ')
					m_text.erase(m_text.begin());
				while (m_text.back() == ' ')
					m_text.pop_back();
				result.result = RETURN_RESULT_ENTER;
				result.data = &m_text;
				return result;
			}
		}
		if (key == VK_BACK)
		{
			if (m_text.size() > 0)
				m_text.pop_back();
		}
		else
		{
			int iKey = (int)key;
			if ((iKey > 64 && iKey < 91) || (iKey > 47 && iKey < 58) || iKey == 32)
			{
				if (m_text.size() < 16u)
					m_text.push_back(key);
			}
		}
	
	return ReturnType();
}

void  UserInterfaceManager::UserInput::Draw(Graphics & gfx)
{
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), m_image);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_frame.ToD2D(), FULL_COLOR_WHITE);


	gfx.RenderText((LPWSTR)m_msg.c_str(), pTextFormat, m_msgRect.ToD2D(), FULL_COLOR_WHITE);
	gfx.RenderText((LPWSTR)m_caption.c_str(), pTextFormat, m_captionRect.ToD2D(), FULL_COLOR_WHITE);
	for (int c = 0; c < 2; c++)
	{
		gfx.DrawFilledRectangle(m_buttons[c].ToD2D(), m_selectedColors[c]);
		gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_buttons[c].ToD2D(), FULL_COLOR_WHITE);
	}
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	gfx.RenderText(L"Ok", pTextFormat, m_buttons[0].ToD2D(), FULL_COLOR_WHITE);
	gfx.RenderText(L"Cancel", pTextFormat, m_buttons[1].ToD2D(), FULL_COLOR_WHITE);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	std::wstring out_text;
	DXStringHandler::DXConvertFromStrToWStr(m_text, out_text);
	
	gfx.DrawFilledRectangle(m_inputFrame.ToD2D(), SELECT_COLOR_BLUE);
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_inputFrame.ToD2D(), FULL_COLOR_WHITE);
	gfx.RenderText((LPWSTR)out_text.c_str(), pTextFormat,
		m_drawRect.ToD2D(), FULL_COLOR_WHITE);
}
