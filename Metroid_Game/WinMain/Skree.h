#pragma once
#include "Enemy.h"
#include "Define.h"

class Skree : public Enemy
{
private:
	Sprite * skreeSprite;
	SKREE_STATE state;
	int animate_rate;

	bool isLeft;
	bool isRight;
	bool isTop;
	bool isBottom;
	bool isCollisionHandled;

	float samusPosX = 0.0f;
	float samusPosY = 0.0f;
	
	float range;
	float liveTime = 0.0f;
public:
	Skree();
	Skree(LPD3DXSPRITE spriteHandler, World * manager, OBJECT_TYPE enemy_type);
	~Skree();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	//============== OVERRIDE VIRTUAL METHOD ===================
	void Update(float t);
	void Render();
	void setEnemyStatefromString(string _state);
	void startMoving();
	void setSamusLocation(float _posX, float _posY);
	void handleBullet(int bulletType);
	//============== END OVERRIDE VIRTUAL METHOD ===============
	void Destroy();
	void Destroy(float x, float y);


	void reset();

	void setState(SKREE_STATE state);
	SKREE_STATE getState();
	void setIsLeft(bool isLeft);
	bool getIsLeft();
	void setIsRight(bool isRight);
	bool getIsRight();
	void setIsTop(bool isTop);
	bool getIsTop();
	void setIsBottom(bool isBottom);
	bool getIsBottom();
	void setIsCollisionHandled(bool isHandled);
	bool getisCollisionHandled();
	void setSamusPosX(float posX);
	float getSamusPosX();
	void setSamusPosY(float posY);
	float getSamusPosY();
	void setRange(float range);
	float getRange();
	void setLiveTime(float liveTime);
	float getLiveTime();
};

