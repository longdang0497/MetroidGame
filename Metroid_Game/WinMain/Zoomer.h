#pragma once
#include "Enemy.h"
#include "Define.h"

enum ZOOMER_STATE
{
	ON_ZOOMER_UP,
	ON_ZOOMER_BOTTOM,
	ON_ZOOMER_LEFT,
	ON_ZOOMER_RIGHT,
};

class Zoomer : public Enemy
{
protected:
	ZOOMER_STATE state;
	Sprite * top;
	Sprite * bottom;
	Sprite * left;
	Sprite * right;
public:
	Zoomer();
	Zoomer(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type);
	~Zoomer();
	virtual void InitSprites(LPDIRECT3DDEVICE9 d3ddv);


	void setState(ZOOMER_STATE _state);
	ZOOMER_STATE getState();



	//============== OVERRIDE VIRTUAL METHOD ===================
	virtual void Update(float t);
	virtual void Render();
	virtual void setEnemyStatefromString(string _state);
	virtual void startMoving();
	//============== END OVERRIDE VIRTUAL METHOD ===============
	void Destroy();
};
