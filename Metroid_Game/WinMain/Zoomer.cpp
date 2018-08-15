#include "Zoomer.h"
#include "World.h"

Zoomer::Zoomer()
{

}

Zoomer::Zoomer(LPD3DXSPRITE spriteHandler, World * manager, OBJECT_TYPE enemy_type) : Enemy(spriteHandler, manager)
{
	this->setType(enemy_type);
	this->setActive(false);

	//Set vận tốc
	vx = 0.0f;
	vy = 0.0f;
	this->width = 30;
	this->height = 30;

	this->health = 100;

	this->grid = manager->getMetroid()->getGrid();

	this->isDeath = false;
	this->setIsEnemyFreezed(false);
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

	this->setInitState(this->getState());
}

void Zoomer::setState(ZOOMER_STATE _state) {
	state = _state;
}


ZOOMER_STATE Zoomer::getState() {
	return state;
}

void Zoomer::setSamusLocation(float posX, float posY)
{
}


// Bắt đầu di chuyển khi camera đi tới
void Zoomer::startMoving()
{
	
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
	if (!this->isActive || this->isDeath) return;
	if (this->isEnemyFreezed) {
		this->isEnemyFreezed = false;
		return;
	}

	this->setIsTopCollided(false);
	this->setIsBottomCollided(false);
	this->setIsRightCollided(false);
	this->setIsLeftCollided(false);
	this->setIsCollisionHandled(false);

	if (getHealth() > 30)
		this->setVelocity();


	GameObject* object = static_cast<GameObject*>(this);
	object->isActive = true;

	int row = (int)floor(this->pos_y / CELL_SIZE);
	int column = (int)floor(this->pos_x / CELL_SIZE);

	// Xet va cham va cap nhat vi tri
	this->grid->handleCell(object, row, column);
	if (!this->getIsCollisionHandled()) {
		ZOOMER_STATE state = this->getState();
		ZOOMER_DIRECTION direction = this->getDirection();

		// Khi không va chạm gì hết sẽ bắt đầu chuyển hướng
		if (!this->getIsTopCollided() && !this->getIsBottomCollided() 
			&& !this->getIsLeftCollided() && !this->getIsRightCollided()) {

			switch (state) {
			case ON_ZOOMER_UP: {
				if (direction == ZOOMER_RIGHT) {
					this->setState(ON_ZOOMER_RIGHT);
					this->pos_x = floor(this->pos_x / 32) * 32;			
				}
				else if (direction == ZOOMER_LEFT) {
					this->setState(ON_ZOOMER_LEFT);
					this->pos_x = floor(this->pos_x / 32) * 32 + 2;
				}

				this->setDirection(ZOOMER_DOWN);
				this->pos_y += 10;

				break;
			}
			case ON_ZOOMER_BOTTOM: {
				this->pos_y -= 10;
				this->setDirection(ZOOMER_UP);

				if (direction == ZOOMER_RIGHT) {
					this->setState(ON_ZOOMER_RIGHT);
					this->pos_x = floor(this->pos_x / 32) * 32;
				}
				else if (direction == ZOOMER_LEFT) {
					this->setState(ON_ZOOMER_LEFT);
					this->pos_x = floor(this->pos_x / 32) * 32 + 2;
				}
				break;
			}

			case ON_ZOOMER_LEFT: {

				this->setDirection(ZOOMER_RIGHT);
				this->pos_x += 10;

				if (direction == ZOOMER_UP) {
					this->setState(ON_ZOOMER_UP);
					this->pos_y = floor(this->pos_y / 32) * 32 + 2;
				}
				else if (direction == ZOOMER_DOWN) {
					this->setState(ON_ZOOMER_BOTTOM);
					this->pos_y = floor(this->pos_y / 32) * 32;
				}

				break;
			}

			case ON_ZOOMER_RIGHT: {
				this->setDirection(ZOOMER_LEFT);
				this->pos_x -= 10;

				if (direction == ZOOMER_UP) {
					this->setState(ON_ZOOMER_UP);
					this->pos_y = floor(this->pos_y / 32) * 32 + 2;
				}
				else if (direction == ZOOMER_DOWN) {
					this->setState(ON_ZOOMER_BOTTOM);
					this->pos_y = floor(this->pos_y / 32) * 32;
				}
				break;
			}
			}
			
		}
		
		// Khi co 2 dieu kien va cham
		else if (this->getIsLeftCollided() && this->getIsBottomCollided()) {
			if (direction == ZOOMER_DOWN) {
				this->setState(ON_ZOOMER_UP);
				this->setDirection(ZOOMER_RIGHT);
			}
			else if (direction == ZOOMER_LEFT) {
				this->setState(ON_ZOOMER_RIGHT);
				this->setDirection(ZOOMER_UP);
			}
		}
		else if (this->getIsTopCollided() && this->getIsLeftCollided()) {
			if (direction == ZOOMER_LEFT) {
				this->setDirection(ZOOMER_DOWN);
				this->setState(ON_ZOOMER_RIGHT);
			}
			else if (direction == ZOOMER_UP) {
				this->setState(ON_ZOOMER_BOTTOM);
				this->setDirection(ZOOMER_RIGHT);
			}
		}
		else if (this->getIsTopCollided() && this->getIsRightCollided()) {
			if (direction == ZOOMER_RIGHT) {
				this->setState(ON_ZOOMER_LEFT);
				this->setDirection(ZOOMER_DOWN);
			}
			else if (direction == ZOOMER_UP) {
				this->setState(ON_ZOOMER_BOTTOM);
				this->setDirection(ZOOMER_LEFT);
			}
		}
		else if (this->getIsRightCollided() && this->getIsBottomCollided()) {
			if (direction == ZOOMER_RIGHT) {
				this->setState(ON_ZOOMER_LEFT);
				this->setDirection(ZOOMER_UP);
			}
			else if (direction == ZOOMER_DOWN) {
				this->setState(ON_ZOOMER_UP);
				this->setDirection(ZOOMER_LEFT);
			}
		}
		else if (this->getIsTopCollided()) {
			this->pos_x += vx * t;
		}
		else if (this->getIsBottomCollided()) {
			pos_x += vx * t;
		}
		else if (this->getIsLeftCollided()) {
			pos_y += vy * t;
		}
		else if (this->getIsRightCollided()) {
			pos_y += vy * t;
		}
		
	}
	

	this->grid->updateGrid(this, this->pos_x, this->pos_y);

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
	if (!isActive)
		return;

	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	// Nếu không active thì không render

	switch (state)
	{
	case ON_ZOOMER_UP:
		top->drawSprite(top->getWidth(), top->getHeight(), position);
		break;
	case ON_ZOOMER_BOTTOM:
		bottom->drawSprite(bottom->getWidth(), bottom->getHeight(), position);
		break;
	case ON_ZOOMER_LEFT:
		left->drawSprite(left->getWidth(), left->getHeight(), position);
		break;
	case ON_ZOOMER_RIGHT:
		right->drawSprite(right->getWidth(), right->getHeight(), position);
		break;
	}
}

void Zoomer::Destroy(float x, float y)
{
	if (this->health == 0)
	{
		manager->explodeEffect->setTimeSurvive(EFFECT_TIME_SURVIVE);
		if (manager->explodeEffect->getTimeSurvive() > 0)
		{
			manager->explodeEffect->setActive(true);
			manager->explodeEffect->setPosX(x - 32);
			manager->explodeEffect->setPosY(y - 32);
		}
		this->isDeath = true;
		this->isEnemyFreezed = false;

		this->reset();
		GameObject* object = static_cast<GameObject*>(this);
		object->setActive(false);
		this->grid->updateGrid(object, this->getPosX(), this->getPosY());
	}
}

void Zoomer::reset() {
	this->pos_x = this->getInitPosX();
	this->pos_y = this->getInitPosY();
	this->direction = this->getInitDirection();
	this->state = this->getInitState();
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

void Zoomer::setIsCollisionHandled(bool isHandled) {
	this->isCollisionHandled = isHandled;
}

bool Zoomer::getIsCollisionHandled() {
	return this->isCollisionHandled;
}