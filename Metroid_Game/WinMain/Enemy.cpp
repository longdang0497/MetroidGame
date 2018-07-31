#include "Enemy.h"
#include "Game.h"
#include "World.h"

Enemy::Enemy()
{
}

Enemy::Enemy(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;

	this->time_freeze = ENEMY_FREEZE;
}

Enemy::~Enemy()
{
}

void Enemy::InitPostition()
{
}

void Enemy::InitPostition(int x, int y)
{
	this->pos_x = x;
	this->pos_y = y;
}

void Enemy::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;
}

void Enemy::SetDirection(string _direction)
{
	direction = _direction;
}
void Enemy::Update(float t)
{
}

void Enemy::Render()
{
}

void Enemy::setEnemyStatefromString(string _state) {

}

void Enemy::startMoving()
{
}

bool Enemy::isInsideMapBound(RECT cameraBound)
{
	RECT bound = cameraBound;
	D3DXVECTOR2 point(this->pos_x, this->pos_y);
	//lam theo map.cpp
	if (Math::isPointinRectangle(point, bound)) {
		return true;
	}
	return false;
}
