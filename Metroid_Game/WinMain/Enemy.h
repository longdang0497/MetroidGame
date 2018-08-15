#pragma once
#include "GameObject.h"
#include <time.h>

#define ANIMATE_ENEMY_RATE 7
#define ENEMY_FREEZE 500;

class Enemy : public GameObject
{
protected:
	LPDIRECT3DTEXTURE9 texture;
	float initPosX;
	float initPosY;
	float isEnemyFreezed;
public:
	float time_freeze;	// thời gian dừng khi bị hit
	int health;		// Máu của object
	float damage;		// Lượng sát thương gây ra của object
	bool DeathByShoot;

	bool isActive = false;
	bool isDeath = false;

	Enemy();
	Enemy(LPD3DXSPRITE spriteHandler, World * manager);
	~Enemy();

	virtual void InitPostition();
	virtual void InitPostition(int x, int y);
	virtual void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);

	//============== OVERRIDE VIRTUAL METHOD ===============
	virtual void Render();
	virtual void Update(float t);
	virtual void setEnemyStatefromString(string _state);
	virtual void startMoving();
	//============== END OVERRIDE VIRTUAL METHOD ============

	virtual void setSamusLocation(float posX, float posY);

	bool isInsideMapBound(RECT cameraBound);

	void setTexture(LPDIRECT3DTEXTURE9 texture);
	LPDIRECT3DTEXTURE9 getTexture();

	void setInitPosX(float x);
	float getInitPosX();
	void setInitPosY(float y);
	float getInitPosY();

	void setHealth(int value) { this->health = value; }
	int getHealth() { return this->health; }

	void setIsEnemyFreezed(bool value) { this->isEnemyFreezed = value; }
	bool getIsEnemyFreezed() { return this->isEnemyFreezed; }

};

