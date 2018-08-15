#pragma once
#include "GameObject.h"
#include "Define.h"

class Ridley : public GameObject
{
private:
	RIDLEY_STATE state;
	bool isLeft;
	bool isRight;
	bool isBottom;
	bool isTop;

	bool isFlyingUp;

	Sprite * sitLeft;
	Sprite* sitRight;
	Sprite *flyLeft;
	Sprite* flyRight;
	DWORD timePush; // thoi gian push luc y cho Ridley bay len
	bool timeIsSet;

	bool isDeath;
	int health;
public:
	Ridley(LPD3DXSPRITE spriteHandler, World * manager);
	Ridley();
	~Ridley();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Init(float x, float y);
	//============= OVERRIDE VIRTUAL METHOD ==================
	void Update(float t);
	void Render();
	//============= END OVERRIDE VIRTUAL METHOD ==============
	void Destroy(float x, float y);

	void setRidleyState(RIDLEY_STATE value);
	RIDLEY_STATE getRidleyState();

	void setIsLeftCollided(bool isLeft);
	bool getIsLeftCollided();
	void setIsRightCollided(bool isRight);
	bool getIsRightCollided();
	void setIsTopCollided(bool isTop);
	bool getIsTopCollided();
	void setIsBottomCollided(bool isBottom);
	bool getIsBottomCollided();
	void setTimePush(DWORD timePush) { this->timePush = timePush; }
	DWORD getTimePush() { return this->timePush; }
	void setIsFlyingUp(bool isFlyingUp) { this->isFlyingUp = isFlyingUp; }
	bool getIsFlyingUp() { return this->isFlyingUp; }
	void setTimeIsSet(bool value) { this->timeIsSet = value; }
	bool getTimeIsSet() { return this->timeIsSet; }
	void setIsDeath(bool value) { this->isDeath = value; }
	bool getIsDeath() { return this->isDeath; }
	void setHealth(int health) { this->health = health; }
	int getHealth() { return this->health; }
};

