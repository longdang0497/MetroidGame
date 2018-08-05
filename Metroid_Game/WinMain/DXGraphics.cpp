#include "DXGraphics.h"

void Graphics::_SetScreenDimension(int Mode)
{
	switch (Mode)
	{
	case GAME_SCREEN_RESOLUTION_640_480_24:
		_ScreenWidth = 640;
		_ScreenHeight = 480;
		_Depth = 24;
		break;

	case GAME_SCREEN_RESOLUTION_800_600_24:
		_ScreenWidth = 800;
		_ScreenHeight = 600;
		_Depth = 24;
		break;

	case GAME_SCREEN_RESOLUTION_1024_768_24:
		_ScreenWidth = 1024;
		_ScreenHeight = 768;
		_Depth = 24;
		break;

	default:
		break;
	}
}

float Graphics::getFrameRate()
{
	return _FrameRate;
}

HWND Graphics::getWnd()
{
	return _hWnd;
}

HINSTANCE Graphics::gethInstance()
{
	return _hInstance;
}

int Graphics::isFullScreen()
{
	return _IsFullScreen;
}

void Graphics::_InitWindow()
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = _hInstance;

	wc.lpfnWndProc = (WNDPROC)Graphics::_WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _Name;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	DWORD style;
	if (_IsFullScreen)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	_hWnd =
		CreateWindow(
			_Name,
			_Name,
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			_ScreenWidth,
			_ScreenHeight,
			NULL,
			NULL,
			_hInstance,
			NULL);

	if (!_hWnd)
	{
		MessageBox(_hWnd, L"[ERROR] Failed to created window!", NULL, NULL);
	}

	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);
}

LRESULT Graphics::_WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Process message sent to windows
	switch (message) {
	case WM_ACTIVATE:
		if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE) {
			PostMessage(hWnd, WM_ACTIVATE, wParam, lParam);
		}
		break;
	case WM_CLOSE: // Windows is about to be closed because user click Close button or press Alt + F4
		break;
	case WM_DESTROY: // Windows is already closed and is about to be destroyed
		PostQuitMessage(0); // put quit message to message queue
		break;
	default:
		break;
	}

	// Default message behaviors
	return DefWindowProc(hWnd, message, wParam, lParam);
}

Graphics::Graphics(HINSTANCE hInstance, LPWSTR name, int mode, int framerate, int isFullScreen)
{
	_hInstance = hInstance;
	_Name = name;
	_Mode = mode;
	_FrameRate = framerate;
	_IsFullScreen = isFullScreen;
	_SetScreenDimension(GAME_SCREEN_RESOLUTION_640_480_24);
}

Graphics::~Graphics()
{
}
