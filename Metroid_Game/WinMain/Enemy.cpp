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

	//Set type
	this->type = ENEMY;

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

void Enemy::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
}

ENEMY_TYPE Enemy::GetEnemyType()
{
	return enemy_type;
}
void Enemy::SetEnemyType(ENEMY_TYPE enemy_type)
{
	this->enemy_type = enemy_type;
}
void Enemy::Update(float t)
{
}

void Enemy::Render()
{
}

