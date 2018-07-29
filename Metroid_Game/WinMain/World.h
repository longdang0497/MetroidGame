#pragma once
#include "MaruMari.h"
#include <d3dx9.h>
#include "Define.h"
#include "Samus.h"
#include "Zoomer.h"
#include <vector>
#include "Texture.h"
#include "Grid.h"
#include "Bullet.h"

using namespace std;

/*
Class này chứa tất cả những thứ trong Game
Các class khác chứa con trỏ đến class này để thao tác với các đối tượng trong class này
*/

class World
{
public:
	Metroid * metroid;
	Grid *grid;
	Samus * samus;
	MaruMari * maruMari;
	vector<Bullet*> samusBullet;
	vector<Enemy*> enemy;
	LPD3DXSPRITE spriteHandler;

	World();
	World(LPD3DXSPRITE spriteHandler, Metroid * metroid, int width, int height);
	~World();

	void Update(float t);
	void Render();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);

	void loadEnemyPositions(string filePath);
	vector<string> World::split(string s, string c);
};