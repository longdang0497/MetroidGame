#pragma once
#include "GameObject.h"
#include "Define.h"


class KraidBoomerang : public GameObject
{
private:
	float posX_Kraid;
	float posY_Kraid;
	Sprite* sprite;
	bool isRendered;

	bool isLeft;
	bool isRight;
	bool isTop;
	bool isBottom;
	BULLET_KRAID_STATE state;

	DWORD timeFreezed;
	DWORD timeStartActive;
	bool isFall;
public:
	KraidBoomerang();
	KraidBoomerang(LPD3DXSPRITE spriteHandler, World* manager);
	~KraidBoomerang();

	void initBullet(float posX, float posY);
	void Update(float t);
	void Update(float t, float posX, float posY);
	void Render();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Reset(float posX, float posY);

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

	void setTimeStartActive(DWORD time) { this->timeStartActive = time; }
	DWORD getTimeStartActive() { return this->timeStartActive; }

	void setIsFall(bool value) { this->isFall = value; }
	bool getIsFall() { return this->isFall; }
};