#include "Zoomer.h"
#include "World.h"

Zoomer::Zoomer()
{

}

Zoomer::Zoomer(LPD3DXSPRITE spriteHandler, World * manager, OBJECT_TYPE enemy_type) : Enemy(spriteHandler, manager)
{
	this->setType(enemy_type);
	this->isActive = false;

	//Set vận tốc
	vx = 0.0f;
	vy = 0.0f;

	this->grid = manager->grid;
}


Zoomer::~Zoomer()
{
	delete(top);
	delete(bottom);
	delete(left);
	delete(right);
}

void Zoomer::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	LPWSTR top_path = NULL, bottom_path = NULL, left_path = NULL, right_path = NULL;
	if (texture == NULL)
		trace(L"Unable to load zoomerTexture");
	this->texture = texture;

	switch (this->type)
	{
	case ZOOMER_YELLOW:
		top_path = ZOOMER_YELLOW_TOP;
		bottom_path = ZOOMER_YELLOW_BOTTOM;
		left_path = ZOOMER_YELLOW_LEFT;
		right_path = ZOOMER_YELLOW_RIGHT;

		//Khởi tạo máu
		//health = HEALTH_BEDGEHOG_YELLOW;

		//Khởi tạo sát thương
		//damage = DAMAGE_BEDGEHOG;
		break;
	case ZOOMER_PINK:
		top_path = ZOOMER_PINK_UP;
		bottom_path = ZOOMER_PINK_BOTTOM;
		left_path = ZOOMER_PINK_LEFT;
		right_path = ZOOMER_PINK_RIGHT;

		//Khởi tạo máu
		//health = HEALTH_ZOOMER_PINK;

		//Khởi tạo sát thương
		//damage = DAMAGE_ZOOMER;
		break;
	}

	//// Khởi tạo sprite
	top = new Sprite(spriteHandler, texture, top_path, ZOOMER_WIDTH, ZOOMER_HEIGHT, ZOOMER_SPRITE_COUNT);
	bottom = new Sprite(spriteHandler, texture, bottom_path, ZOOMER_WIDTH, ZOOMER_HEIGHT, ZOOMER_SPRITE_COUNT);
	left = new Sprite(spriteHandler, texture, left_path, ZOOMER_WIDTH, ZOOMER_HEIGHT, ZOOMER_SPRITE_COUNT);
	right = new Sprite(spriteHandler, texture, right_path, ZOOMER_WIDTH, ZOOMER_HEIGHT, ZOOMER_SPRITE_COUNT);
}

void Zoomer::setEnemyStatefromString(string _state) {
	if (_state == "ON_ZOOMER_UP") {
		setState(ON_ZOOMER_UP);
	}
	else if (_state == "ON_ZOOMER_LEFT") {
		setState(ON_ZOOMER_LEFT);
	}
	else if (_state == "ON_ZOOMER_RIGHT") {
		setState(ON_ZOOMER_RIGHT);
	}
	else if (_state == "ON_ZOOMER_BOTTOM") {
		setState(ON_ZOOMER_BOTTOM);
	}
}

void Zoomer::setState(ZOOMER_STATE _state) {
	state = _state;
}


ZOOMER_STATE Zoomer::getState() {
	return state;
}


// Bắt đầu di chuyển khi camera đi tới
void Zoomer::startMoving()
{
	this->setPosX(this->getInitPosX());
	this->setPosY(this->getInitPosY());
	this->setDirection(this->getInitDirection());
	this->isActive = true;
}

// Dùng để thiết lập vận tốc cho zoomer
// Khi Zoomer đổi hướng cũng có nghĩa là nó cần 1 điểm tựa mới
void Zoomer::setVelocity() {
	switch (this->direction) {
	case ZOOMER_RIGHT: {
		this->setVelocityX(ZOOMER_SPEED);
		if (this->state == ON_ZOOMER_UP) {
			this->setVelocityY(ZOOMER_SPEED);
		}
		else if (this->state == ON_ZOOMER_BOTTOM) {
			this->setVelocityY(-ZOOMER_SPEED);
		}
	}break;

	case ZOOMER_LEFT: {
		this->setVelocityX(-ZOOMER_SPEED);

		if (this->state == ON_ZOOMER_UP) {
			this->setVelocityY(ZOOMER_SPEED);
		}
		else if (this->state == ON_ZOOMER_BOTTOM) {
			this->setVelocityY(-ZOOMER_SPEED);
		}
	}break;

	case ZOOMER_DOWN: {
		this->setVelocityY(ZOOMER_SPEED);
		
		if (this->state == ON_ZOOMER_LEFT) {
			this->setVelocityX(ZOOMER_SPEED);
		}
		else if (this->state == ON_ZOOMER_RIGHT) {
			this->setVelocityX(-ZOOMER_SPEED);
		}
	}break;

	case ZOOMER_UP: {
		this->setVelocityY(-ZOOMER_SPEED);

		if (this->state == ON_ZOOMER_LEFT) {
			this->setVelocityX(ZOOMER_SPEED);
		}
		else if (this->state == ON_ZOOMER_RIGHT) {
			this->setVelocityX(-ZOOMER_SPEED);
		}
	}break;
	}
}

void Zoomer::Update(float t)
{
	this->width = ZOOMER_WIDTH;
	this->height = ZOOMER_HEIGHT;

	if (!this->isActive) return;
	this->setIsTopCollided(false);
	this->setIsBottomCollided(false);
	this->setIsRightCollided(false);
	this->setIsLeftCollided(false);

	this->setVelocity();

	float newPosX = pos_x + vx * t;
	float newPosY = pos_y + vy * t;

	GameObject* object = static_cast<GameObject*>(this);
	object->isActive = true;

	//if (!this->grid->updateGrid(object, newPosX, newPosY)) {
	//	//float a = newPosX - (floor(newPosX / 32)) * 32;
	//	//float b = newPosY - (floor(newPosY / 32)) * 32;
	//	//pos_x = newPosX - a;
	//	//pos_y = newPosY - b;

	//	//if (this->getDirection() == ZOOMER_RIGHT && this->getState() == ON_ZOOMER_UP) {
	//	//	this->setState(ON_ZOOMER_RIGHT);
	//	//	this->setDirection(ZOOMER_DOWN);
	//	//	pos_y += 32;
	//	//}
	//	//else if (this->getDirection() == ZOOMER_DOWN && this->getState() == ON_ZOOMER_RIGHT) {

	//	//}

	//	pos_x = newPosX;
	//	pos_y = newPosY;
	//}

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_ENEMY_RATE)
	{
		switch (state)
		{
		case ON_ZOOMER_UP:
			top->updateSprite();
			break;
		case ON_ZOOMER_BOTTOM:
			bottom->updateSprite();
			break;
		case ON_ZOOMER_LEFT:
			left->updateSprite();
			break;
		case ON_ZOOMER_RIGHT:
			right->updateSprite();
			break;
		}
		last_time = now;
	}

}

void Zoomer::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	// Nếu không active thì không render
	if (!isActive)
		return;
	switch (state)
	{
	case ON_ZOOMER_UP:
		top->drawSprite(ZOOMER_WIDTH, ZOOMER_HEIGHT, position);
		break;
	case ON_ZOOMER_BOTTOM:
		bottom->drawSprite(ZOOMER_WIDTH, ZOOMER_HEIGHT, position);
		break;
	case ON_ZOOMER_LEFT:
		left->drawSprite(ZOOMER_WIDTH, ZOOMER_HEIGHT, position);
		break;
	case ON_ZOOMER_RIGHT:
		right->drawSprite(ZOOMER_WIDTH, ZOOMER_HEIGHT, position);
		break;
	}
}

void Zoomer::Destroy()
{
	this->isActive = false;
}

void Zoomer::setDirection(ZOOMER_DIRECTION direction) {
	this->direction = direction;
}

ZOOMER_DIRECTION Zoomer::getDirection() {
	return this->direction;
}

void Zoomer::setInitDirection(ZOOMER_DIRECTION direction) {
	this->initDirection = direction;
}

ZOOMER_DIRECTION Zoomer::getInitDirection() {
	return this->initDirection;
}

void Zoomer::setIsLeftCollided(bool isLeft) {
	this->isLeftCollided = isLeft;
}

bool Zoomer::getIsLeftCollided() {
	return this->isLeftCollided;
}

void Zoomer::setIsRightCollided(bool isRight) {
	this->isRightCollided = isRight;
}

bool Zoomer::getIsRightCollided() {
	return this->isRightCollided;
}

void Zoomer::setIsTopCollided(bool isTop) {
	this->isTopCollided = isTop;
}

bool Zoomer::getIsTopCollided() {
	return this->isTopCollided;
}

void Zoomer::setIsBottomCollided(bool isBottom) {
	this->isBottomCollided = isBottom;
}

bool Zoomer::getIsBottomCollided() {
	return this->isBottomCollided;
}