#include "MaruMari.h"
#include "World.h"

MaruMari::MaruMari(LPD3DXSPRITE spriteHandler, World * manager, Grid * grid) :Item(spriteHandler, manager, grid)
{
	this->type = MARU_MARI;
	maruMari = NULL;
	isActive = true;
	this->spriteHandler = spriteHandler;
	this->manager = manager;

	currentSprite = nullptr;
	this->grid = grid;
	this->previousUnit = NULL;
	this->nextUnit = NULL;
}

MaruMari::~MaruMari()
{
	currentSprite = nullptr; delete (currentSprite);
	delete(maruMari);
}

void MaruMari::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;
	maruMari = new Sprite(spriteHandler, texture, MARU_MARI_PATH, MARU_MARI_WIDTH, MARU_MARI_HEIGHT, MARU_MARI_COUNT);
}

void MaruMari::Init(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->isActive = true;
	time_survive = ITEM_TIME_SURVIVE;
	currentSprite = maruMari;
}

void MaruMari::Update(float t)
{
	float newPosX = pos_x + vx * t;
	float newPosY = pos_y + vy * t;
	//vy += gravity;
	if (!this->grid->updateGrid(this, newPosX, newPosY)) {
		pos_x = newPosX;
		pos_y = newPosY;
	}
}

void MaruMari::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	if (!isActive)
		return;

	currentSprite->drawSprite(currentSprite->getWidth(), currentSprite->getHeight(), position);
}

void MaruMari::Destroy()
{
	isActive = false;
}


