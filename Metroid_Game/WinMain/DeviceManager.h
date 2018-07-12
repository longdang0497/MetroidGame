#pragma once
#include "DXGraphics.h"

class DeviceManager
{
private:
	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3ddv;		// Rendering device
	LPDIRECT3DSURFACE9 _BackBuffer;	// Pointer to backbuffer 

	D3DFORMAT _BackBufferFormat = D3DFMT_X8R8G8B8;
public:
	DeviceManager();
	~DeviceManager();

	void _InitDirectX(Graphics dxg);

	LPDIRECT3DDEVICE9 getdevice();
	void setdevice(LPDIRECT3DDEVICE9 d3ddv);
	LPDIRECT3DSURFACE9 getBuffer();
	void clearScreen();
};
