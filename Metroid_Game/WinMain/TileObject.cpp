#include "TileObject.h"

TileObject::TileObject()
{
	//Set type
	this->type = BRICK;
}

TileObject::~TileObject()
{
	delete tileMap;
}

void TileObject::InitSprites(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DTEXTURE9 texture)
{
	//---------Khởi tạo spriteHandler---------------
	if (d3ddev == NULL) return;

	HRESULT result = D3DXCreateSprite(d3ddev, &spriteHandler);
	if (result != D3D_OK)
		trace(L"Unable to create SpriteHandler");

	this->tileMap = new Sprite(spriteHandler, texture, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, 1, 1);
	if (this->tileMap == NULL)
		trace(L"Unable to load map sprite");

	width = tileMap->getWidth();
	height = tileMap->getHeight();
}

void TileObject::Update(float t)
{
}

void TileObject::Render(char c, int index, D3DXVECTOR3 pos)
{
	this->type = c;
	tileMap->drawSprite(0, index * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
}

void TileObject::setType(char value)
{
	this->type = value;
}

char TileObject::getType()
{
	return this->type;
}

void TileObject::setXPixel(int value)
{
	this->x_pixel = value;
}

int TileObject::getXPixel()
{
	return this->x_pixel;
}

void TileObject::setYPixel(int value)
{
	this->y_pixel = value;
}

int TileObject::getPixel()
{
	return this->y_pixel;
}
