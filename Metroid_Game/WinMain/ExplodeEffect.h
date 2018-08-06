#pragma once
#include "Effect.h"
#include "Define.h"

class ExplodeEffect : public Effect
{
private:
	Sprite * explode;
	float time_survive = 0;
public:
	ExplodeEffect();
	ExplodeEffect(LPD3DXSPRITE spriteHandler, World *manager, Grid * grid);
	~ExplodeEffect();

	float getTimeSurvive() { return time_survive; };
	void setTimeSurvive(float value) { time_survive = value; };
	void CreateExplode(float x, float y);
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Update(float t);
	void Render();
};

