#include "World.h"
#include <vector>

using namespace std;

World::World()
{
}

World::World(LPD3DXSPRITE spriteHandler, Metroid * metroid)
{
	//Gán
	this->spriteHandler = spriteHandler;
	this->metroid = metroid;

	//Khởi tạo các đối tượng trong World
	samus = new Samus(spriteHandler, this);
}

World::~World()
{
	//delete(samus);
}

void World::Update(float t)
{
	samus->Update(t);
}

void World::Render()
{
	samus->Render();
}

void World::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	samus->InitSprites(d3ddv, texture);
}
