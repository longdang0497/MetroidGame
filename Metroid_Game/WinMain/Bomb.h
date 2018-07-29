#pragma once
#include "Item.h"
#include "Define.h"

class ItemBomb : public Item
{
private:
	Sprite * itemBomb;
public:
	ItemBomb(LPD3DXSPRITE spriteHandler, World * manager, Grid * grid);
	~ItemBomb();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Init(float posX, float posY);
	void Update(float t);
	void Render();
	void Destroy();
};