#pragma once
#include <windows.h>
#include "mouse.h"
#include "keyboard.h"
#include <WindowsX.h>
#include "GameState.h"
#include "InputManager.h"
#include <memory>

const static bool FULL_SCREEN = true;
const static int SCREEN_WIDTH = 800;
const static int SCREEN_HEIGHT = 600;
const static WCHAR* APPLICATION_NAME = L"Shyte";

class Direct3DWindow
{
	friend class Game;
public:
	Direct3DWindow();
	Direct3DWindow(int scrnWidth, int scrnHeight);
	Direct3DWindow(const Direct3DWindow&);
	~Direct3DWindow();

	
	void Shutdown();
	_GameState ProcessMessage();
	int ScreenWidth();
	int ScreenHeight();
	
	void ScreenHalfExtents(float& x, float& y);
	HWND& WindowHandle();
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	void SetEndApp(bool val);
private:
	bool Frame();
	void InitializeWindows();
	void ShutdownWindows();
	_GameState state = _GameState::running;
	
private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	int m_screenHeight;
	int m_screenWidth;
	bool m_endApp = false;
	Mouse mouse;
	Keyboard kbd;
	InputManager m_input;
};


static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


static Direct3DWindow* ApplicationHandle = 0;
