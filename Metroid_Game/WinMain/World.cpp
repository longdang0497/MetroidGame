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
	//bulletManager = new Manager(spriteHandler);
	//Khởi tạo các đối tượng trong World
	samus = new Samus(spriteHandler, this);

	// zoomer yellow
	for (int i = 0; i < zoomerYellow.size(); i++)
	{
		zoomerYellow[i] = new Zoomer(spriteHandler, this, ZOOMER_YELLOW);
		zoomerYellow[i]->setActive(false);
	}

	// zoomer pink
	for (int i = 0; i < zoomerPink.size(); i++)
	{
		zoomerPink[i] = new Zoomer(spriteHandler, this, ZOOMER_PINK);
		zoomerPink[i]->setActive(false);
	}
}

World::~World()
{
	//delete(samus);
}

void World::Update(float t)
{
	samus->Update(t);
	//bulletManager->Update(t);
	// zoomer yellow
	for (int i = 0; i < zoomerYellow.size(); i++)
	{
		zoomerYellow[i]->Update(t);
	}

	// zoomer pink
	for (int i = 0; i < zoomerPink.size(); i++)
	{
		zoomerPink[i]->Update(t);
	}
}

void World::Render()
{
	samus->Render();
	//bulletManager->Render();
	// zoomer yellow
	for (int i = 0; i < zoomerYellow.size(); i++)
	{
		zoomerYellow[i]->Render();
	}

	// zoomer pink
	for (int i = 0; i < zoomerPink.size(); i++)
	{
		zoomerPink[i]->Render();
	}
}

void World::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	samus->InitSprites(d3ddv, texture);
	// zoomer yellow
	for (int i = 0; i < zoomerYellow.size(); i++)
	{
		zoomerYellow[i]->InitSprites(texture);
	}

	// zoomer pink
	for (int i = 0; i < zoomerPink.size(); i++)
	{
		zoomerPink[i]->InitSprites(texture);
	}
}
