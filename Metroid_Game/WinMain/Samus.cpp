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
		// Chỉnh lại pos_y để khi bắn lên không bị hụt sprite xuống
		if (this->state == STAND_SHOOT_UP_LEFT 
			|| this->state == STAND_SHOOT_UP_RIGHT 
			|| this->state == RUN_SHOOT_UP_LEFT 
			|| this->state == RUN_SHOOT_UP_RIGHT) {
			position.y -= 10;
		}

		position.z = 0;

		switch (state)
		{
		case STAND_RIGHT:
			standRight->drawSprite(standRight->getWidth(), standRight->getHeight(), position);
			break;
		case STAND_LEFT:
			standLeft->drawSprite(standLeft->getWidth(), standLeft->getHeight(), position);
			break;
		case RUNNING_RIGHT:
			runRight->drawSprite(runRight->getWidth(), runRight->getHeight(), position);
			break;
		case RUNNING_LEFT:
			runLeft->drawSprite(runLeft->getWidth(), runLeft->getHeight(), position);
			break;
		case STAND_SHOOT_UP_LEFT:
			standShootL->drawSprite(standShootL->getWidth(), standShootL->getHeight(), position);
			break;
		case STAND_SHOOT_UP_RIGHT:
			standShootR->drawSprite(standShootR->getWidth(), standShootR->getHeight(), position);
			break;
		case MORPH_LEFT:
			morphLeft->drawSprite(morphLeft->getWidth(), morphLeft->getHeight(), position);
			break;
		case MORPH_RIGHT:
			morphRight->drawSprite(morphRight->getWidth(), morphRight->getHeight(), position);
			break;
		case RUN_SHOOTING_LEFT:
			runShootL->drawSprite(runShootL->getWidth(), runShootL->getHeight(), position);
			break;
		case RUN_SHOOTING_RIGHT:
			runShootR->drawSprite(runShootR->getWidth(), runShootR->getHeight(), position);
			break;
		case RUN_SHOOT_UP_LEFT:
			runShootUpL->drawSprite(runShootUpL->getWidth(), runShootUpL->getHeight(), position);
			break;
		case RUN_SHOOT_UP_RIGHT:
			runShootUpR->drawSprite(runShootUpR->getWidth(), runShootUpR->getHeight(), position);
			break;
		case JUMP_LEFT:
			jumpLeft->drawSprite(jumpLeft->getWidth(), jumpLeft->getHeight(), position);
			break;
		case JUMP_RIGHT:
			jumpRight->drawSprite(jumpRight->getWidth(), jumpRight->getHeight(), position);
			break;
		case TRANSFORM_BALL_LEFT:
			ballLeft->drawSprite(ballLeft->getWidth(), ballLeft->getHeight(), position);
			break;
		case TRANSFORM_BALL_RIGHT:
			ballRight->drawSprite(ballRight->getWidth(), ballRight->getHeight(), position);
			break;
		case JUMP_SHOOT_UP_LEFT:
			jumpShootL->drawSprite(jumpShootL->getWidth(), jumpShootL->getHeight(), position);
			break;
		case JUMP_SHOOT_UP_RIGHT:
			jumpShootR->drawSprite(jumpShootR->getWidth(), jumpShootR->getHeight(), position);
			break;
		}

	}	
}

Samus::Samus()
{
	this->isActive = true;
	this->isBall = false;

	this->setType(SAMUS);
}

void Samus::Destroy()
{
	//Ngưng active
	this->isActive = false;

	//--TO DO: Đưa Samus ra khỏi viewport
}

Samus::Samus(LPD3DXSPRITE spriteHandler, World * manager, Grid* grid)
{
	this->grid = grid;
	this->setType(SAMUS);
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->isActive = true;

	this->previousUnit = NULL;
	this->nextUnit = NULL;

	//Set type
	this->type = SAMUS;

	gravity = FALLDOWN_VELOCITY_DECREASE;
	this->isBall = false;

	this->height = 64;
	this->width = 32;
}

Samus::~Samus()
{
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
	/*pos_x = 992;	
	pos_y = 320;*/	
	this->pos_x = 1140;
	//this->pos_y = 352;
	pos_y = 200;
	vx = 0;
	vx_last = 1.0f;
	vy = JUMP_VELOCITY_BOOST_FIRST;

	//Init state of samus
	state = STAND_RIGHT;
}

SAMUS_STATE Samus::GetState()
{
	return state;
}

void Samus::SetState(SAMUS_STATE value)
{
	state = value;
}

bool Samus::isSamusJumping()
{
	return isJumping;
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

void Samus::Reset(float x, float y)
{
	// Cho samus active trở lại
	this->isActive = true;

	//Đặt lại vị trí
	this->pos_x = x;
	this->pos_y = y;
}

bool Samus::isSamusDeath()
{
	return isDeath;
}

// Update samus status
void Samus::Update(float t)
{
	//this->vy = 0;
	//float newPosX = pos_x + vx * t;
	//float newPosY = pos_y + vy * t;
	//pos_x = newPosX;
	//pos_y = newPosY;
	
	isTop = false;
	isBottom = false;
	isRight = false;
	isLeft = false;
	isOnGround = false;
	if (this->isFalling != true)
	{
		vy = gravity;
		canJump = true;
	}
	else
	{
		vy += gravity * t;
		isOnGround = false;
		if (vy > MAX_FALLING)
		{
			vy = MAX_FALLING;
		}

		if (this->state == JUMP_LEFT || this->state == JUMP_RIGHT)
		{
			this->width = WIDTH_SAMUS_JUMP;
			this->height = HEIGHT_SAMUS_JUMP;
		}
		else if (this->state == TRANSFORM_BALL_LEFT)
		{
			this->width = WIDTH_SAMUS_BALLLEFT;
			this->height = HEIGHT_SAMUS_BALLLEFT;
		}
		else if (this->state == TRANSFORM_BALL_RIGHT)
		{
			this->width = WIDTH_SAMUS_BALLRIGHT;
			this->height = HEIGHT_SAMUS_BALLRIGHT;
		}
		else
		{
			this->width = 32;
			this->height = 64;
		}
	}


	float newPosX = pos_x + vx * t;
	float newPosY = pos_y + vy * t;

	int row = (int)floor(this->pos_y / CELL_SIZE);
	int column = (int)floor(this->pos_x / CELL_SIZE);
	this->grid->handleCell(this, row, column);

	if (isTop == false && isBottom == false && isLeft == false && isRight == false) {
		/*if (vx > 0 && manager->metroid->getInput()->IsKeyDown(DIK_RIGHT))
		this->SetState(MORPH_RIGHT);
		else if (vx > 0)
		this->SetState(JUMP_RIGHT);

		if (vx < 0 && manager->metroid->getInput()->IsKeyDown(DIK_LEFT))
		this->SetState(MORPH_LEFT);
		else if (vx < 0)
		this->SetState(JUMP_LEFT);*/
		pos_x += vx * t;
		pos_y += vy * t;
	}
	else if (isTop == true && isBottom == true && isLeft == false && isRight == false)
	{
		pos_x += vx * t;
		pos_y += vy * t;
		if (this->GetState() == JUMP_LEFT)
			this->SetState(RUNNING_LEFT);
		else if (this->GetState() == JUMP_RIGHT)
			this->SetState(RUNNING_RIGHT);
	}
	else if (isLeft == true && isBottom == true && isRight == false && isTop == false)
	{

		//if (isFalling != true)
		//pos_y += vy * t;
	}
	else if (isLeft == true && isTop == true && isRight == false && isBottom == false)
	{
		pos_x += vx * t;
		//if (isFalling != true)
		//pos_y += vy * t;
	}
	else if (isRight == true && isBottom == true && isLeft == false && isTop == false)
	{
		//pos_x += vx * t;
		//if (isFalling != true)
		//pos_y += vy * t;
	}
	else if (isRight == true && isTop == true && isLeft == false && isBottom == false)
	{
		pos_x += vx * t;
		//if (isFalling != true)
		//pos_y += vy * t;
	}
	else if (isLeft == true && isBottom == false && isRight == false && isTop == false) {
		/*if (vx > 0)
		this->SetState(RUNNIN_RIGHT);
		else if (vx < 0)
		this->SetState(STAND_LEFT);*/
		if (this->GetState() == JUMP_LEFT)
			this->SetState(RUNNING_LEFT);
		else if (this->GetState() == JUMP_RIGHT)
			this->SetState(RUNNING_RIGHT);

		//pos_y += vy * t;
	}
	else if (isRight == true && isBottom == false && isLeft == false && isTop == false) {
		/*if (vx > 0)
		this->SetState(RUNNIN_RIGHT);
		else if (vx < 0)
		this->SetState(STAND_LEFT);*/
		if (this->GetState() == JUMP_LEFT)
			this->SetState(RUNNING_LEFT);
		else if (this->GetState() == JUMP_RIGHT)
			this->SetState(RUNNING_RIGHT);

		//pos_y += vy * t;
	}
	else if (isTop == true && isLeft == false && isRight == false && isBottom == false) {
		/*if (vx > 0)
		this->SetState(RUNNIN_RIGHT);
		else if (vx < 0)
		this->SetState(STAND_LEFT);*/
		pos_y += vy * t;
		pos_x += vx * t;
	}
	else if (isBottom == true && isLeft == false && isRight == false && isTop == false) {
		/*if (vx > 0)
		this->SetState(RUNNIN_RIGHT);
		else if (vx < 0)
		this->SetState(STAND_LEFT);*/
		if (this->GetState() == JUMP_LEFT || this->GetState() == MORPH_LEFT)
			this->SetState(RUNNING_LEFT);
		else if (this->GetState() == JUMP_RIGHT || this->GetState() == MORPH_RIGHT)
			this->SetState(RUNNING_RIGHT);

		pos_x += vx * t;
	}

	this->grid->updateGrid(this, this->pos_x, this->pos_y);

	// Animate samus if he is running
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case STAND_RIGHT:
			standRight->updateSprite();
			break;
		case STAND_LEFT:
			standLeft->updateSprite();
			break;
		case RUNNING_LEFT:
			runLeft->updateSprite();
			break;
		case RUNNING_RIGHT:
			runRight->updateSprite();
			break;
		case STAND_SHOOT_UP_LEFT:
			standShootL->updateSprite();
			break;
		case STAND_SHOOT_UP_RIGHT:
			standShootR->updateSprite();
			break;
		case MORPH_LEFT:
			morphLeft->updateSprite();
			break;
		case MORPH_RIGHT:
			morphRight->updateSprite();
			break;
		case RUN_SHOOTING_LEFT:
			runShootL->updateSprite();
			break;
		case RUN_SHOOTING_RIGHT:
			runShootR->updateSprite();
			break;
		case RUN_SHOOT_UP_LEFT:
			runShootUpL->updateSprite();
			break;
		case RUN_SHOOT_UP_RIGHT:
			runShootUpR->updateSprite();
			break;
		case JUMP_LEFT:
			jumpLeft->updateSprite();
			break;
		case JUMP_RIGHT:
			jumpRight->updateSprite();
			break;
		case TRANSFORM_BALL_LEFT:
			ballLeft->updateSprite();
			break;
		case TRANSFORM_BALL_RIGHT:
			ballRight->updateSprite();
			break;
		case JUMP_SHOOT_UP_LEFT:
			jumpShootL->updateSprite();
			break;
		case JUMP_SHOOT_UP_RIGHT:
			jumpShootR->updateSprite();
			break;
		}
		last_time = now;
	}
	
}
//----------------------------------------------------------

void Samus::setIsBall(bool isBall) {
	this->isBall = isBall;
}

bool Samus::getIsBall() {
	return this->isBall;
}