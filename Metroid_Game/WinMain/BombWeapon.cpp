#include "BombWeapon.h"
#include "World.h"

BombWeapon::BombWeapon()
{
	this->type = BOMB_WEAPON;
	bomb = nullptr;
}

BombWeapon::BombWeapon(LPD3DXSPRITE spriteHandler, World * manager) {
	this->type = BOMB_WEAPON;
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	bomb = nullptr;
	isActive = false;
	this->width = BOMB_WIDTH;
	this->height = BOMB_HEIGHT;
}

BombWeapon::~BombWeapon()
{
}

void BombWeapon::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	bomb = new Sprite(spriteHandler, texture, BOMB_PATH, BOMB_WIDTH, BOMB_HEIGHT, BOMB_SPRITE_COUNT);
}

void BombWeapon::CreateBomb(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
}

void BombWeapon::Update(float t)
{
	if (isActive == true && isExplode == false)
	{
		// Animate samus if he is running
		DWORD now = GetTickCount();
		if (now - last_time > 1000 / ANIMATE_RATE)
		{
			bomb->updateSprite();
			last_time = now;
		}

		// Tính thời gian hiển thị
		time_survive -= t;
		// Nếu hết thời gian thì nổ
		if (time_survive <= 0)
		{
			isActive = false;
			manager->explodeEffect->setTimeSurvive(EFFECT_TIME_SURVIVE);
			if (manager->explodeEffect->getTimeSurvive() > 0)
			{
				Destroy();
			}
		}
	}
}

void BombWeapon::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	position.y += 10;
	if (isActive == true && isExplode == false)
	{
		bomb->drawSprite(BOMB_WIDTH, BOMB_HEIGHT, position);
	}
}

void BombWeapon::Destroy()
{
	isExplode = true;
	manager->explodeEffect->setActive(true);
	manager->explodeEffect->setPosX(this->pos_x - 32);
	manager->explodeEffect->setPosY(this->pos_y - 32);
}

void BombWeapon::ResetBomb(float x, float y)
{
	this->pos_x = x;
	this->pos_y = y;
}
