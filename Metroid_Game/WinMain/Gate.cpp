#include "Gate.h"

Gate::Gate(LPD3DXSPRITE spriteHandler, World * manager, GATE_TYPE type)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->type = GATE;
	this->width = GATE_WIDTH;
	this->height = GATE_HEIGHT;

	//Set state
	state = GATE_STATE::CLOSE;

	//Set time survive
	time_survive = GATE_TIME_SURVIVE;
}

Gate::~Gate()
{
	delete(exists);
	delete(destroying);
}

GATE_TYPE Gate::GetGateType()
{
	return gate_type;
}

void Gate::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	LPWSTR exists_path = NULL;
	LPWSTR destroy_path = NULL;

	switch (gate_type)
	{
	case LEFT:
		exists_path = GATE_LEFT_EXISTS;
		destroy_path = GATE_LEFT_DESTROYING;
		break;
	case RIGHT:
		exists_path = GATE_RIGHT_EXISTS;
		destroy_path = GATE_RIGHT_DESTROYING;
		break;
	}

	exists = new Sprite(spriteHandler, texture, exists_path, GATE_WIDTH, GATE_HEIGHT, GATE_EXISTS_COUNT);
	destroying = new Sprite(spriteHandler, texture, destroy_path, GATE_WIDTH, GATE_HEIGHT, GATE_DESTROYING_COUNT);
}

void Gate::Update(float t)
{

	if (!isActive)
		return;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case DESTROYING:
			destroying->updateSprite();
			if (destroying->GetIndex() == destroying->GetCount() - 1)
			{
				state = OPEN;
				isActive = false;
			}
			break;
		}
		last_time = now;
	}
}

void Gate::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	if (!isActive)
		return;

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	switch (state)
	{
	case CLOSE:
		exists->drawSprite(exists->getWidth(), exists->getHeight(), position);
		break;
	case DESTROYING:
		destroying->drawSprite(destroying->getWidth(), destroying->getHeight(), position);
		break;
	}
	spriteHandler->End();
}

void Gate::DestroyGate()
{
	//Đặt state là destroy để hủy cổng
	state = DESTROYING;
}
