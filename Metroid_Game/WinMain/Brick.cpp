#include "Brick.h"



Brick::Brick()
{
	this->type = BRICK;
}


Brick::~Brick()
{
}

Brick::Brick(float x, float y, int width, int height){
	this->type = BRICK;
	this->pos_x = x;
	this->pos_y = y;
	this->width = 32;
	this->height = 32;
	this->isActive = true;
}

void Brick::InitSprites(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DTEXTURE9 texture) {

}

void Brick::Update(float t) {

}

void Brick::Render() {

}

void Brick::setIndexX(int x) {
	this->indexX = x;
}

int Brick::getIndexX() {
	return this->indexX;
}

void Brick::setIndexY(int y) {
	this->indexY = y;
}

int Brick::getIndexY() {
	return this->indexY;
}