#pragma once
#include "GameObject.h"
#include "Define.h"


class BulletKraid : public GameObject
{
private:
	float startX;
	float endX;
	float posX_Kraid;
	float posY_Kraid;
	Sprite* spriteLeft;
	Sprite* spriteRight;
	bool isRendered;

	bool isLeft;
	bool isRight;
	bool isTop;
	bool isBottom;
	BULLET_KRAID_STATE state;

	DWORD timeFreezed;
public:
	BulletKraid();
	BulletKraid(LPD3DXSPRITE spriteHandler, World* manager);
	~BulletKraid();

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
	void setPosXKraid(float x);
	float getPosXKraid();
	void setPosYKraid(float y);
	float getPosYKraid();

	void setTimeFreezed(DWORD time) { this->timeFreezed = time; }
	DWORD getTimeFreezed() { return this->timeFreezed; }
};