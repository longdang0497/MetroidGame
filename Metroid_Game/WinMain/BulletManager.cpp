#include "BulletManager.h"

Manager::Manager(LPD3DXSPRITE spriteHandler)
{
	this->spriteHandler = spriteHandler;
}

Manager::~Manager()
{
	if (m_d3ddv) 
	{ 
		m_d3ddv = nullptr; 
		delete m_d3ddv; 
	}
}

void Manager::_CreateBullets(float X, float Y, float VX, float VY)
{
	if (isActive == true)
	{
		weapon.push_back(new Bullet(this->spriteHandler, X, Y, VX, VY));
	}	
}

void Manager::Update(float delta)
{
	for (int i = 0; i < weapon.size(); i++)
	{
		weapon[i]->Update(delta);
	}
}

void Manager::Render()
{
	for (int i = 0; i < weapon.size(); i++)
	{
		weapon[i]->Render();
	}
}