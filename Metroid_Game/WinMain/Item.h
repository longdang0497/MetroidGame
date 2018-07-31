#pragma once
#include "GameObject.h"
class Item : public GameObject
{
protected:
	float time_survive;
	int number_gain;
public:
	Item(LPD3DXSPRITE sprietHandler, World * manager, Grid * grid);
	~Item();
	int getNumberGain();
	void setNumberGain(int num);

	//============= OVERRIDE VIRTUAL METHOD =================
	virtual void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	virtual void Init(float posX, float posY);
	virtual void Update(int t);
	virtual void Render();
	//============= END OVERRIDE VIRTUAL METHOD =============
};

