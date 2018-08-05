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
{}

void Item::Update(int t)
{
	if (!isActive)
		return;

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
