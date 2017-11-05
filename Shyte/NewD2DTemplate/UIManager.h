#pragma once
#include "StartScreen.h"
#include "NewGame.h"
#include "coredata.h"
#include "PausedScreen.h"
#include "BackGround.h"
#include "SelectUsers.h"

class UserInterfaceManager
{
	
	std::unordered_map < std::string, std::shared_ptr<UserInterface> > m_screens;
	std::vector<std::string> m_users;
	std::string m_newUserName;
	
	UserInterface* m_currentScreen = nullptr;
	UserInterface* m_perviousScreen = nullptr;
	ReturnType HandleStartScreen(ReturnType& data);
	ReturnType HandleInputScreen(unsigned char& key);
	ReturnType HandleInputScreen(ReturnType& data);
	ReturnType HandlePausedScreen(ReturnType& data);
	ReturnType HandleSelectUserScreen(ReturnType& data);
	ReturnType HandleNewGameScreen(ReturnType& data);
	bool DoesUserExist(std::string user);
	void AddUser(std::string& user);
public:
	UserInterfaceManager();
	~UserInterfaceManager();;
	void Draw(class Graphics& gfx);
	ReturnType OnMouseClick(Vec2i& mousePos);
	ReturnType OnMouseMove(Vec2i& mousePos);
	ReturnType OnKeyPress(unsigned char& key);
	void SetCurrentScreen(std::string& name);
	void InitializeCurrentUsers(std::vector<std::string>& usernames);
private:
	class Message
	{
		std::wstring m_msg;
		std::wstring m_caption;
		ID2D1Bitmap* m_image = nullptr;
		RectF m_buttons[2];
		RectF m_frame;
		RectF m_msgRect;
		RectF m_captionRect;
		IDWriteTextFormat* pTextFormat = nullptr;
		D2D1_COLOR_F m_selectedColors[2] =
		{
			SELECT_COLOR_NONE,
			SELECT_COLOR_BLUE
		};
		int m_owner = -1;
	public:
		Message(std::wstring text, std::wstring caption,int owner)
			:m_msg(text), m_caption(caption),m_owner(owner)
		{
			m_image = Locator::ImageManager()->GetImage("message_box")->GetTexture();
			pTextFormat = Locator::TextManager()->GetFormat("Tahoma12");

			float x = (Locator::ScreenWidth<float>() / 2) - (float)(m_image->GetSize().width / 2);
			float y = (Locator::ScreenHeight<float>() / 2) - (float)(m_image->GetSize().height / 2);
			m_frame = { x ,y,x + (float)m_image->GetSize().width ,y + (float)m_image->GetSize().height };
			m_buttons[0] = RectF(x + 16.0f*1.0f, y + 16.0f * 6.0f, x + 16.0f * 5.0f, y + 16.0f*7.0f);
			m_buttons[1] = RectF(x + 16.0f*11.0f, y + 16.0f * 6.0f, x + 16.0f * 15.0f, y + 16.0f*7.0f);
			m_msgRect = RectF(x + 16.0f, y + 16.0f * 4.0f, x+m_image->GetSize().width - (16.0f * 2.0f), y + 16.0f * 6.0f);
			m_captionRect = RectF(x +16.0f, y+16.0f , x+m_image->GetSize().width - (16.0f * 2.0f), y + 16.0f * 3.0f);
			
		};
		void Draw(class Graphics& gfx);
		ReturnType OnMouseClick(Vec2i& mousePos);
		ReturnType OnMouseMove(Vec2i& mousePos);
	};
	class UserInput 
	{
		std::string m_text;
		RectF m_drawRect = { 100.0f,100.0f,300.0f,120.0f };
		RectF m_inputFrame;
		RectF m_frame;
		RectF m_msgRect;
		RectF m_captionRect;
		IDWriteTextFormat* pTextFormat = nullptr;
		ID2D1Bitmap* m_image;
		std::wstring m_msg;
		std::wstring m_caption;
		RectF m_buttons[2];
		D2D1_COLOR_F m_selectedColors[2] =
		{
			SELECT_COLOR_NONE,
			SELECT_COLOR_BLUE
		};
		int m_owner = -1;
	
	public:
		UserInput();
		UserInput(std::wstring msg,std::wstring caption,int owner);
		~UserInput();

		// Inherited via UserInterface
		virtual ReturnType OnMouseClick(const Vec2i & mousePos) ;
		virtual ReturnType OnMouseMove(const Vec2i & mousePos);
		virtual ReturnType OnKeyPress(unsigned char & key);
		virtual void Draw(Graphics & gfx) ;
	};
	Message* m_pMessageBox = nullptr;
	UserInput* m_pUserInput = nullptr;
};