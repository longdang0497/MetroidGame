#include "Samus.h"
#include "Game.h"
#include <vector>
#include "trace.h"
#include "Metroid.h"

void Samus::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;
	else {
		D3DXVECTOR3 position;
		position.x = pos_x;
		position.y = pos_y;
		position.z = 0;

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND| D3DXSPRITE_OBJECTSPACE);

		currentSprite->drawSprite(currentSprite->getWidth(), currentSprite->getHeight(), position);

		spriteHandler->End();
	}	
}

Samus::Samus()
{
	/*width = 40;
	height = 64;*/
	this->isActive = true;
}

void Samus::Destroy()
{
	//Ngưng active
	this->isActive = false;

	//--TO DO: Đưa Samus ra khỏi viewport
}

Samus::Samus(LPD3DXSPRITE spriteHandler, World * manager, Grid * grid)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->isActive = true;

	this->grid = grid;
	this->previousUnit = NULL;
	this->nextUnit = NULL;

	//Set type
	this->type = SAMUS;

	/*width = 40;
	height = 50;*/

	gravity = FALLDOWN_VELOCITY_DECREASE;
}

Samus::~Samus()
{
	currentSprite = nullptr; delete (currentSprite);
	delete(standRight);
	delete(standLeft);
	delete(runRight);
	delete(runLeft);
	delete(morphLeft);
	delete(morphRight);
	delete(standShootL);
	delete(standShootR);
	delete(runShootL);
	delete(runShootR);
	delete(runShootUpL);
	delete(runShootUpR);
	delete(ballLeft);
	delete(ballRight);
	delete(jumpShootR);
	delete(jumpShootL);
	delete(jumpRight);
	delete(jumpLeft);
}

void Samus::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;

	//Create instance of sprites
	standRight = new Sprite(spriteHandler, texture, STAND_RIGHT_PATH, WIDTH_SAMUS_STAND, HEIGHT_SAMUS_STAND, COUNT_SAMUS_STAND);
	standLeft = new Sprite(spriteHandler, texture, STAND_LEFT_PATH, WIDTH_SAMUS_STAND, HEIGHT_SAMUS_STAND, COUNT_SAMUS_STAND);
	runRight = new Sprite(spriteHandler, texture, RUNRIGHT_PATH, WIDTH_SAMUS_RUNRIGHT, HEIGHT_SAMUS_RUNRIGHT, COUNT_SAMUS_RUNRIGHT);
	runLeft = new Sprite(spriteHandler, texture, RUNLEFT_PATH, WIDTH_SAMUS_RUNLEFT, HEIGHT_SAMUS_RUNLEFT, COUNT_SAMUS_RUNLEFT);
	standShootL = new Sprite(spriteHandler, texture, STANDSHOOTUP_LEFT_PATH, WIDTH_SAMUS_STANDSHOOTUP, HEIGHT_SAMUS_STANDSHOOTUP, COUNT_SAMUS_STANDSHOOTUP);
	standShootR = new Sprite(spriteHandler, texture, STANDSHOOTUP_RIGHT_PATH, WIDTH_SAMUS_STANDSHOOTUP, HEIGHT_SAMUS_STANDSHOOTUP, COUNT_SAMUS_STANDSHOOTUP);
	morphLeft = new Sprite(spriteHandler, texture, MORPHLEFT_PATH, WIDTH_SAMUS_MORPHLEFT, HEIGHT_SAMUS_MORPHLEFT, COUNT_SAMUS_MORPHLEFT);
	morphRight = new Sprite(spriteHandler, texture, MORPHRIGHT_PATH, WIDTH_SAMUS_MORPHRIGHT, HEIGHT_SAMUS_MORPHRIGHT, COUNT_SAMUS_MORPHRIGHT);
	runShootL = new Sprite(spriteHandler, texture, RUNSHOOTleft_PATH, WIDTH_SAMUS_RUNSHOOTleft, HEIGHT_SAMUS_RUNSHOOTleft, COUNT_SAMUS_RUNSHOOTleft);
	runShootR = new Sprite(spriteHandler, texture, RUNSHOOTright_PATH, WIDTH_SAMUS_RUNSHOOTright, HEIGHT_SAMUS_RUNSHOOTright, COUNT_SAMUS_RUNSHOOTright);
	runShootUpL = new Sprite(spriteHandler, texture, RUN_SHOOTUP_left_PATH, WIDTH_SAMUS_RUN_SHOOTUP_left, HEIGHT_SAMUS_RUN_SHOOTUP_left, COUNT_SAMUS_RUN_SHOOTUP_left);
	runShootUpR = new Sprite(spriteHandler, texture, RUN_SHOOTUP_right_PATH, WIDTH_SAMUS_RUN_SHOOTUP_right, HEIGHT_SAMUS_RUN_SHOOTUP_right, COUNT_SAMUS_RUN_SHOOTUP_right);
	jumpLeft = new Sprite(spriteHandler, texture, JUMPLEFT_PATH, WIDTH_SAMUS_JUMP, HEIGHT_SAMUS_JUMP, COUNT_SAMUS_JUMP);
	jumpRight = new Sprite(spriteHandler, texture, JUMPRIGHT_PATH, WIDTH_SAMUS_JUMP, HEIGHT_SAMUS_JUMP, COUNT_SAMUS_JUMP);
	ballLeft = new Sprite(spriteHandler, texture, BALLLEFT_PATH, WIDTH_SAMUS_BALLLEFT, HEIGHT_SAMUS_BALLLEFT, COUNT_SAMUS_BALLLEFT);
	ballRight = new Sprite(spriteHandler, texture, BALLRIGHT_PATH, WIDTH_SAMUS_BALLRIGHT, HEIGHT_SAMUS_BALLRIGHT, COUNT_SAMUS_BALLRIGHT);
	jumpShootL = new Sprite(spriteHandler, texture, JUMPSHOOTleft_PATH, WIDTH_SAMUS_JUMPSHOOT, HEIGHT_SAMUS_JUMPSHOOT, COUNT_SAMUS_JUMPSHOOT);
	jumpShootR = new Sprite(spriteHandler, texture, JUMPSHOOTright_PATH, WIDTH_SAMUS_JUMPSHOOT, HEIGHT_SAMUS_JUMPSHOOT, COUNT_SAMUS_JUMPSHOOT);
}

void Samus::InitPostition()
{
	//--TO DO: This code will be edited soon
	pos_x = 992;	
	pos_y = 352;	

	vx = 0;
	vx_last = 1.0f;
	vy = 0;

	//Init state of samus
	SetState(STAND_RIGHT);
}

SAMUS_STATE Samus::GetState()
{
	return state;
}

void Samus::SetState(SAMUS_STATE value)
{
	state = value;
	switch (state)
	{
	case STAND_RIGHT:
		currentSprite = standRight;
		break;
	case STAND_LEFT:
		currentSprite = standLeft;
		break;
	case RUNNING_LEFT:
		currentSprite = runLeft;
		break;
	case RUNNING_RIGHT:
		currentSprite = runRight;
		break;
	case STAND_SHOOT_UP_LEFT:
		currentSprite = standShootL;
		break;
	case STAND_SHOOT_UP_RIGHT:
		currentSprite = standShootR;
		break;
	case MORPH_LEFT:
		currentSprite = morphLeft;
		break;
	case MORPH_RIGHT:
		currentSprite = morphRight;
		break;
	case RUN_SHOOTING_LEFT:
		currentSprite = runShootL;
		break;
	case RUN_SHOOTING_RIGHT:
		currentSprite = runShootR;
		break;
	case RUN_SHOOT_UP_LEFT:
		currentSprite = runShootUpL;
		break;
	case RUN_SHOOT_UP_RIGHT:
		currentSprite = runShootUpR;
		break;
	case JUMP_LEFT:
		currentSprite = jumpLeft;
		break;
	case JUMP_RIGHT:
		currentSprite = jumpRight;
		break;
	case TRANSFORM_BALL_LEFT:
		currentSprite = ballLeft;
		break;
	case TRANSFORM_BALL_RIGHT:
		currentSprite = ballRight;
		break;
	case JUMP_SHOOT_UP_LEFT:
		currentSprite = jumpShootL;
		break;
	case JUMP_SHOOT_UP_RIGHT:
		currentSprite = jumpShootR;
		break;
	}
}

bool Samus::isSamusJumping()
{
	if (isJumping == true)
		return true;
	return false;
}

void Samus::ResetAllSprites()
{
	standRight->Reset();
	standLeft->Reset();
	runRight->Reset();
	runLeft->Reset();
	standShootL->Reset();
	standShootR->Reset();
	morphLeft->Reset();
	morphRight->Reset();
	runShootL->Reset();
	runShootR->Reset();
	runShootUpL->Reset();
	runShootUpR->Reset();
	jumpLeft->Reset();
	jumpRight->Reset();
	ballLeft->Reset();
	ballRight->Reset();
	jumpShootL->Reset();
	jumpShootR->Reset();
}

bool Samus::GetStateActive()
{
	return isActive;
}

void Samus::Reset(int x, int y)
{
	//manager->maruMari->Init(704, 186);
	// Cho samus active trở lại
	this->isActive = true;

	//Đặt lại vị trí
	this->pos_x = x;
	this->pos_y = y;
}

bool Samus::isSamusDeath()
{
	if (isDeath == true)
		return true;
}

// Update samus status
void Samus::Update(float t)
{
	//vy += gravity;

	pos_x += vx * t;
	pos_y += vy * t;

	// Animate samus if he is running
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		currentSprite->updateIndex();
		last_time = now;
	}
	
}
//----------------------------------------------------------

