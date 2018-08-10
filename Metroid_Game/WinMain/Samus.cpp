#include "Samus.h"

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
		else if (this->isBall) {
			position.y += 5;
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
	this->isMorphing = false;
	this->setType(SAMUS);
}

void Samus::Destroy()
{
	//Ngưng active
	this->isActive = false;

	//--TO DO: Đưa Samus ra khỏi viewport
}

// Chieu dai va chieu rong cua bounding box
void Samus::setDimension()
{
	switch (this->state) {
	case STAND_LEFT: case STAND_RIGHT: case RUNNING_LEFT: case RUNNING_RIGHT: case STAND_SHOOT_UP_LEFT: case STAND_SHOOT_UP_RIGHT:
	case RUN_SHOOTING_LEFT: case RUN_SHOOTING_RIGHT: case RUN_SHOOT_UP_LEFT: case RUN_SHOOT_UP_RIGHT: {
		this->setWidth(32);
		this->setHeight(64);
		break;
	}
	case MORPH_LEFT: case MORPH_RIGHT: {
		this->setWidth(40);
		this->setHeight(48.0f);
		break;
	}
	case JUMP_LEFT: case JUMP_RIGHT: case JUMP_SHOOT_UP_LEFT: case JUMP_SHOOT_UP_RIGHT: {
		this->setWidth(32);
		this->setHeight(50);
		break;
	}
	case TRANSFORM_BALL_LEFT: case TRANSFORM_BALL_RIGHT: {
		this->setWidth(32);
		this->setHeight(32);
		break;
	}
	}
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
	this->isMorphing = false;
	this->isJumping = false;
	this->canJump = false;
	this->isOnGround = true;
	this->isFalling = false;

	this->height = 64;
	this->width = 32;

	this->startPosJump = 0.0f;
	this->endPosJump = 0.0f;
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
	pos_x = 992;	
	pos_y = 320;	
	//this->pos_x = 1140;
	//this->pos_y = 352;
	//pos_y = 200;
	vx = 0;
	vx_last = 1.0f;
	vy = GRAVITY_VELOCITY;

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
	this->currentTime = t;

	if (this->pos_x > 0 && this->pos_x <= WIDTH_ROOM1)
	{
		setRoomNum(ROOM1);
		isInRoom1 = true;
	}
	else if (this->pos_x > WIDTH_ROOM1 && this->pos_x <= WIDTH_ROOM1 + WIDTH_ROOM2 && isActive == true)
	{
		setRoomNum(ROOM2);
		isInRoom2 = true;
	}
	else if (this->pos_x > WIDTH_ROOM1 + WIDTH_ROOM2 && this->pos_x <= WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS && isActive == true)
	{
		setRoomNum(BOSS1);
		isInBoss1 = true;
	}
	else if (this->pos_x > WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS && this->pos_x <= WIDTH_ROOM1 + WIDTH_ROOM2 + 2 * WIDTH_ROOM_BOSS && isActive == true)
	{
		setRoomNum(BOSS2);
		isInBoss2 = true;
	}

	//this->vy = 0;
	//float newPosX = pos_x + vx * t;
	//float newPosY = pos_y + vy * t;
	//pos_x = newPosX;
	//pos_y = newPosY;
	
	isTop = false;
	isBottom = false;
	isRight = false;
	isLeft = false;
	isColisionHandled = false;

	float newPosX = pos_x + vx * t;
	float newPosY = pos_y + vy * t;

	int row = (int)floor(this->pos_y / CELL_SIZE);
	int column = (int)floor(this->pos_x / CELL_SIZE);

	this->setDimension();

	this->grid->handleCell(this, row, column);

	if (!isColisionHandled) {

		if (isTop == false && isBottom == false && isLeft == false && isRight == false) {
			this->isJumping = true;
			this->isOnGround = false;
			if (!this->isMorphing) {
				if (this->state == RUNNING_LEFT || this->state == STAND_LEFT 
					|| this->state == RUN_SHOOTING_LEFT || state == STAND_SHOOT_UP_LEFT) {
					this->state = JUMP_LEFT;
					this->setWidth(32);
					this->setHeight(50);
				}
				else if (this->state == RUNNING_RIGHT || this->state == STAND_RIGHT 
					|| this->state == RUN_SHOOTING_RIGHT || state == STAND_SHOOT_UP_RIGHT) {
					this->state = JUMP_RIGHT;
					this->setWidth(32);
					this->setHeight(50);
				}
				else if (this->state == STAND_SHOOT_UP_LEFT || this->state == RUN_SHOOT_UP_LEFT) {
					this->state = JUMP_SHOOT_UP_LEFT;
					this->setWidth(32);
					this->setHeight(50);
				}
				else if (this->state == STAND_SHOOT_UP_RIGHT || this->state == RUN_SHOOT_UP_RIGHT) {
					this->state = JUMP_SHOOT_UP_RIGHT;
					this->setWidth(32);
					this->setHeight(50);
				}
			}

			this->endPosJump = this->pos_y;

			if (vy < 0) {
				if (this->startPosJump - this->endPosJump >= SAMUS_MAX_JUMP 
					&& this->canJump && !this->isOnGround) {
					this->canJump = false;
					this->vy = GRAVITY_VELOCITY;
				}
				else if (this->startPosJump - this->endPosJump >= SAMUS_MAX_JUMP - 50 
					&& this->canJump && !this->isOnGround) {
					if (vy < 0) {
						this->vy = -80.0f;
					}
					else {
						this->vy = 80.0f;
					}
				}
				else if (this->startPosJump - this->endPosJump < SAMUS_MIN_JUMP && !this->canJump) {

					if (this->startPosJump - this->endPosJump < 32) {
						this->vy = 50.0f;
					}
					else {
						this->vy = -GRAVITY_VELOCITY;
					}
				}
				else if (this->startPosJump - this->endPosJump >= SAMUS_MIN_JUMP 
					&& this->startPosJump - this->endPosJump <= SAMUS_MAX_JUMP && !this->canJump) {
					this->vy = GRAVITY_VELOCITY;
				}
			}
			else {
				if (!this->canJump && this->isOnGround) {
					this->vy = GRAVITY_VELOCITY;
				}
			}
			//float temPosY = this->pos_y + this->vy*t;
			this->pos_x += vx * t;
			this->pos_y += vy * t;
			/*	if (this->vy > 0) {
			this->pos_y = temPosY;
			}
			else {
			int row = (int)floor(temPosY / 32.0f);
			int column1 = (int)floor(this->pos_x / 32.0f);
			int column2 = (int)ceil(this->pos_x / 32.0f);
			if (this->stringMapSamus[row][column1] == '0' && this->stringMapSamus[row][column2] == '0') {
			this->pos_y = temPosY;
			}
			else {
			if (temPosY < (row) * 32) {
			this->pos_y = (row) * 32;
			this->canJump = false;
			this->vy = GRAVITY_VELOCITY;
			}
			}
			}*/
		}
		else if (isLeft && isBottom) {
			this->pos_x += 1;
			pos_y += 0;
		}
		else if (isRight && isBottom) {
			this->pos_x -= 1;
			pos_y += 0;
		}
		else if (isLeft && isTop) {
			this->pos_x += 1;
			this->canJump = false;
			this->vy = GRAVITY_VELOCITY;
			this->pos_y += vy * t;
		}
		else if (isRight && isTop) {
			this->pos_x -= 1;
			this->canJump = false;
			this->vy = GRAVITY_VELOCITY;
			this->pos_y += 10;
		}
		else if (isLeft) {
			this->pos_x += 1;

			if (this->isJumping) {
				this->endPosJump = this->pos_y;
				if (vy < 0) {
					if (this->startPosJump - this->endPosJump >= SAMUS_MAX_JUMP && this->canJump && !this->isOnGround) {
						this->canJump = false;
						this->vy = GRAVITY_VELOCITY;
					}
					else if (this->startPosJump - this->endPosJump < SAMUS_MIN_JUMP && !this->canJump) {
						this->vy = -GRAVITY_VELOCITY;
					}
					else if (this->startPosJump - this->endPosJump >= SAMUS_MIN_JUMP && this->startPosJump - this->endPosJump <= SAMUS_MAX_JUMP && !this->canJump) {
						this->vy = GRAVITY_VELOCITY;
					}
				}
				else {
					if (!this->canJump && this->isOnGround) {
						this->vy = GRAVITY_VELOCITY;
					}
				}
			}
			this->pos_y += this->vy * t;
		}
		else if (isRight) {
			this->pos_x -= 1;

			if (this->isJumping) {
				this->endPosJump = this->pos_y;
				if (vy < 0) {
					if (this->startPosJump - this->endPosJump >= SAMUS_MAX_JUMP 
						&& this->canJump && !this->isOnGround) {
						this->canJump = false;
						this->vy = GRAVITY_VELOCITY;
					}
					else if (this->startPosJump - this->endPosJump < SAMUS_MIN_JUMP 
						&& !this->canJump) {
						this->vy = -GRAVITY_VELOCITY;
					}
					else if (this->startPosJump - this->endPosJump >= SAMUS_MIN_JUMP 
						&& this->startPosJump - this->endPosJump <= SAMUS_MAX_JUMP 
						&& !this->canJump) {
						this->vy = GRAVITY_VELOCITY;
					}
				}
				else {
					if (!this->canJump && this->isOnGround) {
						this->vy = GRAVITY_VELOCITY;
					}
				}
			}
			this->pos_y += this->vy * t;
		}
		else if (isBottom) {
			this->pos_x += vx * t;
		}
		else if (isTop) {
			if (this->isJumping) {
				this->canJump = false;
				this->vy = GRAVITY_VELOCITY;
				this->pos_y += 10;
			}
			this->pos_x += vx * t;
		}
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