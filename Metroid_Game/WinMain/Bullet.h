#pragma once
#include "Sprite.h"
#include "GameObject.h"
#include "trace.h"
#include "World.h"
#include "Define.h"

enum BULLET_STATE {
	SAMUS_BULLET,
	KREE_BULLET,
	BOSS_BULLET
};

enum BulletDirection
{
	SHOOT_UP,
	SHOOT_LEFT,
	SHOOT_RIGHT
};

class Bullet : public GameObject {
protected:
	Sprite * bulletSprite;
	BulletDirection bulletdir;
	BULLET_STATE state = SAMUS_BULLET;

public:
	bool isActive;
	//ket thuc thoi gian liveTime, xem nhu vien dan bay het duong bay -> huy vien dan
	float liveTime = 0;

	Bullet();
	Bullet(LPD3DXSPRITE spriteHandler, World * manager);
	~Bullet();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void InitPostition();

	BULLET_STATE GetState();
	void SetState(BULLET_STATE value);
	void SetDir(BulletDirection value);
	BulletDirection GetDir();

	void ResetAllSprites();
	bool GetStateActive();

	//================ OVERRIDE VIRTUAL METHOD ==================
	void Reset(int  x, int y);
	void Update(float t);
	void Render();
	void Destroy();
	//================= END OVERRIDE VIRTUAL METHOD =============

};

