#pragma once
#ifndef _SAMUS_H
#define _SAMUS_H_
#include "Sprite.h"
#include "GameObject.h"
#include "trace.h"
#include "World.h"


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
	bool isBall;
public:
	bool isJumping;	// Trạng thái đang nhảy của Samus
	bool canMorph = true;
	bool isMorphing = false;

	float health;	// Máu của Samus
	bool isDeath = false;	// Trạng thái chết của Samus
	Samus();
	Samus(LPD3DXSPRITE spriteHandler, World * manager, Grid * grid);
	~Samus();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void InitPostition();

	SAMUS_STATE GetState();
	void SetState(SAMUS_STATE value);
	bool isSamusJumping();
	//bool isSamusCrouch();
	bool isSamusDeath();

	void ResetAllSprites();
	bool GetStateActive();

	void setIsBall(bool isBall);
	bool getIsBall();

	//================ OVERRIDE VIRTUAL METHOD ==================
	void Reset(float  x, float y);
	void Update(float t);
	void Render();
	void Destroy();
	//================= END OVERRIDE VIRTUAL METHOD =============

};
#endif // !_SAMUS_H


