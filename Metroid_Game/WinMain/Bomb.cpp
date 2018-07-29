#include "Bomb.h"

ItemBomb::ItemBomb(LPD3DXSPRITE spriteHandler, World * manager, Grid * grid) :Item(spriteHandler, manager, grid)
{
	itemBomb = nullptr;
	currentSprite = nullptr;

	isActive = false;
	this->grid = grid;
	this->manager = manager;

	this->type = BOMB_ITEM;
	this->previousUnit = NULL;
	this->nextUnit = NULL;
}

ItemBomb::~ItemBomb()
{
	currentSprite = nullptr; delete (currentSprite);
	delete(itemBomb);
}

void ItemBomb::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;
	itemBomb = new Sprite(spriteHandler, texture, ITEM_BOMB_PATH, ITEM_BOMB_WIDTH, ITEM_BOMB_HEIGHT, 1);
}

void ItemBomb::Init(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->isActive = true;
	time_survive = ITEM_TIME_SURVIVE;
	currentSprite = itemBomb;
}

void ItemBomb::Update(float t)
{
	// Tính thời gian hiển thị
	time_survive -= t;
	// Nếu hết thời gian thì không hiển thị nữa
	if (time_survive <= 0)
	{
		isActive = false;
	}
}

void ItemBomb::Render()
{
	if (isActive == true)
	{
		D3DXVECTOR3 position;
		position.x = pos_x;
		position.y = pos_y;
		position.z = 0;

		if (!isActive)
			return;

		currentSprite->drawSprite(currentSprite->getWidth(), currentSprite->getHeight(), position);
	}
}

void ItemBomb::Destroy()
{
	isActive = false;
}
