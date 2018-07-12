#pragma once
#include "Define.h"
#include <Windows.h>

class Graphics
{
protected:
	HINSTANCE _hInstance;	// Handle of the game instance
	LPWSTR _Name;			// Name of game will be used as Window Class Name
	HWND _hWnd;

	int _IsFullScreen;		// Is running in fullscreen mode?

	int _ScreenWidth;
	int _ScreenHeight;
	float _FrameRate;
	int _Mode;				// Screen mode 
	int _Depth;

	static LRESULT CALLBACK _WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	Graphics(HINSTANCE hInstance, LPWSTR name, int mode, int framerate, int isFullScreen);
	~Graphics();

	int getScreenWidth() { return _ScreenWidth; };
	int getScreenHeight() { return _ScreenHeight; };

	void _SetScreenDimension(int Mode);
	float getFrameRate();
	HWND getWnd();
	HINSTANCE gethInstance();
	int isFullScreen();

	void _InitWindow();
};
