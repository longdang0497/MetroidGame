#include "Game.h"
#include "trace.h"

//SoundManager* Game::gameSound = NULL;
Graphics* Game::_dxgraphics = NULL;

Game::Game()
{
}

Game::Game(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullscreen, int FrameRate)
{
	_device = new DeviceManager();
	_input = new Input();
	_dxgraphics = new Graphics(hInstance, Name, Mode, FrameRate, IsFullscreen);
	//Game::gameSound = new SoundManager();
}

Game::~Game()
{
	//Game::gameSound->shutdownDirectSound();
}

void Game::GameInit()
{
	//Game::gameSound->LoadSound(_hWnd);
	_dxgraphics->_InitWindow();
	_input->_InitKeyboard(_dxgraphics->gethInstance(), _dxgraphics->getWnd());
	_device->_InitDirectX(*_dxgraphics);
	LoadResources(_device->getdevice());
}

void Game::GameRun()
{
	MSG msg;
	int done = 0;
	DWORD frame_start = GetTickCount();;

	DWORD tick_per_frame = 100 / _dxgraphics->getFrameRate();

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;
			else if (msg.message == WM_ACTIVATE) {
				if (_input->getKeyboard() != NULL && _input->getKeyboard()->Poll() != DI_OK) {
					_input->getKeyboard()->Acquire();
				}
				msg.message = 0;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


		DWORD now = GetTickCount();
		_DeltaTime = now - frame_start;
		if (_DeltaTime >= tick_per_frame)
		{
			frame_start = now;
			Update(_DeltaTime / 1000.0f);
			_RenderFrame();

		}
		else
		{
			Sleep(1);
		}

		_input->_ProcessKeyBoard();

		ProcessInput(_device->getdevice(), _DeltaTime);

	}
}

void Game::_RenderFrame()
{
	const auto result = _device->getdevice()->BeginScene();
	if (result == D3D_OK)
	{
		// Clear back buffer with BLACK
		_device->getdevice()->ColorFill(_device->getBuffer(), NULL, D3DCOLOR_XRGB(0xAA, 0xAA, 0xAA));

		_device->clearScreen();
		RenderFrame(_device->getdevice());
		_device->getdevice()->EndScene();
	}

	_device->getdevice()->Present(NULL, NULL, NULL, NULL);
}

void Game::Update(float Delta)
{
}

void Game::RenderFrame(LPDIRECT3DDEVICE9 d3ddv)
{
}

void Game::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
}

void Game::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta)
{
}

void Game::OnKeyDown(int KeyCode)
{
}

void Game::OnKeyUp(int KeyCode)
{
}