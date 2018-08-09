#pragma once
#include "Define.h"

class Texture {
private: 
	LPCWSTR textureFilePath;
	D3DCOLOR transColor;
public:
	Texture();
	~Texture();

	LPDIRECT3DTEXTURE9 loadTexture(LPDIRECT3DDEVICE9, LPCWSTR);
};