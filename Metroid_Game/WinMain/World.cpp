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
	gateRight = new Gate(spriteHandler, this, grid);
	gateLeft = new Gate(spriteHandler, this, grid);
	gateBlock = new GateBlock(spriteHandler, this, grid);
	samus = new Samus(spriteHandler, this, grid);
	grid->addFollowing(samus);
	maruMari = new MaruMari(spriteHandler, this, grid);
	//skree = new Skree(spriteHandler, this, SKREE);
	explode = new ExplodeEffect(spriteHandler, this, grid);
	bomb = new Bomb(spriteHandler, this);
	itemBomb = new ItemBomb(spriteHandler, this, grid);

	// zoomer yellow
	for (int i = 0; i < zoomerYellow.size(); i++)
	{
		//zoomerYellow[i] = new Zoomer(spriteHandler, this, ZOOMER_YELLOW);
		//zoomerYellow[i]->setActive(false);
	}

	// zoomer pink
	for (int i = 0; i < zoomerPink.size(); i++)
	{
		//zoomerPink[i] = new Zoomer(spriteHandler, this, ZOOMER_PINK);
		//zoomerPink[i]->setActive(false);
	}
}

World::~World()
{
	delete(samus);
	delete(maruMari);
	delete(gateRight);
	delete(gateLeft);
	delete(gateBlock);
	delete(grid);
	delete(metroid);
	//delete(skree);
	delete(explode);
	delete(bomb);
	delete(itemBomb);
}

void World::Update(float t)
{
	grid->Update(t);

	//zoomer yellow
	for (int i = 0; i < zoomerYellow.size(); i++)
	{
		//zoomerYellow[i]->Update(t);
	}

	// zoomer pink
	for (int i = 0; i < zoomerPink.size(); i++)
	{
		//zoomerPink[i]->Update(t);
	}
}

void World::Render()
{
	grid->Render();

	//zoomer yellow
	for (int i = 0; i < zoomerYellow.size(); i++)
	{
		//zoomerYellow[i]->Render();
	}

	//zoomer pink
	for (int i = 0; i < zoomerPink.size(); i++)
	{
		//zoomerPink[i]->Render();
	}
}

void World::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	Texture * textureSamus = new Texture();
	LPDIRECT3DTEXTURE9 samus_texture = textureSamus->loadTexture(d3ddv, TEXTURE_GAME_CHARACTERS);
	if (samus_texture == NULL)
		trace(L"Unable to load Samus Texture");
	samus->InitSprites(d3ddv, samus_texture);

	Texture * textureMaru = new Texture();
	LPDIRECT3DTEXTURE9 maru_texture = textureMaru->loadTexture(d3ddv, ITEM_SPRITE_PATH);
	if (maru_texture == NULL)
		trace(L"Unable to load Maru Mari Texture");
	maruMari->InitSprites(d3ddv, maru_texture);

	Texture * textureGate = new Texture();
	LPDIRECT3DTEXTURE9 gate_texture = textureGate->loadTexture(d3ddv, GATE_SPRITES_PATH);
	if (gate_texture == NULL)
		trace(L"Unable to load Gate Texture");
	gateRight->InitSprites(d3ddv, gate_texture, RIGHT);
	gateLeft->InitSprites(d3ddv, gate_texture, LEFT);
	gateBlock->InitSprites(d3ddv, gate_texture);

	Texture * textureExplode = new Texture();
	LPDIRECT3DTEXTURE9 explode_texture = textureExplode->loadTexture(d3ddv, EFFECT_SPRITE_PATH);
	if (explode_texture == NULL)
		trace(L"Unable to load Explode Texture");
	explode->InitSprites(d3ddv, explode_texture);

	Texture * textureItemBomb = new Texture();
	LPDIRECT3DTEXTURE9 itemBomb_texture = textureItemBomb->loadTexture(d3ddv, ITEM_SPRITE_PATH);
	if (itemBomb_texture == NULL)
		trace(L"Unable to load item Bomb Texture");
	itemBomb->InitSprites(d3ddv, itemBomb_texture);

	Texture * textureBomb = new Texture();
	LPDIRECT3DTEXTURE9 bomb_texture = textureBomb->loadTexture(d3ddv, BOMB_TEXTURE);
	if (bomb_texture == NULL)
		trace(L"Unable to load Bomb Texture");
	bomb->InitSprites(d3ddv, bomb_texture);

	Texture * textureZoomer = new Texture();
	LPDIRECT3DTEXTURE9 zoomer_texture = textureZoomer->loadTexture(d3ddv, ENEMY_SPRITE_PATH);
	if (zoomer_texture == NULL)
		trace(L"Unable to load Zoomer Enemy Texture");
	// zoomer yellow
	for (int i = 0; i < zoomerYellow.size(); i++)
	{
		//zoomerYellow[i]->InitSprites(d3ddv, zoomer_texture);
	}

	// zoomer pink
	for (int i = 0; i < zoomerPink.size(); i++)
	{
		//zoomerPink[i]->InitSprites(d3ddv, zoomer_texture);
	}
}
