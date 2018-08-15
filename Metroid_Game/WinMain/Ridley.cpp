#include "Ridley.h"
#include "World.h"


Ridley::Ridley(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->type = RIDLEY;
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->grid = this->manager->getMetroid()->getGrid();
	this->isActive = false;

	this->width = WIDTH_RIDLEY;
	this->height = HEIGHT_RIDLEY_SIT;

	this->state = FLY_LEFT;
	this->vx = 0.0f;
	this->vy = 100.0f;
	this->pos_x = 4626.0f;
	this->pos_y = 80.0f;

	this->timePush = 0.0f;
	this->isFlyingUp = false;
	this->timeIsSet = false;

	this->health = 1000;
	this->isDeath = false;
	this->grid->add(this);
}

Ridley::Ridley()
{
}


Ridley::~Ridley()
{
	delete(this->sitLeft);
	delete(this->sitRight);
	delete(this->flyLeft);
	delete(this->flyRight);
}

void Ridley::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	this->flyLeft = new Sprite(spriteHandler, texture, RIDLEY_FLY_LEFT_PATH, WIDTH_RIDLEY, HEIGHT_RIDLEY_FLY, RIDLEY_COUNT);
	this->flyRight = new Sprite(spriteHandler, texture, RIDLEY_FLY_RIGHT_PATH, WIDTH_RIDLEY, HEIGHT_RIDLEY_FLY, RIDLEY_COUNT);
	this->sitLeft = new Sprite(spriteHandler, texture, RIDLEY_SIT_LEFT_PATH, WIDTH_RIDLEY, HEIGHT_RIDLEY_SIT, RIDLEY_COUNT);
	this->sitRight = new Sprite(spriteHandler, texture, RIDLEY_SIT_RIGHT_PATH, WIDTH_RIDLEY, HEIGHT_RIDLEY_SIT, RIDLEY_COUNT);
}

void Ridley::Init(float x, float y)
{
	this->pos_x = x;
	this->pos_y = y;
}

void Ridley::Update(float t)
{
	if (this->manager->samus->pos_x >= WIDTH_ROOM1 + WIDTH_ROOM2 && this->manager->samus->pos_x <= WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS) {
		this->isActive = true;
	}
	else {
		this->isActive = false;
	}

	if (!this->isActive || this->isDeath) return;

	this->isLeft = false;
	this->isTop = false;
	this->isBottom = false;
	this->isRight = false;

	GameObject* object = static_cast<GameObject*>(this);
	object->setActive(true);
	int row = (int)floor(this->pos_y / CELL_SIZE);
	int column = (int)floor(this->pos_x / CELL_SIZE);
	
	this->grid->handleCell(object, row, column);

	this->grid->updateGrid(object, this->pos_x, this->pos_y);

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / RIDLEY_ANIMATE_RATE)
	{
		switch (state)
		{
		case SIT_LEFT:
			this->sitLeft->updateSprite();
			break;
		case SIT_RIGHT:
			this->sitRight->updateSprite();
			break;
		case FLY_LEFT:
			this->flyLeft->updateSprite();
			break;
		case FLY_RIGHT:
			this->flyRight->updateSprite();
			break;
		}
		last_time = now;
	}
}

void Ridley::Render()
{
	if (!this->isActive || this->isDeath) return;

	D3DXVECTOR3 pos;
	pos.x = pos_x;
	pos.y = pos_y;
	pos.z = 0;

	if (this->manager->samus->pos_x > this->pos_x) {
		this->state = FLY_RIGHT;
	}
	
	switch (state) {
	case SIT_LEFT: {
		this->sitLeft->drawSprite(this->sitLeft->getWidth(), this->sitLeft->getHeight(), pos);
		break;
	}
	case SIT_RIGHT: {
		this->sitRight->drawSprite(this->sitRight->getWidth(), this->sitRight->getHeight(), pos);
		break;
	}
	case FLY_LEFT: {
		this->flyLeft->drawSprite(this->flyLeft->getWidth(), this->flyLeft->getHeight(), pos);
		break;
	}
	case FLY_RIGHT: {
		this->flyRight->drawSprite(this->flyRight->getWidth(), this->flyRight->getHeight(), pos);
		break;
	}
	}
}


void Ridley::Destroy(float x, float y)
{
}

void Ridley::setRidleyState(RIDLEY_STATE value)
{
	this->state = value;
}

RIDLEY_STATE Ridley::getRidleyState()
{
	return this->state;
}

void Ridley::setIsLeftCollided(bool isLeft)
{
	this->isLeft = isLeft;
}

bool Ridley::getIsLeftCollided()
{
	return this->isLeft;
}

void Ridley::setIsRightCollided(bool isRight)
{
	this->isRight = isRight;
}

bool Ridley::getIsRightCollided()
{
	return this->isRight;
}

void Ridley::setIsTopCollided(bool isTop)
{
	this->isTop = isTop;
}

bool Ridley::getIsTopCollided()
{
	return this->isTop;
}

void Ridley::setIsBottomCollided(bool isBottom)
{
	this->isBottom = isBottom;
}

bool Ridley::getIsBottomCollided()
{
	return this->isBottom;
}
