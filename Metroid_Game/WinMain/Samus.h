#pragma once
#ifndef _SAMUS_H
#define _SAMUS_H_
#include "Sprite.h"
#include "GameObject.h"
#include "trace.h"
#include "World.h"

enum SAMUS_STATE {
	STAND_LEFT,
	STAND_RIGHT,
	RUNNING_LEFT,
	RUNNING_RIGHT,
	STAND_SHOOT_UP_LEFT,
	STAND_SHOOT_UP_RIGHT,
	MORPH_LEFT,
	MORPH_RIGHT,
	RUN_SHOOTING_LEFT,
	RUN_SHOOTING_RIGHT,
	RUN_SHOOT_UP_LEFT,
	RUN_SHOOT_UP_RIGHT,
	JUMP_LEFT,
	JUMP_RIGHT,
	TRANSFORM_BALL_LEFT,
	TRANSFORM_BALL_RIGHT,
	JUMP_SHOOT_UP_LEFT,
	JUMP_SHOOT_UP_RIGHT,
};

class Samus : public GameObject
{
protected:
	Sprite * standRight;
	Sprite * standLeft;
	Sprite * runRight;
	Sprite * runLeft;
	Sprite * standShootL;
	Sprite * standShootR;
	Sprite * morphLeft;
	Sprite * morphRight;
	Sprite * runShootL;
	Sprite * runShootR;
	Sprite * runShootUpL;
	Sprite * runShootUpR;
	Sprite * jumpLeft;
	Sprite * jumpRight;
	Sprite * ballLeft;
	Sprite * ballRight;
	Sprite * jumpShootL;
	Sprite * jumpShootR;

	SAMUS_STATE state;	

	int tempX;
public:
	bool isJumping;	// Trạng thái đang nhảy của Samus
	Samus();
	Samus(LPD3DXSPRITE spriteHandler, World * manager);
	~Samus();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void InitPostition();

	SAMUS_STATE GetState();
	void SetState(SAMUS_STATE value);
	bool isSamusJumping();

	void ResetAllSprites();
	bool GetStateActive();

	//================ OVERRIDE VIRTUAL METHOD ==================
	void Reset(int  x, int y);
	void Update(float t);
	void Render();
	void Destroy();
	//================= END OVERRIDE VIRTUAL METHOD =============

};
#endif // !_SAMUS_H


