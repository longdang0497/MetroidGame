#pragma once
#include "Item.h"
#include "Define.h"
class MaruMari : public Item
{
	Sprite * maruMari;
public:
	MaruMari(LPD3DXSPRITE spriteHandler, World * manager);
	~MaruMari();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Init(float posX, float posY);
	void Update(float t);
	void Render();
	void Destroy();
};
