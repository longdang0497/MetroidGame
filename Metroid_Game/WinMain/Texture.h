#pragma once
#include "Define.h"
#include <d3d9.h>
#include <d3dx9.h>


class Texture {
private: 
	LPCWSTR textureFilePath;
	D3DCOLOR transColor;
public:
	Texture();
	~Texture();

	LPDIRECT3DTEXTURE9 loadTexture(LPDIRECT3DDEVICE9, LPCWSTR);
};