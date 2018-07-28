#pragma once
#include "Effect.h"
class ExplodeEffect :	public Effect
{
	Sprite * explode;
public:
	ExplodeEffect(LPD3DXSPRITE spriteHandler, World *manager, Grid * grid);
	~ExplodeEffect();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Update(float t);
	void Render();
};

