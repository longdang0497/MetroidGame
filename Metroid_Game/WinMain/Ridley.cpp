#include "Ridley.h"

Ridley::Ridley(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->type = RIDLEY;
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->grid = manager->getMetroid()->getGrid();
	this->isActive = false;

	this->width = WIDTH_RIDLEY;
	this->height = HEIGHT_RIDLEY_SIT;

	setRidleyState(FLY_LEFT);

	this->vy = GRAVITY_VELOCITY - 65.0f;
	vx = 0.0f;
	isRightCollided = false;
	isLeftCollided = false;
	isTopCollided = false;
	isBottomCollided = false;
	this->isFall = false;

	this->pos_x = WIDTH_ROOM1 + WIDTH_ROOM2 + 384;
	this->pos_y = 64;
	this->isDeath = false;
	this->time_push = GetTickCount();
	this->grid->add(this);
}

Ridley::~Ridley()
{
	delete(fly_left);
	delete(fly_right);
	delete(sit_left);
	delete(sit_right);
}

void Ridley::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (texture == NULL)
		trace(L"Unable to load zoomerTexture");

	fly_left = new Sprite(spriteHandler, texture, RIDLEY_FLY_LEFT_PATH, WIDTH_RIDLEY, HEIGHT_RIDLEY_FLY, RIDLEY_COUNT);
	fly_right = new Sprite(spriteHandler, texture, RIDLEY_FLY_RIGHT_PATH, WIDTH_RIDLEY, HEIGHT_RIDLEY_FLY, RIDLEY_COUNT);
	sit_left = new Sprite(spriteHandler, texture, RIDLEY_SIT_LEFT_PATH, WIDTH_RIDLEY, HEIGHT_RIDLEY_SIT, RIDLEY_COUNT);
	sit_right = new Sprite(spriteHandler, texture, RIDLEY_SIT_RIGHT_PATH, WIDTH_RIDLEY, HEIGHT_RIDLEY_SIT, RIDLEY_COUNT);
}

void Ridley::Init()
{
	this->pos_x = WIDTH_ROOM1 + WIDTH_ROOM2 + 384;
	this->pos_y = 64;
}

void Ridley::Update(float t)
{

	if (isDeath) return;
	if (this->manager->samus->getRoomNum() == BOSS1) {
		this->setActive(true);
	}
	else
		this->setActive(false);
	
	if (!isActive) return;

	this->isLeftCollided = false;
	this->isRightCollided = false;
	this->isTopCollided = false;
	this->isBottomCollided = false;

	if (this->pos_y <= 64.0f) {
		this->isFall = true;
	}

	if (this->isFall)
		this->vy = 100.0f;
	else
		this->vy = -100.0f;

	int row = (int)floor(this->pos_y / CELL_SIZE);
	int column = (int)floor(this->pos_x / CELL_SIZE);
	this->grid->handleCell(this, row, column);

	if (!isTopCollided && !isLeftCollided && !isRightCollided && !isBottomCollided) {
		if (this->state == SIT_LEFT)
			this->state = FLY_LEFT;
		else if (this->state == SIT_RIGHT)
			this->state = FLY_RIGHT;

		this->pos_y += vy * t;
	}
	else if (isBottomCollided) {
		if (GetTickCount() - this->time_push >= 2000) {
			this->isFall = false;
		}
	}

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / RIDLEY_ANIMATE_RATE)
	{
		switch (state)
		{
		case SIT_LEFT:
			sit_left->updateSprite();
			break;
		case SIT_RIGHT:
			sit_right->updateSprite();
			break;
		case FLY_LEFT:
			fly_left->updateSprite();
			break;
		case FLY_RIGHT:
			fly_right->updateSprite();
			break;
		}
		last_time = now;
	}
}

void Ridley::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	if (!isActive)
		return;

	switch (state)
	{
	case SIT_LEFT:
		sit_left->drawSprite(sit_left->getWidth(), sit_left->getHeight(), position);
		break;
	case SIT_RIGHT:
		sit_right->drawSprite(sit_right->getWidth(), sit_right->getHeight(), position);
		break;
	case FLY_LEFT:
		fly_left->drawSprite(fly_left->getWidth(), fly_left->getHeight(), position);
		break;
	case FLY_RIGHT:
		fly_right->drawSprite(fly_right->getWidth(), fly_right->getHeight(), position);
		break;
	}
}

void Ridley::Destroy(float x, float y)
{
	this->isActive = false;
}

void Ridley::setRidleyState(RIDLEY_STATE value)
{
	state = value;
}

RIDLEY_STATE Ridley::getRidleyState()
{
	return this->state;
}

void Ridley::setIsLeftCollided(bool isLeft)
{
	isLeftCollided = isLeft;
}

bool Ridley::getIsLeftCollided()
{
	return isLeftCollided;
}

void Ridley::setIsRightCollided(bool isRight)
{
	isRightCollided = isRight;
}

bool Ridley::getIsRightCollided()
{
	return isRightCollided;
}

void Ridley::setIsTopCollided(bool isTop)
{
	isTopCollided = isTop;
}

bool Ridley::getIsTopCollided()
{
	return isTopCollided;
}

void Ridley::setIsBottomCollided(bool isBottom)
{
	isBottomCollided = isBottom;
}

bool Ridley::getIsBottomCollided()
{
	return isBottomCollided;
}
