#pragma once
#include "GameObject.h"
#include "Define.h"

class Kraid : public GameObject
{
private:
	Sprite * left;
	Sprite* right;
	KraidState state;
	bool isDeath;
	int health;

	bool isLeft;
	bool isTop;
	bool isRight;
	bool isBottom;
public:
	Kraid();
	Kraid(LPD3DXSPRITE spriteHandler, World * manager);
	~Kraid();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void InitPostition();
	void Update(float t);
	void Render();
	void Destroy(float x, float y);

	void setState(KraidState state);
	KraidState getState();
	void setIsDeath(bool value);
	bool getIsDeath();
	void setHealth(int health);
	int getHealth();

	void setIsTop(bool isTop);
	bool getIsTop();
	void setIsBottom(bool isBottom);
	bool getIsBottom();
	void setIsRight(bool isRight);
	bool getIsRight();
	void setIsLeft(bool isLeft);
	bool getIsLeft();
};

