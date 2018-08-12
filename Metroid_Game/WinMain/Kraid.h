#pragma once
#include "GameObject.h"
#include "Define.h"
#include "World.h"

#define KRAID_ANIMATE_RATE 2

enum KraidState {
	KRAID_LEFT,
	KRAID_RIGHT
};

class Kraid : public GameObject
{
private:
	bool isLeftCollided;
	bool isRightCollided;
	bool isTopCollided;
	bool isBottomCollided;
protected:
	//LPDIRECT3DTEXTURE9 textureRidley;
	World * manager;
	Sprite * left;
	Sprite * right;
	KraidState state;
public:
	Kraid(LPD3DXSPRITE spriteHandler, World * manager);
	~Kraid();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Init(int x, int y);
	//============= OVERRIDE VIRTUAL METHOD ==================
	void Update(float t);
	void Render();
	//============= END OVERRIDE VIRTUAL METHOD ==============
	void Destroy(float x, float y);

	void setKraidState(KraidState value);
	KraidState getKraidState();

	void setIsLeftCollided(bool isLeft);
	bool getIsLeftCollided();
	void setIsRightCollided(bool isRight);
	bool getIsRightCollided();
	void setIsTopCollided(bool isTop);
	bool getIsTopCollided();
	void setIsBottomCollided(bool isBottom);
	bool getIsBottomCollided();
};