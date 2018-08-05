#include "Gate.h"

Gate::Gate(LPD3DXSPRITE spriteHandler, World * manager, Grid * grid)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->type = GATE;
	this->width = GATE_WIDTH;
	this->height = GATE_HEIGHT;
	this->grid = grid;

	exists_right = nullptr;
	exists_left = nullptr;
	destroying_right = nullptr;
	destroying_left = nullptr;

	//Set state
	setGateState(CLOSE);

	//Set time survive
	time_survive = GATE_TIME_SURVIVE;
}

Gate::~Gate()
{
	//currentSprite = nullptr; delete (currentSprite);
	delete(exists_right);
	delete(exists_left);
	delete(destroying_right);
	delete(destroying_left);
}

GATE_TYPE Gate::GetGateType()
{
	return gate_type;
}

void Gate::setGateType(GATE_TYPE value)
{
	gate_type = value;
}

void Gate::setGateState(GATE_STATE value)
{
	state = value;
}

GATE_STATE Gate::getGateState()
{
	return state;
}

void Gate::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture, GATE_TYPE gateType)
{
	this->gate_type = gateType;
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	exists_left = new Sprite(spriteHandler, texture, GATE_LEFT_EXISTS, GATE_WIDTH, GATE_HEIGHT, GATE_EXISTS_COUNT);
	destroying_left = new Sprite(spriteHandler, texture, GATE_LEFT_DESTROYING, GATE_WIDTH, GATE_HEIGHT, GATE_DESTROYING_COUNT);
	exists_right = new Sprite(spriteHandler, texture, GATE_RIGHT_EXISTS, GATE_WIDTH, GATE_HEIGHT, GATE_EXISTS_COUNT);
	destroying_right = new Sprite(spriteHandler, texture, GATE_RIGHT_DESTROYING, GATE_WIDTH, GATE_HEIGHT, GATE_DESTROYING_COUNT);
}

void Gate::Init(int x, int y)
{
	this->pos_x = x;
	this->pos_y = y;
}

void Gate::Update(float t)
{
	if (!isActive)
		return;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{			
		switch(state)
		{
		case CLOSE:
			break;
		case DESTROYING:
			//currentSprite->updateSprite();
			/*if (currentSprite == destroying_left || currentSprite == destroying_right)
			{
				
			}
			break;*/

			switch (gate_type)
			{
			case LEFT:
				destroying_left->updateSprite();
				if (destroying_left->GetIndex() == destroying_left->GetCount() - 1)
				{
					state = OPEN;
					isActive = false;
				}
				break;
			case RIGHT:
				destroying_right->updateSprite();
				if (destroying_right->GetIndex() == destroying_right->GetCount() - 1)
				{
					state = OPEN;
					isActive = false;
				}
				break;
			}
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

	//currentSprite->drawSprite(currentSprite->getWidth(), currentSprite->getHeight(), position);
	
	switch (state)
	{
	case CLOSE:
		switch (gate_type)
		{
		case LEFT:
			exists_left->drawSprite(GATE_WIDTH, GATE_HEIGHT, position);
			break;
		case RIGHT:
			exists_right->drawSprite(GATE_WIDTH, GATE_HEIGHT, position);
			break;
		}
		break;
	case DESTROYING:
		switch (gate_type)
		{
		case LEFT:
			destroying_left->drawSprite(GATE_WIDTH, GATE_HEIGHT, position);
			break;
		case RIGHT:
			destroying_right->drawSprite(GATE_WIDTH, GATE_HEIGHT, position);
			break;
		}
		break;
	}
}

void Gate::DestroyGate()
{
	//Đặt state là destroy để hủy cổng
	state = DESTROYING;
}
