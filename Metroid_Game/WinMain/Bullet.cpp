#include "Bullet.h"

Bullet::Bullet() {
	this->isActive = false;
	this->isRendered = false;
	this->count = 0;
	this->setType(BULLET);
}

// isActive và isRendered khi nh?n s? ki?n b?n d?n s? = true, s? khác nhau là:
// isActive: Dùng d? xác d?nh d?n có du?c kh?i t?o r?i hay chua.
// isRendered: Dùng d? xác d?nh và tính toán kho?n cách th?i gian các viên d?n
// du?c b?n ra theo trình t? (? dây là 3 viên d?n).
Bullet::Bullet(LPD3DXSPRITE spriteHandler) {
	this->spriteHandler = spriteHandler;
	this->isActive = false;
	this->isRendered = false;
	this->count = 0;
	this->direction = OFF;
	pos_x =	-100.0f;
	pos_y = -100.0f;
	this->setType(BULLET);
}

Bullet::~Bullet() {
	delete(this->bulletSprite);
}

void Bullet::initBullet(float posX, float posY) {
	if (this->direction == SHOOT_RIGHT) {
		this->pos_x = posX + 32 + 12;
		this->pos_y = posY + 13;
	}
	else if (this->direction == SHOOT_UP_RIGHT) {
		this->pos_x = posX + 16;
		this->pos_y = posY - 22;
	}
	else if (this->direction == SHOOT_UP_LEFT) {
		this->pos_x = posX + 6;
		this->pos_y = posY - 22;
	}
	else if (this->direction == SHOOT_LEFT) {
		this->pos_x = posX - 12;
		this->pos_y = posY + 13;
	}
	else {
		this->pos_x = posX;
		this->pos_y = posY;
	}
}

void Bullet::Reset(float posX, float posY) {
	this->initBullet(posX, posY);
	this->count = 0;
	this->isRendered = false;
	this->setActive(false);
}

void Bullet::Update(float delta) {

}

// C?p nh?t l?i v? trí c?a viên d?n theo con samus khi dã di h?t quãng du?ng b?n.
// Ğu?c c?p nh?t theo tình tr?ng c?a viên d?n
void Bullet::Update(float t, float posX, float posY) {
	if (this->direction == OFF && this->tempDirection == OFF)
	{
		return;
	}
	else if (this->direction == OFF && this->tempDirection != OFF || this->direction != this->tempDirection && this->count == 0) {
		this->direction = this->tempDirection;
	}

	if (this->count == BULLET_COUNT) {
		this->Reset(posX, posY);
	}

	if (this->isActive == true && this->count == 0) {
		if (this->direction == OFF)
			this->isActive = false;
		if (this->isActive) {
			this->initBullet(posX, posY);
			this->isRendered = true;
		}
	}

	if (this->isActive == false && this->count == 0 || this->direction == OFF)
		return;

	if (this->direction == SHOOT_RIGHT) {
		this->pos_x += X_VELOCITY_BULLET;
	}
	else if (this->direction == SHOOT_LEFT) {
		this->pos_x -= X_VELOCITY_BULLET;
	}
	else if (this->direction == SHOOT_UP_RIGHT || this->direction == SHOOT_UP_LEFT) {
		this->pos_y -= Y_VELOCITY_BULLET;
	}
	count++;


}


void Bullet::Render() {
	if (this->isActive == false && this->count == 0|| this->direction == OFF)
		return;
	if (this->count == 3 || this->count == 4 || this->count == 7)
		return;
	D3DXVECTOR3 pos = D3DXVECTOR3(this->pos_x, this->pos_y, 0);
	this->bulletSprite->drawSprite(0, 0, WIDTH_BULLET, HEIGHT_BULLET, pos);
}

void Bullet::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture) {
	if (d3ddv == NULL) return;
	this->bulletSprite = new Sprite(this->spriteHandler, texture, WIDTH_BULLET, HEIGHT_BULLET, 1, 1);
}

void Bullet::setDirection(Bullet_SAMUS_Direction direction) {
	this->tempDirection = direction;
}


Bullet_SAMUS_Direction Bullet::getDirection() {
	return this->direction;
}

void Bullet::setIsRendered(bool isRendered) {
	this->isRendered = isRendered;
}

bool Bullet::getIsRendered() {
	return this->isRendered;
}

void Bullet::setCount(int count) {
	this->count = count;
}

int Bullet::getCount() {
	return this->count;
}