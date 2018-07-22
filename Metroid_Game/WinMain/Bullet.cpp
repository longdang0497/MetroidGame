#include "Bullet.h"

Bullet::Bullet() {
	this->isActive = false;
	this->isRendered = false;
	this->count = 0;
}

// isActive và isRendered khi nhận sự kiện bắn đạn sẽ = true, sự khác nhau là:
// isActive: Dùng để xác định đạn có được khởi tạo rồi hay chưa.
// isRendered: Dùng để xác định và tính toán khoản cách thời gian các viên đạn
// được bắn ra theo trình tự (ở đây là 3 viên đạn).
Bullet::Bullet(LPD3DXSPRITE spriteHandler) {
	this->spriteHandler = spriteHandler;
	this->isActive = false;
	this->isRendered = false;
	this->count = 0;
	this->direction = OFF;
	pos_x =	-100.0f;
	pos_y = -100.0f;
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
		this->pos_y = posY - 12;
	}
	else if (this->direction == SHOOT_UP_LEFT) {
		this->pos_x = posX + 6;
		this->pos_y = posY - 12;
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

// Cập nhật lại vị trí của viên đạn theo con samus khi đã đi hết quãng đường bắn.
// Được cập nhật theo tình trạng của viên đạn
void Bullet::Update(float t, float posX, float posY) {
	if (this->count == BULLET_COUNT) {
		this->Reset(posX, posY);
	}


	if (this->isActive == true && this->count == 0) {
		this->initBullet(posX, posY);
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
	if (this->isActive == false && this->count == 0)
		return;
	D3DXVECTOR3 pos = D3DXVECTOR3(this->pos_x, this->pos_y, 0);
	this->bulletSprite->drawSprite(0, 0, WIDTH_BULLET, HEIGHT_BULLET, pos);
}

void Bullet::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture) {
	if (d3ddv == NULL) return;
	this->bulletSprite = new Sprite(this->spriteHandler, texture, WIDTH_BULLET, HEIGHT_BULLET, 1, 1);
}

void Bullet::setDirection(Bullet_SAMUS_Direction direction) {
	this->direction = direction;
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