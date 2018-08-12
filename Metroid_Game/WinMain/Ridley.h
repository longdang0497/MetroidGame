#pragma once
#include "GameObject.h"
#include "Define.h"
#include "World.h"

#define RIDLEY_ANIMATE_RATE 2

class Ridley : public GameObject
{
private:
	bool isLeftCollided;
	bool isRightCollided;
	bool isTopCollided;
	bool isBottomCollided;
protected:
	//LPDIRECT3DTEXTURE9 textureRidley;
	RIDLEY_STATE state;
	World * manager;
	Sprite * sit_left;
	Sprite * sit_right;
	Sprite * fly_left;
	Sprite * fly_right;
	float time_push; //thời gian push lực y cho Ridley bay lên
public:
	Ridley(LPD3DXSPRITE spriteHandler, World * manager);
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
};