#include "Metroid.h"
#include <time.h>
#include "trace.h"
#include "utils.h"

void Metroid::_InitBackground()
{
}

void Metroid::_InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	world->InitSprites(d3ddv, texture);	
}

void Metroid::_InitPositions()
{
	world->samus->InitPostition();
}

Metroid::Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate) 
	:Game(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	tick_per_frame = 1000 / _dxgraphics->getFrameRate();

	isFreezing = false;
	isOnFloor = false;
	isInGame = false;
}

Metroid::~Metroid()
{
	delete(map);
	//delete(world);
}

/*
	Khoi tao Spritehandler va Texture cho game
*/
void Metroid::LoadResources(LPDIRECT3DDEVICE9 d3ddev)
{
	//---------Khởi tạo spriteHandler---------------
	if (d3ddev == NULL) return;

	HRESULT result = D3DXCreateSprite(d3ddev, &spriteHandler);
	if (result != D3D_OK) 
		trace(L"Unable to create SpriteHandler");

	Texture text;
	this->setPlayerTexture(text.loadTexture(d3ddev, TEXTURE_GAME_CHARACTERS));
	if (this->getPlayerTexture() == NULL)
		trace(L"Unable to load PlayerTexture");

	Texture text1;
	this->setBrickTexture(text1.loadTexture(d3ddev, L"brick_32x32.png"));
	if (this->getBrickTexture() == NULL)
		trace(L"Unable to load BrickTexture");

	
	world = new World(spriteHandler, this);
	srand((unsigned)time(NULL));
	this->_InitSprites(d3ddev, this->getPlayerTexture());

	// Khoi tao map
	this->map = new Map(this->getSpriteHandler(), this->getBrickTexture(), "field1.txt", this->_device, 0, 0);
	
	if (map) 
	{
	}
	else 
		trace(L"Unable to load map");
	
	if (camera) 
	{
		camera->Follow(world->samus);
		camera->SetMapBoundary(map->getBoundary());
	}
		


	this->_InitPositions();
}

//Kiểm tra screen Mode (bắt đầu, room1, room2,... hay gameover)
void Metroid::Update(float Delta)
{
	this->camera->Update();
	map->UpdateMap(this->camera->getBoundary());
	UpdateFrame(Delta);
}

//update các object trong game
void Metroid::UpdateFrame(float Delta)
{
	world->Update(Delta);
}

//render từng screen mode (room1, room2,... hay gameover)
void Metroid::Render(LPDIRECT3DDEVICE9 d3ddv)
{
	RenderStartScreen(_device->getdevice());
}

//render các scene chính (room1, room2...) trong game
void Metroid::RenderStartScreen(LPDIRECT3DDEVICE9 d3ddv)
{
	
}

//render từng object trong game
void Metroid::RenderFrame(LPDIRECT3DDEVICE9 d3ddv)
{
	map->drawMap();
	world->Render();
}

void Metroid::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta)
{
	if (_input->IsKeyDown(DIK_RIGHT))
	{
		world->samus->setVelocityXLast(world->samus->getVelocityX());
		world->samus->setVelocityX(SAMUS_SPEED);

		if (world->samus->GetState() != MORPH_LEFT && world->samus->GetState() != MORPH_RIGHT
			&& world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != JUMP_RIGHT
			&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT && world->samus->GetState() != JUMP_SHOOT_UP_RIGHT
			&& world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT)
		{
			world->samus->SetState(RUNNING_RIGHT);			
		}
	}
	else if (_input->IsKeyDown(DIK_LEFT)) {
		world->samus->setVelocityXLast(world->samus->getVelocityX());
		world->samus->setVelocityX(-SAMUS_SPEED);
		if (world->samus->GetState() != MORPH_LEFT && world->samus->GetState() != MORPH_RIGHT
			&& world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != JUMP_RIGHT
			&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT && world->samus->GetState() != JUMP_SHOOT_UP_RIGHT
			&& world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT)
		{
			world->samus->SetState(RUNNING_LEFT);
		}
	}
	else
	{
		if (world->samus->getVelocityXLast() > 0)
		{
			if (world->samus->GetState() != MORPH_LEFT && world->samus->GetState() != MORPH_RIGHT
				&& world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != JUMP_RIGHT
				&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT && world->samus->GetState() != JUMP_SHOOT_UP_RIGHT
				&& world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT)
			{
				world->samus->SetState(STAND_RIGHT);
				world->samus->ResetAllSprites();
			}
		}
		if (world->samus->getVelocityXLast() < 0)
		{
			if (world->samus->GetState() != MORPH_LEFT && world->samus->GetState() != MORPH_RIGHT
				&& world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != JUMP_RIGHT
				&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT && world->samus->GetState() != JUMP_SHOOT_UP_RIGHT
				&& world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT)
			{
				world->samus->SetState(STAND_LEFT);
				world->samus->ResetAllSprites();
			}
		}
		world->samus->setVelocityX(0);
	}

	if (_input->IsKeyDown(DIK_UP))
	{
		if (world->samus->GetState() == RUNNING_LEFT)
			world->samus->SetState(RUN_SHOOT_UP_LEFT);
		if (world->samus->GetState() == RUNNING_RIGHT)
			world->samus->SetState(RUN_SHOOT_UP_RIGHT);
		if (world->samus->GetState() == STAND_LEFT)
			world->samus->SetState(STAND_SHOOT_UP_LEFT);
		if (world->samus->GetState() == STAND_RIGHT)
			world->samus->SetState(STAND_SHOOT_UP_RIGHT);
		if (world->samus->GetState() == JUMP_LEFT)
		{
			world->samus->SetState(JUMP_SHOOT_UP_LEFT);
		}
		if (world->samus->GetState() == JUMP_RIGHT)
		{
			world->samus->SetState(JUMP_SHOOT_UP_RIGHT);
		}
		if (world->samus->GetState() == MORPH_LEFT)
			world->samus->SetState(STAND_LEFT);
		if (world->samus->GetState() == MORPH_RIGHT)
			world->samus->SetState(STAND_RIGHT);
	}
}

void Metroid::OnKeyDown(int KeyCode)
{
	world->samus->isJumping = false;
	if (world->samus->isSamusJumping() == false)
	{
		/*switch (KeyCode)
		{
		case DIK_X:
			
		}*/
		if (_input->IsKeyDown(DIK_X))
		{
			world->samus->isJumping = true;
			if (world->samus->GetState() != MORPH_RIGHT && _input->IsKeyDown(DIK_RIGHT))
			{
				start_jump = GetTickCount();
				now_jump = GetTickCount();
				world->samus->SetState(MORPH_RIGHT);
				world->samus->setVelocityY(world->samus->getVelocityY() + JUMP_VELOCITY_BOOST_FIRST);

				now_jump = GetTickCount();
				if ((now_jump - start_jump) <= 10 * tick_per_frame)
				{
					world->samus->setVelocityY(world->samus->getVelocityY() + JUMP_VELOCITY_BOOST);
				}
			}
			else if (world->samus->GetState() != MORPH_LEFT && _input->IsKeyDown(DIK_LEFT))
			{
				start_jump = GetTickCount();
				now_jump = GetTickCount();
				world->samus->SetState(MORPH_LEFT);
				world->samus->setVelocityY(world->samus->getVelocityY() + JUMP_VELOCITY_BOOST_FIRST);

				now_jump = GetTickCount();
				if ((now_jump - start_jump) <= 10 * tick_per_frame)
				{
					world->samus->setVelocityY(world->samus->getVelocityY() + JUMP_VELOCITY_BOOST);
				}
			}
			if (world->samus->getVelocityXLast() < 0)
			{
				if (world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != MORPH_LEFT
					&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT)
				{
					start_jump = GetTickCount();
					now_jump = GetTickCount();
					if (world->samus->GetState() == STAND_SHOOT_UP_LEFT)
						world->samus->SetState(JUMP_SHOOT_UP_LEFT);
					else
						world->samus->SetState(JUMP_LEFT);
					world->samus->setVelocityY(world->samus->getVelocityY() + JUMP_VELOCITY_BOOST_FIRST);

					now_jump = GetTickCount();
					if ((now_jump - start_jump) <= 10 * tick_per_frame)
					{
						world->samus->setVelocityY(world->samus->getVelocityY() + JUMP_VELOCITY_BOOST);
					}
				}
			}
			if (world->samus->getVelocityXLast() > 0)
			{
				if (world->samus->GetState() != JUMP_RIGHT && world->samus->GetState() != MORPH_RIGHT
					&& world->samus->GetState() != JUMP_SHOOT_UP_RIGHT)
				{
					start_jump = GetTickCount();
					now_jump = GetTickCount();
					if (world->samus->GetState() == STAND_SHOOT_UP_RIGHT)
						world->samus->SetState(JUMP_SHOOT_UP_RIGHT);
					else
						world->samus->SetState(JUMP_RIGHT);
					world->samus->setVelocityY(world->samus->getVelocityY() + JUMP_VELOCITY_BOOST_FIRST);

					now_jump = GetTickCount();
					if ((now_jump - start_jump) <= 10 * tick_per_frame)
					{
						world->samus->setVelocityY(world->samus->getVelocityY() + JUMP_VELOCITY_BOOST);
					}
				}
			}
		}
	}
}

void Metroid::OnKeyUp(int KeyCode)
{
}

DWORD Metroid::GetTickPerFrame()
{
	return tick_per_frame;
}

LPD3DXSPRITE Metroid::getSpriteHandler() {
	return this->spriteHandler;
}

Map * Metroid::getMap() {
	return this->map;
}