#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Texture.h"

enum BulletDirection
{
	SHOOT_UP,
	SHOOT_LEFT,
	SHOOT_RIGHT
};

class Bullet : public GameObject
{
private:
	LPDIRECT3DDEVICE9 m_d3ddv;
	Sprite *bullet;
	Texture *texture;
	BulletDirection bulletdir;
	bool isRender;
	LPDIRECT3DTEXTURE9 bulletTexture;
public:
	Bullet(LPD3DXSPRITE spriteHandler, float X = 0, float Y = 0, float VX = 0, float VY = 0);
	~Bullet();

	void SetState(BulletDirection value);
	BulletDirection GetState();

	virtual void Render();
	void CreateBullet();
	void Update(float Delta);
	bool isRendering();
};