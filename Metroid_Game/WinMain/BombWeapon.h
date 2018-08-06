#pragma once
#include "Define.h"
#include "GameObject.h"

class BombWeapon : public GameObject
{
private:
	Sprite * bomb;
	float time_survive = 0;
	bool isExplode = true;

public:
	BombWeapon();
	BombWeapon(LPD3DXSPRITE spriteHandler, World * manager);
	~BombWeapon();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void CreateBomb(float posX, float posY);
	void Update(float t);
	void Render();
	void Destroy();
	void ResetBomb(float x, float y);
	float getTimeSurvive() { return time_survive; };
	void setBombExplode(bool value) { isExplode = value; };
	bool getBombExplode() { return isExplode; };
	void setTimeSurvive(float time) { time_survive = time; };
};

