#pragma once
#include "Sprite.h"
#include "GameObject.h"
#include "trace.h"
#include "World.h"
#include <vector>

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

	bool isInRoom1 = true;
	bool isInRoom2 = false;
	bool isInBoss1 = false;
	bool isInBoss2 = false;

	int tempX;
	bool isBall;

	float startPosJump;
	float endPosJump;
private:
	vector<string> stringMapSamus;
	bool isChangingRoom;
	float posX_StartChangingRoom;
	float posX_EndChangingRoom;
public:
	bool isJumping;	// Trạng thái đang nhảy của Samus
	bool canMorph = true;
	bool isMorphing = false;

	bool isOnGround = false;
	bool isTop = false;
	bool isBottom = false;
	bool isLeft = false;
	bool isRight = false;
	bool isColisionHandled = false;

	float health;	// Máu của Samus
	bool isDeath = false;	// Trạng thái chết của Samus
	Samus();
	Samus(LPD3DXSPRITE spriteHandler, World * manager, Grid* grid);
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

	void setStartPosJump(float posY) { this->startPosJump = posY; }
	float getStartPosJump() { return this->startPosJump; }
	void setEndPosJump(float currentPosY) { this->endPosJump = currentPosY; }
	float getEndPosJump() { return this->endPosJump; }

	void setDimension();
	void setStringMap(vector<string> stringMap) { this->stringMapSamus = stringMap; }
	vector<string> getStringMap() { return this->stringMapSamus; }

	void setIsChangingRoom(bool value) { this->isChangingRoom = value; }
	bool getIsChangingRoom() { return this->isChangingRoom; }

	void setPosX_StartChangingRoom(float value) { this->posX_StartChangingRoom = value; }
	float getPosX_StartChangingRoom() { return this->posX_StartChangingRoom; }
	void  setPosX_EndChangingRoom(float value) { this->posX_EndChangingRoom = value; }
	float getPosX_EndChangingRoom() { return this->posX_EndChangingRoom; }
};


