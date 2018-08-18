#include "Missble.h"
#include "World.h"


Missible::Missible()
{
}

Missible::Missible(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->grid = this->manager->getMetroid()->getGrid();
	this->isActive = false;
	this->isRendered = false;
	this->setType(MISSIBLE);
	this->pos_x = 0.0f;
	this->pos_y = 0.0f;
	this->grid->add(this);

	this->startX = 0.0f;
	this->startY = 0.0f;
	this->endX = 0.0f;
	this->endY = 0.0f;
}


Missible::~Missible()
{
	delete(this->spriteUp);
	delete(this->spriteLeft);
	delete(this->spriteRight);
}

void Missible::initBullet(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->isActive = true;
	this->isRendered = true;
	this->startX = this->pos_x;
	this->endX = this->pos_x;
	this->startY = this->pos_y;
	this->endY = this->pos_y;

	this->setDimension();
}

void Missible::Update(float t)
{
	this->Update(t, this->manager->samus->pos_x, this->manager->samus->pos_y);
}

void Missible::Update(float t, float posX, float posY)
{
	if (!isActive) return;

	if (startX == 0.0f && endX == 0.0f && startY == 0.0f && endY == 0.0f) {
		this->initBullet(posX, posY);
	}

	this->endX = this->pos_x;
	this->endY = this->pos_y;

	if (fabs(endX - startX) >= RANGE_MISSIBLE || fabs(endY - startY) >= RANGE_MISSIBLE) {
		this->Reset(0.0f, 0.0f);
		return;
	}

	this->isRight = false;
	this->isLeft = false;
	this->isTop = false;

	this->grid->updateGrid(this, this->pos_x, this->pos_y);
	
	int row = (int)floor(this->pos_y / CELL_SIZE);
	int column = (int)floor(this->pos_x / CELL_SIZE);
	this->grid->handleCell(this, row, column);

	if (!isTop && !isRight && !isLeft) {
		this->pos_x += vx * t;
		this->pos_y += vy * t;
	}

	this->grid->updateGrid(this, this->pos_x, this->pos_y);
}

void Missible::Render()
{
	if (!isActive) return;
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(pos_x, pos_y, 0);

	switch (this->state) {
	case MISSIBLE_SHOT_LEFT: {
		this->spriteLeft->drawSprite(spriteLeft->getWidth(), spriteLeft->getHeight(), pos);
		break;
	}

	case MISSIBLE_SHOT_RIGHT: {
		this->spriteRight->drawSprite(spriteRight->getWidth(), spriteRight->getHeight(), pos);
		break;
	}

	case MISSIBLE_SHOT_UP: {
		this->spriteUp->drawSprite(spriteUp->getWidth(), spriteUp->getHeight(), pos);
		break;
	}
	}
}

void Missible::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	this->spriteLeft = new Sprite(this->spriteHandler, texture, MISSIBLE_LEFT_PATH, WIDTH_MISSIBLE, HEIGHT_MISSIBLE, 1);
	this->spriteRight = new Sprite(this->spriteHandler, texture, MISSIBLE_RIGHT_PATH, WIDTH_MISSIBLE, HEIGHT_MISSIBLE, 1);
	this->spriteUp = new Sprite(this->spriteHandler, texture, MISSIBLE_UP_PATH, HEIGHT_MISSIBLE, WIDTH_MISSIBLE, 1);
}

void Missible::Reset(float posX, float posY)
{
	this->initBullet(0.0f, 0.0f);
	this->isActive = false;
	this->isRendered = false;
}

void Missible::setDimension()
{
	if (this->state == MISSIBLE_SHOT_RIGHT)
	{
		this->width = WIDTH_MISSIBLE;
		this->height = HEIGHT_MISSIBLE;
		this->pos_x += 32;
		this->pos_y += 10;
		this->vx = X_VELOCITY_MISSIBLE;
		this->vy = 0.0f;
	}
	else if (this->state == MISSIBLE_SHOT_LEFT) {
		this->width = WIDTH_MISSIBLE;
		this->height = HEIGHT_MISSIBLE;
		this->pos_y += 10;
		this->vx = -X_VELOCITY_MISSIBLE;
		this->vy = 0.0f;
	}
	else {
		this->width = HEIGHT_MISSIBLE;
		this->height = WIDTH_MISSIBLE;
		this->pos_x += 10;
		this->vx = 0.0f;
		this->vy = -Y_VELOCITY_MISSIBLE;
	}
}

void Missible::setStartX(float x)
{
	this->startX = x;
}

float Missible::getStartX()
{
	return this->startX;
}

void Missible::setEndX(float x)
{
	this->endX = x;
}

float Missible::getEndX()
{
	return this->endX;
}

void Missible::setStartY(float y)
{
	this->startY = y;
}

float Missible::getStartY()
{
	return this->startY;
}

void Missible::setEndY(float y)
{
	this->endY = y;
}

float Missible::getEndY()
{
	return this->endY;
}

void Missible::setIsLeft(bool isLeft)
{
	this->isLeft = isLeft;
}

bool Missible::getIsLeft()
{
	return this->isLeft;
}

void Missible::setIsRight(bool isRight)
{
	this->isRight = isRight;
}

bool Missible::getIsRight()
{
	return this->isRight;
}

void Missible::setIsTop(bool isTop)
{
	this->isTop = isTop;
}

bool Missible::getIsTop()
{
	return this->isTop;
}

void Missible::setIsRenderd(bool isRendered)
{
	this->isRendered = isRendered;
}

bool Missible::getIsRendered()
{
	return this->isRendered;
}

void Missible::setState(MISSIBLE_STATE state)
{
	this->state = state;
}

MISSIBLE_STATE Missible::getState()
{
	return this->state;
}
