#pragma once
#include "GameObject.h"
#include "Define.h"
#include <time.h>

class BulletRidley:public GameObject
{
private:
	float startX;
	float endX;
	float posX_Ridley;
	float posY_Ridley;
	Sprite* sprite;
	bool isRendered;

	bool isLeft;
	bool isRight;
	bool isTop;
	bool isBottom;
	bool isFall;
	BULLET_RIDLEY_STATE state;

	DWORD timeFreezed;

	float range;
public:
	BulletRidley();
	BulletRidley(LPD3DXSPRITE spriteHandler, World* manager);
	~BulletRidley();

	void initBullet(float posX, float posY);
	void Update(float t);
	void Update(float t, float posX, float posY);
	void Render();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Reset(float posX, float posY);

	void setStartX(float x);
	float getStartX();
	void setEndX(float x);
	float getEndX();
	void setIsLeft(bool isLeft);
	bool getIsLeft();
	void setIsRight(bool isRight);
	bool getIsRight();
	void setIsTop(bool isTop);
	bool getIsTop();
	void setIsBottom(bool isBottom);
	bool getIsBottom();
	void setIsRenderd(bool isRendered);
	bool getIsRendered();
	void setPosXRidley(float x);
	float getPosXRidley();
	void setPosYRidley(float y);
	float getPosYRidley();

	void setTimeFreezed(DWORD time) { this->timeFreezed = time; }
	DWORD getTimeFreezed() { return this->timeFreezed; }

	void setRange(float value) { this->range = value; }
	float getRange() { return this->range; }

	void setIsFall(bool value) { this->isFall = value; }
	bool getIsFall() { return this->isFall; }
};

