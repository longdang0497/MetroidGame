#include "KraidBullet.h"

KraidBullet::KraidBullet() {
	this->isActive = false;
	this->isRendered = false;
	this->count = 0;
	this->setType(BULLET);
}

// isActive và isRendered khi nhận sự kiện bắn đạn sẽ = true, sự khác nhau là:
// isActive: Dùng để xác định đạn có được khởi tạo rồi hay chưa.
// isRendered: Dùng để xác định và tính toán khoản cách thời gian các viên đạn
// được bắn ra theo trình tự (ở đây là 3 viên đạn).
KraidBullet::KraidBullet(LPD3DXSPRITE spriteHandler, Grid*grid) {
	this->spriteHandler = spriteHandler;
	this->isActive = false;
	this->isRendered = false;
	this->count = 0;
	//this->direction = OFF;
	pos_x = 0.0f;
	pos_y = 0.0f;
	this->setType(BULLET);
	//this->grid = grid;
	this->startX = 0.0f;
	this->startY = 0.0f;
	this->endX = 0.0f;
	this->endY = 0.0f;
	//this->grid->add(this);
	this->width = WIDTH_KRAID_BULLET;
	this->height = HEIGHT_KRAID_BULLET + 10;
}

KraidBullet::~KraidBullet() {
	delete(kraidBullet);
}

void KraidBullet::initBullet(float posX, float posY) {

	/*if (this->direction == SHOOT_RIGHT) {
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
	this->startX = this->pos_x;
	this->startY = this->pos_y;
	this->endX = this->pos_x;
	this->endY = this->pos_y;*/
}

void KraidBullet::Reset() {
	this->startX = 0.0f;
	this->startY = 0.0f;
	this->endX = 0.0f;
	this->endY = 0.0f;
	this->isRendered = false;
	this->setActive(false);
}

void KraidBullet::Update(float delta) {

}

// Cập nhật lại vị trí của viên đạn theo con samus khi đã đi hết quãng đường bắn.
// Được cập nhật theo tình trạng của viên đạn
void KraidBullet::Update(float t, float posX, float posY) {
	/*if (this->direction == OFF && this->tempDirection == OFF)
	{
	return;
	}
	else if (this->direction == OFF && this->tempDirection != OFF
	|| this->direction != this->tempDirection && (this->endX - this->startX == 0) && (this->endY - this->startY == 0)) {
	this->direction = this->tempDirection;
	}
	if (fabs(this->endX - this->startX) >= 96 || fabs(this->endY - this->startY) >= 96) {
	this->Reset();
	}
	if (this->isActive == true && (this->endX - this->startX == 0) && (this->endY - this->startY == 0)) {
	if (this->direction == OFF)
	this->isActive = false;
	if (this->isActive) {
	this->initBullet(posX, posY);
	this->isRendered = true;
	}
	}
	if (this->isActive == false && (this->endX - this->startX == 0) && (this->endY - this->startY == 0) || this->direction == OFF)
	return;
	if (this->direction == SHOOT_RIGHT) {
	this->vx = X_VELOCITY_BULLET;
	this->vy = 0.0f;
	}
	else if (this->direction == SHOOT_LEFT) {
	this->vx = -X_VELOCITY_BULLET;
	this->vy = 0.0f;
	}
	else if (this->direction == SHOOT_UP_RIGHT || this->direction == SHOOT_UP_LEFT) {
	this->vy = -Y_VELOCITY_BULLET;
	this->vx = 0.0f;
	}*/

	this->pos_x = endX;
	this->pos_y = endY;

	int row = (int)floor(this->pos_y / CELL_SIZE);
	int column = (int)floor(this->pos_x / CELL_SIZE);

	this->isRight = false;
	this->isLeft = false;
	this->isTop = false;
	this->isBottom = false;
	this->isHandled = false;

	//this->grid->updateGrid(this, this->pos_x, this->pos_y);

	// Xet va cham va cap nhat vi tri
	//this->grid->handleCell(this, row, column);
	if (!isHandled) {
		if (!isRight && !isTop && !isBottom && !isLeft) {
			this->pos_x += this->vx * t;
			this->pos_y += this->vy *t;

			this->endX = this->pos_x;
			this->endY = this->pos_y;
		}
	}
	//this->grid->updateGrid(this, this->pos_x, this->pos_y);
}

void KraidBullet::Render() {
	/*if (this->isActive == false && this->count == 0 || this->direction == OFF)
	return;
	if (this->count == 3 || this->count == 4 || this->count == 7)
	return;*/
	D3DXVECTOR3 pos = D3DXVECTOR3(this->pos_x, this->pos_y, 0);
	this->kraidBullet->drawSprite(0, 0, WIDTH_KRAID_BULLET, HEIGHT_KRAID_BULLET, pos);
}

void KraidBullet::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture) {
	if (d3ddv == NULL) return;
	kraidBullet = new Sprite(this->spriteHandler, texture, KRAID_BULLET_PATH, WIDTH_KRAID_BULLET, HEIGHT_KRAID_BULLET, COUNT_KRAID_BULLET);
}

//void KraidBomerang::setDirection(Bullet_SAMUS_Direction direction) {
//	this->tempDirection = direction;
//}
//
//
//Bullet_SAMUS_Direction KraidBomerang::getDirection() {
//	return this->direction;
//}

void KraidBullet::setIsRendered(bool isRendered) {
	this->isRendered = isRendered;
}

bool KraidBullet::getIsRendered() {
	return this->isRendered;
}

void KraidBullet::setCount(int count) {
	this->count = count;
}

int KraidBullet::getCount() {
	return this->count;
}