#pragma once
#include "GameObject.h"
#include "Define.h"

class BulletSkree : public GameObject
{
private:
	float startX;
	float startY;
	float endX;
	float endY;
	float posX_Skree;
	float posY_Skree;
	Sprite* sprite;
	bool isRendered;

	bool isLeft;
	bool isRight;
	bool isTop;
	bool isBottom;
	Bullet_Skree_Direction direction;
public:
	BulletSkree();
	BulletSkree(LPD3DXSPRITE spriteHandler, World* manager, Bullet_Skree_Direction direction);
	~BulletSkree();

	void initBullet(float posX, float posY);
	void Update(float t);
	void Update(float t, float posX, float posY);
	void Render();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Reset(float posX, float posY);

	void setStartX(float x);
	float getStartX();
	void setStartY(float y);
	float getStartY();
	void setEndX(float x);
	float getEndX();
	void setEndY(float y);
	float getEndY();
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
	void setPosXSkree(float x);
	float getPosXSkree();
	void setPosYSkree(float y);
	float getPosYSkree();
};

