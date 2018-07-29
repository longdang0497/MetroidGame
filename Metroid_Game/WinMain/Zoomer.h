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
	Zoomer(LPD3DXSPRITE spriteHandler, World * manager);
	~Zoomer();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	//============== OVERRIDE VIRTUAL METHOD ===================
	virtual void Update(float t);
	virtual void Render();
	//============== END OVERRIDE VIRTUAL METHOD ===============
	void Destroy();
};
