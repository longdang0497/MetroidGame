#pragma once
#include "MaruMari.h"
#include <d3dx9.h>
#include "Define.h"
#include "Samus.h"
#include "Skree.h"
#include "Zoomer.h"
#include <vector>
#include "Texture.h"
#include "Grid.h"

using namespace std;
//#include "BulletManager.h"

/*
Class này chứa tất cả những thứ trong Game
Các class khác chứa con trỏ đến class này để thao tác với các đối tượng trong class này
*/

class World
{
public:
	Grid * grid;
	Metroid * metroid;
	Samus * samus;
	MaruMari * maruMari;
	Skree * skree;
	Zoomer * zoomer_yellow;
	Zoomer * zoomer_pink;
	//Manager * bulletManager;
	LPD3DXSPRITE spriteHandler;
	vector<Zoomer*> zoomerYellow = vector<Zoomer*>(5);
	vector<Zoomer*> zoomerPink = vector<Zoomer*>(5);

	World();
	World(LPD3DXSPRITE spriteHandler, Metroid * metroid);
	~World();

	void Update(float t);
	void Render();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);

};