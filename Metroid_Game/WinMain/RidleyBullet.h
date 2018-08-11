#pragma once
#include "GameObject.h"
#include "Define.h"

class RidleyBullet : public GameObject
{
private:
	Sprite * ridleyBullet;
	//Bullet_SAMUS_Direction direction;
	//Bullet_SAMUS_Direction tempDirection;
	bool isRendered;
	int count;
	float startX;
	float startY;
	float endX;
	float endY;

	bool isLeft;
	bool isTop;
	bool isBottom;
	bool isRight;
	bool isHandled;
public:
	void initBullet(float posX, float posY);
	void Update(float t);
	void Update(float t, float posX, float posY);
	void Render();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Reset();
	RidleyBullet();
	RidleyBullet(LPD3DXSPRITE spriteHandler, Grid* grid);
	~RidleyBullet();

	//void setDirection(Bullet_SAMUS_Direction direction);
	//Bullet_SAMUS_Direction getDirection();
	void setIsRendered(bool isRendered);
	bool getIsRendered();
	void setCount(int count);
	int getCount();

	void setIsLeft(bool isLeft) { this->isLeft = isLeft; }
	bool getIsLeft() { return this->isLeft; }
	void setIsRight(bool isRight) { this->isRight = isRight; }
	bool getIsRight() { return this->isRight; }
	void setIsTop(bool isTop) { this->isTop = isTop; }
	bool getIsTop() { return this->isTop; }
	void setIsBottom(bool isBottom) { this->isBottom = isBottom; }
	bool getIsBottom() { return this->isBottom; }
	void setIsHandled(bool isHandled) { this->isHandled = isHandled; }
	bool getIsHandled() { return this->isHandled; }
};