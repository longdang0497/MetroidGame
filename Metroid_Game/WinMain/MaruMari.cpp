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
	this->width = MARU_MARI_WIDTH;
	this->height = MARU_MARI_HEIGHT;
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

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		maruMari->updateSprite();
		last_time = now;
	}

	//if (!isActive)
	//	return;

	//vy -= FALLDOWN_VELOCITY_DECREASE;


	//// Xét va chạm với ground
	//for (int i = 0; i < manager->quadtreeGroup->size; i++)
	//{
	//	switch (manager->quadtreeGroup->objects[i]->GetType())
	//	{
	//	case BRICK:
	//		float timeScale = SweptAABB(manager->quadtreeGroup->objects[i], t);

	//		// Chỉ cần xét va chạm phía trên cục gạch thôi
	//		if (timeScale < 1.0f && normaly > 0.1f)
	//		{
	//			this->pos_y = (manager->quadtreeGroup->objects[i]->GetPosY() + manager->quadtreeGroup->objects[i]->GetCollider()->GetTop() - this->collider->GetBottom()) + 0.1f;
	//			pos_y -= vy*t;
	//		}
	//		break;
	//	}
	//}

	//pos_x += vx*t;
	//pos_y += vy*t;

	// Morph ball không cần set thời gian để biến mất như những item khác
	// xxx
}

void MaruMari::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	if (!isActive)
		return;

	maruMari->drawSprite(MARU_MARI_WIDTH, MARU_MARI_HEIGHT, position);
}

void MaruMari::Destroy()
{
	isActive = false;
}


