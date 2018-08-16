#include "Gate.h"

Gate::Gate()
{
}

Gate::Gate(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->type = GATE;
	this->width = GATE_WIDTH;
	this->height = GATE_HEIGHT;

	exists_right = nullptr;
	exists_left = nullptr;
	destroying_right = nullptr;
	destroying_left = nullptr;

	//Set state
	setGateState(CLOSE);

	//Set time survive
	time_survive = GATE_TIME_SURVIVE;
	this->timeStartOpen = 0.0f;
	
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
	//destroying_left = new Sprite(spriteHandler, texture, GATE_LEFT_DESTROYING, GATE_WIDTH, GATE_HEIGHT, GATE_DESTROYING_COUNT);
	exists_right = new Sprite(spriteHandler, texture, GATE_RIGHT_EXISTS, GATE_WIDTH, GATE_HEIGHT, GATE_EXISTS_COUNT);
	//destroying_right = new Sprite(spriteHandler, texture, GATE_RIGHT_DESTROYING, GATE_WIDTH, GATE_HEIGHT, GATE_DESTROYING_COUNT);
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

	if (GetTickCount() - this->timeStartOpen >= time_survive) {
		this->setGateState(CLOSE);
		if (this->pos_x <= this->manager->samus->pos_x && this->manager->samus->pos_x <= this->pos_x + this->width) {
			this->setGateState(OPEN);
		}
	}
	else {
		this->setGateState(OPEN);
	}


	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		if (this->state == CLOSE) {
			switch (this->gate_type) {
			case GATE_LEFT: {
				exists_left->updateSprite();
				break;
			}
			case GATE_RIGHT: {
				exists_right->updateSprite();
				break;
			}
			}
		}
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
	
	if (this->state == CLOSE) {
		switch (this->gate_type) {
		case GATE_LEFT: {
			exists_left->drawSprite(exists_left->getWidth(), exists_left->getHeight(), position);
			break;
		}
		case GATE_RIGHT: {
			exists_right->drawSprite(exists_right->getWidth(), exists_right->getHeight(), position);
			break;
		}
		}
	}
}

void Gate::DestroyGate()
{
	//Đặt state là destroy để hủy cổng
	state = DESTROYING;
}

void Gate::setIsRight(bool value)
{
	isRight = value;
}

void Gate::setIsLeft(bool value)
{
	isLeft = value;
}
