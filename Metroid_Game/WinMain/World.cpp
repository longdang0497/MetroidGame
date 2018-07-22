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
	grid = new Grid();
	samus = new Samus(spriteHandler, this, grid);
	this->samusBullet = new Bullet(spriteHandler);

	grid->addFollowing(samus);
	maruMari = new MaruMari(spriteHandler, this, grid);
	//grid->add(maruMari);

	//// zoomer yellow
	//for (int i = 0; i < zoomerYellow.size(); i++)
	//{
	//	zoomerYellow[i] = new Zoomer(spriteHandler, this, ZOOMER_YELLOW);
	//	zoomerYellow[i]->setActive(false);
	//}

	//// zoomer pink
	//for (int i = 0; i < zoomerPink.size(); i++)
	//{
	//	zoomerPink[i] = new Zoomer(spriteHandler, this, ZOOMER_PINK);
	//	zoomerPink[i]->setActive(false);
	//}
}

World::~World()
{
	//delete(samus);
}

void World::Update(float t)
{
	grid->Update(t);
	maruMari->Update(t);
	this->samusBullet->Update(t, this->samus->getPosX(), this->samus->getPosY());
	//bulletManager->Update(t);
	// zoomer yellow
	//for (int i = 0; i < zoomerYellow.size(); i++)
	//{
	//	zoomerYellow[i]->Update(t);
	//}

	//// zoomer pink
	//for (int i = 0; i < zoomerPink.size(); i++)
	//{
	//	zoomerPink[i]->Update(t);
	//}
}

void World::Render()
{
	grid->Render();
	maruMari->Render();
	this->samusBullet->Render();
	//bulletManager->Render();
	// zoomer yellow
	//for (int i = 0; i < zoomerYellow.size(); i++)
	//{
	//	zoomerYellow[i]->Render();
	//}

	//// zoomer pink
	//for (int i = 0; i < zoomerPink.size(); i++)
	//{
	//	zoomerPink[i]->Render();
	//}
}

void World::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	Texture * texture = new Texture();
	LPDIRECT3DTEXTURE9 samus_texture = texture->loadTexture(d3ddv, TEXTURE_GAME_CHARACTERS);
	if (samus_texture == NULL)
		trace(L"Unable to load PlayerTexture");
	samus->InitSprites(d3ddv, samus_texture);

	Texture * texture1 = new Texture();
	LPDIRECT3DTEXTURE9 maru_texture = texture1->loadTexture(d3ddv, ITEM_SPRITE_PATH);
	if (maru_texture == NULL)
		trace(L"Unable to load PlayerTexture");
	maruMari->InitSprites(d3ddv, maru_texture);

	// Bullet Texture
	Texture texture2;
	LPDIRECT3DTEXTURE9 bulletTexture = texture2.loadTexture(d3ddv, SAMUS_BULLET_PATH);
	if (bulletTexture == NULL)
		trace(L"Unable to load BulletTexture");
	this->samusBullet->InitSprites(d3ddv, bulletTexture);

	//Texture * texture2 = new Texture();
	//LPDIRECT3DTEXTURE9 zoomer_texture = texture2->loadTexture(d3ddv, ENEMY_SPRITE_PATH);
	//if (zoomer_texture == NULL)
	//	trace(L"Unable to load PlayerTexture");
	//// zoomer yellow
	//for (int i = 0; i < zoomerYellow.size(); i++)
	//{
	//	zoomerYellow[i]->InitSprites(zoomer_texture);
	//}

	//// zoomer pink
	//for (int i = 0; i < zoomerPink.size(); i++)
	//{
	//	zoomerPink[i]->InitSprites(zoomer_texture);
	//}
}
