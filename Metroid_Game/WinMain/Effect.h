#pragma once
#include "GameObject.h"
#include "Define.h"

class Effect :	public GameObject
{
protected:
	float time_survive;
public:
	Effect(LPD3DXSPRITE spriteHandler, World *manager, Grid* grid);
	~Effect();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void Init(int pos_x, int pos_y);

	virtual void Update(const float Deltatime);
	virtual void Render();

	// create new effect
	//static Effect* CreateEffect(EFFECT_TYPE effectType, int pos_x, int pos_y, int heso, LPD3DXSPRITE spriteHandler, World *_manager);
};

