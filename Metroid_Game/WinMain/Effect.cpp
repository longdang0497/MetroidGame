#include "Effect.h"

Effect::Effect(LPD3DXSPRITE spriteHandler, World * manager, Grid * grid)
{
	/*this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->type = EFFECT;
	this->grid = grid;
	time_survive = EFFECT_TIME_SURVIVE;
	isActive = false;

	vx = 0;
	vy = 0;*/
}

Effect::~Effect()
{
}

void Effect::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
}

void Effect::Init(int pos_x, int pos_y)
{
	/*this->isActive = true;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	time_survive = EFFECT_TIME_SURVIVE;*/
}

void Effect::Update(const float Deltatime)
{
}

void Effect::Render()
{
	//if (!isActive)
	//	return;

	//spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	////effectSprite->Render(pos_x, pos_y);
	//spriteHandler->End();
}

//Effect * Effect::CreateEffect(EFFECT_TYPE effectType, int pos_x, int pos_y, int param, LPD3DXSPRITE spriteHandler, World * manager)
//{
//	Effect* effect = new Effect(spriteHandler, manager);
//
//	switch (effectType)
//	{
//	case EXPLOSION:
//		effect = new ExplodeEffect(spriteHandler, manager);
//		effect->Init(pos_x, pos_y);
//		break;
//	default:
//		break;
//	}
//
//	return effect;
//}
