#include "BulletKraid.h"
#include "World.h"

BulletKraid::BulletKraid()
{
}

BulletKraid::BulletKraid(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler; 
	this->manager = manager;

	this->isActive = false;
	this->isRendered = false;
	this->setType(KRAID_BULLET);
	this->grid = this->manager->getMetroid()->getGrid();
	this->pos_x = 0.0f;
	this->pos_y = 0.0f;
	this->startX = 0.0f;
	this->endX = 0.0f;
	this->width = WIDTH_KRAID_BULLET;
	this->height = HEIGHT_KRAID_BULLET;
	this->grid->add(this);
	this->timeFreezed = GetTickCount();
}

BulletKraid::~BulletKraid()
{
	delete(this->spriteLeft);
	delete(this->spriteRight);
}

void BulletKraid::initBullet(float posX, float posY)
{
	this->pos_x = posX;
	this->startX = this->pos_x;
	this->endX = this->pos_x;
	this->isActive = true;
	this->isRendered = true;

	if (this->manager->samus->pos_x < this->pos_x) {
		this->state = BULLET_KRAID_LEFT;
		if (pos_y == 202.0f) {
			pos_x += 10;
		}
		else if (pos_y == 232.0f) {
			pos_x += 5;
		}
		else if (pos_y == 262.0f) {
		}
	}
	else {
		this->state = BULLET_KRAID_RIGHT;
		if (pos_y == 202.0f) {
			pos_x += 20;
		}
		else if (pos_y == 232.0f) {
			pos_x += 25;
		}
		else if (pos_y == 262.0f) {
			pos_x += 30;
		}
	}
}

void BulletKraid::Update(float t)
{
	this->Update(t, this->posX_Kraid, this->posY_Kraid);
}

void BulletKraid::Update(float t, float posX, float posY)
{
	
	if (!isActive) return;

	if (startX == 0.0f && endX == 0.0f) {
		this->initBullet(posX, posY);
	}

	this->endX = this->pos_x;
	if (fabs(endX - startX) >= RANGE_BULLET_KRAID) {
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

	if (!isTop && !isRight && !isLeft && !isBottom) {
		switch (state) {
		case BULLET_KRAID_LEFT: {
			this->vx = -KRAID_BULLET_SPEED;
			this->vy = 0.0f;
			break;
		}

		case BULLET_KRAID_RIGHT: {
			this->vx = KRAID_BULLET_SPEED;
			this->vy = 0.0f;
			break;
		}
		}
		this->pos_x += vx * t;
		this->pos_y += vy * t;
	}
	
	this->grid->updateGrid(this, this->pos_x, this->pos_y);
}

void BulletKraid::Render()
{
	if (!isActive) return;
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(pos_x, pos_y, 0);

	// Cho nay k hieu sao bi lech, nen thoi ke :)) 
	switch (this->state) {
	case BULLET_KRAID_LEFT: {
		spriteRight->drawSprite(spriteRight->getWidth(), spriteRight->getHeight(), pos);
		break;
	}

	case BULLET_KRAID_RIGHT: {
		
		spriteLeft->drawSprite(spriteLeft->getWidth(), spriteLeft->getHeight(), pos);
		break;
	}
	}
}

void BulletKraid::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	this->spriteLeft = new Sprite(this->spriteHandler, texture, KRAID_BULLET_LEFT_PATH, WIDTH_KRAID_BULLET, HEIGHT_KRAID_BULLET, 1);
	this->spriteRight = new Sprite(this->spriteHandler, texture, KRAID_BULLET_RIGHT_PATH, WIDTH_KRAID_BULLET, HEIGHT_KRAID_BULLET, 1);
}

void BulletKraid::Reset(float posX, float posY)
{
	this->initBullet(0.0f, 0.0f);
	this->isActive = false;
	this->isRendered = false;
	this->timeFreezed = GetTickCount();
}

void BulletKraid::setStartX(float x)
{
	this->startX = x;
}

float BulletKraid::getStartX()
{
	return this->startX;
}

void BulletKraid::setEndX(float x)
{
	this->endX = x;
}

float BulletKraid::getEndX()
{
	return this->endX;
}


void BulletKraid::setIsLeft(bool isLeft)
{
	this->isLeft = isLeft;
}

bool BulletKraid::getIsLeft()
{
	return this->isLeft;
}

void BulletKraid::setIsRight(bool isRight)
{
	this->isRight = isRight;
}

bool BulletKraid::getIsRight()
{
	return this->isRight;
}

void BulletKraid::setIsTop(bool isTop)
{
	this->isTop = isTop;
}

bool BulletKraid::getIsTop()
{
	return this->isTop;
}

void BulletKraid::setIsBottom(bool isBottom)
{
	this->isBottom = isBottom;
}

bool BulletKraid::getIsBottom()
{
	return this->isBottom;
}

void BulletKraid::setIsRenderd(bool isRendered)
{
	this->isRendered = isRendered;
}

bool BulletKraid::getIsRendered()
{
	return this->isRendered;
}

void BulletKraid::setPosXKraid(float x)
{
	this->posX_Kraid = x;
}

float BulletKraid::getPosXKraid()
{
	return this->posX_Kraid;
}

void BulletKraid::setPosYKraid(float y)
{
	this->posY_Kraid = y;
}

float BulletKraid::getPosYKraid()
{
	return this->posY_Kraid;
}
