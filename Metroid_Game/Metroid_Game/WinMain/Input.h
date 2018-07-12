#pragma once
#include "Define.h"
#include "trace.h"
#include <dinput.h>

class Input
{
private:
	LPDIRECTINPUT8       _di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 
	HWND _hWnd;				// Handle of the Game Window
	BYTE  _KeyStates[256];			// DirectInput keyboard state buffer

									// Buffered keyboard data
	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];
public:
	Input();
	~Input();

	LPDIRECTINPUTDEVICE8 getKeyboard();
	void _InitKeyboard(HINSTANCE _hInstance, HWND hwnd);
	void _ProcessKeyBoard();
	int IsKeyDown(int KeyCode);

	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};