#include "BombWeapon.h"

Bomb::Bomb()
{
	this->type = BOMB_WEAPON;
	bomb = nullptr;
}

Bomb::Bomb(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->type = BOMB_WEAPON;
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	bomb = nullptr;
	isActive = false;
}

Bomb::~Bomb()
{
	currentSprite = nullptr; delete currentSprite;
	delete bomb;
	delete manager;
}

void Bomb::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	bomb = new Sprite(spriteHandler, texture, BOMB_PATH, BOMB_WIDTH, BOMB_HEIGHT, BOMB_SPRITE_COUNT);
}

void Bomb::CreateBomb(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	currentSprite = bomb;
}

void Bomb::Update(float t)
{
	if (isActive == true && isExplode == false)
	{
		// Animate samus if he is running
		DWORD now = GetTickCount();
		if (now - last_time > 1000 / ANIMATE_RATE)
		{
			currentSprite->updateIndex();
			last_time = now;
		}	

		// Tính thời gian hiển thị
		time_survive -= t;
		// Nếu hết thời gian thì nổ
		if (time_survive <= 0)
		{
			isActive = false;
			manager->explode->setTimeSurvive(EFFECT_TIME_SURVIVE);
			if (manager->explode->getTimeSurvive() > 0)
			{
				Destroy();
			}			
		}
	}	
}

void Bomb::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	if (isActive == true && isExplode == false)
	{
		currentSprite->drawSprite(currentSprite->getWidth(), currentSprite->getHeight(), position);
	}		
}

void Bomb::Destroy()
{
	isExplode = true;
	manager->explode->setActive(true);
	manager->explode->setPosX(this->pos_x - 32);
	manager->explode->setPosY(this->pos_y - 32);
	/*float time = manager->explode->getTimeSurvive();
	if (time < 0)
		manager->explode->setActive(false);*/
}

void Bomb::ResetBomb(float x, float y)
{
	this->pos_x = x;
	this->pos_y = y;
}
//
//void Bomb::setBombNo(int value)
//{
//	countBomb = value;
//}
//
//int Bomb::getBombNo()
//{
//	return countBomb;
//}
