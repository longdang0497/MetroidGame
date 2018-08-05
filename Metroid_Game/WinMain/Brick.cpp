#include "Brick.h"



Brick::Brick()
{
	this->type = BRICK;
}


Brick::~Brick()
{
}

Brick::Brick(float x, float y, int width, int height, Grid * grid){
	this->type = BRICK;
	this->pos_x = x;
	this->pos_y = y;
	this->width = width;
	this->height = height;
	this->grid = grid;
}

void Brick::InitSprites(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DTEXTURE9 texture) {

}

void Brick::Update(float t) {

}

void Brick::Render() {

}