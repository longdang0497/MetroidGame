#pragma once
#include "Effect.h"
#include "Define.h"
#include "World.h"

class ExplodeEffect :	public Effect
{
	Sprite * explode;
	float time_survive = 0;
	bool isRendering = false;
public:
	ExplodeEffect(LPD3DXSPRITE spriteHandler, World *manager, Grid * grid);
	~ExplodeEffect();

	void CreateExplode(float x, float y );
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Update(float t);
	void Render();
};

