#pragma once
#include "MaruMari.h"
#include "Define.h"
#include "Samus.h"
#include "Zoomer.h"
#include <vector>
#include "Texture.h"
#include "Bullet.h"
#include "ExplodeEffect.h"
#include "BombWeapon.h"
#include "Gate.h"
#include "GateBlock.h"
#include "Ridley.h"
#include "Kraid.h"

using namespace std;

/*
Class này chứa tất cả những thứ trong Game
Các class khác chứa con trỏ đến class này để thao tác với các đối tượng trong class này
*/

class World
{
public:
	Metroid * metroid;
	Samus * samus;
	MaruMari * maruMari;
	ExplodeEffect* explodeEffect;
	BombWeapon* bombWeapon;
	Gate * gateLeftRoom1;
	Gate * gateRightRoom1;
	Gate * gateLeftRoom2;
	Gate * gateRightRoom2;
	Gate * gateLeftBoss1;
	Gate * gateRightBoss1;
	GateBlock * gateBlockRoom1;
	GateBlock * gateBlockRoom2;
	GateBlock * gateBlockBoss1;
	Kraid * kraid;
	Ridley * ridley;

	vector<Bullet*> samusBullet;
	vector<Enemy*> enemy;
	LPD3DXSPRITE spriteHandler;

	World();
	World(LPD3DXSPRITE spriteHandler, Metroid * metroid);
	~World();

	void Update(float t);
	void Render();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);

	void loadEnemyPositions(string filePath);
	vector<string> World::split(string s, string c);
	Metroid * getMetroid();

	void setDirectionForZoomer(Enemy*, string str);
};