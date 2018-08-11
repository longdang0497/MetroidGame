#include "Kraid.h"

Kraid::Kraid(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->type = RIDLEY;
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->isActive = true;

	this->width = WIDTH_KRAID;
	this->height = HEIGHT_KRAID;
	//health = HEALTH_RIDLEY;
}

Kraid::~Kraid()
{
	delete(left);
	//delete(right);
}

void Kraid::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (texture == NULL)
		trace(L"Unable to load zoomerTexture");
	this->texture = texture;

	left = new Sprite(spriteHandler, texture, KRAID_LEFT_PATH, WIDTH_KRAID, HEIGHT_KRAID, KRAID_COUNT);
	//right = new Sprite(spriteHandler, texture, KRAID_RIGHT_PATH, WIDTH_KRAID, HEIGHT_KRAID, KRAID_COUNT);
}

void Kraid::Init(float x, float y)
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
		left->updateSprite();
		//right->updateSprite();
		last_time = now;
	}
}

void Kraid::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	if (!isActive)
		return;

	left->drawSprite(left->getWidth(), left->getHeight(), position);
	//right->drawSprite(right->getWidth(), right->getHeight(), position);
}

void Kraid::Destroy(float x, float y)
{
	this->isActive = false;
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