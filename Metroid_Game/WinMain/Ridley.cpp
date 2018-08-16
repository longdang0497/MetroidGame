#include "Ridley.h"

Ridley::Ridley(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->type = RIDLEY;
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->isActive = false;

	this->width = WIDTH_RIDLEY;
	this->height = HEIGHT_RIDLEY_FLY;
	//health = HEALTH_RIDLEY;

	setRidleyState(FLY_LEFT);

	this->vy = GRAVITY_VELOCITY - 65.0f;
	//this->vx = SAMUS_SPEED - 50.0f;
	//vy = 0.5f;
	vx = 1.0f;
	//vx_last = -1.0f;

	//this->pos_x = WIDTH_ROOM1 + WIDTH_ROOM2 + 350.0f;
	//this->pos_y = 192.0f;

	isRightCollided = false;
	isLeftCollided = false;
	isTopCollided = false;
	isBottomCollided = false;
}

Ridley::~Ridley()
{
	delete(fly_left);
	delete(fly_right);
	delete(sit_left);
	delete(sit_right);
}

void Ridley::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (texture == NULL)
		trace(L"Unable to load zoomerTexture");

	fly_left = new Sprite(spriteHandler, texture, RIDLEY_FLY_LEFT_PATH, WIDTH_RIDLEY, HEIGHT_RIDLEY_FLY, RIDLEY_COUNT);
	fly_right = new Sprite(spriteHandler, texture, RIDLEY_FLY_RIGHT_PATH, WIDTH_RIDLEY, HEIGHT_RIDLEY_FLY, RIDLEY_COUNT);
	sit_left = new Sprite(spriteHandler, texture, RIDLEY_SIT_LEFT_PATH, WIDTH_RIDLEY, HEIGHT_RIDLEY_SIT, RIDLEY_COUNT);
	sit_right = new Sprite(spriteHandler, texture, RIDLEY_SIT_RIGHT_PATH, WIDTH_RIDLEY, HEIGHT_RIDLEY_SIT, RIDLEY_COUNT);
}

void Ridley::Init()
{
	this->pos_x = WIDTH_ROOM1 + WIDTH_ROOM2 + 384;
	this->pos_y = 64;
	/*D3DXVECTOR2 pos(this->pos_x, this->pos_y);
	RECT camera = manager->getMetroid()->camera->getBoundary();
	if (Math::isPointinRectangle(pos, camera) == true)
		this->isActive = true;*/
}

void Ridley::Update(float t)
{
	if (isActive == false)
	{
		D3DXVECTOR2 posRidley(this->pos_x + this->width/2, this->pos_y + this->height / 2);
		D3DXVECTOR2 posSamus(manager->samus->pos_x + manager->samus->width / 2, manager->samus->pos_y + manager->samus->height / 2);
		if (Math::distance(posRidley, posSamus) <= WIDTH_ROOM_BOSS)
			this->isActive = true;
	}
	else if (this->isActive == true)
	{
		pos_y += vy * t;

		int row = (int)floor(this->pos_y / CELL_SIZE);
		int column = (int)floor(this->pos_x / CELL_SIZE);
		manager->getMetroid()->getGrid()->handleCell(this, row, column);

		time_push -= t;
		if (isBottomCollided == true)
		{
			if (time_push > 0)
			{
				vy -= 5.5f;
			}
			//pos_y += vy * t;
		}
		else if (isTopCollided == true)
		{
			if (time_push <= 0)
			{
				vy += 10.0f;
			}
		}

		//pos_x += vx * t;

		manager->getMetroid()->getGrid()->updateGrid(this, this->pos_x, this->pos_y);

		DWORD now = GetTickCount();
		if (now - last_time > 1000 / RIDLEY_ANIMATE_RATE)
		{
			switch (state)
			{
			case SIT_LEFT:
				sit_left->updateSprite();
				break;
			case SIT_RIGHT:
				sit_right->updateSprite();
				break;
			case FLY_LEFT:
				fly_left->updateSprite();
				break;
			case FLY_RIGHT:
				fly_right->updateSprite();
				break;
			}
			last_time = now;
		}
	}
}

void Ridley::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	if (!isActive)
		return;

	switch (state)
	{
	case SIT_LEFT:
		sit_left->drawSprite(sit_left->getWidth(), sit_left->getHeight(), position);
		break;
	case SIT_RIGHT:
		sit_right->drawSprite(sit_right->getWidth(), sit_right->getHeight(), position);
		break;
	case FLY_LEFT:
		fly_left->drawSprite(fly_left->getWidth(), fly_left->getHeight(), position);
		break;
	case FLY_RIGHT:
		fly_right->drawSprite(fly_right->getWidth(), fly_right->getHeight(), position);
		break;
	}	
}

void Ridley::Destroy(float x, float y)
{
	this->isActive = false;
}

void Ridley::setRidleyState(RIDLEY_STATE value)
{
	state = value;
}

RIDLEY_STATE Ridley::getRidleyState()
{
	return this->state;
}

void Ridley::setIsLeftCollided(bool isLeft)
{
	isLeftCollided = isLeft;
}

bool Ridley::getIsLeftCollided()
{
	return isLeftCollided;
}

void Ridley::setIsRightCollided(bool isRight)
{
	isRightCollided = isRight;
}

bool Ridley::getIsRightCollided()
{
	return isRightCollided;
}

void Ridley::setIsTopCollided(bool isTop)
{
	isTopCollided = isTop;
}

bool Ridley::getIsTopCollided()
{
	return isTopCollided;
}

void Ridley::setIsBottomCollided(bool isBottom)
{
	isBottomCollided = isBottom;
}

bool Ridley::getIsBottomCollided()
{
	return isBottomCollided;
}
