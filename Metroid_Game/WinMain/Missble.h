#pragma once
#include "GameObject.h"
#include "Define.h"


class Missible : public GameObject
{
private:
	float startX;
	float endX;
	float startY;
	float endY;
	Sprite* spriteUp;
	Sprite* spriteRight;
	Sprite* spriteLeft;
	bool isRendered;

	bool isLeft;
	bool isRight;
	bool isTop;
	MISSIBLE_STATE state;

	DWORD timeFreezed;
public:
	Missible();
	Missible(LPD3DXSPRITE spriteHandler, World* manager);
	~Missible();

	void initBullet(float posX, float posY);
	void Update(float t);
	void Update(float t, float posX, float posY);
	void Render();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Reset(float posX, float posY);
	void setDimension();
	void setStartX(float x);
	float getStartX();
	void setEndX(float x);
	float getEndX();
	void setStartY(float y);
	float getStartY();
	void setEndY(float y);
	float getEndY();
	void setIsLeft(bool isLeft);
	bool getIsLeft();
	void setIsRight(bool isRight);
	bool getIsRight();
	void setIsTop(bool isTop);
	bool getIsTop();
	void setIsRenderd(bool isRendered);
	bool getIsRendered();

	void setState(MISSIBLE_STATE state);
	MISSIBLE_STATE getState();
};