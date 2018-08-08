#pragma once
#include "Effect.h"
#include "Define.h"

class ExplodeEffect : public Effect
{
private:
	Sprite * explode;
	float time_survive = 0;

	bool isLeft;
	bool isTop;
	bool isBottom;
	bool isRight;
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

	void setIsLeft(bool isLeft) { this->isLeft = isLeft; }
	bool getIsLeft() { return this->isLeft; }
	void setIsRight(bool isRight) { this->isRight = isRight; }
	bool getIsRight() { return this->isRight; }
	void setIsTop(bool isTop) { this->isTop = isTop; }
	bool getIsTop() { return this->isTop; }
	void setIsBottom(bool isBottom) { this->isBottom = isBottom; }
	bool getIsBottom() { return this->isBottom; }
};

