#pragma once
#include "GameObject.h"
//#include "BulletManager.h"
#include <time.h>

#define ANIMATE_ENEMY_RATE 7
#define ENEMY_FREEZE 500;

class Enemy : public GameObject
{
public:
	float time_freeze;	// thời gian dừng khi bị hit
	float health;		// Máu của object
	float damage;		// Lượng sát thương gây ra của object
	bool DeathByShoot;

	bool isActive = false;
	bool isDeath = false;

	string direction = "";


	Enemy();
	Enemy(LPD3DXSPRITE spriteHandler, World * manager);
	~Enemy();

	virtual void InitPostition();
	virtual void InitPostition(int x, int y);
	virtual void InitSprites(LPDIRECT3DDEVICE9 d3ddv);

	void SetDirection(string _direction);

	//============== OVERRIDE VIRTUAL METHOD ===============
	virtual void Render();
	virtual void Update(float t);
	virtual void setEnemyStatefromString(string _state);
	virtual void startMoving();
	//============== END OVERRIDE VIRTUAL METHOD ============

	bool isInsideMapBound(RECT cameraBound);
};

