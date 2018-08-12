#include "Kraid.h"

Kraid::Kraid(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->type = KRAID;
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->isActive = true;

	this->width = WIDTH_KRAID;
	this->height = HEIGHT_KRAID;

	setKraidState(KRAID_LEFT);
	//health = HEALTH_RIDLEY;

	vx = 1.0f;
	vy = 0.0f;
	vx_last = -1.0f;
}

Kraid::~Kraid()
{
	delete(left);
	delete(right);
}

void Kraid::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	if (texture == NULL)
		trace(L"Unable to load Kraid Texture");

	left = new Sprite(spriteHandler, texture, KRAID_LEFT_PATH, WIDTH_KRAID, HEIGHT_KRAID, KRAID_COUNT);
	right = new Sprite(spriteHandler, texture, KRAID_RIGHT_PATH, WIDTH_KRAID, HEIGHT_KRAID, KRAID_COUNT);
}

void Kraid::Init(int x, int y)
{
	this->pos_x = x;
	this->pos_y = y;
}

void Kraid::Update(float t)
{
	if (!isActive) return;

	pos_x += vx * t;
	pos_y += vy * t;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / KRAID_ANIMATE_RATE)
	{
		switch (this->state)
		{
		case KRAID_LEFT:
			left->updateSprite();
			break;
		case KRAID_RIGHT:
			right->updateSprite();
			break;
		}		
		last_time = now;
	}
}

void Kraid::Render()
{
	if (!isActive)
		return;

	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	switch (this->state)
	{
	case KRAID_LEFT:
		left->drawSprite(left->getWidth(), left->getHeight(), position);
		break;
	case KRAID_RIGHT:
		right->drawSprite(right->getWidth(), right->getHeight(), position);
		break;
	}
}

void Kraid::Destroy(float x, float y)
{
	this->isActive = false;
}

void Kraid::setKraidState(KraidState value)
{
	this->state = value;
}

KraidState Kraid::getKraidState()
{
	return this->state;
}

void Kraid::setIsLeftCollided(bool isLeft)
{
	isLeftCollided = isLeft;
}

bool Kraid::getIsLeftCollided()
{
	return isLeftCollided;
}

void Kraid::setIsRightCollided(bool isRight)
{
	isRightCollided = isRight;
}

bool Kraid::getIsRightCollided()
{
	return isRightCollided;
}

void Kraid::setIsTopCollided(bool isTop)
{
	isTopCollided = isTop;
}

bool Kraid::getIsTopCollided()
{
	return isTopCollided;
}

void Kraid::setIsBottomCollided(bool isBottom)
{
	isBottomCollided = isBottom;
}

bool Kraid::getIsBottomCollided()
{
	return isBottomCollided;
}