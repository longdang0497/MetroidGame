#include  "Item.h"
#include "World.h"

Item::Item(LPD3DXSPRITE sprietHandler, World * manager)
{
	this->type = ITEM;
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->time_survive = ITEM_TIME_SURVIVE;

	vx = 0;
	vy = 0;
}

Item::~Item()
{
	delete(itemSprite);
}

int Item::getNumberGain()
{
	return number_gain;
}

void Item::setNumberGain(int num)
{
	number_gain = num;
}

void Item::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
}

void Item::Init(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->isActive = true;
	time_survive = ITEM_TIME_SURVIVE;
}



void Item::Update(int t)
{
	if (!isActive)
		return;

	pos_x += vx * t;
	pos_y += vy * t;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		itemSprite->updateSprite();
		last_time = now;
	}

	// Tính thời gian hiển thị
	time_survive -= t;

	// Nếu hết thời gian thì không hiển thị nữa
	if (time_survive <= 0)
	{
		isActive = false;
	}
}

void Item::Render()
{
}
