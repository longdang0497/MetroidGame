#include "Input.h"

Input::Input()
{
	_di = NULL;
	_Keyboard = NULL;
	ZeroMemory(_KeyStates, 256);
}

Input::~Input()
{
	if (_di != NULL)
		this->_di->Release();
	if (_Keyboard != NULL)
		this->_Keyboard->Release();
}

LPDIRECTINPUTDEVICE8 Input::getKeyboard()
{
	return _Keyboard;
}

void Input::_InitKeyboard(HINSTANCE _hInstance, HWND hwnd)
{
	_hWnd = hwnd;

	HRESULT hr = DirectInput8Create(
		_hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&_di,
		NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;

	trace(L"DirectInput has been created");

	hr = _di->CreateDevice(GUID_SysKeyboard, &_Keyboard, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;

	trace(L"DirectInput keyboard has been created");

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = _Keyboard->SetDataFormat(&c_dfDIKeyboard);

	trace(L"SetDataFormat for keyboard successfully");

	hr = _Keyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	trace(L"SetCooperativeLevel for keyboard successfully");

	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	trace(L"SetProperty for keyboard successfully");

	hr = _Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	/*hr = _Keyboard->Acquire();
	if (hr != DI_OK) return;*/

	hr = _Keyboard->Acquire();
	if (hr != DI_OK) return;

	trace(L"Keyboard has been acquired successfully");
}

void Input::_ProcessKeyBoard()
{
	static HRESULT result;
	// Collect all key states first
	result = _Keyboard->GetDeviceState(sizeof(_KeyStates), _KeyStates);

	if (IsKeyDown(DIK_ESCAPE))
	{
		trace(L"Escape key pressed!");
		PostMessage(_hWnd, WM_QUIT, 0, 0);
	}

	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			_Keyboard->Acquire();
		}
	}
	//CheckKey();
}

//// Scan through all data, check if the key is pressed or released	
//void Input::CheckKey()
//{
//	// Collect all buffered events
//	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
//	HRESULT hr = _Keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);
//
//	for (DWORD i = 0; i < dwElements; i++)
//	{
//		int KeyCode = _KeyEvents[i].dwOfs;
//		int KeyState = _KeyEvents[i].dwData;
//		if ((KeyState & 0x80) > 0)
//			OnKeyDown(KeyCode);
//		else
//			OnKeyUp(KeyCode);
//	}
//}

int Input::IsKeyDown(int KeyCode)
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}

//void Input::OnKeyDown(int KeyCode)
//{
//	//Game::OnKeyDown(KeyCode);
//}
//
//void Input::OnKeyUp(int KeyCode)
//{
//}
