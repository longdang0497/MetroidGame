#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Texture.h"
#include "Metroid.h"

class Bullet : public GameObject
{
private:
	Sprite *bulletSprite;
	Bullet_SAMUS_Direction direction;
	bool isRendered;
	int count;
public:
	void initBullet(float posX, float posY);
	void Update(float t);
	void Update(float t, float posX, float posY);
	void Render();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Reset(float posX, float posY);
	Bullet();
	Bullet(LPD3DXSPRITE spriteHandler);
	~Bullet();
	

	void setDirection(Bullet_SAMUS_Direction direction);
	Bullet_SAMUS_Direction getDirection();
	void setIsRendered(bool isRendered);
	bool getIsRendered();
	void setCount(int count);
	int getCount();
};