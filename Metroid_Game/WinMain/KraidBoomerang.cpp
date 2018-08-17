#include "KraidBoomerang.h"
#include "World.h"

KraidBoomerang::KraidBoomerang()
{
}

KraidBoomerang::KraidBoomerang(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;

	this->isActive = false;
	this->isRendered = false;
	this->setType(KRAID_BOMERANG);
	this->grid = this->manager->getMetroid()->getGrid();
	this->pos_x = 0.0f;
	this->pos_y = 0.0f;
	this->width = SIZE_KRAID_BOMERANG;
	this->height = SIZE_KRAID_BOMERANG;
	this->grid->add(this);
	this->timeFreezed = GetTickCount();
	this->timeStartActive = GetTickCount();
	this->isFall = false;
}

KraidBoomerang::~KraidBoomerang()
{
	delete(this->sprite);
}

void KraidBoomerang::initBullet(float posX, float posY)
{
	this->pos_x = posX + 10;
	this->pos_y = posY;
	
	this->isActive = true;
	this->isRendered = true;

	this->timeStartActive = GetTickCount();
	if (this->manager->samus->pos_x < this->pos_x) {
		this->state = BULLET_KRAID_LEFT;
	}
	else
		this->state = BULLET_KRAID_RIGHT;
}

void KraidBoomerang::Update(float t)
{
	this->Update(t, this->posX_Kraid, this->posY_Kraid);
}

void KraidBoomerang::Update(float t, float posX, float posY)
{
	if (!isActive) return;
	if (this->pos_x == 0 && this->pos_y == 0)
		this->initBullet(posX, posY);

	if (this->pos_y < 96.0f)
		this->isFall = true;

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
			break;
		}

		case BULLET_KRAID_RIGHT: {
			this->vx = KRAID_BULLET_SPEED;
			break;
		}
		}

		if (isFall) {
			this->vy = KRAID_BULLET_SPEED;
		}
		else {
			this->vy = -KRAID_BULLET_SPEED;
		}

		this->pos_x += vx * t;
		this->pos_y += vy * t;
	}

	this->grid->updateGrid(this, this->pos_x, this->pos_y);

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		this->sprite->updateSprite();
	}
}

void KraidBoomerang::Render()
{
	if (!isActive) return;
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(pos_x, pos_y, 0);

	sprite->drawSprite(sprite->getWidth(), sprite->getHeight(), pos);
}

void KraidBoomerang::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	this->sprite = new Sprite(this->spriteHandler, texture, KRAID_BOMERANG_PATH, SIZE_KRAID_BOMERANG, SIZE_KRAID_BOMERANG, COUNT_KRAID_BOMERANG);
}

void KraidBoomerang::Reset(float posX, float posY)
{
	this->pos_x = 0.0f;
	this->pos_y = 0.0f;
	this->isActive = false;
	this->isRendered = false;
	this->timeFreezed = GetTickCount();
}

void KraidBoomerang::setIsLeft(bool isLeft)
{
	this->isLeft = isLeft;
}

bool KraidBoomerang::getIsLeft()
{
	return this->isLeft;
}

void KraidBoomerang::setIsRight(bool isRight)
{
	this->isRight = isRight;
}

bool KraidBoomerang::getIsRight()
{
	return this->isRight;
}

void KraidBoomerang::setIsTop(bool isTop)
{
	this->isTop = isTop;
}

bool KraidBoomerang::getIsTop()
{
	return this->isTop;
}

void KraidBoomerang::setIsBottom(bool isBottom)
{
	this->isBottom = isBottom;
}

bool KraidBoomerang::getIsBottom()
{
	return this->isBottom;
}

void KraidBoomerang::setIsRenderd(bool isRendered)
{
	this->isRendered = isRendered;
}

bool KraidBoomerang::getIsRendered()
{
	return this->isRendered;
}

void KraidBoomerang::setPosXKraid(float x)
{
	this->posX_Kraid = x;
}

float KraidBoomerang::getPosXKraid()
{
	return this->posX_Kraid;
}

void KraidBoomerang::setPosYKraid(float y)
{
	this->posY_Kraid = y;
}

float KraidBoomerang::getPosYKraid()
{
	return this->posY_Kraid;
}
