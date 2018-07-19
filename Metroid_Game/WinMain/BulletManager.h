#pragma once
#include "bullet.h"
#include <vector>

class Manager
{
private:
	LPDIRECT3DDEVICE9 m_d3ddv;
	LPD3DXSPRITE spriteHandler;
	vector<Bullet*> weapon = vector<Bullet*>(0);
	bool isActive = false;
public:
	Manager(LPD3DXSPRITE spriteHandler);
	~Manager();

	void SetState(bool value) { isActive = value; };
	bool GetState() { return isActive; };

	void _CreateBullets(float X = 0, float Y = 0, float VX = 0, float VY = 0);
	virtual void Update(float delta);
	virtual void Render();
};
