#include "Kraid.h"
#include "World.h"
#include "BulletKraid.h"

Kraid::Kraid()
{
}

Kraid::Kraid(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->grid = manager->getMetroid()->getGrid();
	this->setType(KRAID);
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->isActive = false;

	this->previousUnit = NULL;
	this->nextUnit = NULL;

	this->vy = GRAVITY_VELOCITY;
	this->vx = SAMUS_SPEED - 50.0f;

	this->height = HEIGHT_KRAID;
	this->width = WIDTH_KRAID;

	this->health = 1000.0f;
	this->isDeath = false;

	this->pos_x = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS + 350.0f;
	this->pos_y = 192.0f;

	this->state = KRAID_LEFT;
	this->grid->add(this);
}


Kraid::~Kraid()
{
	delete(this->right);
	delete(this->left);
}

void Kraid::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	left = new Sprite(spriteHandler, texture, KRAID_LEFT_PATH, WIDTH_KRAID, HEIGHT_KRAID, KRAID_COUNT);
	right = new Sprite(spriteHandler, texture, KRAID_RIGHT_PATH, WIDTH_KRAID, HEIGHT_KRAID, KRAID_COUNT);
}

void Kraid::InitPostition()
{
	this->pos_x = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS + 300.0f;
	this->pos_y = 200.0f;
}

void Kraid::Update(float t)
{
	if (isDeath) return;
	if (this->manager->samus->getRoomNum() == BOSS2) {
		this->setActive(true);
	}
	else
		this->setActive(false);

	if (!this->isActive)
		return;

	this->vy = GRAVITY_VELOCITY;
	if (this->state == KRAID_RIGHT)
		this->vx = SAMUS_SPEED - 150.0f;
	else
		this->vx = -(SAMUS_SPEED - 150.0f);

	//GameObject* object = static_cast<GameObject*>(this);
	//object->isActive = true;

	this->isBottom = false;
	this->isTop = false;
	this->isLeft = false;
	this->isRight = false;
	int row = (int)floor(this->pos_y / CELL_SIZE);
	int column = (int)floor(this->pos_x / CELL_SIZE);
	this->grid->handleCell(this, row, column);
	if (!isBottom && !isTop && !isLeft && !isRight) {
		this->pos_y += vy * t;
	}else if (isBottom && isRight) {
		this->setState(KRAID_LEFT);
	}
	else if (isBottom && isLeft) {
		this->setState(KRAID_RIGHT);
	}
	else if (isBottom) {
		this->pos_x += this->vx *t;
	}

	this->grid->updateGrid(this, this->pos_x, this->pos_y);

	for (int i = 0; i < this->manager->kraidBullet.size(); i++) {
		if (!this->manager->kraidBullet[i]->isActive && GetTickCount() - this->manager->kraidBullet[i]->getTimeFreezed() >= 1500) {
			this->manager->kraidBullet[i]->setActive(true);
			this->manager->kraidBullet[i]->setPosXKraid(this->pos_x);
			this->manager->kraidBullet[i]->setPosYKraid(this->pos_y);
		}
	}

	for (int i = 0; i < this->manager->kraidBomerang.size(); i++) {
		if (!this->manager->kraidBomerang[i]->isActive ) {
			if (i == 0 && GetTickCount() - this->manager->kraidBomerang[i]->getTimeFreezed() >= 1500) {
				this->manager->kraidBomerang[i]->setActive(true);
				this->manager->kraidBomerang[i]->setPosXKraid(this->pos_x);
				this->manager->kraidBomerang[i]->setPosYKraid(this->pos_y);
			}
			else if (i == 1 && GetTickCount() - this->manager->kraidBomerang[i]->getTimeFreezed() >= 1800) {
				this->manager->kraidBomerang[i]->setActive(true);
				this->manager->kraidBomerang[i]->setPosXKraid(this->pos_x);
				this->manager->kraidBomerang[i]->setPosYKraid(this->pos_y);
			}
				
		}
	}

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
	if (!this->isActive) return;

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
}

void Kraid::setState(KraidState state)
{
	this->state = state;
}

KraidState Kraid::getState()
{
	return this->state;
}

void Kraid::setIsDeath(bool value)
{
	this->isDeath = value;
}

bool Kraid::getIsDeath()
{
	return this->isDeath;
}

void Kraid::setHealth(int health)
{
	this->health = health;
}

int Kraid::getHealth()
{
	return this->health;
}

void Kraid::setIsTop(bool isTop)
{
	this->isTop = isTop;
}

bool Kraid::getIsTop()
{
	return this->isTop;
}

void Kraid::setIsBottom(bool isBottom)
{
	this->isBottom = isBottom;
}

bool Kraid::getIsBottom()
{
	return this->isBottom;
}

void Kraid::setIsRight(bool isRight)
{
	this->isRight = isRight;
}

bool Kraid::getIsRight()
{
	return this->isRight;
}

void Kraid::setIsLeft(bool isLeft)
{
	this->isLeft = isLeft;
}

bool Kraid::getIsLeft()
{
	return this->isLeft;
}
