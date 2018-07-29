#include "TileObject.h"

TileObject::TileObject(float x, float y)
{	
	//Set type
	this->type = BRICK;
	currentSprite = nullptr;

	pos_x = x;
	pos_y = y;

	vx = 0;
	vy = 0;
	vx_last = 0.0f;

	objBound.top = y;
	objBound.left = x;
	objBound.bottom = y + BRICK_SIZE;
	objBound.right = x + BRICK_SIZE;
}

TileObject::~TileObject()
{
}

void TileObject::Update(float t)
{
}

void TileObject::Render()
{
	
}