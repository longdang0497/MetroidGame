#pragma once
#include "Define.h"
#include "GameObject.h"
#include "World.h"

class Bomb : public GameObject
{
private:
	Sprite * bomb;
	int countBomb = 1;
	float time_survive = 0;
	bool isExplode = false;
public:
	Bomb();
	Bomb(LPD3DXSPRITE spriteHandler, World * manager);
	~Bomb();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void CreateBomb(float posX, float posY);
	void Update(float t);
	void Render();
	void Destroy();
	void ResetBomb(float x, float y);
	void setBombNo(int value);
	void ResetBombNo(int value);
	float getTimeSurvive() { return time_survive; };
	void setBombExplode(bool value) { isExplode = value; };
	bool getBombExplode() { return isExplode; };
	void setTimeSurvive(float time) { time_survive = time; };
};