#pragma once
#include "Enemy.h"
#include "Define.h"

class Skree : public Enemy
{
protected:
	Sprite * skree;
	
	int animate_rate;	// cần biến này vì khi dí theo Samus animate rate thay đổi
public:
	Skree();
	Skree(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type);
	~Skree();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	//============== OVERRIDE VIRTUAL METHOD ===================
	virtual void Update(float t);
	virtual void Render();
	//============== END OVERRIDE VIRTUAL METHOD ===============
	void Destroy();
};