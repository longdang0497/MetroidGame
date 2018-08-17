#include "BulletRidley.h"
#include "World.h"


BulletRidley::BulletRidley()
{

}

BulletRidley::BulletRidley(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->grid = this->manager->getMetroid()->getGrid();

	this->isActive = false;
	this->isRendered = false;

	this->setType(RIDLEY_BULLET);

	this->pos_x = 0.0f;
	this->pos_y = 0.0f;
	this->startX = 0.0f;
	this->endX = 0.0f;
	this->grid->add(this);
	this->timeFreezed = GetTickCount();
	this->width = WIDTH_RIDLEY_BULLET;
	this->height = HEIGHT_RIDLEY_BULLET;
	this->isFall = false;
}


BulletRidley::~BulletRidley()
{
	delete(this->sprite);
}

void BulletRidley::initBullet(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->startX = this->pos_x;
	this->endX = this->pos_x;
	this->isActive = true;
	this->isRendered = true;
	
	srand(time(NULL));

	int tempV = rand() % 3 + 1;

	if (this->manager->samus->pos_x < this->pos_x) {
		this->state = BULLET_RIDLEY_LEFT;
		if (tempV == 1) {
			this->vx = -BULLET_RIDLEY_SPEED_1;
		}
		else if (tempV == 2) {
			this->vx = -BULLET_RIDLEY_SPEED_2;
		}
		else if (tempV == 3) {
			this->vx = -BULLET_RIDLEY_SPEED_2;
		}
	}
	else {
		this->state = BULLET_RIDLEY_RIGHT;
		if (tempV == 1) {
			this->vx = BULLET_RIDLEY_SPEED_1;
		}
		else if (tempV == 2) {
			this->vx = BULLET_RIDLEY_SPEED_2;
		}
		else if (tempV == 3) {
			this->vx = BULLET_RIDLEY_SPEED_3;
		}
		
	}
}

void BulletRidley::Update(float t)
{
	this->Update(t, this->posX_Ridley, this->posY_Ridley);
}

void BulletRidley::Update(float t, float posX, float posY)
{
	if (!isActive) return;
	if (this->pos_x == 0 && this->pos_y == 0)
		this->initBullet(posX, posY);

	this->endX = this->pos_x;
	float range = 0.0f;
	if (vx < 0)
		range = 250.0f;
	else
		range = 150.0f;
	if (fabs(this->endX - this->startX) >= range) {
		this->Reset(0.0f, 0.0f);
		return;
	}

	if (this->pos_y < 96.0f)
		this->isFall = true;
	else if (this->pos_y > 210.0f)
		this->isFall = false;

	this->isRight = false;
	this->isLeft = false;
	this->isTop = false;
	this->isBottom = false;

	this->grid->updateGrid(this, this->pos_x, this->pos_y);

	int row = (int)floor(this->pos_y / CELL_SIZE);
	int column = (int)floor(this->pos_x / CELL_SIZE);
	this->grid->handleCell(this, row, column);

	if (!isTop && !isBottom && !isRight && !isLeft) {
		if (isFall) {
			this->vy = 200.0f;
		}
		else {
			this->vy = -200.0f;
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

void BulletRidley::Render()
{
	if (!isActive) return;
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(pos_x, pos_y, 0);

	sprite->drawSprite(sprite->getWidth(), sprite->getHeight(), pos);
}

void BulletRidley::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	this->sprite = new Sprite(this->spriteHandler, texture, RIDLEY_BULLET_PATH, WIDTH_RIDLEY_BULLET, HEIGHT_RIDLEY_BULLET, RIDLEY_BULLET_COUNT);
}

void BulletRidley::Reset(float posX, float posY)
{
	this->initBullet(0.0f, 0.0f);
	this->isActive = false;
	this->isRendered = false;
	this->timeFreezed = GetTickCount();
}

void BulletRidley::setStartX(float x)
{
	this->startX = x;
}

float BulletRidley::getStartX()
{
	return this->startX;
}

void BulletRidley::setEndX(float x)
{
	this->endX = x;
}

float BulletRidley::getEndX()
{
	return this->endX;
}


void BulletRidley::setIsLeft(bool isLeft)
{
	this->isLeft = isLeft;
}

bool BulletRidley::getIsLeft()
{
	return this->isLeft;
}

void BulletRidley::setIsRight(bool isRight)
{
	this->isRight = isRight;
}

bool BulletRidley::getIsRight()
{
	return this->isRight;
}

void BulletRidley::setIsTop(bool isTop)
{
	this->isTop = isTop;
}

bool BulletRidley::getIsTop()
{
	return this->isTop;
}

void BulletRidley::setIsBottom(bool isBottom)
{
	this->isBottom = isBottom;
}

bool BulletRidley::getIsBottom()
{
	return this->isBottom;
}

void BulletRidley::setIsRenderd(bool isRendered)
{
	this->isRendered = isRendered;
}

bool BulletRidley::getIsRendered()
{
	return this->isRendered;
}

void BulletRidley::setPosXRidley(float x)
{
	this->posX_Ridley = x;
}

float BulletRidley::getPosXRidley()
{
	return this->posX_Ridley;
}

void BulletRidley::setPosYRidley(float y)
{
	this->posY_Ridley = y;
}

float BulletRidley::getPosYRidley()
{
	return this->posY_Ridley;
}



