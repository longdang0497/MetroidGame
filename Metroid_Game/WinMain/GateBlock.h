#pragma once
#include "GameObject.h"
#include "Define.h"

class GateBlock : public GameObject
{
private:
	Sprite * gateBlock;
public:
	GateBlock(LPD3DXSPRITE spriteHandler, World * manager, Grid * grid);
	~GateBlock();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Init(int x, int y);
	void Update(float t);
	void Render();
};