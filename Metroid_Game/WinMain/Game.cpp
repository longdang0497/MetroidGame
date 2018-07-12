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
	delete (camera);
	delete (_input);
	delete (_dxgraphics);
	delete(_device);
}

void Game::GameInit()
{
	//Game::gameSound->LoadSound(_hWnd);
	_dxgraphics->_InitWindow();
	int width = _dxgraphics->getScreenWidth();
	int height = _dxgraphics->getScreenHeight();
	camera = new Camera(width, height, 0, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
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
		CheckKey();

		ProcessInput(_device->getdevice(), _DeltaTime);

	}
}

void Game::CheckKey() 
{
	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = _input->getKeyboard()->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _input->getKeyEvents(), &dwElements, 0);

	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _input->getKeyEvents()[i].dwOfs;
		int KeyState = _input->getKeyEvents()[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}

void Game::_RenderFrame()
{
	const auto result = _device->getdevice()->BeginScene();
	if (result == D3D_OK)
	{
		// Clear back buffer with BLACK
		//_device->getdevice()->ColorFill(_device->getBuffer(), NULL, D3DCOLOR_XRGB(0, 0, 0));

		_device->clearScreen();
		if (camera)
		{
			camera->SetTransform(_device);
		}
		RenderFrame(_device->getdevice());
		_device->getdevice()->EndScene();
	}

	_device->getdevice()->Present(NULL, NULL, NULL, NULL);
}

void Game::Update(float Delta)
{
}

void Game::RenderFrame(LPDIRECT3DDEVICE9 device)
{

}

void Game::LoadResources(LPDIRECT3DDEVICE9 d3ddev)
{

}

void Game::ProcessInput(LPDIRECT3DDEVICE9 device, float Delta)
{
}

void Game::OnKeyDown(int KeyCode)
{
}

void Game::OnKeyUp(int KeyCode)
{
}

void Game::setPlayerTexture(LPDIRECT3DTEXTURE9 playerTexture) {
	this->playerTexture = playerTexture;
}

LPDIRECT3DTEXTURE9 Game::getPlayerTexture() {
	return this->playerTexture;
}

void Game::setBrickTexture(LPDIRECT3DTEXTURE9 brickTexture) {
	this->brickTexture = brickTexture;
}

LPDIRECT3DTEXTURE9 Game::getBrickTexture() {
	return this->brickTexture;
}