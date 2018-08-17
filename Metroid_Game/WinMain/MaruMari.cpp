﻿#include "MaruMari.h"
#include "World.h"

MaruMari::MaruMari(LPD3DXSPRITE spriteHandler, World * manager) :Item(spriteHandler, manager)
{
	this->setType(ITEM);
	this->type = MARU_MARI;
	maruMari = NULL;
	isActive = true;

	this->previousUnit = NULL;
	this->nextUnit = NULL;
	this->width = 32;
	this->height = 32;
}

MaruMari::~MaruMari()
{
	delete(maruMari);
}

void MaruMari::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;
	maruMari = new Sprite(spriteHandler, texture, MARU_MARI_PATH, MARU_MARI_WIDTH, MARU_MARI_HEIGHT, MARU_MARI_COUNT);
}

void MaruMari::Init(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->isActive = true;
	time_survive = ITEM_TIME_SURVIVE;
}

void MaruMari::Update(float t)
{
	if (!this->isActive) return;

	float posXSamus = this->manager->samus->pos_x;
	float posYSamus = this->manager->samus->pos_y;
	float widthSamsus = this->manager->samus->getWidth();
	float heightSamus = this->manager->samus->getHeight();

	if (this->pos_y <= posYSamus + heightSamus + 32 && posXSamus >= this->pos_x && posXSamus <= this->pos_x + this->width) {
		this->isActive = false;
		return;
	}

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		maruMari->updateSprite();
		last_time = now;
	}
}

void MaruMari::Render()
{
	if (!this->isActive) return;

	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	maruMari->drawSprite(maruMari->getWidth(), maruMari->getHeight(), position);
	spriteHandler->End();
}

void MaruMari::Destroy()
{
	isActive = false;
}


