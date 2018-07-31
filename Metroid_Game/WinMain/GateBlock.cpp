#include "GateBlock.h"

GateBlock::GateBlock(LPD3DXSPRITE spriteHandler, World * manager, Grid * grid)
{
	gateBlock = nullptr;
	this->grid = grid;
}

GateBlock::~GateBlock()
{
	delete(gateBlock);
}

void GateBlock::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	gateBlock = new Sprite(spriteHandler, texture, GATE_BLOCK_PATH, GATE_BLOCK_WIDTH, GATE_BLOCK_HEIGHT, 1);
}

void GateBlock::Init(int x, int y)
{
	this->pos_x = x;
	this->pos_y = y;
	currentSprite = gateBlock;
}

void GateBlock::Update(float t)
{
}

void GateBlock::Render()
{
	D3DXVECTOR3 posBlock;
	posBlock.x = pos_x;
	posBlock.y = pos_y;
	posBlock.z = 0;

	currentSprite->drawSprite(currentSprite->getWidth(), currentSprite->getHeight(), posBlock);
}
