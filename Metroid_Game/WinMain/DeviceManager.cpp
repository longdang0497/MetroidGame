#include "DeviceManager.h"

DeviceManager::DeviceManager()
{
	_d3d = NULL;
	_d3ddv = NULL;
	_BackBuffer = NULL;
}

DeviceManager::~DeviceManager()
{
	if (_d3ddv != NULL) _d3ddv->Release();
	if (_d3d != NULL) _d3d->Release();
}

void DeviceManager::_InitDirectX(Graphics dxg)
{
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = _BackBufferFormat;
	d3dpp.BackBufferWidth = dxg.getScreenWidth();
	d3dpp.BackBufferHeight = dxg.getScreenHeight();
	d3dpp.Windowed = TRUE;
	d3dpp.hDeviceWindow = dxg.getWnd();
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	const auto rs = _d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		dxg.getWnd(),
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&_d3ddv);

	if (_d3ddv == nullptr)
	{
		MessageBox(NULL, L"Error creating Direct3D Device", L"Error", MB_OK);
	}

	_d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &_BackBuffer);
}

LPDIRECT3DDEVICE9 DeviceManager::getdevice()
{
	return _d3ddv;
}

void DeviceManager::setdevice(LPDIRECT3DDEVICE9 d3ddv)
{
	_d3ddv = d3ddv;
}

LPDIRECT3DSURFACE9 DeviceManager::getBuffer()
{
	return _BackBuffer;
}

void DeviceManager::clearScreen()
{
	_d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	//_d3ddv->ColorFill(_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
}
