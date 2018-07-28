#include "ExplodeEffect.h"

ExplodeEffect::ExplodeEffect(LPD3DXSPRITE spriteHandler, World *manager, Grid * grid) : Effect(spriteHandler, manager, grid)
{/*
	effect_type = EXPLOSION;
	explode = nullptr;
	currentSprite = explode;*/
}

ExplodeEffect::~ExplodeEffect()
{
	//delete explode;
}

void ExplodeEffect::Update(float t)
{
	/*DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		currentSprite->updateIndex();
		last_time = now;
	}*/

	//// Tính thời gian hiển thị
	//time_survive -= t;
	//// Nếu hết thời gian thì không hiển thị nữa
	//if (time_survive <= 0)
	//{
	//	isActive = false;
	//}
}

void ExplodeEffect::Render()
{
}

void ExplodeEffect::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	//if (d3ddv == NULL) return;
	////Create sprite handler
	//HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	//if (result != D3D_OK) return;

	//currentSprite = new Sprite(spriteHandler, texture, EFFECT_EXPLOSION, EFFECT_EXPLOSION_WIDTH, EFFECT_EXPLOSION_HEIGHT, EFFECT_EXPLOSION_COUNT);
}
