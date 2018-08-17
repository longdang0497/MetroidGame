#include "BulletSkree.h"
#include "World.h"
#include "Math.h"

BulletSkree::BulletSkree()
{
}

BulletSkree::BulletSkree(LPD3DXSPRITE spriteHandler, World * manager, Bullet_Skree_Direction direction)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->grid = manager->getMetroid()->getGrid();
	this->isActive = false;
	this->isRendered = false;
	this->direction = direction;
	this->pos_x = 0;
	this->pos_y = 0;
	this->setType(SKREE_BULLET);
	this->startX = 0.0f;
	this->startY = 0.0f;
	this->endX = 0.0f;
	this->endY = 0.0f;
	this->grid->add(this);
	this->width = SKREE_BULLET_WIDTH;
	this->height = SKREE_BULLET_HEIGHT;
}


BulletSkree::~BulletSkree()
{
	delete(this->sprite);
}

void BulletSkree::initBullet(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->startX = posX;
	this->startY = posY;
}

void BulletSkree::Update(float t)
{
	this->Update(t, this->posX_Skree, this->posY_Skree);
}

// Cap nhat lai vi tri cua vien dan khi Skree chet
void BulletSkree::Update(float t, float posX, float posY)
{
	if (!this->isActive) return;

	if(this->startX == 0 && this->startY == 0 && this->endX == 0.0f && this->endY == 0.0f)
		this->initBullet(this->posX_Skree, this->posY_Skree);

	this->endX = this->pos_x;
	this->endY = this->pos_y;

	if (Math::distance(startX, endX, startY, endY) >= SKREE_BULLET_DISTANCE) {
		this->Reset(0.0f, 0.0f);
		return;
	}

	this->isRight = false;
	this->isLeft = false;
	this->isTop = false;
	this->isBottom = false;

	this->grid->updateGrid(this, this->pos_x, this->pos_y);

	int row = (int)floor(this->pos_y / CELL_SIZE);
	int column = (int)floor(this->pos_x / CELL_SIZE);
	this->grid->handleCell(this, row, column);

	if (!isTop && !isRight && !isBottom && !isLeft) {
		switch (direction) {
		case BULLET_RIGHT:
			this->vx = SKREE_BULLET_SPEED;
			this->vy = 0.0f;
			break;

		case BULLET_LEFT:
			this->vx = -SKREE_BULLET_SPEED;
			this->vy = 0.0f;
			break;

		case BULLET_TOPRIGHT:
			this->vx = SKREE_BULLET_SPEED;
			this->vy = -SKREE_BULLET_SPEED;
			break;

		case BULLET_TOPLEFT:
			this->vx = -SKREE_BULLET_SPEED;
			this->vy = -SKREE_BULLET_SPEED;
			break;
		}
		this->pos_x += vx * t;
		this->pos_y += vy * t;
	}

	this->grid->updateGrid(this, this->pos_x, this->pos_y);
}

void BulletSkree::Render()
{
	if (!isActive) return;

	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(pos_x, pos_y, 0);
	sprite->drawSprite(sprite->getWidth(), sprite->getHeight(), position);
}

void BulletSkree::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	this->sprite = new Sprite(this->spriteHandler, texture, BULLET_SKREE_PATH, SKREE_BULLET_WIDTH, SKREE_BULLET_HEIGHT, 1);
}

void BulletSkree::Reset(float posX, float posY)
{
	this->initBullet(posX, posY);
	this->endX = 0.0f;
	this->endY = 0.0f;
	this->startX = 0.0f;
	this->startY = 0.0f;
	this->isActive = false;
	this->isRendered = false;
}

void BulletSkree::setStartX(float x)
{
	this->startX = x;
}

float BulletSkree::getStartX()
{
	return this->startX;
}

void BulletSkree::setStartY(float y)
{
	this->startY = y;
}

float BulletSkree::getStartY()
{
	return this->startY;
}

void BulletSkree::setEndX(float x)
{
	this->endX = x;
}

float BulletSkree::getEndX()
{
	return this->endX;
}

void BulletSkree::setEndY(float y)
{
	this->endY = y;
}

float BulletSkree::getEndY()
{
	return this->endY;
}

void BulletSkree::setIsLeft(bool isLeft)
{
	this->isLeft = isLeft;
}

bool BulletSkree::getIsLeft()
{
	return this->isLeft;
}

void BulletSkree::setIsRight(bool isRight)
{
	this->isRight = isRight;
}

bool BulletSkree::getIsRight()
{
	return this->isRight;
}

void BulletSkree::setIsTop(bool isTop)
{
	this->isTop = isTop;
}

bool BulletSkree::getIsTop()
{
	return this->isTop;
}

void BulletSkree::setIsBottom(bool isBottom)
{
	this->isBottom = isBottom;
}

bool BulletSkree::getIsBottom()
{
	return this->isBottom;
}

void BulletSkree::setIsRenderd(bool isRendered)
{
}

bool BulletSkree::getIsRendered()
{
	return false;
}

void BulletSkree::setPosXSkree(float x)
{
	this->posX_Skree = x;
}

float BulletSkree::getPosXSkree()
{
	return this->posX_Skree;
}

void BulletSkree::setPosYSkree(float y)
{
	this->posY_Skree = y;
}

float BulletSkree::getPosYSkree()
{
	return this->posY_Skree;
}
