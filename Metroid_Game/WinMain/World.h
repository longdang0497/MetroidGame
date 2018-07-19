#pragma once
#ifndef _WORLD_H_
#define _WORLD_H_

#include <d3dx9.h>
#include "Define.h"
#include "Samus.h"
#include "Zoomer.h"
#include <vector>

using namespace std;
//#include "BulletManager.h"

/*
Class này chứa tất cả những thứ trong Game
Các class khác chứa con trỏ đến class này để thao tác với các đối tượng trong class này
*/

class World
{
public:
	Metroid * metroid;
	Samus * samus;
	Zoomer * zoomer_yellow;
	Zoomer * zoomer_pink;
	//Manager * bulletManager;
	LPD3DXSPRITE spriteHandler;
	vector<Zoomer*> zoomerYellow = vector<Zoomer*>(3);
	vector<Zoomer*> zoomerPink = vector<Zoomer*>(3);

	World();
	World(LPD3DXSPRITE spriteHandler, Metroid * metroid);
	~World();

	void Update(float t);
	void Render();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);

};

#endif // !_WORLD_H_

